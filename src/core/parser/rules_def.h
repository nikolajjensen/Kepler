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
                    boost::apply_visitor(*this, input);
                }

                void operator()(List<Token>& list) const {
                    // Shouldn't do anything here, as this should never happen.
                }

                void operator()(x3::unused_type) const {

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

                token(Token::content_type content_) : token_class(PrimitiveToken), content(content_) {}
                token(TokenClass token_class_ = PrimitiveToken) : token_class(token_class_) {}

                template <typename Iterator, typename Context, typename RContext, typename Attribute>
                bool parse(Iterator &first, Iterator const& last, Context const& context, RContext const& rContext, Attribute& attr) const {
                    if(first == last) {
                        return false;
                    }

                    bool matched = (*first).tokenClass == token_class;

                    if(matched && content && (*first).content) {
                        matched = matched && (*first).content == content;
                    }

                    if(matched) {
                        //if (Token* token = boost::get<Token>(&attr)) {
                        //    token->tokenClass = (*first).tokenClass;
                        //    token->content = (*first).content;
                        //}


                        //Token& token = boost::get<Token>(attr);
                        //token.tokenClass = (*first).tokenClass;
                        //token.content = (*first).content;

                        //attr.tokenClass = (*first).tokenClass;
                        //attr.content = (*first).content;
                        //boost::variant<List<Token>, Token> input;
                        //Token t;
                        //List<Token> lt;
                        visitor v((*first).tokenClass, (*first).content);
                        v(attr);
                        //boost::apply_visitor(v, attr);

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

            struct clear : x3::parser<clear> {
            public:
                using attribute_type = x3::unused_type;

                template <typename Iterator, typename Context, typename RContext, typename Attribute>
                bool parse(Iterator &first, Iterator const& last, Context const& context, RContext const& rContext, Attribute& attr) const {
                    //x3::_val(rContext).clear();

                    return true;
                }
            };
        };

        namespace rules {
            using parsers::token;
            using parsers::set_class;
            using parsers::clear;
            using kepler::Token;
            using kepler::List;

            template <typename T = x3::unused_type>
            auto as(auto p, char const* name = typeid(decltype(p)).name()) {
                return x3::rule<struct _, T>{name} = p;
            }

            auto as_list(auto p) {
                return x3::repeat(1)[p];
            }

            auto const small_circle = x3::rule<struct small_circle_class, Token>{"small_circle"} = token(U'∘')[set_class(SmallCircleToken)];
            auto const index_separator = x3::rule<struct index_separator, Token>{"index_separator"} = token(U';')[set_class(IndexSeparatorToken)];
            auto const right_index_bracket = x3::rule<struct right_index_bracket, Token>{"right_index_bracket"} = token(U']')[set_class(RightIndexBracketToken)];
            auto const left_index_bracket = x3::rule<struct left_index_bracket, Token>{"left_index_bracket"} = token(U'[')[set_class(LeftIndexBracketToken)];
            auto const assignment_arrow = x3::rule<struct assignment_arrow, Token>{"assignment_arrow"} = token(U'←')[set_class(AssignmentArrowToken)];
            auto const branch_arrow = x3::rule<struct branch_arrow, Token>{"branch_arrow"} = token(U'→')[set_class(BranchArrowToken)];
            auto const right_axis_bracket = x3::rule<struct right_axis_bracket, Token>{"right_axis_bracket"} = token(U']')[set_class(RightAxisBracketToken)];
            auto const left_axis_bracket = x3::rule<struct left_axis_bracket, Token>{"left_axis_bracket"} = token(U'[')[set_class(LeftAxisBracketToken)];
            auto const right_parenthesis = x3::rule<struct right_parenthesis, Token>{"right_parenthesis"} = token(U')')[set_class(RightParenthesisToken)];
            auto const left_parenthesis = x3::rule<struct left_parenthesis, Token>{"left_parenthesis"} = token(U'(')[set_class(LeftParenthesisToken)];
            auto const diaeresis_tilde = x3::rule<struct diaeresis_tilde, Token>{"diaeresis_tilde"} = token(U'⍨');
            auto const diaeresis_jot = x3::rule<struct diaeresis_jot, Token>{"diaeresis_jot"} = token(U'⍤');



            auto const primitive_dyadic_operator = x3::rule<struct primitive_dyadic_operator, Token>{"primitive_dyadic_operator"} = diaeresis_jot;
            auto const axis_monadic_operator = x3::rule<struct axis_monadic_operator, Token>{"axis_monadic_operator"} = token(U'/') | token(U'⌿') | token(U'\\') | token(U'⍀');
            auto const primitive_monadic_operator = x3::rule<struct primitive_monadic_operator, Token>{"primitive_monadic_operator"} = axis_monadic_operator | diaeresis_tilde;
            auto const monadic_operator = x3::rule<struct monadic_operator, Token>{"monadic_operator"} = (primitive_monadic_operator | token(DefinedMonadicOperatorNameToken))[set_class(MonadicOperatorToken)];
            auto const dyadic_operator = x3::rule<struct dyadic_operator, Token>{"dyadic_operator"} = (primitive_dyadic_operator | token(DefinedDyadicOperatorNameToken))[set_class(DyadicOperatorToken)];

            auto const primitive_function = x3::rule<struct primitive_function, Token>{"primitive_function"}
                = ((token(U'<') | token(U'≤') | token(U'=') | token(U'≥') | token(U'>') | token(U'≠') | token(U'∨') | token(U'∧') | token(U'-') | token(U'÷') | token(U'+')[set_class(PrimitiveFunctionToken)])
                | (token(U'×') | token(U'?') | token(U'∊') | token(U'⍴') | token(U'~') | token(U'↑') | token(U'↓') | token(U'⍳') | token(U'○') | token(U'*') | token(U'⌈')[set_class(PrimitiveFunctionToken)])
                | (token(U'⌊') | token(U'⊥') | token(U'⊤') | token(U'|') | token(U'\\') | token(U',') | token(U'/') | token(U'⍒') | token(U'⍋') | token(U'⌽') | token(U'⍉')[set_class(PrimitiveFunctionToken)])
                | (token(U'⊖') | token(U'⍟') | token(U'⍱') | token(U'⍲') | token(U'!') | token(U'⌹') | token(U'⍎') | token(U'⍕') | token(U'⍀') | token(U'⌿') | token(U'⍪')[set_class(PrimitiveFunctionToken)]));

            struct index;
            x3::rule<index, List<Token>> index = "index";

            struct expression;
            x3::rule<expression, List<Token>> expression = "expression";

            struct derived_function;
            x3::rule<derived_function, List<Token>> derived_function = "derived_function";

            struct assignment;
            x3::rule<assignment, List<Token>> assignment = "assignment";

            struct function;
            x3::rule<function, List<Token>> function = "function";

            struct axis_specification;
            x3::rule<axis_specification, List<Token>> axis_specification = "axis_specification";

            struct operation;
            x3::rule<operation, List<Token>> operation = "operation";

            struct operand;
            x3::rule<operand, List<Token>> operand = "operand";

            auto const assignment_def
                = (token(VariableNameToken) | token(SystemVariableNameToken) | token(SharedVariableNameToken))
                        >> -index
                        >> assignment_arrow;

            auto const function_def
                = as_list(primitive_function) | derived_function | token(DefinedFunctionNameToken) | token(SystemFunctionNameToken);

            auto const index_def
                = left_index_bracket >> -expression >> right_index_bracket;

            auto const operand_def
                = ((left_parenthesis >> expression >> right_parenthesis)
                        | token(ConstantToken)
                        | token(VariableNameToken)
                        | token(SharedVariableNameToken)
                        | token(SystemVariableNameToken)
                        | token(NiladicSystemFunctionNameToken)
                        | token(NiladicDefinedFunctionNameToken)
                    ) >> -index;

            auto const axis_specification_def
                = left_axis_bracket >> expression >> right_axis_bracket;

            auto const derived_function_def
                = as_list((small_circle | primitive_function) >> token(U'.') >> primitive_function)
                        | (primitive_function >> -axis_monadic_operator >> -axis_specification)
                        //| ((function | operand) >> token(DefinedDyadicOperatorNameToken) >> (function | operand))
                        //| ((function | operand) >> token(DefinedMonadicOperatorNameToken))
                        ;


            auto const operation_def
                = assignment | token(DefinedFunctionNameToken) | token(SystemFunctionNameToken) | derived_function;

            auto const expression_def
                = *operation >> operand >> *(+operation >> operand);

            struct statement_class;
            x3::rule<statement_class, List<Token>> statement = "statement";
            auto const statement_def = -branch_arrow >> -expression;

            BOOST_SPIRIT_DEFINE(statement, index, assignment, function, axis_specification, operation, operand, expression, derived_function)
        };

        rules::statement_type const& statement() {
            return rules::statement;
        }
    };
};