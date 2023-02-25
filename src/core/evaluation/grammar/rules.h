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

#pragma once
#include <vector>
#include "context.h"
#include "core/datatypes.h"

namespace kepler::grammar::rules {
    bool line(const std::vector<Char>& input, context<Char>& context, int& head);
    bool identifier(const std::vector<Char>& input, context<Char>& context, int& head);
    bool simple_identifier(const std::vector<Char>& input, context<Char>& context, int& head);
    bool literal_identifier(const std::vector<Char>& input, context<Char>& context, int& head);
    bool direct_identifier(const std::vector<Char>& input, context<Char>& context, int& head);
    bool distinguished_identifier(const std::vector<Char>& input, context<Char>& context, int& head);
    bool numeric_literal(const std::vector<Char>& input, context<Char>& context, int& head);
    bool real_scalar_literal(const std::vector<Char>& input, context<Char>& context, int& head);
    bool exponent(const std::vector<Char>& input, context<Char>& context, int& head);
    bool numeric_scalar_literal(const std::vector<Char>& input, context<Char>& context, int& head);
    bool imaginary_part(const std::vector<Char>& input, context<Char>& context, int& head);
    bool character_literal(const std::vector<Char>& input, context<Char>& context, int& head);
    bool comment(const std::vector<Char>& input, context<Char>& context, int& head);
    bool any(const std::vector<Char>& input, context<Char>& context, int& head);
    bool primitive(const std::vector<Char>& input, context<Char>& context, int& head);
    bool space(const std::vector<Char>& input, context<Char>& context, int& head);
    bool nonquote(const std::vector<Char>& input, context<Char>& context, int& head);
    bool statement_separator(const std::vector<Char>& input, context<Char>& context, int& head);
    bool letter(const std::vector<Char>& input, context<Char>& context, int& head);
    bool digit(const std::vector<Char>& input, context<Char>& context, int& head);
    bool ideogram(const std::vector<Char>& input, context<Char>& context, int& head);
    bool quote(const std::vector<Char>& input, context<Char>& context, int& head);
    bool exponent_marker(const std::vector<Char>& input, context<Char>& context, int& head);
    bool complex_marker(const std::vector<Char>& input, context<Char>& context, int& head);
    bool dot(const std::vector<Char>& input, context<Char>& context, int& head);
    bool underbar(const std::vector<Char>& input, context<Char>& context, int& head);
    bool overbar(const std::vector<Char>& input, context<Char>& context, int& head);
    bool blank(const std::vector<Char>& input, context<Char>& context, int& head);
    bool del(const std::vector<Char>& input, context<Char>& context, int& head);
    bool del_tilde(const std::vector<Char>& input, context<Char>& context, int& head);
    bool lamp(const std::vector<Char>& input, context<Char>& context, int& head);
    bool quad(const std::vector<Char>& input, context<Char>& context, int& head);
    bool quote_quad(const std::vector<Char>& input, context<Char>& context, int& head);
    bool diamond(const std::vector<Char>& input, context<Char>& context, int& head);
};

