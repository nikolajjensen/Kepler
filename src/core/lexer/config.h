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

#include <boost/spirit/home/x3.hpp>

namespace kepler {
    namespace lexer {
        namespace rules {
            namespace x3 = boost::spirit::x3;

            //using skipper_parser = x3::rule< class skipper_class, x3::unused_type const>;

            using iterator_type = std::u32string::const_iterator;
            using context_type = x3::phrase_parse_context<skipper_parser>::type;
        };
    };
};