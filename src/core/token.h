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
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>

namespace kepler {
    struct Token : boost::spirit::x3::position_tagged {
        TokenClass tokenClass;
        boost::variant<Char, List<Char>> content;

        bool is_identifier() {
            return  tokenClass == TokenClass::SimpleIdentifierToken
                    || tokenClass == TokenClass::DistinguishedIdentifierToken;
        }

        bool is_literal() {
            return  tokenClass == TokenClass::CharacterLiteralToken
                    || tokenClass == TokenClass::NumericLiteralToken;
        }

        bool is_primitive() {
            return  tokenClass == TokenClass::PrimitiveToken;
        }

        TokenClass current_class() {


            return tokenClass;
        }
    };
};

BOOST_FUSION_ADAPT_STRUCT(kepler::Token,
        tokenClass, content
)