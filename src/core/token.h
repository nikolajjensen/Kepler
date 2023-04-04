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
    struct Token : position {
        TokenType type;
        std::optional<std::vector<Char>> content;

        Token(long pos, TokenType type_, Char content_) : position(pos), type(type_), content(std::vector<Char>{content_}) {}
        Token(long pos, TokenType type_, std::u32string content_) : position(pos), type(type_), content({content_.begin(), content_.end()}) {}
        Token(TokenType type_, std::u32string content_) : type(type_), content({content_.begin(), content_.end()}) {}
        Token(long pos, TokenType type_) : position(pos), type(type_), content(std::nullopt) {}

        friend bool operator==(const Token& lhs, const Token& rhs) {
            return lhs.type == rhs.type && lhs.content == rhs.content;
        }

        std::string to_string() const {
            std::stringstream ss;
            ss << "Token(" << kepler::to_string(type);

            if(content.has_value()) {
                auto unwrapped = content.value();
                auto str = std::u32string(unwrapped.begin(), unwrapped.end());
                ss << ", " << uni::utf32to8(str);
            }
            ss << ")";
            return ss.str();
        }
    };
};