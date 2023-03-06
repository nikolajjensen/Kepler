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
        std::vector<Token>* input;
        int cursor;

        void advance();
        const Token& current();
        bool at_end();
        void eat(TokenType type);
        TokenType peek();
        TokenType peek_beyond_parenthesis();

        ASTNode<Array>* parse_program();
        ASTNode<Array>* parse_statement_list();
        ASTNode<Array>* parse_statement();
        ASTNode<Array>* parse_vector();
        ASTNode<Array>* parse_scalar();
        ASTNode<Operation*>* parse_function();
        ASTNode<Operation*>* parse_mop();
        ASTNode<Operation*>* parse_f();

    public:
        explicit Parser();

        ASTNode<Array>* parse(std::vector<Token>* input_);
    };
};