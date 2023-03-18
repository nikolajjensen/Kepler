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
#include "core/datatypes.h"

namespace kepler {
    class Tokenizer {
    private:
        const std::vector<Char>* input;
        int cursor;

        void advance();
        const char32_t& current();
        const char32_t& peek();
        bool at_end();
        bool one_of(const char32_t& ch, std::u32string elements);

        void skip_blanks();
        void skip_comment();
        std::u32string get_integer();
        std::u32string get_exponent();
        std::u32string get_real_number();
        Token number_token();
        Token identifier_token();
        Token string_token();
        Token wysiwyg_token();
        Token next_token();

    public:
        explicit Tokenizer();

        std::vector<Token> tokenize(std::vector<Char>* input_);
    };
};
