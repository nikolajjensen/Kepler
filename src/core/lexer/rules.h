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
#include "models.h"

namespace kepler {
    namespace lexer {

        //Employee parser declaration
        namespace rules {
            namespace x3 = boost::spirit::x3;

            typedef x3::rule<class token_list_class, models::TokenList> token_list_type;
            typedef x3::rule<class skipper_class, x3::unused_type const> skipper_type;

            BOOST_SPIRIT_DECLARE(skipper_type, token_list_type)
        };

        rules::token_list_type const& token_list();
        rules::skipper_type const& skipper();
    };
};