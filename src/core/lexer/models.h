//
// Copyright 2022 Nikolaj Banke Jensen.
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

#include <boost/fusion/include/io.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3.hpp>

#include <iostream>
#include <string>
#include <uni_algo/conv.h>

namespace kepler {
    namespace lexer {
        namespace models {
            enum TokenType {
                AssignmentArrow,
                SimpleIdentifier,
                Primitive,
                DistinguishedIdentifier,
                NumericLiteral,
                CharacterLiteral,

                //Not present in ISO-13751:2001
                DirectIdentifier,
                StatementSeparator,

                Unrecognized,
            };

            struct Token : boost::spirit::x3::position_tagged {
                TokenType type = TokenType::Unrecognized;
                boost::variant<char32_t, std::u32string> content = U"0";
            };

            typedef std::vector<Token> TokenList;
        };
    };
};