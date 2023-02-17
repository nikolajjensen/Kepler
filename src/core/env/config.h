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
#include "../datatypes.h"
#include "../token.h"
#include "reduction_style.h"

namespace kepler {
    struct Config {
        Number comparison_tolerance = 0.0001;
        Number index_origin = 1;
        List<Token> initialLatent_expression = {};
        UnsignedInteger print_precision = 10;
        Number random_link = 123;
        ReductionStyle reduction_style = ReductionStyle::EncloseReductionStyle;


        const StringUTF8 clear_workspace_identifier = "unnamed";
        const Number positive_number_limit = numeric_limit_max();
        const Number negative_number_limit = numeric_limit_min();
        const Integer positive_integer_limit = std::numeric_limits<Integer>::max();
        const Integer negative_integer_limit = std::numeric_limits<Integer>::min();
        const UnsignedInteger index_limit = positive_integer_limit;
        const UnsignedInteger count_limit = index_limit;
        const UnsignedInteger rank_limit = 15;
        const UnsignedInteger workspace_name_length_limit = 25;
        const UnsignedInteger identifier_length_limit = count_limit;
        const Integer quote_quad_output_limit = 1000;
        const Number comparison_tolerance_limit = 1;
        const Number integer_tolerance = 0.001;
        const Number real_tolerance = 0.00001;
        const UnsignedInteger full_print_precision = 64;
        const UnsignedInteger print_precision_limit = full_print_precision;
        const UnsignedInteger exponent_field_width = 5;
        const StringUTF8 indent_prompt = ">>>  ";
        const StringUTF8 quad_prompt = ">  ";
        const StringUTF8 function_definition_prompt = indent_prompt;
        const UnsignedInteger line_limit = 100;
        const UnsignedInteger definition_line_limit = 100;
    };
};
