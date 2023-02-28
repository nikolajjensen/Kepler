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

#include "rules.h"
#include "context.h"
#include "core/error.h"

namespace kepler::grammar {
    bool rules::opening_request(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;

        if(context.match(permitted_blanks, input, counter)
           && context.match(del, input, counter)
           && (context.match(creation_request, input, counter) || context.match(change_request, input, counter))) {
            head = counter;
            return true;
        }

        context.backtrack(counter - head);
        return false;
    }

    bool rules::creation_request(const std::vector<Char> &input, context<Char> &context, int &head) {
        return context.match(header_line, input, head);
    }

    bool rules::change_request(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;

        if(context.match(permitted_blanks, input, counter)
           && context.match(subject_function, input, counter)
           && context.match(permitted_blanks, input, counter)
           && context.match(initial_request, input, counter)) {
            head = counter;
            return true;
        }

        context.backtrack(counter - head);
        return false;
    }

    bool rules::initial_request(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;

        if(context.match(left_bracket, input, counter)) {
            if(!context.match(any, input, counter)) {
                context.backtrack(counter - head);
                return false;
            }
            while(context.match(any, input, counter)) {}

            head = counter;
            return true;
        }

        return false;
    }

    bool rules::general_request(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;
        if(context.match(permitted_blanks, input, counter)) {
            bool matched_pos_req = false;

            while(context.match(positioning_request, input, counter)) {
                matched_pos_req = true;

                if(!context.match(permitted_blanks, input, counter)) {
                    break; // Escape while loop.
                }
            }

            if(matched_pos_req && context.match(function_line, input, counter)) {}
            else if(context.match(deletion_request, input, counter)) {}
            else if(context.match(display_request, input, counter)) {}
            else {
                context.backtrack(counter - head);
                return false;
            }

            context.match(end_definition, input, counter);
            head = counter;
            return true;
        }

        return false;
    }

    bool rules::positioning_request(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;

        if(context.match(left_bracket, input, counter)
           && context.match(permitted_blanks, input, counter)
           && context.match(line_number, input, counter)
           && context.match(right_bracket, input, counter)) {
            head = counter;
            return true;
        }

        context.backtrack(counter - head);
        return false;
    }

    bool rules::deletion_request(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;

        if(context.match(left_bracket, input, counter)
           && context.match(permitted_blanks, input, counter)
           && context.match(delta, input, counter)
           && context.match(permitted_blanks, input, counter)
           && context.match(line_number, input, counter)
           && context.match(right_bracket, input, counter)) {
            head = counter;
            return true;
        }

        context.backtrack(counter - head);
        return false;
    }

    bool rules::display_request(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;

        if(context.match(left_bracket, input, counter)
           && context.match(permitted_blanks, input, counter)
           && context.match(quad, input, counter)
           && context.match(permitted_blanks, input, counter)
           && context.match(right_bracket, input, counter)) {
            head = counter;
            return true;
        }

        context.backtrack(counter - head);
        return false;
    }

    bool rules::function_line(const std::vector<Char> &input, context<Char> &context, int &head) {
        return context.match(body_line, input, head);
    }

    bool rules::end_definition(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;

        if(context.match(permitted_blanks, input, counter)
           && context.match(del, input, counter)
           && context.match(permitted_blanks, input, counter)) {
            head = counter;
            return true;
        }

        context.backtrack(counter - head);
        return false;
    }

    bool rules::line_number(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;

        if(context.match(decimal_rational, input, counter)
           && context.match(permitted_blanks, input, counter)) {
            head = counter;
            return true;
        }

        context.backtrack(counter - head);
        return false;
    }

    bool rules::subject_function(const std::vector<Char> &input, context<Char> &context, int &head) {
        return context.match(simple_identifier, input, head);
    }

    bool rules::delta(const std::vector<Char> &input, context<Char> &context, int &head) {
        return context.match(constants::delta, input, head);
    }

    bool rules::left_bracket(const std::vector<Char> &input, context<Char> &context, int &head) {
        return context.match(constants::left_bracket, input, head);
    }

    bool rules::right_bracket(const std::vector<Char> &input, context<Char> &context, int &head) {
        return context.match(constants::right_bracket, input, head);
    }



    bool rules::header_line(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;

        if(context.match(permitted_blanks, input, counter)
           && (context.match(result, input, counter) || true)
           && context.match(permitted_blanks, input, counter)
           && context.match(form, input, counter)
           && context.match(permitted_blanks, input, counter)
           && (context.match(locals_list, input, counter) || true)) {
            head = counter;
            return true;
        }

        context.backtrack(counter - head);
        return false;
    }

