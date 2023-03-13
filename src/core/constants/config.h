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
#include "core/datatypes.h"
#include "core/token.h"

namespace kepler::constants {
    const std::string indent_prompt = "     > ";
    const std::string quad_prompt = "⎕:\n     > ";

    const std::u32string index_origin_id = U"⎕IO";
    const Number initial_index_origin = 1;

    const std::u32string print_precision_id = U"⎕PP";
    const Number initial_print_precision = 10;

    const std::u32string recursive_call_id = U"∇";

    void check_valid_system_param_value(const std::u32string& id, const Array& value);
    void check_valid_system_param_value(const std::u32string& id, const Number& value);
};
