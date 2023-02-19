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

#include "token_class.h"
#include "datatypes.h"
#include "uni_algo/conv.h"
#include "array.h"
#include <boost/optional.hpp>

namespace kepler {

    struct Token {
        typedef boost::variant<
                    Char,
                    Array,
                    List<Char>,
                    List<Number>
                > content_type;

        typedef boost::optional<content_type> optional_content_type;

        TokenClass token_class;
        optional_content_type content;

        Token(TokenClass token_class_, content_type content_) : token_class(token_class_), content(content_) {}
        Token(TokenClass token_class_ = TokenClass::NilToken) : token_class(token_class_), content(boost::none) {}

        void set(TokenClass new_class) {
            token_class = new_class;
        }

        void set(optional_content_type new_content) {
            content = new_content;
        }

        void set(TokenClass new_class, optional_content_type new_content) {
            set(new_class);
            set(new_content);
        }

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
};