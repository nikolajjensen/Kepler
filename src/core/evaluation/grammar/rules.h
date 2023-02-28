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
    bool opening_request(const std::vector<Char>& input, context<Char>& context, int& head);
    bool creation_request(const std::vector<Char>& input, context<Char>& context, int& head);
    bool change_request(const std::vector<Char>& input, context<Char>& context, int& head);
    bool initial_request(const std::vector<Char>& input, context<Char>& context, int& head);
    bool general_request(const std::vector<Char>& input, context<Char>& context, int& head);
    bool positioning_request(const std::vector<Char>& input, context<Char>& context, int& head);
    bool deletion_request(const std::vector<Char>& input, context<Char>& context, int& head);
    bool display_request(const std::vector<Char>& input, context<Char>& context, int& head);
    bool function_line(const std::vector<Char>& input, context<Char>& context, int& head);
    bool end_definition(const std::vector<Char>& input, context<Char>& context, int& head);
    bool line_number(const std::vector<Char>& input, context<Char>& context, int& head);
    bool subject_function(const std::vector<Char>& input, context<Char>& context, int& head);
    bool delta(const std::vector<Char>& input, context<Char>& context, int& head);
    bool left_bracket(const std::vector<Char>& input, context<Char>& context, int& head);
    bool right_bracket(const std::vector<Char>& input, context<Char>& context, int& head);

    bool header_line(const std::vector<Char>& input, context<Char>& context, int& head);
    bool result(const std::vector<Char>& input, context<Char>& context, int& head);
    bool result_name(const std::vector<Char>& input, context<Char>& context, int& head);
    bool form(const std::vector<Char>& input, context<Char>& context, int& head);
    bool niladic_function_header(const std::vector<Char>& input, context<Char>& context, int& head);
    bool monadic_function_header(const std::vector<Char>& input, context<Char>& context, int& head);
    bool ambivalent_function_header(const std::vector<Char>& input, context<Char>& context, int& head);
    bool monadic_monadic_operator_header(const std::vector<Char>& input, context<Char>& context, int& head);
    bool monadic_dyadic_operator_header(const std::vector<Char>& input, context<Char>& context, int& head);
    bool ambivalent_monadic_operator_header(const std::vector<Char>& input, context<Char>& context, int& head);
    bool ambivalent_dyadic_operator_header(const std::vector<Char>& input, context<Char>& context, int& head);
    bool monadic_operator_part(const std::vector<Char>& input, context<Char>& context, int& head);
    bool dyadic_operator_part(const std::vector<Char>& input, context<Char>& context, int& head);
    bool right_argument_name(const std::vector<Char>& input, context<Char>& context, int& head);
    bool left_argument_name(const std::vector<Char>& input, context<Char>& context, int& head);
    bool right_operand_name(const std::vector<Char>& input, context<Char>& context, int& head);
    bool left_operand_name(const std::vector<Char>& input, context<Char>& context, int& head);
    bool locals_list(const std::vector<Char>& input, context<Char>& context, int& head);
    bool colon(const std::vector<Char>& input, context<Char>& context, int& head);
    bool local_marker(const std::vector<Char>& input, context<Char>& context, int& head);
    bool function_name(const std::vector<Char>& input, context<Char>& context, int& head);
    bool local_name(const std::vector<Char>& input, context<Char>& context, int& head);
    bool label_name(const std::vector<Char>& input, context<Char>& context, int& head);
    bool body_line(const std::vector<Char>& input, context<Char>& context, int& head);
    bool labelled_line(const std::vector<Char>& input, context<Char>& context, int& head);
    bool labelled_line(const std::vector<Char>& input, context<Char>& context, int& head);
    bool permitted_blanks(const std::vector<Char>& input, context<Char>& context, int& head);
    bool required_blanks(const std::vector<Char>& input, context<Char>& context, int& head);

    // Chapter 15.3 - p. 231
    bool zero_digit(const std::vector<Char>& input, context<Char>& context, int& head);
    bool nonzero_digit(const std::vector<Char>& input, context<Char>& context, int& head);
    bool sign(const std::vector<Char>& input, context<Char>& context, int& head);
    bool decimal_integer(const std::vector<Char>& input, context<Char>& context, int& head);
    bool decimal_rational(const std::vector<Char>& input, context<Char>& context, int& head);
    bool decimal_rational_row(const std::vector<Char>& input, context<Char>& context, int& head);
    bool minimal_decimal_exponential(const std::vector<Char>& input, context<Char>& context, int& head);
    bool decimal_exponential(const std::vector<Char>& input, context<Char>& context, int& head);
    bool decimal_exponential_row(const std::vector<Char>& input, context<Char>& context, int& head);
    bool fixed_decimal(const std::vector<Char>& input, context<Char>& context, int& head);

    bool statement(const std::vector<Token>& input, context<Token>& context, int& head);
    bool expression(const std::vector<Token>& input, context<Token>& context, int& head);
    bool operation(const std::vector<Token>& input, context<Token>& context, int& head);
    bool token_operation(const std::vector<Token>& input, context<Token>& context, int& head);
    bool assignment(const std::vector<Token>& input, context<Token>& context, int& head);
    bool token_variable(const std::vector<Token>& input, context<Token>& context, int& head);
    bool derived_function(const std::vector<Token>& input, context<Token>& context, int& head);
    bool token_dot(const std::vector<Token>& input, context<Token>& context, int& head);
    bool axis_specification(const std::vector<Token>& input, context<Token>& context, int& head);
    bool operand(const std::vector<Token>& input, context<Token>& context, int& head);
    bool token_operand(const std::vector<Token>& input, context<Token>& context, int& head);
    bool index(const std::vector<Token>& input, context<Token>& context, int& head);
    bool primitive_function(const std::vector<Token>& input, context<Token>& context, int& head);
    bool function(const std::vector<Token>& input, context<Token>& context, int& head);
    bool token_function(const std::vector<Token>& input, context<Token>& context, int& head);
    bool dyadic_operator(const std::vector<Token>& input, context<Token>& context, int& head);
    bool defined_dyadic_operator(const std::vector<Token>& input, context<Token>& context, int& head);
    bool monadic_operator(const std::vector<Token>& input, context<Token>& context, int& head);
    bool defined_monadic_operator(const std::vector<Token>& input, context<Token>& context, int& head);
    bool axis_monadic_operator(const std::vector<Token>& input, context<Token>& context, int& head);
    bool primitive_monadic_operator(const std::vector<Token>& input, context<Token>& context, int& head);
    bool primitive_dyadic_operator(const std::vector<Token>& input, context<Token>& context, int& head);
    bool diaeresis_jot(const std::vector<Token>& input, context<Token>& context, int& head);
    bool diaeresis_tilde(const std::vector<Token>& input, context<Token>& context, int& head);
    bool left_parenthesis(const std::vector<Token>& input, context<Token>& context, int& head);
    bool right_parenthesis(const std::vector<Token>& input, context<Token>& context, int& head);
    bool left_axis_bracket(const std::vector<Token>& input, context<Token>& context, int& head);
    bool right_axis_bracket(const std::vector<Token>& input, context<Token>& context, int& head);
    bool branch_arrow(const std::vector<Token>& input, context<Token>& context, int& head);
    bool assignment_arrow(const std::vector<Token>& input, context<Token>& context, int& head);
    bool left_index_bracket(const std::vector<Token>& input, context<Token>& context, int& head);
    bool right_index_bracket(const std::vector<Token>& input, context<Token>& context, int& head);
    bool index_separator(const std::vector<Token>& input, context<Token>& context, int& head);
    bool small_circle(const std::vector<Token>& input, context<Token>& context, int& head);

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

#include "rules.tpp"
