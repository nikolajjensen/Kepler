//
// Copyright 2023 Nikolaj Banke Jensen.
//
// This file is part of Test.
// 
// Test is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Test is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License 
// along with Test. If not, see <https://www.gnu.org/licenses/>.
//

#pragma once

#include "core/datatypes.h"
#include "core/token.h"
#include "core/context.h"
#include "core/evaluation/grammar/matcher.h"
#include "core/evaluation/grammar/rules.h"

namespace kepler::evaluation {
    class Lexer {
    public:
        Lexer(List<Char> input, kepler::List<kepler::Token>* output_);

        void lex();
    private:
        using rule = int (Lexer::*)();

        int line();
        int identifier();
        int simple_identifier();
        int literal_identifier();
        int direct_identifier();
        int distinguished_identifier();
        int numeric_literal();
        int real_scalar_literal();
        int exponent();
        int numeric_scalar_literal();
        int imaginary_part();
        int character_literal();
        int comment();
        int any();
        int primitive();
        int space();
        int nonquote();
        int statement_separator();
        int letter();
        int digit();
        int ideogram();
        int quote();
        int exponent_marker();
        int complex_marker();
        int dot();
        int underbar();
        int overbar();
        int blank();
        int del();
        int del_tilde();
        int lamp();
        int quad();
        int quote_quad();
        int diamond();

        bool match(rule rule, int* counter = nullptr);
        bool match(kepler::Char character, int* counter = nullptr, bool append = true);
        bool match(std::initializer_list<kepler::Char> characters, int* counter = nullptr, bool append = true);

        bool check(kepler::Char character);
        void advance();
        void backtrack(int& counter);
        bool isAtEnd();

        void clear();
        void create(kepler::TokenClass tokenClass);

        kepler::Char& peek();

        List<Char> input;
        List<Char> content;
        kepler::List<kepler::Token>* output;
        int current = 0;
    };
};