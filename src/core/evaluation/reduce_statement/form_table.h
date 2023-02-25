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
#include <memory>
#include "core/token.h"
#include "core/token_class.h"
#include "core/constants/literals.h"
#include "core/helpers/classifiers.h"
#include "core/error.h"
#include "core/session.h"
#include "form_table_applicators.h"

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
        using search_t = List<boost::variant<const Token*, kepler::Token::content_type, TableAtomic>>;
        using input_t = List<const Token*>;
        using applicator = kepler::Token (*)(const List<const Token*>, kepler::Session* session);

        namespace patterns {
            /// Monadic scalar functions.
            const pattern<2> conjugate = {constants::plus, Constant};
            const pattern<2> negative = {constants::bar, Constant};
            const pattern<2> direction = {constants::multiply, Constant};
            const pattern<2> reciprocal = {constants::divide, Constant};
            const pattern<2> floor = {constants::down_stile, Constant};
            const pattern<2> ceiling = {constants::up_stile, Constant};
            const pattern<2> exponential = {constants::star, Constant};
            const pattern<2> natural_log = {constants::circle_star, Constant};
            const pattern<2> magnitude = {constants::stile, Constant};
            const pattern<2> factorial = {constants::quote_dot, Constant};
            const pattern<2> pi_times = {constants::circle, Constant};
            const pattern<2> negation = {constants::tilde, Constant};    // Called 'not' in ISO.

            /// Dyadic scalar functions.
            const pattern<3> plus = {Constant, constants::plus, Constant};
            const pattern<3> minus = {Constant, constants::bar, Constant};
            const pattern<3> times = {Constant, constants::multiply, Constant};
            const pattern<3> divide = {Constant, constants::divide, Constant};
            const pattern<3> maximum = {Constant, constants::up_stile, Constant};
            const pattern<3> minimum = {Constant, constants::down_stile, Constant};
            const pattern<3> power = {Constant, constants::star, Constant};
            const pattern<3> logarithm = {Constant, constants::circle_star, Constant};
            const pattern<3> residue = {Constant, constants::stile, Constant};
            const pattern<3> binomial = {Constant, constants::quote_dot, Constant};
            const pattern<3> circular_functions = {Constant, constants::circle, Constant};
            const pattern<3> and_lcm = {Constant, constants::up_caret, Constant};
            const pattern<3> or_gcd = {Constant, constants::down_caret, Constant};
            const pattern<3> nand = {Constant, constants::up_caret_tilde, Constant};
            const pattern<3> nor = {Constant, constants::down_caret_tilde, Constant};
            const pattern<3> equal = {Constant, constants::equal, Constant};
            const pattern<3> less_than = {Constant, constants::left_caret, Constant};
            const pattern<3> less_than_or_equal_to = {Constant, constants::less_than_or_equal, Constant};
            const pattern<3> not_equal = {Constant, constants::not_equal, Constant};
            const pattern<3> greater_than_or_equal_to = {Constant, constants::greater_than_or_equal, Constant};
            const pattern<3> greater_than = {Constant, constants::right_caret, Constant};


            /// Monadic array functions.
            const pattern<2> ravel = {constants::comma, Constant};
            const pattern<2> shape = {constants::rho, Constant};
            const pattern<2> index_generator = {constants::iota, Constant};
            const pattern<2> table = {constants::comma_bar, Constant};

            /// Dyadic array functions.
            const pattern<3> reshape = {Constant, constants::rho, Constant};
            const pattern<3> join_1 = {Constant, constants::comma, Constant};
            const pattern<3> join_2 = {Constant, constants::comma_bar, Constant};


            /// Operators.
            const pattern<3> reduction_1 = {Func, constants::slash, Constant};


            const pattern<3> comparison_tolerance_1 = {constants::CT, constants::left_arrow, Constant};
            const pattern<1> comparison_tolerance_2 = {constants::CT};

            const pattern<3> index_origin_1 = {constants::IO, constants::left_arrow, Constant};
            const pattern<1> index_origin_2 = {constants::IO};

            const pattern<3> print_precision_1 = {constants::PP, constants::left_arrow, Constant};
            const pattern<1> print_precision_2 = {constants::PP};


            const pattern<1> quad_input = {constants::quad};

        };


        struct match : boost::static_visitor<bool> {
            bool operator()(const Token*& token, const Token::content_type& target) const {
                return token->content && (token->content.get() == target);
            }

            bool operator()(TableAtomic& atomic, const TableAtomic& target) const {
                return atomic == target;
            }

            bool operator()(Token::content_type& content, const Token::content_type& target) const {
                return content == target;
            }

            bool operator()(const Token*& token, const TableAtomic& target) const {
                if(target == Func) {
                    return helpers::is(*token, PrimitiveFunctionToken)
                            || helpers::is(*token, PrimitiveDyadicOperatorToken)
                            || helpers::is(*token, PrimitiveMonadicOperatorToken)
                            || helpers::is(*token, AxisMonadicOperatorToken);
                }

                return false;
            }

            template <typename T, typename U>
            bool operator()(T& lhs, const U& rhs) const {
                return false;
            }
        };

        template <std::size_t S, const pattern<S>& Pattern>
        bool match_pattern(search_t& search);

        template <typename F>
        applicator build();


        //extensions::extension lookup_evaluator(search_t& search, Session* session);

        std::unique_ptr<applicators::applicator> lookup(search_t&& search, Session* session);



        //applicator lookup(search_t&& search);

        // NOTE: This will throw InternalError if there
        // is no match in form table.
        kepler::Token evaluate(search_t search, input_t input, kepler::Session* session);
    };
};
