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
#include "core/symbol_table.h"
#include "core/datatypes.h"
#include "core/token.h"
#include "core/reduction_style.h"

namespace kepler {
    namespace config {
        const Number initial_comparison_tolerance = 0.0001;
        const Number initial_index_origin = 1;
        const List<Token> initial_latent_expression = {};
        const int initial_print_precision = 10;
        const Number initial_random_link = 123;


        const ReductionStyle reduction_style = ReductionStyle::EncloseReductionStyle;
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
        const StringUTF8 indent_prompt = ">>>  ";
        const StringUTF8 quad_prompt = ">  ";
        const StringUTF8 function_definition_prompt = indent_prompt;
        const int line_limit = 100;
        const int definition_line_limit = 100;

        void set_initial_values(SymbolTable& symbol_table);
    };
};
