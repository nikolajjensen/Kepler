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

namespace kepler::evaluation {
    class FuncParser {
    public:
        explicit FuncParser(List<Token>* tokens_) : tokens(tokens_) {}

    private:
        using rule = int (FuncParser::*)();

        int opening_request();
        int creation_request();
        int change_request();
        int initial_request();
        int general_request();
        int positioning_request();
        int deletion_request();
        int display_request();
        int function_line();
        int end_definition();
        int line_number();
        int subject_function();
        int delta();
        int left_bracket();
        int right_bracket();

        int del();
        int permitted_blanks();

        bool match(rule rule, int* counter = nullptr);
        bool match(kepler::TokenClass tokenClass, int* counter = nullptr);
        bool match(const kepler::Token::content_type& content, int* counter = nullptr, kepler::TokenClass tokenClass = kepler::PrimitiveToken);
        bool match(std::initializer_list<kepler::Token::content_type> contents, int* counter = nullptr, kepler::TokenClass tokenClass = kepler::PrimitiveToken);

        bool check(kepler::TokenClass tokenClass);
        bool check(const kepler::Token::content_type& content);
        void advance();
        void backtrack(int& counter);
        bool isAtEnd();
        kepler::Token& peek();
        kepler::Token& previous();

        List<Token>* tokens;
        int current = 0;
    };
};