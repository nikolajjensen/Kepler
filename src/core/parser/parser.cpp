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

#include "parser.h"
#include "config.h"
#include "rules.h"

#include <boost/spirit/home/x3.hpp>

bool kepler::parser::parse(kepler::List<kepler::Token> &token_list) {
    namespace x3 = boost::spirit::x3;
    using kepler::parser::iterator_type;

    iterator_type iter = token_list.begin();
    iterator_type const end = token_list.end();

    kepler::List<kepler::Token> results;
    bool success = x3::parse(iter, end, kepler::parser::statement(), results);

    token_list = results;

    return success && iter == end;
}