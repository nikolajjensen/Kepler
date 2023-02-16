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

#include <complex>

#include <utility>
#include <array>
#include "../token.h"
#include "../token_class.h"
#include "../characters.h"
#include "evaluation_outcome.h"
#include "../classifiers.h"
#include "../error/error.h"
#include "core/env/session.h"

namespace kepler {
    namespace form_table {
        enum TableAtomic {
            Constant,
            CompleteList,
            Func,
            DFN
        };

        using pattern_atomic = boost::variant<kepler::Token::content_type, TableAtomic>;
        template <std::size_t Size>
        using pattern = std::array<pattern_atomic, Size>;
        using search_t = List<boost::variant<Token*, TableAtomic>>;
        using input_t = List<const Token*>;
        using evaluator = kepler::Token (*)(const List<const Token*>, kepler::Session* session);

        namespace patterns {
            constexpr std::size_t niladic = 1;
            constexpr std::size_t monadic = 2;
            constexpr std::size_t dyadic = 3;

            /// Monadic scalar functions.
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

            /// Dyadic scalar functions.
            const pattern<dyadic> plus = {Constant, characters::plus, Constant};
            const pattern<dyadic> divide = {Constant, characters::divide, Constant};
            const pattern<dyadic> maximum = {Constant, characters::up_stile, Constant};
            const pattern<dyadic> minimum = {Constant, characters::down_stile, Constant};
            const pattern<dyadic> power = {Constant, characters::star, Constant};
            const pattern<dyadic> logarithm = {Constant, characters::circle_star, Constant};
            const pattern<dyadic> residue = {Constant, characters::stile, Constant};
            const pattern<dyadic> binomial = {Constant, characters::quote_dot, Constant};
            const pattern<dyadic> circular_functions = {Constant, characters::circle, Constant};
            const pattern<dyadic> and_lcm = {Constant, characters::up_caret, Constant};
            const pattern<dyadic> or_gcd = {Constant, characters::down_caret, Constant};
            const pattern<dyadic> nand = {Constant, characters::up_caret_tilde, Constant};
            const pattern<dyadic> nor = {Constant, characters::down_caret_tilde, Constant};
            const pattern<dyadic> equal = {Constant, characters::equal, Constant};
            const pattern<dyadic> less_than = {Constant, characters::left_caret, Constant};
            const pattern<dyadic> less_than_or_equal_to = {Constant, characters::less_than_or_equal, Constant};
            const pattern<dyadic> not_equal = {Constant, characters::not_equal, Constant};
            const pattern<dyadic> greater_than_or_equal_to = {Constant, characters::greater_than_or_equal, Constant};
            const pattern<dyadic> greater_than = {Constant, characters::right_caret, Constant};


            /// Monadic array functions.
            const pattern<monadic> ravel = {characters::comma, Constant};
            const pattern<monadic> shape = {characters::rho, Constant};
            const pattern<monadic> index_generator = {characters::iota, Constant};
            const pattern<monadic> table = {characters::comma_bar, Constant};

            /// Dyadic array functions.
            const pattern<dyadic> reshape = {Constant, characters::rho, Constant};
            const pattern<dyadic> join_1 = {Constant, characters::comma, Constant};
            const pattern<dyadic> join_2 = {Constant, characters::comma_bar, Constant};

            /// Operators.

        };


        struct match : boost::static_visitor<bool> {
            bool operator()(Token*& token, const Token::content_type& target) const {
                return token->content && (token->content.get() == target);
            }

            bool operator()(TableAtomic& atomic, const TableAtomic& target) const {
                return atomic == target;
            }

            template <typename T, typename U>
            bool operator()(T&, const U&) const {
                return false;
            }
        };

        template <std::size_t S, const pattern<S>& Pattern>
        bool match_pattern(search_t& search);

        template <typename F>
        evaluator build();

        evaluator lookup(search_t&& search);

        // NOTE: This will throw InternalError if there
        // is no match in form table.
        kepler::Token evaluate(search_t search, input_t input, kepler::Session* session);
    };
};
