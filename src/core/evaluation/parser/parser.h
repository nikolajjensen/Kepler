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

#pragma once
#include "core/token.h"
#include <vector>
#include "core/token_type.h"
#include "core/evaluation/ast.h"
#include "core/helpers/conversion.h"
#include "core/helpers/classifiers.h"

namespace kepler {
    class Parser {
    private:
        SymbolTable* symbol_table;
        std::vector<Token>::const_iterator cursor;
        std::vector<Token>::const_iterator flag;
        std::vector<Token>::const_iterator begin;
        std::vector<Token>::const_iterator end;

        void advance();
        const Token& current();
        bool at_end();
        long position(const std::vector<Token>::const_iterator& it);
        long position();
        void eat(TokenType type);
        TokenType peek_beyond_parenthesis();

        void assert_matching(const TokenType& left, const TokenType& right, const Char& right_char);

        bool identifies_function(Token token);
        std::vector<Token>::const_iterator next_separator(const std::vector<Token>::const_iterator& current);
        std::vector<Token>::const_iterator matching_brace(const std::vector<Token>::const_iterator& begin);

        ASTNode<Operation_ptr>* parse_dfn();
        ASTNode<Array>* parse_argument();

        Statements* parse_program();
        Statements* parse_statement_list();
        ASTNode<Array>* parse_statement();
        ASTNode<Array>* parse_vector();
        ASTNode<Array>* parse_scalar();
        ASTNode<Operation_ptr>* parse_function();
        ASTNode<Operation_ptr>* parse_mop();
        ASTNode<Operation_ptr>* parse_f();

    public:
        explicit Parser(SymbolTable& parent_table, std::vector<Token>::const_iterator begin, std::vector<Token>::const_iterator end);
        explicit Parser(const std::vector<Token>& input_);

        void use_table(SymbolTable* new_table);

        Statements* parse();
    };
};