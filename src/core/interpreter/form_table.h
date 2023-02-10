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
        using evaluator_input = kepler::List<kepler::Token::content_type*>;

        namespace patterns {
            constexpr std::size_t niladic = 1;
            constexpr std::size_t monadic = 2;
            constexpr std::size_t dyadic = 3;

            // Niladic functions:
            const pattern<niladic> niladic_cdf = {DFN};
            const pattern<monadic> monadic_cdf = {DFN, Constant};

            // Monadic functions:
            const pattern<monadic> conjugate = {characters::plus, Constant};
            const pattern<monadic> negative = {characters::bar, Constant};
            const pattern<monadic> direction = {characters::multiply, Constant};
            const pattern<monadic> reciprocal = {characters::divide, Constant};
            const pattern<monadic> floor = {characters::down_stile, Constant};
            const pattern<monadic> ceiling = {characters::up_stile, Constant};
            const pattern<monadic> exponential = {characters::star, Constant};
            const pattern<monadic> natural_log = {characters::circle_star, Constant};
            const pattern<monadic> magnitude = {characters::stile, Constant};
            const pattern<monadic> factorial = {characters::quote_dot, Constant};
            const pattern<monadic> pi_times = {characters::circle, Constant};
            const pattern<monadic> negation = {characters::tilde, Constant};    // Called 'not' in ISO.

            // Dyadic functions:
            const pattern<dyadic> plus = {Constant, characters::plus, Constant};

        };

        using form_evaluator = kepler::Token (*)(evaluator_input&& input);

        namespace evaluators {
            void conjugate(kepler::Number& number);
            /*
            template <std::size_t S, const pattern<S>& Pattern>
            kepler::Token conjugate(evaluator_input&& input);

            template <std::size_t S, const pattern<S>& Pattern>
            kepler::Token negative(evaluator_input&& input);

            template <std::size_t S, const pattern<S>& Pattern>
            kepler::Token direction(evaluator_input&& input);

            template <std::size_t S, const pattern<S>& Pattern>
            kepler::Token plus(evaluator_input&& input);
             */

            template <std::size_t S, const pattern<S>& Pattern>
            kepler::Token call_defined_function(evaluator_input&& input);
        };

        bool match(kepler::Token* token, Selection& selection, const pattern_atomic& target);

        template <std::size_t S, const pattern<S>& Pattern>
        bool match_pattern(List<Token*>& tokens, selector& selector);

        form_evaluator lookup(List<Token*>&& input, selector&& selector);
        form_evaluator lookup(List<Token*>& input, selector&& selector);
        //boost::optional<kepler::Token> evaluate(evaluator_input&& input, selector&& selector);
    };
};