    bool rules::result(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;

        if(context.match(result_name, input, counter)
           && context.match(permitted_blanks, input, counter)
           && context.match(constants::left_arrow, input, counter)) {
            head = counter;
            return true;
        }

        context.backtrack(counter - head);
        return false;
    }

    bool rules::result_name(const std::vector<Char> &input, context<Char> &context, int &head) {
        return context.match(simple_identifier, input, head);
    }

    bool rules::form(const std::vector<Char> &input, context<Char> &context, int &head) {
        if(context.match(niladic_function_header, input, head)) {}
        else if(context.match(monadic_function_header, input, head)) {}
        else if(context.match(ambivalent_function_header, input, head)) {}
        else if(context.match(monadic_monadic_operator_header, input, head)) {}
        else if(context.match(monadic_dyadic_operator_header, input, head)) {}
        else if(context.match(ambivalent_monadic_operator_header, input, head)) {}
        else if(context.match(ambivalent_dyadic_operator_header, input, head)) {}
        else { return false; }

        return true;
    }

    bool rules::niladic_function_header(const std::vector<Char> &input, context<Char> &context, int &head) {
        return context.match(function_name, input, head);
    }

    bool rules::monadic_function_header(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;

        if(context.match(function_name, input, counter)
           && context.match(required_blanks, input, counter)
           && context.match(right_argument_name, input, counter)) {
            head = counter;
            return true;
        }

        context.backtrack(counter - head);
        return false;
    }

    bool rules::ambivalent_function_header(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;

        if(context.match(left_argument_name, input, counter)
           && context.match(required_blanks, input, counter)
           && context.match(function_name, input, counter)
           && context.match(required_blanks, input, counter)
           && context.match(right_argument_name, input, counter)) {
            head = counter;
            return true;
        }

        context.backtrack(counter - head);
        return false;
    }

    bool rules::monadic_monadic_operator_header(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;

        if(context.match(permitted_blanks, input, counter)
           && context.match(monadic_operator_part, input, counter)
           && context.match(permitted_blanks, input, counter)
           && context.match(right_argument_name, input, counter)) {
            head = counter;
            return true;
        }

        context.backtrack(counter - head);
        return false;
    }

    bool rules::monadic_dyadic_operator_header(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;

        if(context.match(permitted_blanks, input, counter)
           && context.match(dyadic_operator_part, input, counter)
           && context.match(permitted_blanks, input, counter)
           && context.match(right_argument_name, input, counter)) {
            head = counter;
            return true;
        }

        context.backtrack(counter - head);
        return false;
    }

    bool rules::ambivalent_monadic_operator_header(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;

        if(context.match(left_argument_name, input, counter)
           && context.match(permitted_blanks, input, counter)
           && context.match(monadic_operator_part, input, counter)
           && context.match(permitted_blanks, input, counter)
           && context.match(right_argument_name, input, counter)) {
            head = counter;
            return true;
        }

        context.backtrack(counter - head);
        return false;
    }

    bool rules::ambivalent_dyadic_operator_header(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;

        if(context.match(left_argument_name, input, counter)
           && context.match(permitted_blanks, input, counter)
           && context.match(dyadic_operator_part, input, counter)
           && context.match(permitted_blanks, input, counter)
           && context.match(right_argument_name, input, counter)) {
            head = counter;
            return true;
        }

        context.backtrack(counter - head);
        return false;
    }

    bool rules::monadic_operator_part(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;

        if(context.match(constants::left_parenthesis, input, counter)
           && context.match(permitted_blanks, input, counter)
           && context.match(left_operand_name, input, counter)
           && context.match(required_blanks, input, counter)
           && context.match(function_name, input, counter)
           && context.match(permitted_blanks, input, counter)
           && context.match(constants::right_parenthesis, input, counter)) {
            head = counter;
            return true;
        }

        context.backtrack(counter - head);
        return false;
    }

    bool rules::dyadic_operator_part(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;

        if(context.match(constants::left_parenthesis, input, counter)
           && context.match(permitted_blanks, input, counter)
           && context.match(left_operand_name, input, counter)
           && context.match(required_blanks, input, counter)
           && context.match(function_name, input, counter)
           && context.match(required_blanks, input, counter)
           && context.match(right_operand_name, input, counter)
           && context.match(permitted_blanks, input, counter)
           && context.match(constants::right_parenthesis, input, counter)) {
            head = counter;
            return true;
        }

        context.backtrack(counter - head);
        return false;
    }

    bool rules::right_argument_name(const std::vector<Char> &input, context<Char> &context, int &head) {
        return context.match(simple_identifier, input, head);
    }

    bool rules::left_argument_name(const std::vector<Char> &input, context<Char> &context, int &head) {
        return context.match(simple_identifier, input, head);
    }

    bool rules::right_operand_name(const std::vector<Char> &input, context<Char> &context, int &head) {
        return context.match(simple_identifier, input, head);
    }

