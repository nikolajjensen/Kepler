//
// Copyright 2023 Nikolaj Banke Jensen.
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

#include "context.h"
#include "rules.h"

namespace kepler::grammar {
    void lexer_context::apply_for(rule_type<Char> rule, const std::vector<Char> &input, const int &start,
                                 const int &end) {
        if(rule == rules::diamond
            || rule == rules::quote_quad
            || rule == rules::quad
            || rule == rules::lamp
            || rule == rules::del_tilde
            || rule == rules::del
            || rule == rules::blank
            || rule == rules::overbar
            || rule == rules::underbar
            || rule == rules::dot
            || rule == rules::complex_marker
            || rule == rules::exponent_marker
            || rule == rules::quote
            || rule == rules::ideogram
            || rule == rules::digit
            || rule == rules::letter) {

            append(input, start, end);
        } else if(rule == rules::comment
                    || rule == rules::space) {
            clear();
        } else if(rule == rules::primitive) {
            create(PrimitiveToken);
        } else if(rule == rules::character_literal) {
            create(CharacterLiteralToken);
        } else if(rule == rules::numeric_literal) {
            create(NumericLiteralToken);
        } else if(rule == rules::distinguished_identifier) {
            create(DistinguishedIdentifierToken);
        } else if(rule == rules::literal_identifier) {
            create(SimpleIdentifierToken);
        }
    }
};