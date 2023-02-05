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
#include "../token.h"
#include "../token_class.h"
#include "../characters.h"
#include "evaluation_outcome.h"
#include "../classifiers.h"

namespace kepler {
    namespace form_table {
        enum TokenType {
            Constant,
            CompleteList,
            Func,
            DFN
        };

        enum Selection {
            Content,
            Type
        };

        using pattern_atomic = boost::variant<kepler::Token::content_type, TokenType>;
        template <std::size_t Size>
        using pattern = std::array<pattern_atomic, Size>;
        using selector = kepler::List<Selection>;
        using token_input = kepler::List<kepler::Token*>;

        constexpr std::size_t conjugate_size = 2;
        const pattern<conjugate_size> conjugate = {characters::plus, Constant};

        constexpr std::size_t niladic_cdf_size = 1;
        const pattern<niladic_cdf_size> niladic_cdf = {DFN};

        using phrase_evaluator = kepler::Token (*)(token_input&& input);

        namespace evaluators {
            template <std::size_t S, const pattern<S>& Pattern>
            kepler::Token conjugate(token_input&& input);

            template <std::size_t S, const pattern<S>& Pattern>
            kepler::Token call_defined_function(token_input&& input);
        };

        bool match(kepler::Token* token, Selection& selection, const pattern_atomic& target);

        template <std::size_t S, const pattern<S>& Pattern>
        bool match_pattern(token_input& input, selector& selector);

        phrase_evaluator lookup(token_input&& input, selector&& selector);
        phrase_evaluator lookup(token_input& input, selector&& selector);
        kepler::Token evaluate(token_input&& input, selector&& selector);


        /*

        template <typename... Args>
        using phrase_evaluator = kepler::Token (*)(Args&... args);

        namespace evaluators {
            template <typename... Args>
            kepler::Token conjugate(Args&... args) {
                auto tokens = std::make_tuple(args...);
                kepler::Token& first = std::get<0>(tokens);
                return first;
            }

            template <std::size_t S, const pattern<S>& Pattern, typename... Args>
            kepler::Token call_defined_function(Args&... args) {
                if(Pattern == niladic_cdf) {

                }

                return kepler::Token();
            }
        };

        bool match_type(const kepler::Token& token, TokenType type);

        template <std::size_t S, const pattern<S>& Pattern, typename... Args>
        bool match(Args&... args) {
            auto tokens = std::make_tuple(args...);
            if(std::tuple_size<decltype(tokens)>::value > S) {
                return false;
            }

            int i = 0;
            for(const kepler::Token& token : {args...}) {
                if(const TokenType* cl = boost::get<TokenType>(&Pattern[i])) {
                    if(!match_type(token, *cl)) { return false; }
                } else if(const Token::content_type* content = boost::get<Token::content_type>(&Pattern[i])) {
                    if(token.content.get() != *content) { return false; }
                }
                ++i;
            }

            return true;
        }

        template <std::size_t S, const pattern<S>& Pattern, typename... Args>
        phrase_evaluator<Args&...> lookup(Args&... args) {
            static_assert(std::conjunction_v<std::is_same<Args, kepler::Token>...>, "All arguments must be of type 'Token'.");

            if(match<S, Pattern>(std::forward<Args&>(args)...)) {
                return evaluators::conjugate;
            }

            return nullptr;
        }
        */
    };

    /*
    namespace interpreter {
        namespace form_table {
            enum PatternClass {
                DFN, B, Content
            };

            namespace tokens {
                const Token A(ConstantToken);
                const Token B(ConstantToken);
                const Token Z(ConstantToken);
                const Token I(CompleteIndexListToken);
                const Token K(CompleteIndexListToken);
                const Token F(PrimitiveFunctionToken);
                const Token G(DefinedFunctionToken);
                const Token DFN(DefinedFunctionToken);

                const Token plus(PrimitiveFunctionToken, characters::plus);
                const Token bar(PrimitiveFunctionToken, characters::bar);
                const Token multiply(PrimitiveFunctionToken, characters::multiply);
                const Token divide(PrimitiveFunctionToken, characters::divide);
                const Token down_stile(PrimitiveFunctionToken, characters::down_stile);
                const Token up_stile(PrimitiveFunctionToken, characters::up_stile);
                const Token star(PrimitiveFunctionToken, characters::star);
                const Token circle_star(PrimitiveFunctionToken, characters::circle_star);
                const Token stile(PrimitiveFunctionToken, characters::stile);
                const Token quote_dot(PrimitiveFunctionToken, characters::quote_dot);
                const Token circle(PrimitiveFunctionToken, characters::circle);
                const Token tilde(PrimitiveFunctionToken, characters::tilde);

                const Token quad(NilToken, characters::quad);
            };

            namespace patterns {
                const List<Token> conjugate = {tokens::plus, tokens::B};
                const List<Token> negative = {tokens::bar, tokens::B};
                const List<Token> direction = {tokens::multiply, tokens::B};
                const List<Token> reciprocal = {tokens::divide, tokens::B};
                const List<Token> floor = {tokens::down_stile, tokens::B};
                const List<Token> ceiling = {tokens::up_stile, tokens::B};
                const List<Token> exponential = {tokens::star, tokens::B};
                const List<Token> natural_logarithm = {tokens::circle_star, tokens::B};
                const List<Token> magnitude = {tokens::stile, tokens::B};
                const List<Token> factorial = {tokens::quote_dot, tokens::B};
                const List<Token> pi_times = {tokens::circle, tokens::B};
                // NB: Was not called "negation" but "not" in ISO.
                const List<Token> negation = {tokens::tilde, tokens::B};

                const List<Token> quad_input = {tokens::quad};
            };

            namespace evaluators {
                Token conjugate(List<Token>& operands);
                Token negative(List<Token>& operands);
            };

            bool match_form(const List<Token>& tokens, const List<PatternClass>& form, const List<Token>& pattern);

            //boost::optional<Token> form_table_evaluation(List<Token>&& tokens, const List<Token>& pattern);
            boost::optional<Token> form_table_evaluation(List<Token>&& tokens, List<PatternClass> form);
            bool lookup(List<Token>&& tokens, List<PatternClass>&& form);
        };

    };
     */
};
