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

#include "form_table.h"
#include "form_table_evaluators.h"
#include "form_table_applicators.h"

template <std::size_t S, const kepler::form_table::pattern<S> &Pattern>
bool kepler::form_table::match_pattern(search_t &search) {
    if(search.size() < S) {
        return false;
    }

    for(int i = 0; i < S; ++i) {
        if(!boost::apply_visitor(match(), search[i], Pattern[i])) {
            return false;
        }
    }

    return true;
}

template<typename F>
kepler::form_table::evaluator kepler::form_table::build() {
    return [](const List<const Token*> tokens, kepler::Session* session){
        return F(session)(tokens);
    };
}

kepler::form_table::evaluator kepler::form_table::lookup(search_t &&search) {
    /// Monadic scalar functions.
    if(match_pattern<patterns::monadic, patterns::conjugate>(search)) {
        return build<applicators::monadic<applicators::scalar<evaluators::conjugate>>>();
    } else if(match_pattern<patterns::monadic, patterns::negative>(search)) {
        return build<applicators::monadic<applicators::scalar<evaluators::negative>>>();
    } else if(match_pattern<patterns::monadic, patterns::direction>(search)) {
        return build<applicators::monadic<applicators::scalar<evaluators::direction>>>();
    } else if(match_pattern<patterns::monadic, patterns::reciprocal>(search)) {
        return build<applicators::monadic<applicators::scalar<evaluators::reciprocal>>>();
    } else if(match_pattern<patterns::monadic, patterns::floor>(search)) {
        return build<applicators::monadic<applicators::scalar<evaluators::floor>>>();
    } else if(match_pattern<patterns::monadic, patterns::ceiling>(search)) {
        return build<applicators::monadic<applicators::scalar<evaluators::ceiling>>>();
    } else if(match_pattern<patterns::monadic, patterns::exponential>(search)) {
        return build<applicators::monadic<applicators::scalar<evaluators::exponential>>>();
    } else if(match_pattern<patterns::monadic, patterns::natural_log>(search)) {
        return build<applicators::monadic<applicators::scalar<evaluators::natural_log>>>();
    } else if(match_pattern<patterns::monadic, patterns::magnitude>(search)) {
        return build<applicators::monadic<applicators::scalar<evaluators::magnitude>>>();
    } else if(match_pattern<patterns::monadic, patterns::factorial>(search)) {
        return build<applicators::monadic<applicators::scalar<evaluators::factorial>>>();
    } else if(match_pattern<patterns::monadic, patterns::pi_times>(search)) {
        return build<applicators::monadic<applicators::scalar<evaluators::pi_times>>>();
    } else if(match_pattern<patterns::monadic, patterns::negation>(search)) {
        return build<applicators::monadic<applicators::scalar<evaluators::negation>>>();
    }

    /// Dyadic scalar functions.
    else if(match_pattern<patterns::dyadic, patterns::plus>(search)) {
        return build<applicators::dyadic<applicators::scalar<evaluators::plus>>>();
    } else if(match_pattern<patterns::dyadic, patterns::divide>(search)) {
        return build<applicators::dyadic<applicators::scalar<evaluators::divide>>>();
    } else if(match_pattern<patterns::dyadic, patterns::maximum>(search)) {
        return build<applicators::dyadic<applicators::scalar<evaluators::maximum>>>();
    } else if(match_pattern<patterns::dyadic, patterns::minimum>(search)) {
        return build<applicators::dyadic<applicators::scalar<evaluators::minimum>>>();
    } else if(match_pattern<patterns::dyadic, patterns::power>(search)) {
        return build<applicators::dyadic<applicators::scalar<evaluators::power>>>();
    } else if(match_pattern<patterns::dyadic, patterns::logarithm>(search)) {
        return build<applicators::dyadic<applicators::scalar<evaluators::logarithm>>>();
    } else if(match_pattern<patterns::dyadic, patterns::residue>(search)) {
        return build<applicators::dyadic<applicators::scalar<evaluators::residue>>>();
    } else if(match_pattern<patterns::dyadic, patterns::binomial>(search)) {
        return build<applicators::dyadic<applicators::scalar<evaluators::binomial>>>();
    } else if(match_pattern<patterns::dyadic, patterns::circular_functions>(search)) {
        return build<applicators::dyadic<applicators::scalar<evaluators::circular_functions>>>();
    } else if(match_pattern<patterns::dyadic, patterns::and_lcm>(search)) {
        return build<applicators::dyadic<applicators::scalar<evaluators::and_lcm>>>();
    } else if(match_pattern<patterns::dyadic, patterns::or_gcd>(search)) {
        return build<applicators::dyadic<applicators::scalar<evaluators::or_gcd>>>();
    } else if(match_pattern<patterns::dyadic, patterns::nand>(search)) {
        return build<applicators::dyadic<applicators::scalar<evaluators::nand>>>();
    } else if(match_pattern<patterns::dyadic, patterns::nor>(search)) {
        return build<applicators::dyadic<applicators::scalar<evaluators::nor>>>();
    } else if(match_pattern<patterns::dyadic, patterns::equal>(search)) {
        return build<applicators::dyadic<applicators::scalar<evaluators::equal>>>();
    } else if(match_pattern<patterns::dyadic, patterns::less_than>(search)) {
        return build<applicators::dyadic<applicators::scalar<evaluators::less_than>>>();
    } else if(match_pattern<patterns::dyadic, patterns::less_than_or_equal_to>(search)) {
        return build<applicators::dyadic<applicators::scalar<evaluators::less_than_or_equal_to>>>();
    } else if(match_pattern<patterns::dyadic, patterns::not_equal>(search)) {
        return build<applicators::dyadic<applicators::scalar<evaluators::not_equal>>>();
    } else if(match_pattern<patterns::dyadic, patterns::greater_than_or_equal_to>(search)) {
        return build<applicators::dyadic<applicators::scalar<evaluators::greater_than_or_equal_to>>>();
    } else if(match_pattern<patterns::dyadic, patterns::greater_than>(search)) {
        return build<applicators::dyadic<applicators::scalar<evaluators::greater_than>>>();
    }

    /// Monadic array functions.
    else if(match_pattern<patterns::monadic, patterns::ravel>(search)) {
        return build<applicators::monadic<applicators::array<evaluators::ravel>>>();
    } else if(match_pattern<patterns::monadic, patterns::shape>(search)) {
        return build<applicators::monadic<applicators::array<evaluators::shape>>>();
    } else if(match_pattern<patterns::monadic, patterns::index_generator>(search)) {
        return build<applicators::monadic<applicators::array<evaluators::index_generator>>>();
    } else if(match_pattern<patterns::monadic, patterns::table>(search)) {
        return build<applicators::monadic<applicators::array<evaluators::table>>>();
    }

    /// Dyadic array functions.
    else if(match_pattern<patterns::dyadic, patterns::reshape>(search)) {
        return build<applicators::dyadic<applicators::array<evaluators::reshape>>>();
    } else if(match_pattern<patterns::dyadic, patterns::join_1>(search)) {
        return build<applicators::dyadic<applicators::array<evaluators::join_1>>>();
    } else if(match_pattern<patterns::dyadic, patterns::join_2>(search)) {
        return build<applicators::dyadic<applicators::array<evaluators::join_2>>>();
    }

    return nullptr;
}

kepler::Token kepler::form_table::evaluate(search_t search, input_t input, kepler::Session* session) {
    auto evaluator = lookup(std::move(search));
    if(evaluator == nullptr) {
        throw error(InternalError, "Expected to find form-table evaluator for expression.");
    }
    return evaluator(std::move(input), session);
}