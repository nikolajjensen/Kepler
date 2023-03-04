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

#include "tokenizer.h"

namespace kepler {
    /*
    Tokenizer::Tokenizer(const List<Char> &input_) : input(input_) {}

    Token Tokenizer::next() {
        skip_blanks();
        skip_comment();

        if(next_is_in(U"¯.0123456789")) {
            return number();
        } else if(next_is_in(U"abcdefghijklmnopqrstuvWxyzABCDEFGHIJKLMNOPQRSTUVWXYZ")) {
            return identifier();
        }
    }

    List<Token> Tokenizer::lex() {
        List<Token> result = {next()};

        while(cursor < input.size()) {
            result.emplace_back(std::move(next()));
        }

        return result;
    }
    */
};