//
// Copyright 2022 Nikolaj Banke Jensen.
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
#include "rules.h"
#include "config.h"
#include "../characters.h"
#include <boost/fusion/include/std_tuple.hpp>
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>

namespace kepler {
    namespace parser {
        namespace x3 = boost::spirit::x3;

        namespace parsers {
            struct visitor : public boost::static_visitor<> {
            private:
                TokenClass tokenClass;
                Token::optional_content_type content;

            public:
                visitor(TokenClass tokenClass_, Token::optional_content_type content_) : tokenClass(tokenClass_), content(content_) {}

                void operator()(boost::variant<List<Token>, Token>& input) {
                    //boost::apply_visitor(*this, input);
                }

                void operator()(List<Token>& list) const {
                    // Shouldn't do anything here, as this should never happen.
                }

                void operator()(x3::unused_type& something) const {

                }

                void operator()(Token& token) const {
                    token.tokenClass = tokenClass;
                    token.content = content;
                }
            };

            struct token : x3::parser<token> {
            private:
                TokenClass token_class;
                Token::optional_content_type content;

            public:
                using attribute_type = Token;

                token(const Token::content_type& content_) : token_class(PrimitiveToken), content(content_) {}
                explicit token(TokenClass token_class_ = PrimitiveToken) : token_class(token_class_) {}

                template <typename Iterator, typename Context, typename RContext, typename Attribute>
                bool parse(Iterator &first, Iterator const& last, Context const& context, RContext const& rContext, Attribute& attr) const {
                    x3::skip_over(first, last, context);

                    bool matched = (*first).tokenClass == token_class;

                    if(content && (*first).content) {
                        matched = matched && (*first).content == content;
                    }

                    if(matched) {
                        x3::traits::move_to(*first, attr);

                        ++first;
                        return true;
                    }

                    return false;
                }
            };

            struct set_class {
            private:
                TokenClass token_class;

            public:
                set_class(TokenClass token_class_) : token_class(token_class_) {}

                template <typename Context>
                void operator()(Context& context) const {
                    x3::_val(context) = x3::_attr(context);
                    x3::_val(context).tokenClass = token_class;
                }
            };
        };

        namespace rules {
            using parsers::token;
            using parsers::set_class;
            using kepler::Token;
            using kepler::List;

            namespace characters = kepler::characters;

            template <typename T = x3::unused_type>
            auto as(auto p, char const* name = typeid(decltype(p)).name()) {
                return x3::rule<struct _, T>{name} = p;
            }

            auto as_list(auto p) {
                return x3::repeat(1)[p];
            }

            auto const small_circle = x3::rule<struct small_circle, Token, true>{"small_circle"} = token(characters::jot);
            auto const index_separator = x3::rule<struct index_separator, Token, true>{"index_separator"} = token(characters::semicolon);
            auto const right_index_bracket = x3::rule<struct right_index_bracket, Token, true>{"right_index_bracket"} = token(characters::right_bracket);
            auto const left_index_bracket = x3::rule<struct left_index_bracket, Token, true>{"left_index_bracket"} = token(characters::left_bracket);
            auto const assignment_arrow = x3::rule<struct assignment_arrow, Token, true>{"assignment_arrow"} = token(characters::left_arrow);
            auto const branch_arrow = x3::rule<struct branch_arrow, Token, true>{"branch_arrow"} = token(characters::right_arrow);
            auto const right_axis_bracket = x3::rule<struct right_axis_bracket, Token, true>{"right_axis_bracket"} = token(characters::right_bracket);
            auto const left_axis_bracket = x3::rule<struct left_axis_bracket, Token, true>{"left_axis_bracket"} = token(characters::left_bracket);
            auto const right_parenthesis = x3::rule<struct right_parenthesis, Token, true>{"right_parenthesis"} = token(characters::right_parenthesis);
            auto const left_parenthesis = x3::rule<struct left_parenthesis, Token, true>{"left_parenthesis"} = token(characters::left_parenthesis);
            auto const diaeresis_tilde = x3::rule<struct diaeresis_tilde, Token, true>{"diaeresis_tilde"} = token(characters::diaeresis_tilde);
            auto const diaeresis_jot = x3::rule<struct diaeresis_jot, Token, true>{"diaeresis_jot"} = token(characters::diaeresis_jot);



