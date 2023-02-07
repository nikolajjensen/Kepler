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

        constexpr std::size_t negation_size = 2;
        const pattern<negation_size> negation = {characters::bar, Constant};

        constexpr std::size_t direction_size = 2;
        const pattern<direction_size> direction = {characters::multiply, Constant};

        constexpr std::size_t plus_size = 3;
        const pattern<plus_size> plus = {Constant, characters::plus, Constant};

        constexpr std::size_t niladic_cdf_size = 1;
        const pattern<niladic_cdf_size> niladic_cdf = {DFN};

        using phrase_evaluator = kepler::Token (*)(token_input&& input);

        namespace evaluators {
            template <std::size_t S, const pattern<S>& Pattern>
            kepler::Token conjugate(token_input&& input);

            template <std::size_t S, const pattern<S>& Pattern>
            kepler::Token negation(token_input&& input);

            template <std::size_t S, const pattern<S>& Pattern>
            kepler::Token direction(token_input&& input);

            template <std::size_t S, const pattern<S>& Pattern>
            kepler::Token plus(token_input&& input);

            template <std::size_t S, const pattern<S>& Pattern>
            kepler::Token call_defined_function(token_input&& input);
        };

        bool match(kepler::Token* token, Selection& selection, const pattern_atomic& target);

        template <std::size_t S, const pattern<S>& Pattern>
        bool match_pattern(token_input& input, selector& selector);

        phrase_evaluator lookup(token_input&& input, selector&& selector);
        phrase_evaluator lookup(token_input& input, selector&& selector);
        kepler::Token evaluate(token_input&& input, selector&& selector);
    };
};
