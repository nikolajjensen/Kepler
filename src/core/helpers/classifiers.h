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
#include "core/token.h"
#include "core/session.h"

namespace kepler::helpers {
    bool is_identifier(const Token& token);
    bool is_literal(const Token& token);
    bool is_lexical_unit(const Token& token);
    bool is_value(const Token& token);
    bool is_delimiter(const Token& token);
    bool is_defined_name(const Token& token);
    bool is_defined_operator(const Token& token);
    bool is_system_name(const Token& token);
    bool is_classified_name(const Token& token);
    bool is_syntactic_unit(const Token& token);
    bool is_error(const Token& token);
    bool is_report(const Token& token);
    bool is_exception(const Token& token);
    bool is_result(const Token& token);

    bool is(const Token& token, TokenClass tokenClass);

    bool is_scalar(const Token& token);
};