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
#include "matcher.h"
#include "core/evaluation/numeric.h"

namespace kepler::grammar {
    template <>
    template <>
    bool context<Char>::comparator(const Char &atom, const Char &comp) {
        return atom == comp;
    }

    template <>
    template <>
    bool context<Token>::comparator(const Token &atom, const Char &comp) {
        return atom.contains<Char>() && atom.get_content<Char>() == comp;
    }

    template <>
    template <>
    bool context<Token>::comparator(const Token &atom, const TokenClass &comp) {
        return atom.token_class == comp;
    }


    void generic_char_context::backtrack(int amount) {}

    void generic_char_context::apply_semantic_action(rule_type rule, const std::vector<Char> &input, const int &start,
                                                     const int &end) {}



    void lexer_context::backtrack(int amount) {
        content.resize(content.size() - amount);
    }

    void lexer_context::append(const std::vector<Char>& input, const int& start, const int& end) {
        std::copy(input.begin() + start, input.begin() + end, std::back_inserter(content));
    }

    void lexer_context::clear() {
        content.clear();
    }

    void lexer_context::create(TokenClass cl) {
        if(content.size() == 1) {
            output.emplace_back(cl, content.front());
        } else {
            output.emplace_back(cl, content);
        }
        content.clear();
    }

    void lexer_context::apply_semantic_action(rule_type rule, const std::vector<Char> &input, const int &start, const int &end) {
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
        } else if(rule == rules::statement_separator) {
            create(StatementSeparatorToken);
        }
    }



    void parser_context::backtrack(int amount) {
        output.resize(output.size() - amount);
    }

    void parser_context::accept(const std::vector<Token> &input, const int &head) {
        output.emplace_back(input[head]);
    }

    void parser_context::set_class(TokenClass token_class) {
        if(output.empty()) return;
        output.back().token_class = token_class;
    }

    void parser_context::apply_semantic_action(rule_type rule, const std::vector<Token> &input, const int &head, const int& end) {
        if(rule == rules::token_operand
           || rule == rules::token_variable
           || rule == rules::token_operation
           || rule == rules::token_dot
           || rule == rules::token_function
           || rule == rules::defined_dyadic_operator
           || rule == rules::defined_monadic_operator)
        {
            accept(input, head);
        } else if(rule == rules::primitive_function) {
            accept(input, head);
            set_class(PrimitiveFunctionToken);
        } else if(rule == rules::dyadic_operator) {
            set_class(DyadicOperatorToken);
        } else if(rule == rules::monadic_operator) {
            set_class(MonadicOperatorToken);
        } else if(rule == rules::axis_monadic_operator) {
            accept(input, head);
            set_class(AxisMonadicOperatorToken);
        } else if(rule == rules::primitive_monadic_operator) {
            set_class(PrimitiveMonadicOperatorToken);
        } else if(rule == rules::primitive_dyadic_operator) {
            set_class(PrimitiveDyadicOperatorToken);
        } else if(rule == rules::diaeresis_jot) {
            accept(input, head);
        } else if(rule == rules::diaeresis_tilde) {
            accept(input, head);
        } else if(rule == rules::left_parenthesis) {
            accept(input, head);
            set_class(LeftParenthesisToken);
        } else if(rule == rules::right_parenthesis) {
            accept(input, head);
            set_class(RightParenthesisToken);
        } else if(rule == rules::left_axis_bracket) {
            accept(input, head);
            set_class(LeftAxisBracketToken);
        } else if(rule == rules::right_axis_bracket) {
            accept(input, head);
            set_class(RightAxisBracketToken);
        } else if(rule == rules::branch_arrow) {
            accept(input, head);
            set_class(BranchArrowToken);
        } else if(rule == rules::assignment_arrow) {
            accept(input, head);
            set_class(AssignmentArrowToken);
        } else if(rule == rules::left_index_bracket) {
            accept(input, head);
            set_class(LeftIndexBracketToken);
        } else if(rule == rules::right_index_bracket) {
            accept(input, head);
            set_class(RightIndexBracketToken);
        } else if(rule == rules::index_separator) {
            accept(input, head);
            set_class(IndexSeparatorToken);
        } else if(rule == rules::small_circle) {
            accept(input, head);
            set_class(SmallCircleToken);
        }
    }

    void function_context::backtrack(int amount) {

    }

    void function_context::apply_semantic_action(rule_type rule, const std::vector<Char> &input, const int &start,
                                                 const int &end) {
        if(rule == rules::creation_request) {
            request.clear();
            std::copy(input.begin() + start, input.begin() + end, std::back_inserter(request));
        } else if(rule == rules::function_name) {
            identifier = {SimpleIdentifierToken, {input.begin() + start, input.begin() + end}};
        } else if(rule == rules::subject_function) {
            identifier = {SimpleIdentifierToken, {input.begin() + start, input.begin() + end}};
        } else if(rule == rules::initial_request) {
            request.clear();
            std::copy(input.begin() + start, input.begin() + end, std::back_inserter(request));
        }
    }

    function_editing_context::function_editing_context(Token& identifier_, Context &context_) : identifier(identifier_), context(context_) {}

    void function_editing_context::backtrack(int amount) {

    }

    void
    function_editing_context::apply_semantic_action(rule_type rule, const std::vector<Char> &input, const int &start, const int &end) {
        DefinedFunction& function = context.current_function.get();

        if(rule == rules::positioning_request) {
            List<Char> char_list = {input.begin() + start, input.begin() + end};
            Number number = number_from_characters(char_list);
            if(algorithms::less_than(number, 0)) {
                throw kepler::error(DefinitionError, "Line number cannot be negative.");
            }
            if(algorithms::greater_than(number, constants::definition_line_limit)) {
                throw kepler::error(LimitError, "Line number cannot be greater than " + std::to_string(constants::definition_line_limit) + ".");
            }

            context.current_line_number = number;
        } else if(rule == rules::deletion_request) {
            List<Char> char_list = {input.begin() + start, input.begin() + end};
            Number number = number_from_characters(char_list);

            if(!algorithms::greater_than(number, 0)) {
                throw kepler::error(DefinitionError, "Line number must be positive.");
            }
            if(algorithms::greater_than(number, constants::definition_line_limit)) {
                throw kepler::error(LimitError, "Line number cannot be greater than " + std::to_string(constants::definition_line_limit) + ".");
            }

            context.current_line_number = number;

            // TODO: Delete the row associated with 'number' in
            //  canonical-representation, current-stop-vector,
            //  and current-trace-vector.
        } else if(rule == rules::display_request) {
            // TODO: Display the function.
        } else if(rule == rules::function_line) {
            List<Char> char_list = {input.begin() + start, input.begin() + end};

            bool is_all_blanks = Matcher<Char, grammar::generic_char_context>(char_list).match(rules::permitted_blanks);

            if(!is_all_blanks) {
                if(context.current_line_number == 0.0) {
                    bool is_header = Matcher<Char, grammar::generic_char_context>(char_list).match(rules::header_line);
                    if(!is_header) throw kepler::error(DefinitionError, "Line 0 must be a function header.");
                }

                function.canonical_representation[(int)context.current_line_number.real()] = char_list;

            }
        } else if(rule == rules::end_definition) {
            std::cout << "End definition" << std::endl;
            // TODO: Check if properly defined.
            // TODO: Check if repeated argument
        }
    }
};