    bool rules::left_operand_name(const std::vector<Char> &input, context<Char> &context, int &head) {
        return context.match(simple_identifier, input, head);
    }

    bool rules::locals_list(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;

        while(true) {
            if(context.match(local_marker, input, counter)
               && context.match(permitted_blanks, input, counter)
               && context.match(local_name, input, counter)
               && context.match(permitted_blanks, input, counter)) {
                head = counter;
            } else {
                context.backtrack(counter - head);
                break;
            }
        }

        return true;
    }

    bool rules::colon(const std::vector<Char> &input, context<Char> &context, int &head) {
        return context.match(constants::colon, input, head);
    }

    bool rules::local_marker(const std::vector<Char> &input, context<Char> &context, int &head) {
        return context.match(constants::semicolon, input, head);
    }

    bool rules::function_name(const std::vector<Char> &input, context<Char> &context, int &head) {
        return context.match(simple_identifier, input, head);
    }

    bool rules::local_name(const std::vector<Char> &input, context<Char> &context, int &head) {
        return context.match(identifier, input, head);
    }

    bool rules::label_name(const std::vector<Char> &input, context<Char> &context, int &head) {
        return context.match(simple_identifier, input, head);
    }

    bool rules::body_line(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;

        if(context.match(permitted_blanks, input, counter)
           && (context.match(labelled_line, input, counter) || context.match(line, input, counter))) {
            head = counter;
            return true;
        }

        context.backtrack(counter - head);
        return false;
    }

    bool rules::labelled_line(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;

        if(context.match(label_name, input, counter)
           && context.match(permitted_blanks, input, counter)
           && context.match(colon, input, counter)
           && context.match(permitted_blanks, input, counter)
           && context.match(line, input, counter)) {
            head = counter;
            return true;
        }

        context.backtrack(counter - head);
        return false;
    }

    bool rules::permitted_blanks(const std::vector<Char> &input, context<Char> &context, int &head) {
        while(context.match(blank, input, head)) {}
        return true;
    }

    bool rules::required_blanks(const std::vector<Char> &input, context<Char> &context, int &head) {
        if(context.match(blank, input, head)) {
            while(context.match(blank, input, head)) {}

            return true;
        }

        return false;
    }


    bool rules::zero_digit(const std::vector<Char> &input, context<Char> &context, int &head) {
        return context.match(constants::zero, input, head);
    }

    bool rules::nonzero_digit(const std::vector<Char> &input, context<Char> &context, int &head) {
        return context.match<Char>(
                {
                    constants::one, constants::two, constants::three,
                    constants::four, constants::five, constants::six,
                    constants::seven, constants::eight, constants::nine,
                }, input, head);
    }

    bool rules::sign(const std::vector<Char> &input, context<Char> &context, int &head) {
        context.match(constants::overbar, input, head);
        return true;
    }

    bool rules::decimal_integer(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;

        if(context.match(zero_digit, input, counter)) {}
        else if(context.match(sign, input, counter) && context.match(nonzero_digit, input, counter)) {
            while(context.match(digit, input, counter)) {}
        } else {
            context.backtrack(counter - head);
            return false;
        }

        head = counter;
        return true;
    }

    bool rules::decimal_rational(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;

        if(context.match(decimal_integer, input, counter)) {
            if(context.match(dot, input, counter)) {
                while(context.match(digit, input, counter)) {}
                if(!context.match(nonzero_digit, input, counter)) {
                    context.backtrack(counter - head);
                    return false;
                }
            }
        } else if(context.match(overbar, input, counter)
                  && context.match(zero_digit, input, counter)
                  && context.match(dot, input, counter)) {
            while(context.match(digit, input, counter)) {}
            if(!context.match(nonzero_digit, input, counter)) {
                context.backtrack(counter - head);
                return false;
            }
        } else {
            context.backtrack(counter - head);
            return false;
        }

        head = counter;
        return true;
    }

    bool rules::decimal_rational_row(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;
        int matched_decimal_rational = false;

        while(context.match(blank, input, counter)) {}
        while(context.match(decimal_rational, input, counter)) {
            matched_decimal_rational = true;
            while(context.match(blank, input, counter)) {}
        }

        if(matched_decimal_rational) {
            head = counter;
            return true;
        } else {
            context.backtrack(counter - head);
            return false;
        }
    }

