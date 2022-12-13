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

#include "lexer.h"

#include "core/lexer/rules.h"
#include "core/lexer/config.h"

#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>
#include <boost/spirit/home/x3.hpp>

#include <iostream>

bool kepler::lexer::lex(const kepler::StringUTF32 &input, kepler::List<kepler::Token> &token_list) {
    namespace x3 = boost::spirit::x3;
    using kepler::lexer::iterator_type;

    iterator_type iter = input.begin();
    iterator_type const end = input.end();

    std::stringstream ss;

    using x3::with;
    using kepler::lexer::error_handler_type;
    using kepler::lexer::error_handler_tag;
    error_handler_type error_handler(iter, end, ss);

    auto const parser = with<error_handler_tag>(std::ref(error_handler))
    [
            kepler::lexer::token_list()
    ];

    bool success = phrase_parse(iter, end, parser, kepler::lexer::skipper(), token_list);

    return success && iter == end;
}