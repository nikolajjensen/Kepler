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
#include "interface/conversion.h"
#include "core/evaluation/classifiers.h"

namespace kepler {
    class Parser {
    private:
        SymbolTable* symbol_table;
        std::vector<Token>::const_iterator cursor;
        std::vector<Token>::const_iterator flag;
        std::vector<Token>::const_iterator begin;
        std::vector<Token>::const_iterator end;

        void advance();
        const Token& current() const;
        const Token& peek(int amount = 1) const;
        TokenType peek_beyond_parenthesis() const;
        bool at_end() const;
        long position(const std::vector<Token>::const_iterator& it) const;
        long position() const;
        bool identifies_function(const Token& token) const;

        void eat(TokenType type);
        std::vector<Token>::const_iterator next_separator(std::vector<Token>::const_iterator current) const;
        std::vector<Token>::const_iterator matching_brace(std::vector<Token>::const_iterator begin) const;
        void assert_matching(const TokenType& left, const TokenType& right, const Char& right_char) const;

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
        explicit Parser();
        void use_table(SymbolTable* new_table);

        Statements* parse(const std::vector<Token>& input_);
        Statements* parse(SymbolTable* parent_table, std::vector<Token>::const_iterator begin, std::vector<Token>::const_iterator end);
    };
};