    bool rules::minimal_decimal_exponential(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;

        if(context.match(zero_digit, input, counter)
           && context.match(exponent_marker, input, counter)
           && context.match(zero_digit, input, counter)) {}
        else if(context.match(sign, input, counter)) {

            int optional = counter;
            if(context.match(nonzero_digit, input, optional)
               && context.match(dot, input, optional)) {
                while(context.match(digit, input, optional)) {}

                counter = optional;
            } else {
                context.backtrack(optional - counter);
            }

            if(!(context.match(nonzero_digit, input, counter)
                 && context.match(exponent_marker, input, counter)
                 && context.match(decimal_integer, input, counter))) {
                context.backtrack(counter - head);
                return false;
            }
        } else {
            context.backtrack(counter - head);
            return false;
        }

        head = counter;
        return true;
    }

    bool rules::decimal_exponential(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;

        if(context.match(sign, input, counter)) {
            if(!context.match(nonzero_digit, input, counter)) {
                context.backtrack(counter - head);
                return false;
            }

            if(context.match(dot, input, counter)) {
                if(!context.match(digit, input, counter)) {
                    context.backtrack(counter - head);
                    return false;
                }

                while(context.match(digit, input, counter)) {}
            }

            if(!(context.match(exponent_marker, input, counter)
                 && context.match(decimal_integer, input, counter))) {
                context.backtrack(counter - head);
                return false;
            }
        } else if(context.match(zero_digit, input, counter)) {
            if(context.match(dot, input, counter)) {
                if(!context.match(zero_digit, input, counter)) {
                    context.backtrack(counter - head);
                    return false;
                }

                while(context.match(zero_digit, input, counter)) {}
            }

            if(!(context.match(exponent_marker, input, counter)
                 && context.match(zero_digit, input, counter))) {
                context.backtrack(counter - head);
                return false;
            }
        }

        head = counter;
        return true;
    }

    bool rules::decimal_exponential_row(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;
        int matched_decimal_rational = false;

        while(context.match(blank, input, counter)) {
            while(context.match(blank, input, counter)) {}

            if(context.match(decimal_exponential, input, counter)) {
                matched_decimal_rational = true;
            } else {
                break;
            }
        }

        if(matched_decimal_rational) {
            head = counter;
            return true;
        } else {
            context.backtrack(counter - head);
            return false;
        }
    }

    bool rules::fixed_decimal(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;

        if(context.match(decimal_integer, input, counter)) {}
        else if(context.match(zero_digit, input, counter)) {
            if(!context.match(dot, input, counter)) {
                context.backtrack(counter - head);
                return false;
            }

            if(!context.match(zero_digit, input, counter)) {
                context.backtrack(counter - head);
                return false;
            }

            while(context.match(zero_digit, input, counter)) {}
        } else if(context.match(sign, input, counter)) {
            if(!context.match(nonzero_digit, input, counter)) {

            }
        }

        head = counter;
        return true;
    }

    bool rules::statement(const std::vector<Token> &input, context<Token> &context, int &head) {
        context.match(branch_arrow, input, head);
        context.match(expression, input, head);
        return true;
    }

    bool rules::expression(const std::vector<Token> &input, context<Token> &context, int &head) {
        while(context.match(operation, input, head)) {}
        while(context.match(operand, input, head)) {
            if(!context.match(operation, input, head)) {
                return true;
            } else {
                while(context.match(operation, input, head)) {}
            }
        }

        return false;
    }

    bool rules::operation(const std::vector<Token> &input, context<Token> &context, int &head) {
        return context.match(assignment, input, head)
                || context.match(token_operation, input, head)
                || context.match(derived_function, input, head);
    }

    bool rules::token_operation(const std::vector<Token> &input, context<Token> &context, int &head) {
        return context.match(DefinedFunctionNameToken, input, head)
               || context.match(SystemFunctionNameToken, input, head);
    }

    bool rules::assignment(const std::vector<Token> &input, context<Token> &context, int &head) {
        int counter = head;

        if(context.match(token_variable, input, counter)) {
            context.match(index, input, counter);
            if(!context.match(assignment_arrow, input, counter)) {
                context.backtrack(counter - head);
                return false;
            }

            head = counter;
            return true;
        }

        return false;
    }

    bool rules::token_variable(const std::vector<Token> &input, context<Token> &context, int &head) {
        return context.match(VariableNameToken, input, head)
               || context.match(SystemVariableNameToken, input, head)
               || context.match(SharedVariableNameToken, input, head);
    }

    bool rules::derived_function(const std::vector<Token> &input, context<Token> &context, int &head) {
        int counter = head;
        if(context.match(small_circle, input, counter) || context.match(primitive_function, input, counter)) {
            if(context.match(token_dot, input, counter)) {
                if(!context.match(primitive_function, input, counter)) {
                    throw error(SyntaxError, "Expected a primitive function.", counter, input);
                }
            } else {
                context.match(axis_monadic_operator, input, counter);
                context.match(axis_specification, input, counter);
            }
        }
        else if(context.match(operand, input, counter) || context.match(function, input, counter)) {
            if(context.match(dyadic_operator, input, counter)) {
                if(!context.match(operand, input, counter) || context.match(function, input, counter)) {
                    throw error(SyntaxError, "Expected either an operand or another function.", counter, input);
                }
            }
            else if(context.match(monadic_operator, input, counter)) {}
            else {
                context.backtrack(counter - head);
                return false;
            }
        }
        else { return false; }

        head = counter;
        return true;
    }

