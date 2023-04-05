//
// Copyright 2022 Nikolaj Banke Jensen.
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

#include "token_type.h"
#include "datatypes.h"
#include "uni_algo/conv.h"
#include "array.h"
#include "interface/conversion.h"
#include <utility>
#include <optional>
#include "position.h"

namespace kepler {

    /**
     * A Token represents a single lexical unit in the source code.
     *
     * It contains the type of the token, and optionally the content of the token. It is also position-tagged.
     */
    struct Token : Position {

        TokenType type;
        std::optional<std::vector<Char>> content;

        /**
         * Creates a Token with the given type, content, and position.
         * @param pos The position of the token.
         * @param type_ The type of the token.
         * @param content_ The content of the token.
         */
        Token(long pos, TokenType type_, Char content_) : Position(pos), type(type_), content(std::vector<Char>{content_}) {}

        /**
         * Creates a Token with the given type, content, and position.
         * @param pos The position of the token.
         * @param type_ The type of the token.
         * @param content_ The content of the token.
         */
        Token(long pos, TokenType type_, String content_) : Position(pos), type(type_), content({content_.begin(), content_.end()}) {}

        /**
         * Creates a Token with the given type and content.
         * @param type_ The type of the token.
         * @param content_ The content of the token.
         */
        Token(TokenType type_, String content_) : type(type_), content({content_.begin(), content_.end()}) {}

        /**
         * Creates a Token with no content.
         * @param pos The position of the token.
         * @param type_ The type of the token.
         */
        Token(long pos, TokenType type_) : Position(pos), type(type_), content(std::nullopt) {}

        /**
         * Checks if two tokens are equal.
         *
         * Two tokens are equal if they have the same type and content.
         * @param lhs Left hand side Token.
         * @param rhs Right hand side Token.
         * @return True if the tokens are equal, false otherwise.
         */
        friend bool operator==(const Token& lhs, const Token& rhs) {
            return lhs.type == rhs.type && lhs.content == rhs.content;
        }

        /**
         * Returns the a string representation of the Token.
         */
        [[nodiscard]] std::string to_string() const {
            std::stringstream ss;
            ss << "Token(" << kepler::to_string(type);

            if(content.has_value()) {
                auto unwrapped = content.value();
                auto str = String(unwrapped.begin(), unwrapped.end());
                ss << ", " << uni::utf32to8(str);
            }
            ss << ")";
            return ss.str();
        }
    };
};