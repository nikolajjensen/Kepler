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
    /*
    const Number initial_comparison_tolerance = 0.0001;
    //const Number initial_index_origin = 1;
    const List<Token> initial_latent_expression = {};
    //const int initial_print_precision = 10;
    const Number initial_random_link = 123;
    //const ReductionStyle reduction_style = ReductionStyle::EncloseReductionStyle;
    const StringUTF8 clear_workspace_identifier = "unnamed";
    const Number positive_number_limit = numeric_limit_max();
    const Number negative_number_limit = numeric_limit_min();
    const int positive_integer_limit = std::numeric_limits<int>::max();
    const int negative_integer_limit = std::numeric_limits<int>::min();
    const int index_limit = positive_integer_limit;
    const int count_limit = index_limit;
    const int rank_limit = 15;
    const int workspace_name_length_limit = 25;
    const int identifier_length_limit = count_limit;
    const int quote_quad_output_limit = 1000;
    const Number comparison_tolerance_limit = 1;
    const Number integer_tolerance = 0.001;
    const Number real_tolerance = 0.00001;
    const int full_print_precision = 64;
    const int print_precision_limit = full_print_precision;
    const int exponent_field_width = 5;
    const int line_limit = 100;
    const int definition_line_limit = 100;
    */

    const std::string indent_prompt = "     > ";
    const std::string quad_prompt = "⎕:\n     > ";

    const std::u32string index_origin_id = U"⎕IO";
    const Number initial_index_origin = 1;

    const std::u32string print_precision_id = U"⎕PP";
    const Number initial_print_precision = 10;

    void check_valid_system_param_value(const std::u32string& id, const Array& value);
    void check_valid_system_param_value(const std::u32string& id, const Number& value);
};