    bool rules::token_dot(const std::vector<Token> &input, context<Token> &context, int &head) {
        return context.match(constants::dot, input, head);
    }

    bool rules::axis_specification(const std::vector<Token> &input, context<Token> &context, int &head) {
        int counter = head;

        if(context.match(left_axis_bracket, input, counter)) {
            int end = context.peek(constants::right_bracket, input, counter);
            if(end == -1) {
                throw error(SyntaxError, "Expected a matching closing bracket.", counter - 1, input);
            }
            if(!context.match(expression, input, counter)) {
                throw error(SyntaxError, "Expected an expression here.", counter - 1, input);
            }
            context.match(right_axis_bracket, input, counter);
            head = counter;
            return true;
        }

        return false;
    }

    bool rules::operand(const std::vector<Token> &input, context<Token> &context, int &head) {
        if(context.match(left_parenthesis, input, head)) {
            int counter = head;
            int end = context.peek(constants::right_parenthesis, input, counter);
            if(end == -1) {
                throw error(SyntaxError, "Expected a matching closing parenthesis.", counter - 1, input);
            }
            if(!context.match(expression, input, counter)) {
                throw error(SyntaxError, "Expected an expression here.", counter - 1, input);
            }
            context.match(right_parenthesis, input, counter);
            head = counter;
        }
        else if(context.match(token_operand, input, head)) {}
        else { return false; }

        context.match(index, input, head);

        return true;
    }

    bool rules::token_operand(const std::vector<Token> &input, context<Token> &context, int &head) {
        return context.match(ConstantToken, input, head)
                || context.match(VariableNameToken, input, head)
                || context.match(SharedVariableNameToken, input, head)
                || context.match(SystemVariableNameToken, input, head)
                || context.match(NiladicSystemFunctionNameToken, input, head)
                || context.match(NiladicDefinedFunctionNameToken, input, head);
    }

    bool rules::index(const std::vector<Token> &input, context<Token> &context, int &head) {
        int counter = head;
        if(context.match(left_index_bracket, input, counter)) {
            int end = context.peek(constants::right_bracket, input, counter);
            if(end != -1) {
                // Should match only until 'end'.
                context.match(expression, input, counter);
                while(context.match(index_separator, input, counter)) {
                    while(context.match(index_separator, input, counter)) {}
                    if(!context.match(expression, input, counter)) {
                        break;
                    }
                }

                context.match(right_index_bracket, input, counter);

                head = counter;
                return true;
            }

            throw kepler::error(SyntaxError, "Expected a matching end index bracket", counter + 1, input);
        }

        return false;
    }

    bool rules::primitive_function(const std::vector<Token> &input, context<Token> &context, int &head) {
        return context.match<Char>(
                {
                    constants::left_caret, constants::less_than_or_equal, constants::equal,
                    constants::greater_than_or_equal, constants::right_caret, constants::not_equal,
                    constants::down_caret, constants::up_caret, constants::bar,
                    constants::divide, constants::plus, constants::multiply,
                    constants::query, constants::epsilon, constants::rho,
                    constants::tilde, constants::up_arrow, constants::down_arrow,
                    constants::iota, constants::circle, constants::star,
                    constants::up_stile, constants::down_stile, constants::up_tack,
                    constants::down_tack, constants::stile, constants::back_slash,
                    constants::comma, constants::slash, constants::del_stile,
                    constants::delta_stile, constants::circle_stile, constants::circle_back_slash,
                    constants::circle_bar, constants::circle_star, constants::down_caret_tilde,
                    constants::up_caret_tilde, constants::quote_dot, constants::quad_divide,
                    constants::up_tack_jot, constants::down_tack_jot, constants::back_slash_bar,
                    constants::slash_bar, constants::comma_bar
                }, input, head);
    }

    bool rules::function(const std::vector<Token> &input, context<Token> &context, int &head) {
        return context.match(primitive_function, input, head)
               /*|| context.match(derived_function, input, head)*/
               || context.match(token_function, input, head);
    }

    bool rules::token_function(const std::vector<Token> &input, context<Token> &context, int &head) {
        return context.match(DefinedFunctionNameToken, input, head)
               || context.match(SystemFunctionNameToken, input, head);
    }

