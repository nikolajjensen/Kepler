//
// Copyright 2023 Nikolaj Banke Jensen.
//
// This file is part of Kepler.
// 
// Kepler is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Kepler is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License 
// along with Kepler. If not, see <https://www.gnu.org/licenses/>.
//

#include "parser.h"
#include "core/error.h"
#include "core/symbol_table.h"
#include "core/constants/literals.h"

namespace kepler {

    void Parser::advance() {
        if(!at_end()) cursor--;
    }

    const Token& Parser::current() {
        return *cursor;
    }

    bool Parser::at_end() {
        return cursor < begin;
    }

    long Parser::position(const std::vector<Token>::const_iterator& it) {
        return it->get_position();
    }

    long Parser::position() {
        return cursor->get_position();
    }

    void Parser::eat(TokenType type) {
        if(current().type != type) {
            throw kepler::error(InternalError, "Expected token of type: " + kepler::to_string(type) + ", but found token of type: " + kepler::to_string(current().type), position());
        } else {
            advance();
        }
    }


    bool Parser::identifies_function(Token token) {
        if(!token.content.has_value()) return false;
        std::u32string id = {token.content->begin(), token.content->end()};
        if(id == U"∇") return true;
        return symbol_table->contains(id) && symbol_table->get_type(id) == FunctionSymbol;
    }

    TokenType Parser::peek_beyond_parenthesis() {
        auto peek_at = cursor - 1;
        while(peek_at >= begin && peek_at->type == RPARENS) {
            --peek_at;
        }
        if(peek_at >= begin) return peek_at->type;
        return END;
    }

    void Parser::assert_matching(const TokenType& left, const TokenType& right, const Char& right_char) {
        auto it = begin;
        std::vector<std::vector<Token>::const_iterator> stack;

        while(it != end) {
            if(it->type == left) {
                stack.emplace_back(it);
            } else if(it->type == right){
                if(stack.empty()) {
                    throw kepler::error(SyntaxError, "Expected a matching '" + uni::utf32to8(std::u32string(1, right_char)) + "'.", position(it));
                }
                stack.pop_back();
            }
            ++it;
        }

        if(!stack.empty()) {
            throw kepler::error(SyntaxError, "Expected a matching '" + uni::utf32to8(std::u32string(1, right_char)) + "'.", position(stack.back()));
        }
    }


    Statements* Parser::parse_program() {
        assert_matching(LBRACE, RBRACE, U'}');
        assert_matching(LPARENS, RPARENS, U')');
        cursor = begin;
        return parse_statement_list();
    }

    std::vector<Token>::const_iterator Parser::next_separator(const std::vector<Token>::const_iterator& current) {
        auto it = current;
        int level = 0;
        while(it != end) {
            if(it->type == LBRACE) {
                ++level;
            } else if(it->type == RBRACE) {
                --level;
            } else if(it->type == DIAMOND && level == 0) {
                break;
            }
            ++it;
        }

        return it;
    }

    std::vector<Token>::const_iterator Parser::matching_brace(const std::vector<Token>::const_iterator& index) {
        int level = 1;
        auto it = index - 1;
        while(it >= begin && level != 0) {
            if(it->type == LBRACE) {
                --level;
            } else if(it->type == RBRACE) {
                ++level;
            }
            --it;
        }

        return it + 1;
    }


    Statements* Parser::parse_statement_list() {
        std::vector<ASTNode<Array>*> statements{};

        while(flag != end) {
            auto tmp = next_separator(flag + 1);

            // If the next separator is immediately the next one
            // then skip this statement, as there is nothing useful
            // in '◊◊'.
            if(flag->type == DIAMOND && tmp == flag + 1) {
                flag = tmp;
                continue;
            } else {
                flag = tmp;
                cursor = flag - 1;
                statements.emplace_back(parse_statement());
            }
        }

        return new Statements(statements, symbol_table);
    }

    ASTNode<Array>* Parser::parse_statement() {
        if(current().type == RBRACE) {
            ASTNode<Operation_ptr>* function = parse_function();
            if(current().type != ASSIGNMENT) {
                throw kepler::error(SyntaxError, "Expected an assignment here.", position());
            }
            eat(ASSIGNMENT);
            if(at_end() || current().type != ID) {
                throw kepler::error(SyntaxError, "Expected an identifier here.", position());
            }
            Token identifier = current();
            auto statement = new FunctionAssignment(identifier, function);
            eat(ID);

            symbol_table->bind_function({identifier.content->begin(), identifier.content->end()});
            return statement;
        } else {
            ASTNode<Array>* statement = parse_argument();

            while(!at_end() && (helpers::is_function(current().type)
                  || helpers::is_monadic_operator(current().type)
                  || current().type == ASSIGNMENT
                  || current().type == RPARENS
                  || current().type == RBRACE
                  || identifies_function(current()))
                  || current().type == COLON) {

                if(current().type == ASSIGNMENT) {
                    eat(ASSIGNMENT);

                    if(current().type != ID) {
                        throw kepler::error(SyntaxError, "Expected an identifier here.", position());
                    }

                    statement = new Assignment(current(), statement);
                    eat(ID);
                } else if(current().type == COLON) {
                    eat(COLON);
                    ASTNode<Array>* condition = parse_statement();
                    statement = new Conditional(condition, statement, parse_statement_list());
                } else {
                    long func_pos = position();
                    ASTNode<Operation_ptr>* function = parse_function();
                    function->set_position(func_pos);

                    if(!at_end() && (current().type == RPARENS || helpers::is_array_token(current().type))) {
                        statement = new DyadicFunction(function, parse_argument(), statement);
                    } else {
                        statement = new MonadicFunction(function, statement);
                    }
                }
            }

            return statement;
        }
    }

