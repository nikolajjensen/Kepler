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
#include <algorithm>
#include "core/error.h"
#include "core/symbol_table.h"
#include "core/literals.h"

namespace kepler {

    void Parser::advance() {
        if(!at_end()) cursor--;
    }

    const Token& Parser::current() const {
        return *cursor;
    }

    const Token& Parser::peek(int amount) const {
        return *(cursor - amount);
    }

    bool Parser::at_end() const {
        return (cursor == before_input) || (cursor == after_input);
    }

    long Parser::position(const std::vector<Token>::const_iterator& it) const {
        return it->get_position();
    }

    long Parser::position() const {
        return cursor->get_position();
    }

    void Parser::eat(TokenType type) {
        if(current().type != type) {
            throw kepler::Error(InternalError, "Expected token of type: " + kepler::to_string(type) + ", but found token of type: " + kepler::to_string(current().type), position());
        } else {
            advance();
        }
    }


    bool Parser::identifies_function(const Token& token) const {
        if(!token.content.has_value()) return false;
        String id = {token.content->begin(), token.content->end()};
        if(id == U"∇") return true;
        return symbol_table->contains(id) && symbol_table->get_type(id) == FunctionSymbol;
    }

    TokenType Parser::peek_beyond_parenthesis() const {
        auto peek_at = cursor - 1;
        while(peek_at > before_input && peek_at->type == RIGHT_PARENS) {
            --peek_at;
        }
        return peek_at->type;
        //if(peek_at >= before_input) return peek_at->type;
        //return END;
    }

    void Parser::assert_matching(const TokenType& left, const TokenType& right, const Char& right_char) const {
        auto it = before_input + 1;
        std::vector<std::vector<Token>::const_iterator> stack;

        while(it != after_input) {
            if(it->type == left) {
                stack.emplace_back(it);
            } else if(it->type == right){
                if(stack.empty()) {
                    throw kepler::Error(SyntaxError, "Expected a matching '" + uni::utf32to8(String(1, right_char)) + "'.", position(it));
                }
                stack.pop_back();
            }
            ++it;
        }

        if(!stack.empty()) {
            throw kepler::Error(SyntaxError, "Expected a matching '" + uni::utf32to8(String(1, right_char)) + "'.", position(stack.back()));
        }
    }


    Statements* Parser::parse_program() {
        assert_matching(LEFT_BRACE, RIGHT_BRACE, U'}');
        assert_matching(LEFT_PARENS, RIGHT_PARENS, U')');
        return parse_statement_list();
    }

    std::vector<Token>::const_iterator Parser::next_separator(std::vector<Token>::const_iterator current) const {
        auto it = current;
        int level = 0;
        while(it != after_input) {
            if(it->type == LEFT_BRACE) {
                ++level;
            } else if(it->type == RIGHT_BRACE) {
                --level;
            } else if(it->type == DIAMOND && level == 0) {
                break;
            }
            ++it;
        }

        return it;
    }

    std::vector<Token>::const_iterator Parser::matching_brace(std::vector<Token>::const_iterator index) const {
        int level = 1;
        auto it = index - 1;
        while(it > before_input && level != 0) {
            if(it->type == LEFT_BRACE) {
                --level;
            } else if(it->type == RIGHT_BRACE) {
                ++level;
            }
            --it;
        }

        return it + 1;
    }