    bool rules::dyadic_operator(const std::vector<Token> &input, context<Token> &context, int &head) {
        return context.match(primitive_dyadic_operator, input, head)
               || context.match(defined_dyadic_operator, input, head);
    }

    bool rules::defined_dyadic_operator(const std::vector<Token> &input, context<Token> &context, int &head) {
        return context.match(DefinedDyadicOperatorNameToken, input, head);
    }

    bool rules::monadic_operator(const std::vector<Token> &input, context<Token> &context, int &head) {
        return context.match(primitive_monadic_operator, input, head)
               || context.match(defined_monadic_operator, input, head);
    }

    bool rules::defined_monadic_operator(const std::vector<Token> &input, context<Token> &context, int &head) {
        return context.match(DefinedMonadicOperatorNameToken, input, head);
    }

    bool rules::axis_monadic_operator(const std::vector<Token> &input, context<Token> &context, int &head) {
        return context.match(constants::slash, input, head)
               || context.match(constants::slash_bar, input, head)
               || context.match(constants::back_slash, input, head)
               || context.match(constants::back_slash_bar, input, head);
    }

    bool rules::primitive_monadic_operator(const std::vector<Token> &input, context<Token> &context, int &head) {
        if(context.match(axis_monadic_operator, input, head)) {}
        else if(context.match(diaeresis_tilde, input, head)) {}
        else { return false; }

        return true;
    }

    bool rules::primitive_dyadic_operator(const std::vector<Token> &input, context<Token> &context, int &head) {
        return context.match(diaeresis_jot, input, head);
    }

    bool rules::diaeresis_jot(const std::vector<Token> &input, context<Token> &context, int &head) {
        return context.match(constants::diaeresis_jot, input, head);
    }

    bool rules::diaeresis_tilde(const std::vector<Token> &input, context<Token> &context, int &head) {
        return context.match(constants::diaeresis_tilde, input, head);
    }

    bool rules::left_parenthesis(const std::vector<Token> &input, context<Token> &context, int &head) {
        return context.match(constants::left_parenthesis, input, head);
    }

    bool rules::right_parenthesis(const std::vector<Token> &input, context<Token> &context, int &head) {
        return context.match(constants::right_parenthesis, input, head);
    }

    bool rules::left_axis_bracket(const std::vector<Token> &input, context<Token> &context, int &head) {
        return context.match(constants::left_bracket, input, head);
    }

    bool rules::right_axis_bracket(const std::vector<Token> &input, context<Token> &context, int &head) {
        return context.match(constants::right_bracket, input, head);
    }

    bool rules::branch_arrow(const std::vector<Token> &input, context<Token> &context, int &head) {
        return context.match(constants::right_arrow, input, head);
    }

    bool rules::assignment_arrow(const std::vector<Token> &input, context<Token> &context, int &head) {
        return context.match(constants::left_arrow, input, head);
    }

    bool rules::left_index_bracket(const std::vector<Token> &input, context<Token> &context, int &head) {
        return context.match(constants::left_bracket, input, head);
    }

    bool rules::right_index_bracket(const std::vector<Token> &input, context<Token> &context, int &head) {
        return context.match(constants::right_bracket, input, head);
    }

    bool rules::index_separator(const std::vector<Token> &input, context<Token> &context, int &head) {
        return context.match(constants::semicolon, input, head);
    }

    bool rules::small_circle(const std::vector<Token> &input, context<Token> &context, int &head) {
        return context.match(constants::jot, input, head);
    }
















    bool rules::line(const std::vector<Char> &input, context<Char> &context, int &head) {
        if(context.match(identifier, input, head));
        else if(context.match(numeric_literal, input, head)) {}

        while(context.match(primitive, input, head)
              || context.match(character_literal, input, head)
              || context.match(space, input, head)
              || context.match(statement_separator, input, head)) {
            if(context.match(identifier, input, head));
            else if(context.match(numeric_literal, input, head)) {}
        }
        context.match(comment, input, head);
        return true;
    }

    bool rules::identifier(const std::vector<Char> &input, context<Char> &context, int &head) {
        if(context.match(simple_identifier, input, head)) {}
        else if(context.match(distinguished_identifier, input, head)) {}
        else { return false; }

        return true;
    }

    bool rules::simple_identifier(const std::vector<Char> &input, context<Char> &context, int &head) {
        if(context.match(literal_identifier, input, head)) {}
        else if(context.match(direct_identifier, input, head)) {}
        else { return false; }

        return true;
    }

    bool rules::literal_identifier(const std::vector<Char> &input, context<Char> &context, int &head) {
        if(context.match(letter, input, head)) {
            while(context.match(letter, input, head)
                    || context.match(digit, input, head)
                    || context.match(underbar, input, head)
                    || context.match(overbar, input, head)) {}

            return true;
        }

        return false;
    }