            auto const primitive_dyadic_operator = x3::rule<struct primitive_dyadic_operator, Token, true>{"primitive_dyadic_operator"} = diaeresis_jot;
            auto const axis_monadic_operator = x3::rule<struct axis_monadic_operator, Token, true>{"axis_monadic_operator"} = token(characters::slash) | token(characters::slash_bar) | token(characters::back_slash) | token(characters::back_slash_bar);
            auto const primitive_monadic_operator = x3::rule<struct primitive_monadic_operator, Token, true>{"primitive_monadic_operator"} = axis_monadic_operator | diaeresis_tilde;
            auto const monadic_operator = x3::rule<struct monadic_operator, Token, true>{"monadic_operator"} = (primitive_monadic_operator | token(DefinedMonadicOperatorNameToken));
            auto const dyadic_operator = x3::rule<struct dyadic_operator, Token, true>{"dyadic_operator"} = (primitive_dyadic_operator | token(DefinedDyadicOperatorNameToken));

            auto const primitive_function = x3::rule<struct primitive_function, Token, true>{"primitive_function"}
                = (token(characters::left_caret) | token(characters::less_than_or_equal) | token(characters::equal) | token(characters::greater_than_or_equal) | token(characters::right_caret) | token(characters::not_equal) | token(characters::down_caret) | token(characters::up_caret) | token(characters::bar) | token(characters::divide) | token(characters::plus)
                | token(characters::multiply) | token(characters::query) | token(characters::epsilon) | token(characters::rho) | token(characters::tilde) | token(characters::up_arrow) | token(characters::down_arrow) | token(characters::iota) | token(characters::circle) | token(characters::star) | token(characters::up_stile)
                | token(characters::down_stile) | token(characters::up_tack) | token(characters::down_tack) | token(characters::stile) | token(characters::back_slash) | token(characters::comma) | token(characters::slash) | token(characters::del_stile) | token(characters::delta_stile) | token(characters::circle_stile) | token(characters::circle_backslash)
                | token(characters::circle_bar) | token(characters::circle_star) | token(characters::down_caret_tilde) | token(characters::up_caret_tilde) | token(characters::quote_dot) | token(characters::quote_quad) | token(characters::up_tack_jot) | token(characters::down_tack_jot) | token(characters::back_slash_bar) | token(characters::slash_bar) | token(characters::comma_bar));

            struct statement_class;
            x3::rule<statement_class, List<Token>> statement = "statement";
            struct expression;
            x3::rule<expression, List<Token>> expression = "expression";
            struct operation;
            x3::rule<operation, List<Token>> operation = "operation";
            struct assignment;
            x3::rule<assignment, List<Token>> assignment = "assignment";
            struct axis_specification;
            x3::rule<axis_specification, List<Token>> axis_specification = "axis_specification";
            struct operand;
            x3::rule<operand, List<Token>> operand = "operand";
            struct index;
            x3::rule<index, List<Token>> index = "index";
            struct derived_function;
            x3::rule<derived_function, List<Token>> derived_function = "derived_function";
            struct function;
            x3::rule<function, List<Token>> function = "function";

            // F←{⍳⍵}
            // G←{⍴⍵}
            // G F 10 => 102+3

            auto const statement_def = -branch_arrow >> -expression;
            auto const expression_def = x3::raw[*operation >> operand >> *(+operation >> operand)];
            auto const assignment_def = x3::raw[token(VariableNameToken) >> -index >> assignment_arrow];
            auto const axis_specification_def = left_axis_bracket >> expression >> right_axis_bracket;
            auto const index_def = left_axis_bracket >> *index_separator >> (expression >> *(index_separator >> expression)) >> *index_separator >> right_axis_bracket;
            auto const operation_def = assignment | as_list(token(DefinedFunctionNameToken) | token(SystemFunctionNameToken)) | derived_function;
            auto const operand_def =
                    (left_parenthesis >> expression >> right_parenthesis)
                    | as_list(token(ConstantToken)
                    | token(VariableNameToken)
                    | token(SharedVariableNameToken)
                    | token(SystemVariableNameToken)
                    | token(NiladicSystemFunctionNameToken)
                    | token(NiladicDefinedFunctionNameToken)) >> -index;

            auto const function_def = as_list(primitive_function | token(DefinedFunctionNameToken) | token(SystemFunctionNameToken)) /*| derived_function*/;

            auto const derived_function_def =
                    as_list((small_circle | primitive_function) >> token(characters::dot) >> primitive_function)
                    | as_list(primitive_function >> -axis_monadic_operator >> -axis_specification)
                    | as_list((function | operand) >> token(DefinedDyadicOperatorNameToken) >> (function | operand))
                    | as_list((function | operand) >> token(DefinedMonadicOperatorNameToken));

            BOOST_SPIRIT_DEFINE(statement, expression, index, axis_specification, operation, assignment, operand, derived_function, function)
        };

        rules::statement_type const& statement() {
            return rules::statement;
        }
    };
};