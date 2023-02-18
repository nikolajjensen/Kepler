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
#include "form_table_extractors.h"

template <std::size_t S, const kepler::form_table::pattern<S> &Pattern>
bool kepler::form_table::match_pattern(search_t &search) {
    if(search.size() < S) {
        return false;
    }

    for(int i = 0; i < S; ++i) {
        auto& s = search[i];
        auto& p = Pattern[i];
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
    if(match_pattern<2, patterns::conjugate>(search)) {
        return build<extractors::monadic<applicators::scalar<evaluators::conjugate>>>();
    } else if(match_pattern<2, patterns::negative>(search)) {
        return build<extractors::monadic<applicators::scalar<evaluators::negative>>>();
    } else if(match_pattern<2, patterns::direction>(search)) {
        return build<extractors::monadic<applicators::scalar<evaluators::direction>>>();
    } else if(match_pattern<2, patterns::reciprocal>(search)) {
        return build<extractors::monadic<applicators::scalar<evaluators::reciprocal>>>();
    } else if(match_pattern<2, patterns::floor>(search)) {
        return build<extractors::monadic<applicators::scalar<evaluators::floor>>>();
    } else if(match_pattern<2, patterns::ceiling>(search)) {
        return build<extractors::monadic<applicators::scalar<evaluators::ceiling>>>();
    } else if(match_pattern<2, patterns::exponential>(search)) {
        return build<extractors::monadic<applicators::scalar<evaluators::exponential>>>();
    } else if(match_pattern<2, patterns::natural_log>(search)) {
        return build<extractors::monadic<applicators::scalar<evaluators::natural_log>>>();
    } else if(match_pattern<2, patterns::magnitude>(search)) {
        return build<extractors::monadic<applicators::scalar<evaluators::magnitude>>>();
    } else if(match_pattern<2, patterns::factorial>(search)) {
        return build<extractors::monadic<applicators::scalar<evaluators::factorial>>>();
    } else if(match_pattern<2, patterns::pi_times>(search)) {
        return build<extractors::monadic<applicators::scalar<evaluators::pi_times>>>();
    } else if(match_pattern<2, patterns::negation>(search)) {
        return build<extractors::monadic<applicators::scalar<evaluators::negation>>>();
    }

    /// Dyadic scalar functions.
    else if(match_pattern<3, patterns::plus>(search)) {
        return build<extractors::dyadic<applicators::scalar<evaluators::plus>>>();
    } else if(match_pattern<3, patterns::minus>(search)) {
        return build<extractors::dyadic<applicators::scalar<evaluators::minus>>>();
    } else if(match_pattern<3, patterns::times>(search)) {
        return build<extractors::dyadic<applicators::scalar<evaluators::times>>>();
    } else if(match_pattern<3, patterns::divide>(search)) {
        return build<extractors::dyadic<applicators::scalar<evaluators::divide>>>();
    } else if(match_pattern<3, patterns::maximum>(search)) {
        return build<extractors::dyadic<applicators::scalar<evaluators::maximum>>>();
    } else if(match_pattern<3, patterns::minimum>(search)) {
        return build<extractors::dyadic<applicators::scalar<evaluators::minimum>>>();
    } else if(match_pattern<3, patterns::power>(search)) {
        return build<extractors::dyadic<applicators::scalar<evaluators::power>>>();
    } else if(match_pattern<3, patterns::logarithm>(search)) {
        return build<extractors::dyadic<applicators::scalar<evaluators::logarithm>>>();
    } else if(match_pattern<3, patterns::residue>(search)) {
        return build<extractors::dyadic<applicators::scalar<evaluators::residue>>>();
    } else if(match_pattern<3, patterns::binomial>(search)) {
        return build<extractors::dyadic<applicators::scalar<evaluators::binomial>>>();
    } else if(match_pattern<3, patterns::circular_functions>(search)) {
        return build<extractors::dyadic<applicators::scalar<evaluators::circular_functions>>>();
    } else if(match_pattern<3, patterns::and_lcm>(search)) {
        return build<extractors::dyadic<applicators::scalar<evaluators::and_lcm>>>();
    } else if(match_pattern<3, patterns::or_gcd>(search)) {
        return build<extractors::dyadic<applicators::scalar<evaluators::or_gcd>>>();
    } else if(match_pattern<3, patterns::nand>(search)) {
        return build<extractors::dyadic<applicators::scalar<evaluators::nand>>>();
    } else if(match_pattern<3, patterns::nor>(search)) {
        return build<extractors::dyadic<applicators::scalar<evaluators::nor>>>();
    } else if(match_pattern<3, patterns::equal>(search)) {
        return build<extractors::dyadic<applicators::scalar<evaluators::equal>>>();
    } else if(match_pattern<3, patterns::less_than>(search)) {
        return build<extractors::dyadic<applicators::scalar<evaluators::less_than>>>();
    } else if(match_pattern<3, patterns::less_than_or_equal_to>(search)) {
        return build<extractors::dyadic<applicators::scalar<evaluators::less_than_or_equal_to>>>();
    } else if(match_pattern<3, patterns::not_equal>(search)) {
        return build<extractors::dyadic<applicators::scalar<evaluators::not_equal>>>();
    } else if(match_pattern<3, patterns::greater_than_or_equal_to>(search)) {
        return build<extractors::dyadic<applicators::scalar<evaluators::greater_than_or_equal_to>>>();
    } else if(match_pattern<3, patterns::greater_than>(search)) {
        return build<extractors::dyadic<applicators::scalar<evaluators::greater_than>>>();
    }

    /// Monadic array functions.
    else if(match_pattern<2, patterns::ravel>(search)) {
        return build<extractors::monadic<applicators::structural<evaluators::ravel>>>();
    } else if(match_pattern<2, patterns::shape>(search)) {
        return build<extractors::monadic<applicators::structural<evaluators::shape>>>();
    } else if(match_pattern<2, patterns::index_generator>(search)) {
        return build<extractors::monadic<applicators::structural<evaluators::index_generator>>>();
    } else if(match_pattern<2, patterns::table>(search)) {
        return build<extractors::monadic<applicators::structural<evaluators::table>>>();
    }

    /// Dyadic array functions.
    else if(match_pattern<3, patterns::reshape>(search)) {
        return build<extractors::dyadic<applicators::structural<evaluators::reshape>>>();
    } else if(match_pattern<3, patterns::join_1>(search)) {
        return build<extractors::dyadic<applicators::structural<evaluators::join_1>>>();
    } else if(match_pattern<3, patterns::join_2>(search)) {
        return build<extractors::dyadic<applicators::structural<evaluators::join_2>>>();
    }

    else if(match_pattern<3, patterns::index_origin_1>(search)) {
        return build<extractors::monadic<applicators::system_variable<evaluators::index_origin>>>();
    } else if(match_pattern<1, patterns::index_origin_2>(search)) {
        return build<extractors::niladic<applicators::system_variable<evaluators::index_origin>>>();
    } else if(match_pattern<3, patterns::print_precision_1>(search)) {
        return build<extractors::monadic<applicators::system_variable<evaluators::print_precision>>>();
    } else if(match_pattern<1, patterns::print_precision_2>(search)) {
        return build<extractors::niladic<applicators::system_variable<evaluators::print_precision>>>();
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