    bool rules::direct_identifier(const std::vector<Char> &input, context<Char> &context, int &head) {
        if(context.match(constants::alpha, input, head)) {}
        else if(context.match(constants::omega, input, head)) {}
        else { return false; }

        return true;
    }

    bool rules::distinguished_identifier(const std::vector<Char> &input, context<Char>& context, int &head) {
        if(context.match(quote_quad, input, head)) {
            return true;
        } else if(context.match(quad, input, head)) {
            while(context.match(letter, input, head) || context.match(digit, input, head)) {}
            return true;
        }

        return false;
    }

    bool rules::numeric_literal(const std::vector<Char> &input, context<Char> &context, int &head) {
        if(context.match(numeric_scalar_literal, input, head)) {
            int counter = head;

            while(context.match(blank, input, counter)) {
                while(context.match(blank, input, counter)) {}

                if(context.match(numeric_scalar_literal, input, counter)) {
                    head = counter;
                } else {
                    context.backtrack(counter - head);
                }
            }

            return true;
        }

        return false;
    }

    bool rules::real_scalar_literal(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;

        context.match(overbar, input, counter);

        if(context.match(digit, input, counter)) {
            while(context.match(digit, input, counter)) {}
            context.match(dot, input, counter);
            while(context.match(digit, input, counter)) {}
        } else {
            if(!context.match(dot, input, counter)) {
                return false;
            }
            if(!context.match(digit, input, counter)) {
                context.backtrack(counter - head);
                return false;
            }
            while(context.match(digit, input, counter)) {}
        }

        context.match(exponent, input, counter);

        head = counter;
        return true;
    }

    bool rules::exponent(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;
        if(context.match(exponent_marker, input, counter)) {
            context.match(overbar, input, counter);

            if(!context.match(digit, input, counter)) {
                throw error(SyntaxError, "Expected at least one digit", counter, input);
            }

            while(context.match(digit, input, counter)) {}
            head = counter;
            return true;
        }

        return false;
    }

    bool rules::numeric_scalar_literal(const std::vector<Char> &input, context<Char> &context, int &head) {
        if(context.match(real_scalar_literal, input, head)) {
            context.match(imaginary_part, input, head);

            return true;
        }

        return false;
    }

    bool rules::imaginary_part(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;
        if(context.match(complex_marker, input, counter)) {
            if(context.match(real_scalar_literal, input, counter)) {
                head = counter;
                return true;
            }

            throw error(SyntaxError, "Expected a real scalar", counter, input);
        }

        return false;
    }

    bool rules::character_literal(const std::vector<Char> &input, context<Char>& context, int &head) {
        int counter = head;
        if(context.match(quote, input, counter)) {
            int end = context.peek(constants::quote, input, counter);
            if(end != -1) {
                // Should match only until 'end'.
                while(context.match(nonquote, input, counter)) {}
                context.match(quote, input, counter);

                head = counter;
                return true;
            }

            throw error(SyntaxError, "Expected a matching end quote", counter - 1, input);
        }

        return false;
    }

    bool rules::comment(const std::vector<Char> &input, context<Char>& context, int &head) {
        if(context.match(lamp, input, head)) {
            while(context.match(any, input, head)) {}
            return true;
        }
        return false;
    }

    bool rules::any(const std::vector<Char> &input, context<Char> &context, int &head) {
        if(context.match(quote, input, head)) {}
        else if(context.match(nonquote, input, head)) {}
        else { return false; }

        return true;
    }

    bool rules::primitive(const std::vector<Char> &input, context<Char> &context, int &head) {
        return context.match(ideogram, input, head);
    }

    bool rules::space(const std::vector<Char> &input, context<Char> &context, int &head) {
        return context.match(constants::blank, input, head);
    }

    bool rules::nonquote(const std::vector<Char> &input, context<Char>& context, int &head) {
        if(context.match(ideogram, input, head)) {}
        else if(context.match(digit, input, head)) {}
        else if(context.match(blank, input, head)) {}
        else if(context.match(letter, input, head)) {}
        else if(context.match(lamp, input, head)) {}
        else if(context.match(del, input, head)) {}
        else if(context.match(del_tilde, input, head)) {}
        else if(context.match(quad, input, head)) {}
        else if(context.match(quote_quad, input, head)) {}
        else if(context.match(diamond, input, head)) {}
        else { return false; }

        return true;
    }

    bool rules::statement_separator(const std::vector<Char> &input, context<Char> &context, int &head) {
        return context.match(diamond, input, head);
    }

