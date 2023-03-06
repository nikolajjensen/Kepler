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
#include "core/helpers/conversion.h"
#include <utility>
#include <optional>

namespace kepler {

    struct Token {
        TokenType type;
        std::optional<std::vector<Char>> content;

        Token(TokenType type_, Char content_) : type(type_), content(std::vector<Char>{content_}) {}
        Token(TokenType type_, std::u32string content_) : type(type_), content({content_.begin(), content_.end()}) {}
        Token(TokenType type_) : type(type_), content(std::nullopt) {}

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

        friend std::ostream& operator<<(std::ostream& os, const Token& token) {
            return os << token.to_string();
        }
    };

    /*
    struct Token {
        typedef boost::variant<
                    Char,
                    Array,
                    List<Char>,
                    List<Number>
                > content_type;

        typedef boost::optional<content_type> optional_content_type;

        TokenType token_class;
        optional_content_type content;

        Token(TokenType token_class_, content_type content_) : token_class(token_class_), content(content_) {}
        Token(TokenType token_class_, std::string content_) : token_class(token_class_), content() {
            StringUTF32 tmp = uni::utf8to32u(content_);
            List<Char> raw = {tmp.begin(), tmp.end()};
            if(raw.size() == 1) {
                content = raw.front();
            } else {
                content = raw;
            }
        }
        explicit Token(TokenType token_class_ = TokenType::NilToken) : token_class(token_class_), content(boost::none) {}

        template <typename Variant>
        bool contains() const {
            return content && content->type() == typeid(Variant);
        }

        template <typename Variant>
        Variant& get_content() {
            return boost::get<Variant>(content.get());
        }

        template <typename Variant>
        const Variant& get_content() const {
            return boost::get<const Variant>(content.get());
        }

        friend bool operator==(const Token& lhs, const Token& rhs) {
            return lhs.token_class == rhs.token_class && lhs.content == rhs.content;
        }
    };
     */
};