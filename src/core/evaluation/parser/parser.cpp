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

namespace kepler {

    void Parser::advance() {
        if(!at_end()) cursor--;
    }

    const Token& Parser::current() {
        return (*input)[cursor];
    }

    bool Parser::at_end() {
        return cursor < 0;
    }

    void Parser::eat(TokenType type) {
        if(current().type != type) {
            throw std::runtime_error("Expected token of type: " + kepler::to_string(type) + ", but found token of type: " + kepler::to_string(current().type));
        } else {
            advance();
        }
    }

    TokenType Parser::peek() {
        int peek_at = cursor - 1;
        if(peek_at >= 0) return (*input)[peek_at].type;
        return END;
    }

    TokenType Parser::peek_beyond_parenthesis() {
        int peek_at = cursor - 1;
        while(peek_at >= 0 && (*input)[peek_at].type == RPARENS) peek_at--;
        if(peek_at >= 0) return (*input)[peek_at].type;
        return END;
    }


    ASTNode<Array>* Parser::parse_program() {
        ASTNode<Array>* statement_list = parse_statement_list();
        eat(END);
        return statement_list;
    }

    ASTNode<Array>* Parser::parse_statement_list() {
        std::vector<ASTNode<Array>*> statements = {parse_statement()};
        while(current().type == DIAMOND) {
            eat(DIAMOND);
            statements.emplace_back(parse_statement());
        }
        return new Statements(statements);
    }

    ASTNode<Array>* Parser::parse_statement() {
        ASTNode<Array>* statement = parse_vector();

        while(helpers::is_function(current().type) || helpers::is_monadic_operator(current().type) || current().type == ASSIGNMENT || current().type == RPARENS) {

            if(current().type == ASSIGNMENT) {
                eat(ASSIGNMENT);
                statement = new Assignment(current(), statement);
                eat(ID);
            } else {
                ASTNode<Operation*>* function = parse_function();

                if(current().type == RPARENS || helpers::is_array_token(current().type)) {
                    statement = new DyadicFunction(function, parse_vector(), statement);
                } else {
                    statement = new MonadicFunction(function, statement);
                }
            }
        }

        return statement;
    }

    ASTNode<Array>* Parser::parse_vector() {
        std::vector<ASTNode<Array>*> nodes;

        while(current().type == RPARENS || helpers::is_array_token(current().type)) {
            if(current().type == RPARENS) {
                if(helpers::is_array_token(peek_beyond_parenthesis())) {
                    eat(RPARENS);
                    nodes.emplace_back(parse_statement());
                    eat(LPARENS);
                } else {
                    break;
                }
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
        } else if(tok.type == STRING) {
            eat(STRING);
            return new Scalar(tok, std::u32string{tok.content->begin(), tok.content->end()});
        } else {
            throw std::runtime_error("Scalar must be either number of ID");
        }
    }

    ASTNode<Operation*>* Parser::parse_function() {
        if(helpers::is_monadic_operator(current().type)) {
            return parse_mop();
        } else {
            auto function = parse_f();
            if(helpers::is_dyadic_operator(current().type)) {
                Token tok = current();
                eat(tok.type);
                return new DyadicOperator(tok, parse_function(), function);
            }
            return function;
        }
    }

    ASTNode<Operation*>* Parser::parse_mop() {
        if(helpers::is_monadic_operator(current().type)) {
            Token tok = current();
            eat(tok.type);
            return new MonadicOperator(tok, parse_function());
        } else {
            throw std::runtime_error(kepler::to_string(current().type) + " is not a valid monadic operator.");
        }
    }

    ASTNode<Operation*>* Parser::parse_f() {
        Token tok = current();
        if(helpers::is_function(tok.type)) {
            eat(tok.type);
            return new Function(tok);
        } else {
            eat(RPARENS);
            auto func = parse_function();
            eat(LPARENS);
            return func;
        }
    }

    Parser::Parser() : input(), cursor(-1) {}

    ASTNode<Array>* Parser::parse(std::vector<Token>* input_) {
        input = input_;
        cursor = input->size() - 1;
        return parse_program();
    }
};