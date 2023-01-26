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
#include "core/parser/token_converter.h"
#include "core/env/printers.h"

#include <boost/spirit/home/x3.hpp>
/*
bool kepler::parser::parse(kepler::List<kepler::Token> &tokens, Session& session) {
    namespace x3 = boost::spirit::x3;
    using kepler::parser::iterator_type;

    kepler::parser::convert_tokens(tokens, session);

    iterator_type iter = tokens.begin();
    iterator_type const end = tokens.end();

    kepler::List<kepler::Token> results;
    bool success = x3::parse(iter, end, kepler::parser::statement(), results);
    success = success && iter == end;

    results.insert(results.begin(), Token(LeftEndOfStatementToken));
    results.push_back(Token(RightEndOfStatementToken));

    tokens = results;

    return success;
}
*/

bool kepler::parser::parse(kepler::Context* context, kepler::Session* session) {
    namespace x3 = boost::spirit::x3;
    using kepler::parser::iterator_type;

    kepler::parser::convert_tokens(context->currentStatement, *session);

    iterator_type iter = context->currentStatement.begin();
    iterator_type const end = context->currentStatement.end();

    kepler::List<kepler::Token> results;
    bool success = x3::parse(iter, end, kepler::parser::statement(), results);
    success = success && iter == end;

    results.insert(results.begin(), Token(LeftEndOfStatementToken));
    results.push_back(Token(RightEndOfStatementToken));

    context->currentStatement = results;

    return success;
}