    Statements* Parser::parse_statement_list() {
        std::vector<ASTNode<Array>*> statements{};

        while(flag != after_input) {
            auto tmp = next_separator(flag + 1);

            // If the next separator is immediately the next one
            // then skip this statement, as there is nothing useful
            // in '◊◊'.
            if((flag->type == DIAMOND || flag == before_input) && tmp == flag + 1) {
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
        if(current().type == RIGHT_BRACE) {
            ASTNode<Operation_ptr>* function = parse_function();
            if(current().type != ASSIGNMENT) {
                throw kepler::Error(SyntaxError, "Expected an assignment here.", position());
            }
            eat(ASSIGNMENT);
            if(at_end() || current().type != ID) {
                throw kepler::Error(SyntaxError, "Expected an identifier here.", position());
            }
            Token identifier = current();
            auto statement = new FunctionAssignment(identifier, function);
            eat(ID);

            symbol_table->bind_function({identifier.content->begin(), identifier.content->end()});
            return statement;
        } else {
            ASTNode<Array>* statement = parse_vector();

            while(!at_end() && (helpers::is_function(current().type)
                  || helpers::is_monadic_operator(current().type)
                  || current().type == ASSIGNMENT
                  || current().type == RIGHT_PARENS
                  || current().type == RIGHT_BRACE
                  || identifies_function(current()))
                  || current().type == COLON) {

                if(current().type == ASSIGNMENT) {
                    eat(ASSIGNMENT);

                    if(at_end() || current().type != ID) {
                        throw kepler::Error(SyntaxError, "Expected an identifier here.", position());
                    }

                    statement = new Assignment(current(), statement);
                    eat(ID);
                } else if(current().type == COLON) {
                    eat(COLON);
                    ASTNode<Array>* condition = parse_statement();
                    statement = new Conditional(condition, statement, parse_statement_list());
                } else {
                    long func_pos = position();
                    bool is_monadic = helpers::is_monadic_function(current().type);

                    ASTNode<Operation_ptr>* function = parse_function();
                    function->set_position(func_pos);

                    if(!at_end() && !is_monadic && (current().type == RIGHT_PARENS || helpers::is_array_token(current().type))) {
                        statement = new DyadicFunction(function, parse_vector(), statement);
                    } else {
                        statement = new MonadicFunction(function, statement);
                    }
                }
            }

            return statement;
        }
    }

    ASTNode<Operation_ptr>* Parser::parse_dfn() {
        if(current().type != RIGHT_BRACE) {
            throw kepler::Error(SyntaxError, "Expected '}' here.", position());
        }
        eat(RIGHT_BRACE);
        auto dfn_start = matching_brace(cursor + 1);
        auto dfn_end = cursor + 1;

        Parser dfn_parser;
        auto body = dfn_parser.parse(symbol_table, dfn_start, dfn_end);

        cursor -= dfn_end - dfn_start;
        // To get back the left brace.
        cursor++;

        if(at_end() || current().type != LEFT_BRACE) {
            throw kepler::Error(SyntaxError, "Expected '{' here.", position());
        }

        eat(LEFT_BRACE);
        return new AnonymousFunction(body);
    }

    ASTNode<Array>* Parser::parse_vector() {
        std::vector<ASTNode<Array>*> nodes;

        while(!at_end() && (current().type == RIGHT_PARENS || helpers::is_array_token(current().type))) {
            if(current().type == RIGHT_PARENS) {
                if(helpers::is_array_token(peek_beyond_parenthesis()) && peek(2).type != POWER) {
                    eat(RIGHT_PARENS);
                    nodes.emplace_back(parse_statement());
                    eat(LEFT_PARENS);
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
        } else if(tok.type == ALPHA || tok.type == OMEGA) {
            eat(tok.type);
            return new Variable(tok);
        } else if(tok.type == NUMBER) {
            eat(NUMBER);
            return new Scalar(tok, kepler::from_string({tok.content->begin(), tok.content->end()}));
        } else {
            // Must be string.
            eat(STRING);
            return new Scalar(tok, String{tok.content->begin(), tok.content->end()});
        }
    }

    ASTNode<Operation_ptr>* Parser::parse_function() {
        if(helpers::is_monadic_operator(current().type)) {
            return parse_mop();
        } else if(current().type == RIGHT_BRACE) {
            return parse_dfn();
        } else if(identifies_function(current())) {
            Token tok = current();
            eat(ID);
            return new FunctionVariable(tok);
        } else if(peek().type == POWER) {
            // Power operator with non-function right argument.
            auto scalar = parse_scalar();
            Token tok = current();
            eat(POWER);
            return new DyadicOperator(tok, parse_function(), scalar);

        } else {
            auto function = parse_f();

            if(!at_end() && current().type == PRODUCT && peek().type == JOT) {
                Token tok = current();
                eat(PRODUCT);
                eat(JOT);
                return new MonadicOperator(tok, function);
            } else if(!at_end() && helpers::is_dyadic_operator(current().type)) {
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
        } else if(!at_end() && current().type == RIGHT_PARENS) {
            eat(RIGHT_PARENS);
            auto func = parse_function();

            if(at_end() || current().type != LEFT_PARENS) {
                throw kepler::Error(SyntaxError, "Expected a '(' here.", position());
            }
            eat(LEFT_PARENS);
            return func;
        } else {
            throw kepler::Error(SyntaxError, "Invalid primitive.", position() + 1);
        }
    }

    void Parser::use_table(SymbolTable *new_table) {
        delete symbol_table;
        symbol_table = new_table;
    }

    Parser::Parser() : symbol_table(new SymbolTable()), cursor(nullptr), flag(nullptr), before_input(nullptr), after_input(nullptr) {}

    Statements* Parser::parse(const std::vector<Token>& input_) {
        before_input = input_.begin();
        after_input = input_.end();
        flag = before_input;
        cursor = before_input;
        _tmp = input_;
        return parse_program();
    }

    Statements* Parser::parse(SymbolTable* parent_table, std::vector<Token>::const_iterator begin_, std::vector<Token>::const_iterator end_) {
        symbol_table->attach_parent(parent_table);
        before_input = begin_;
        after_input = end_;
        flag = before_input;
        cursor = before_input;
        _tmp = {begin_, end_};
        return parse_program();
    }
};