    ASTNode<Operation_ptr>* Parser::parse_dfn() {
        if(current().type != RBRACE) {
            throw kepler::error(SyntaxError, "Expected '}' here.", position());
        }
        eat(RBRACE);
        auto dfn_start = matching_brace(cursor + 1) + 1;
        auto dfn_end = cursor + 1;

        Parser dfn_parser(*symbol_table, dfn_start, dfn_end);
        auto body = dfn_parser.parse();

        cursor -= dfn_end - dfn_start;

        if(at_end() || current().type != LBRACE) {
            throw kepler::error(SyntaxError, "Expected '{' here.", position());
        }

        eat(LBRACE);
        return new AnonymousFunction(body);
    }

    ASTNode<Array>* Parser::parse_argument() {
        if(current().type == ALPHA || current().type == OMEGA) {
            Token tok = current();
            eat(tok.type);
            return new Variable(tok);
        } else {
            return parse_vector();
        }
    }

    ASTNode<Array>* Parser::parse_vector() {
        std::vector<ASTNode<Array>*> nodes;

        while(!at_end() && (current().type == RPARENS || helpers::is_array_token(current().type))) {
            if(current().type == RPARENS) {
                if(helpers::is_array_token(peek_beyond_parenthesis())) {
                    eat(RPARENS);
                    nodes.emplace_back(parse_statement());
                    eat(LPARENS);
                } else {
                    break;
                }
            } else if(current().type == ID && identifies_function(current())) {
                // Need to check if the id is a variable or a function call.
                break;
            } else {
                nodes.emplace_back(parse_scalar());
            }
        }

        std::reverse(nodes.begin(), nodes.end());

        if(nodes.size() == 1) {
            return nodes[0];
        } else {
            return new Vector(nodes);
        }
    }

    ASTNode<Array>* Parser::parse_scalar() {
        Token tok = current();
        if (tok.type == ID) {
            eat(ID);
            return new Variable(tok);
        } else if(tok.type == NUMBER) {
            eat(NUMBER);
            return new Scalar(tok, kepler::from_string({tok.content->begin(), tok.content->end()}));
        } else {
            // Must be string.
            eat(STRING);
            return new Scalar(tok, std::u32string{tok.content->begin(), tok.content->end()});
        }
    }

    ASTNode<Operation_ptr>* Parser::parse_function() {
        if(helpers::is_monadic_operator(current().type)) {
            return parse_mop();
        } else if(current().type == RBRACE) {
            return parse_dfn();
        } else if(identifies_function(current())) {
            Token tok = current();
            eat(ID);
            return new FunctionVariable(tok);
        } else {
            auto function = parse_f();
            if(!at_end() && helpers::is_dyadic_operator(current().type)) {
                Token tok = current();
                eat(tok.type);
                return new DyadicOperator(tok, parse_function(), function);
            }
            return function;
        }
    }

    ASTNode<Operation_ptr>* Parser::parse_mop() {
        Token tok = current();
        eat(tok.type);
        return new MonadicOperator(tok, parse_function());
    }

    ASTNode<Operation_ptr>* Parser::parse_f() {
        Token tok = current();
        if(helpers::is_function(tok.type)) {
            eat(tok.type);
            return new Function(tok);
        } else {
            if(at_end() || current().type != RPARENS) {
                throw kepler::error(SyntaxError, "Expected a ')' here.", position());
            }
            eat(RPARENS);
            auto func = parse_function();

            if(at_end() || current().type != LPARENS) {
                throw kepler::error(SyntaxError, "Expected a '(' here.", position());
            }
            eat(LPARENS);
            return func;
        }
    }

    Parser::Parser(const std::vector<Token> &input_)
                   : symbol_table(new SymbolTable()),
                     cursor(input_.begin()),
                     flag(input_.begin()),
                     begin(input_.begin()),
                     end(input_.end()) {}

    Parser::Parser(SymbolTable &parent_table,
                   std::vector<Token>::const_iterator begin_,
                   std::vector<Token>::const_iterator end_)
                   : symbol_table(new SymbolTable()),
                     cursor(begin_),
                     flag(begin_),
                     begin(begin_),
                     end(end_) {
        symbol_table->attach_parent(&parent_table);
    }

    Statements* Parser::parse() {
        return parse_program();
    }

    void Parser::use_table(SymbolTable *new_table) {
        delete symbol_table;
        symbol_table = new_table;
    }
};