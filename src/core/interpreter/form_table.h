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
#include "../env/distinguished_identifiers.h"

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
        using search_t = List<boost::variant<Token*, kepler::Token::content_type, TableAtomic>>;
        using input_t = List<const Token*>;
        using evaluator = kepler::Token (*)(const List<const Token*>, kepler::Session* session);

        namespace patterns {
            /// Monadic scalar functions.
            const pattern<2> conjugate = {characters::plus, Constant};
            const pattern<2> negative = {characters::bar, Constant};
            const pattern<2> direction = {characters::multiply, Constant};
            const pattern<2> reciprocal = {characters::divide, Constant};
            const pattern<2> floor = {characters::down_stile, Constant};
            const pattern<2> ceiling = {characters::up_stile, Constant};
            const pattern<2> exponential = {characters::star, Constant};
            const pattern<2> natural_log = {characters::circle_star, Constant};
            const pattern<2> magnitude = {characters::stile, Constant};
            const pattern<2> factorial = {characters::quote_dot, Constant};
            const pattern<2> pi_times = {characters::circle, Constant};
            const pattern<2> negation = {characters::tilde, Constant};    // Called 'not' in ISO.

            /// Dyadic scalar functions.
            const pattern<3> plus = {Constant, characters::plus, Constant};
            const pattern<3> minus = {Constant, characters::bar, Constant};
            const pattern<3> times = {Constant, characters::multiply, Constant};
            const pattern<3> divide = {Constant, characters::divide, Constant};
            const pattern<3> maximum = {Constant, characters::up_stile, Constant};
            const pattern<3> minimum = {Constant, characters::down_stile, Constant};
            const pattern<3> power = {Constant, characters::star, Constant};
            const pattern<3> logarithm = {Constant, characters::circle_star, Constant};
            const pattern<3> residue = {Constant, characters::stile, Constant};
            const pattern<3> binomial = {Constant, characters::quote_dot, Constant};
            const pattern<3> circular_functions = {Constant, characters::circle, Constant};
            const pattern<3> and_lcm = {Constant, characters::up_caret, Constant};
            const pattern<3> or_gcd = {Constant, characters::down_caret, Constant};
            const pattern<3> nand = {Constant, characters::up_caret_tilde, Constant};
            const pattern<3> nor = {Constant, characters::down_caret_tilde, Constant};
            const pattern<3> equal = {Constant, characters::equal, Constant};
            const pattern<3> less_than = {Constant, characters::left_caret, Constant};
            const pattern<3> less_than_or_equal_to = {Constant, characters::less_than_or_equal, Constant};
            const pattern<3> not_equal = {Constant, characters::not_equal, Constant};
            const pattern<3> greater_than_or_equal_to = {Constant, characters::greater_than_or_equal, Constant};
            const pattern<3> greater_than = {Constant, characters::right_caret, Constant};


            /// Monadic array functions.
            const pattern<2> ravel = {characters::comma, Constant};
            const pattern<2> shape = {characters::rho, Constant};
            const pattern<2> index_generator = {characters::iota, Constant};
            const pattern<2> table = {characters::comma_bar, Constant};

            /// Dyadic array functions.
            const pattern<3> reshape = {Constant, characters::rho, Constant};
            const pattern<3> join_1 = {Constant, characters::comma, Constant};
            const pattern<3> join_2 = {Constant, characters::comma_bar, Constant};


            const pattern<3> index_origin_1 = {distinguished_identifiers::IO, characters::left_arrow, Constant};
            const pattern<1> index_origin_2 = {distinguished_identifiers::IO};

            const pattern<3> print_precision_1 = {distinguished_identifiers::PP, characters::left_arrow, Constant};
            const pattern<1> print_precision_2 = {distinguished_identifiers::PP};

        };


        struct match : boost::static_visitor<bool> {
            bool operator()(Token*& token, const Token::content_type& target) const {
                return token->content && (token->content.get() == target);
            }

            bool operator()(TableAtomic& atomic, const TableAtomic& target) const {
                return atomic == target;
            }

            bool operator()(Token::content_type& content, const Token::content_type& target) const {
                return content == target;
            }

            template <typename T, typename U>
            bool operator()(T& lhs, const U& rhs) const {
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
