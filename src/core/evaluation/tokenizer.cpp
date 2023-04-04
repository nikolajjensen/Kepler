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

#include <algorithm>
#include "tokenizer.h"
#include "core/literals.h"
#include "core/error.h"

namespace kepler {

    void Tokenizer::advance() {
        if(!at_end()) cursor++;
    }

    const char32_t& Tokenizer::current() const {
        return (*input)[cursor];
    }

    const char32_t& Tokenizer::peek() const {
        return (*input)[cursor + 1];
    }

    bool Tokenizer::at_end() const {
        return cursor >= input->size();
    }


    bool Tokenizer::one_of(const char32_t& ch, const std::u32string& elements) const {
        return std::any_of(elements.begin(), elements.end(), [&](const Char& element) { return ch == element; });
    }


    void Tokenizer::skip_blanks() {
        while(!at_end() && current() == U' ') {
            advance();
        }
    }

    void Tokenizer::skip_comment() {
        if(!at_end() && current() == U'⍝') {
            while(!at_end() && current() != U'\n') {
                advance();
            }
        }
    }

    std::u32string Tokenizer::get_integer() {
        int start = cursor;
        while(!at_end() && one_of(current(), constants::digit)) {
            advance();
        }
        return {input->begin() + start, input->begin() + cursor};
    }

    std::u32string Tokenizer::get_exponent() {
        std::u32string exponent;

        if(!at_end() && current() == constants::exponent_marker) {
            advance();
            exponent += constants::exponent_marker;
            if(!at_end() && current() == U'¯') {
                advance();
                exponent += U'-';
            }
            std::u32string integer = get_integer();
            if(integer.empty()) {
                throw kepler::Error(SyntaxError, "Expected a digit here.", cursor + 1);
            }
            exponent += integer;
        }

        return exponent;
    }

    std::u32string Tokenizer::get_real_number() {
        std::u32string number;

        if(!at_end() && current() == U'¯') {
            advance();
            number += '-';
        }
        number += get_integer();

        if(!at_end() && current() == U'.') {
            advance();
            number += '.';
        }

        number += get_integer();

        if(number.empty()) {
            throw kepler::Error(SyntaxError, "Expected at least one digit here.", cursor);
        } else if(number == U".") {
            throw kepler::Error(SyntaxError, "Expected at least one digit on either side.", cursor);
        } else if(number == U"-") {
            throw kepler::Error(SyntaxError, "Expected at least one digit here.", cursor + 1);
        }

        number += get_exponent();
        return number;
    }

    Token Tokenizer::number_token() {
        std::u32string number = get_real_number();

        if(!at_end() && current() == constants::complex_marker) {
            advance();
            number += constants::complex_marker;

            std::u32string real = get_real_number();
            number += real;
        }

        return {cursor, NUMBER, number};
    }

    Token Tokenizer::identifier_token() {
        int start = cursor;
        while(!at_end() && one_of(current(), constants::identifier_chars)) {
            advance();
        }
        return {cursor, ID, {input->begin() + start, input->begin() + cursor}};
    }

    Token Tokenizer::string_token() {
        advance();
        int start = cursor;

        while(!at_end() && current() != U'\'') {
            advance();
        }

        if(at_end() || current() != U'\'') {
            throw kepler::Error(SyntaxError, "Expected a matching quote.", cursor + 1);
        }

        std::u32string result = {input->begin() + start, input->begin() + cursor};

        // Go past quote.
        advance();
        return {cursor, STRING, result};
    }

    Token Tokenizer::wysiwyg_token() {
        char32_t character = current();
        advance();
        return {cursor, constants::symbol_mapping.at(character), character};
    }

    Token Tokenizer::next_token() {
        skip_blanks();
        skip_comment();

        if(at_end()) {
            return {cursor, END};
        } else if(one_of(current(), U"¯0123456789") || (current() == U'.' && !one_of(peek(), constants::symbols))) {
            return number_token();
        } else if(one_of(current(), constants::identifier_chars)) {
            return identifier_token();
        } else if(one_of(current(), constants::symbols)) {
            return wysiwyg_token();
        } else if(current() == U'\'') {
            return string_token();
        } else {
            throw kepler::Error(SyntaxError, "Unexpected symbol.", cursor + 1);
        }
    }

    Tokenizer::Tokenizer() : input(), cursor(0) {}

    std::vector<Token> Tokenizer::tokenize(const std::vector<Char>* input_) {
        cursor = 0;
        input = input_;

        std::vector<Token> result = {next_token()};

        while(result.back().type != END) {
            result.emplace_back(std::move(next_token()));
        }

        result.pop_back();

        return result;
    }
};