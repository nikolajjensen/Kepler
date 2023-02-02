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
#include <utility>

#include "../datatypes.h"
#include "../token.h"
#include "../token_class.h"
#include "../env/context.h"
#include "../env/session.h"

namespace kepler {
    namespace parser {
        class Parser {
        public:
            Parser(kepler::List<kepler::Token>* tokens_) : tokens(tokens_) {}

            bool parse();

            static bool parse(kepler::Context* context, kepler::Session* session);

        private:
            using rule = int (Parser::*)();

            int statement();
            int expression();
            int operation();
            int assignment();
            int derived_function();
            int axis_specification();
            int operand();
            int index();
            int primitive_function();
            int function();
            int dyadic_operator();
            int monadic_operator();
            int axis_monadic_operator();
            int primitive_monadic_operator();
            int primitive_dyadic_operator();

            int diaeresis_jot();
            int diaeresis_tilde();
            int left_parenthesis();
            int right_parenthesis();
            int left_axis_bracket();
            int right_axis_bracket();
            int branch_arrow();
            int assignment_arrow();
            int left_index_bracket();
            int right_index_bracket();
            int index_separator();
            int small_circle();
            int dot();

            bool match(rule rule, int* counter = nullptr);
            bool match(kepler::TokenClass tokenClass, int* counter = nullptr);
            bool match(const kepler::Token::content_type& content, int* counter = nullptr, kepler::TokenClass tokenClass = kepler::PrimitiveToken);
            bool match(std::initializer_list<kepler::Token::content_type> contents, int* counter = nullptr, kepler::TokenClass tokenClass = kepler::PrimitiveToken);

            void set_class(kepler::TokenClass tokenClass);

            bool check(kepler::TokenClass tokenClass);
            bool check(const kepler::Token::content_type& content);
            void advance();
            void backtrack(int& counter);
            bool isAtEnd();
            kepler::Token& peek();
            kepler::Token& previous();


            std::map<int, kepler::TokenClass> backtrack_log;
            kepler::List<kepler::Token>* tokens;
            int current = 0;
        };
    };
};