    bool rules::letter(const std::vector<Char> &input, context<Char>& context, int &head) {
        return context.match<Char>(
                {
                    constants::A, constants::B, constants::C,
                    constants::D, constants::E, constants::F,
                    constants::G, constants::H, constants::I,
                    constants::J, constants::K, constants::L,
                    constants::M, constants::N, constants::O,
                    constants::P, constants::Q, constants::R,
                    constants::S, constants::T, constants::U,
                    constants::V, constants::W, constants::X,
                    constants::Y, constants::Z,
                    constants::a, constants::b, constants::c,
                    constants::d, constants::e, constants::f,
                    constants::g, constants::h, constants::i,
                    constants::j, constants::k, constants::l,
                    constants::m, constants::n, constants::o,
                    constants::p, constants::q, constants::r,
                    constants::s, constants::t, constants::u,
                    constants::v, constants::w, constants::x,
                    constants::y, constants::z
                }, input, head);
    }

    bool rules::digit(const std::vector<Char> &input, context<Char> &context, int &head) {
        return context.match<Char>(
                {
                    constants::one, constants::two, constants::three,
                    constants::four, constants::five, constants::six,
                    constants::seven, constants::eight, constants::nine,
                    constants::zero
                }, input, head);
    }

    bool rules::ideogram(const std::vector<Char> &input, context<Char>& context, int &head) {
        return context.match<Char>(
                {
                    constants::diaeresis, constants::overbar, constants::left_caret,
                    constants::less_than_or_equal, constants::equal, constants::greater_than_or_equal,
                    constants::right_caret, constants::not_equal, constants::down_caret,
                    constants::up_caret, constants::bar, constants::divide,
                    constants::plus, constants::multiply, constants::query,
                    constants::omega, constants::epsilon, constants::rho,
                    constants::tilde, constants::up_arrow, constants::down_arrow,
                    constants::iota, constants::circle, constants::star,
                    constants::right_arrow, constants::left_arrow, constants::alpha,
                    constants::up_stile, constants::down_stile, constants::underbar,
                    constants::jot, constants::left_parenthesis, constants::right_parenthesis,
                    constants::left_bracket, constants::right_bracket, constants::left_shoe,
                    constants::right_shoe, constants::up_shoe, constants::down_shoe,
                    constants::up_tack, constants::down_tack, constants::stile,
                    constants::semicolon, constants::colon, constants::back_slash,
                    constants::comma, constants::dot, constants::slash,
                    constants::del_stile, constants::delta_stile, constants::circle_stile,
                    constants::circle_back_slash, constants::circle_bar, constants::circle_star,
                    constants::down_caret_tilde, constants::up_caret_tilde, constants::quote_dot,
                    constants::quote_quad, constants::up_tack_jot, constants::down_tack_jot,
                    constants::back_slash_bar, constants::slash_bar, constants::diaeresis_jot,
                    constants::comma_bar, constants::diaeresis_tilde, constants::left_brace,
                    constants::right_brace, constants::right_tack, constants::left_tack,
                    constants::dollar_sign,
                }, input, head);
    }

    bool rules::quote(const std::vector<Char> &input, context<Char>& context, int &head) {
        return context.match(constants::quote, input, head);
    }

    bool rules::exponent_marker(const std::vector<Char> &input, context<Char>& context, int &head) {
        return context.match(constants::E, input, head);
    }

    bool rules::complex_marker(const std::vector<Char> &input, context<Char>& context, int &head) {
        return context.match(constants::J, input, head);
    }

    bool rules::dot(const std::vector<Char> &input, context<Char>& context, int &head) {
        return context.match(constants::dot, input, head);
    }

    bool rules::underbar(const std::vector<Char> &input, context<Char>& context, int &head) {
        return context.match(constants::underbar, input, head);
    }

    bool rules::overbar(const std::vector<Char> &input, context<Char>& context, int &head) {
        return context.match(constants::overbar, input, head);
    }

    bool rules::blank(const std::vector<Char> &input, context<Char>& context, int &head) {
        return context.match(constants::blank, input, head);
    }

    bool rules::del(const std::vector<Char>& input, context<Char>& context, int &head) {
        return context.match(constants::del, input, head);
    }

    bool rules::del_tilde(const std::vector<Char>& input, context<Char>& context, int &head) {
        return context.match(constants::del_tilde, input, head);
    }

    bool rules::lamp(const std::vector<Char>& input, context<Char>& context, int &head) {
        return context.match(constants::up_shoe_jot, input, head);
    }

    bool rules::quad(const std::vector<Char> &input, context<Char>& context, int &head) {
        return context.match(constants::quad, input, head);
    }

    bool rules::quote_quad(const std::vector<Char> &input, context<Char>& context, int &head) {
        return context.match(constants::quote_quad, input, head);
    }

    bool rules::diamond(const std::vector<Char> &input, context<Char>& context, int &head) {
        return context.match(constants::diamond, input, head);
    }
};