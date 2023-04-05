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

    /**
     * Tokenizes a string into a list of tokens.
     */
    class Tokenizer {
    private:
        const std::vector<Char>* input;
        int cursor;

        /**
         * Advances the cursor.
         *
         * Will only advance if the cursor is not at the end of the input.
         */
        void advance();

        /**
         * Returns the character at the current position.
         *
         * Note that there is no check to ensure that
         * the cursor is not past the end of the input.
         *
         * @return The character at the current position.
         */
        [[nodiscard]] const Char& current() const;

        /**
         * Returns the character at the next position.
         *
         * Note that there is no check to ensure that
         * the cursor is not at the end of the input.
         *
         * @return The character at the next position.
         */
        [[nodiscard]] const Char& peek() const;

        /**
         * Checks if the cursor is at the end of the input.
         * @return True if the cursor is at the end of the input, false otherwise.
         */
        [[nodiscard]] bool at_end() const;

        /**
         * Checks if the given character is one of the characters in the string.
         * @param ch The character to check.
         * @param elements The elements to check against.
         * @return True if the character is one of the elements, false otherwise.
         */
        [[nodiscard]] bool one_of(const Char& ch, const String& elements) const;

        /**
         * Skips all blanks.
         */
        void skip_blanks();

        /**
         * Skips a comment.
         *
         * A comment is a sequence of characters starting with '⍝' and ending with a newline.
         */
        void skip_comment();

        /**
         * Returns a string of characters which denote a contiguous
         * segment of the input that forms a valid integer.
         */
        String get_integer();

        /**
         * Returns a string of characters which denote a contiguous
         * segment of the input that forms a valid exponent of a number.
         */
        String get_exponent();

        /**
         * Returns a string of characters which denote a contiguous
         * segment of the input that forms a valid real number.
         */
        String get_real_number();

        /**
         * Returns a number token identifier.
         *
         * The token contains the numbers as content.
         * The cursor is advanced.
         *
         * @return The identifier token.
         */
        Token number_token();

        /**
         * Returns a token identifier.
         *
         * The token contains the current identifier as content.
         * The cursor is advanced.
         *
         * @return The identifier token.
         */
        Token identifier_token();

        /**
         * Returns a string token. A string is a sequence of characters between single quotes.
         *
         * The token contains the current string as content.
         * The cursor is advanced.
         *
         * @return The string token.
         */
        Token string_token();

        /**
         * Returns a primitive token which has a type consistent
         * with the current character.
         *
         * The token contains the current character as content.
         * The cursor is advanced.
         *
         * @return The primitive token.
         */
        Token primitive_token();

        /**
         * Returns the next token.
         *
         * If no more tokens are available, an END token will be returned.
         * @return The next token.
         */
        Token next_token();

    public:
        /**
         * Creates a new tokenizer.
         */
        explicit Tokenizer();

        /**
         * Tokenizes the given input.
         * @param input_ The input to tokenize.
         * @return A list of tokens.
         */
        std::vector<Token> tokenize(const std::vector<Char>* input_);
    };
};
