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
#include "form_table_extensions.h"
#include "form_table_applicators.h"

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

std::unique_ptr<kepler::form_table::applicators::applicator> kepler::form_table::lookup(search_t &&search, Session *session) {
    if(match_pattern<2, patterns::conjugate>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::monadic, extensions::scalar, evaluators::conjugate>(session));
    } else if(match_pattern<2, patterns::negative>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::monadic, extensions::scalar, evaluators::negative>(session));
    } else if(match_pattern<2, patterns::direction>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::monadic, extensions::scalar, evaluators::direction>(session));
    } else if(match_pattern<2, patterns::reciprocal>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::monadic, extensions::scalar, evaluators::reciprocal>(session));
    } else if(match_pattern<2, patterns::floor>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::monadic, extensions::scalar, evaluators::floor>(session));
    } else if(match_pattern<2, patterns::ceiling>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::monadic, extensions::scalar, evaluators::ceiling>(session));
    } else if(match_pattern<2, patterns::exponential>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::monadic, extensions::scalar, evaluators::exponential>(session));
    } else if(match_pattern<2, patterns::natural_log>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::monadic, extensions::scalar, evaluators::natural_log>(session));
    } else if(match_pattern<2, patterns::magnitude>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::monadic, extensions::scalar, evaluators::magnitude>(session));
    } else if(match_pattern<2, patterns::factorial>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::monadic, extensions::scalar, evaluators::factorial>(session));
    } else if(match_pattern<2, patterns::pi_times>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::monadic, extensions::scalar, evaluators::pi_times>(session));
    } else if(match_pattern<2, patterns::negation>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::monadic, extensions::scalar, evaluators::negation>(session));
    }

    /// Dyadic scalar functions.
    else if(match_pattern<3, patterns::plus>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::dyadic, extensions::scalar, evaluators::plus>(session));
    } else if(match_pattern<3, patterns::minus>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::dyadic, extensions::scalar, evaluators::minus>(session));
    } else if(match_pattern<3, patterns::times>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::dyadic, extensions::scalar, evaluators::times>(session));
    } else if(match_pattern<3, patterns::divide>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::dyadic, extensions::scalar, evaluators::divide>(session));
    } else if(match_pattern<3, patterns::maximum>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::dyadic, extensions::scalar, evaluators::maximum>(session));
    } else if(match_pattern<3, patterns::minimum>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::dyadic, extensions::scalar, evaluators::minimum>(session));
    } else if(match_pattern<3, patterns::power>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::dyadic, extensions::scalar, evaluators::power>(session));
    } else if(match_pattern<3, patterns::logarithm>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::dyadic, extensions::scalar, evaluators::logarithm>(session));
    } else if(match_pattern<3, patterns::residue>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::dyadic, extensions::scalar, evaluators::residue>(session));
    } else if(match_pattern<3, patterns::binomial>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::dyadic, extensions::scalar, evaluators::binomial>(session));
    } else if(match_pattern<3, patterns::circular_functions>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::dyadic, extensions::scalar, evaluators::circular_functions>(session));
    } else if(match_pattern<3, patterns::and_lcm>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::dyadic, extensions::scalar, evaluators::and_lcm>(session));
    } else if(match_pattern<3, patterns::or_gcd>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::dyadic, extensions::scalar, evaluators::or_gcd>(session));
    } else if(match_pattern<3, patterns::nand>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::dyadic, extensions::scalar, evaluators::nand>(session));
    } else if(match_pattern<3, patterns::nor>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::dyadic, extensions::scalar, evaluators::nor>(session));
    } else if(match_pattern<3, patterns::equal>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::dyadic, extensions::scalar, evaluators::equal>(session));
    } else if(match_pattern<3, patterns::less_than>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::dyadic, extensions::scalar, evaluators::less_than>(session));
    } else if(match_pattern<3, patterns::less_than_or_equal_to>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::dyadic, extensions::scalar, evaluators::less_than_or_equal_to>(session));
    } else if(match_pattern<3, patterns::not_equal>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::dyadic, extensions::scalar, evaluators::not_equal>(session));
    } else if(match_pattern<3, patterns::greater_than_or_equal_to>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::dyadic, extensions::scalar, evaluators::greater_than_or_equal_to>(session));
    } else if(match_pattern<3, patterns::greater_than>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::dyadic, extensions::scalar, evaluators::greater_than>(session));
    }

    /// Monadic array functions.
    else if(match_pattern<2, patterns::ravel>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::monadic, extensions::structural, evaluators::ravel>(session));
    } else if(match_pattern<2, patterns::shape>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::monadic, extensions::structural, evaluators::shape>(session));
    } else if(match_pattern<2, patterns::index_generator>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::monadic, extensions::structural, evaluators::index_generator>(session));
    } else if(match_pattern<2, patterns::table>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::monadic, extensions::structural, evaluators::table>(session));
    }


    /// Dyadic array functions.
    else if(match_pattern<3, patterns::reshape>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::dyadic, extensions::structural, evaluators::reshape>(session));
    } else if(match_pattern<3, patterns::join_1>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::dyadic, extensions::structural, evaluators::join_1>(session));
    } else if(match_pattern<3, patterns::join_2>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::dyadic, extensions::structural, evaluators::join_2>(session));
    }

    /// Operators.
    else if(match_pattern<3, patterns::reduction_1>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::dyadic, extensions::operators, evaluators::reduction>(session));
    }

    else if(match_pattern<3, patterns::comparison_tolerance_1>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::monadic, extensions::system_variable, evaluators::comparison_tolerance>(session));
    } else if(match_pattern<1, patterns::comparison_tolerance_2>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::niladic, extensions::system_variable, evaluators::comparison_tolerance>(session));
    } else if(match_pattern<3, patterns::index_origin_1>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::monadic, extensions::system_variable, evaluators::index_origin>(session));
    } else if(match_pattern<1, patterns::index_origin_2>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::niladic, extensions::system_variable, evaluators::index_origin>(session));
    } else if(match_pattern<3, patterns::print_precision_1>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::monadic, extensions::system_variable, evaluators::print_precision>(session));
    } else if(match_pattern<1, patterns::print_precision_2>(search)) {
        return std::make_unique<applicators::applicator>(applicators::applicator::construct<applicators::niladic, extensions::system_variable, evaluators::print_precision>(session));
    }

    return nullptr;
}
/*
kepler::form_table::applicator kepler::form_table::lookup(search_t &&search) {
    /// Monadic scalar functions.
    if(match_pattern<2, patterns::conjugate>(search)) {
        return build<applicators::monadic<extensions::scalar<evaluators::conjugate>>>();
    } else if(match_pattern<2, patterns::negative>(search)) {
        return build<applicators::monadic<extensions::scalar<evaluators::negative>>>();
    } else if(match_pattern<2, patterns::direction>(search)) {
        return build<applicators::monadic<extensions::scalar<evaluators::direction>>>();
    } else if(match_pattern<2, patterns::reciprocal>(search)) {
        return build<applicators::monadic<extensions::scalar<evaluators::reciprocal>>>();
    } else if(match_pattern<2, patterns::floor>(search)) {
        return build<applicators::monadic<extensions::scalar<evaluators::floor>>>();
    } else if(match_pattern<2, patterns::ceiling>(search)) {
        return build<applicators::monadic<extensions::scalar<evaluators::ceiling>>>();
    } else if(match_pattern<2, patterns::exponential>(search)) {
        return build<applicators::monadic<extensions::scalar<evaluators::exponential>>>();
    } else if(match_pattern<2, patterns::natural_log>(search)) {
        return build<applicators::monadic<extensions::scalar<evaluators::natural_log>>>();
    } else if(match_pattern<2, patterns::magnitude>(search)) {
        return build<applicators::monadic<extensions::scalar<evaluators::magnitude>>>();
    } else if(match_pattern<2, patterns::factorial>(search)) {
        return build<applicators::monadic<extensions::scalar<evaluators::factorial>>>();
    } else if(match_pattern<2, patterns::pi_times>(search)) {
        return build<applicators::monadic<extensions::scalar<evaluators::pi_times>>>();
    } else if(match_pattern<2, patterns::negation>(search)) {
        return build<applicators::monadic<extensions::scalar<evaluators::negation>>>();
    }

    /// Dyadic scalar functions.
    else if(match_pattern<3, patterns::plus>(search)) {
        return build<applicators::dyadic<extensions::scalar<evaluators::plus>>>();
    } else if(match_pattern<3, patterns::minus>(search)) {
        return build<applicators::dyadic<extensions::scalar<evaluators::minus>>>();
    } else if(match_pattern<3, patterns::times>(search)) {
        return build<applicators::dyadic<extensions::scalar<evaluators::times>>>();
    } else if(match_pattern<3, patterns::divide>(search)) {
        return build<applicators::dyadic<extensions::scalar<evaluators::divide>>>();
    } else if(match_pattern<3, patterns::maximum>(search)) {
        return build<applicators::dyadic<extensions::scalar<evaluators::maximum>>>();
    } else if(match_pattern<3, patterns::minimum>(search)) {
        return build<applicators::dyadic<extensions::scalar<evaluators::minimum>>>();
    } else if(match_pattern<3, patterns::power>(search)) {
        return build<applicators::dyadic<extensions::scalar<evaluators::power>>>();
    } else if(match_pattern<3, patterns::logarithm>(search)) {
        return build<applicators::dyadic<extensions::scalar<evaluators::logarithm>>>();
    } else if(match_pattern<3, patterns::residue>(search)) {
        return build<applicators::dyadic<extensions::scalar<evaluators::residue>>>();
    } else if(match_pattern<3, patterns::binomial>(search)) {
        return build<applicators::dyadic<extensions::scalar<evaluators::binomial>>>();
    } else if(match_pattern<3, patterns::circular_functions>(search)) {
        return build<applicators::dyadic<extensions::scalar<evaluators::circular_functions>>>();
    } else if(match_pattern<3, patterns::and_lcm>(search)) {
        return build<applicators::dyadic<extensions::scalar<evaluators::and_lcm>>>();
    } else if(match_pattern<3, patterns::or_gcd>(search)) {
        return build<applicators::dyadic<extensions::scalar<evaluators::or_gcd>>>();
    } else if(match_pattern<3, patterns::nand>(search)) {
        return build<applicators::dyadic<extensions::scalar<evaluators::nand>>>();
    } else if(match_pattern<3, patterns::nor>(search)) {
        return build<applicators::dyadic<extensions::scalar<evaluators::nor>>>();
    } else if(match_pattern<3, patterns::equal>(search)) {
        return build<applicators::dyadic<extensions::scalar<evaluators::equal>>>();
    } else if(match_pattern<3, patterns::less_than>(search)) {
        return build<applicators::dyadic<extensions::scalar<evaluators::less_than>>>();
    } else if(match_pattern<3, patterns::less_than_or_equal_to>(search)) {
        return build<applicators::dyadic<extensions::scalar<evaluators::less_than_or_equal_to>>>();
    } else if(match_pattern<3, patterns::not_equal>(search)) {
        return build<applicators::dyadic<extensions::scalar<evaluators::not_equal>>>();
    } else if(match_pattern<3, patterns::greater_than_or_equal_to>(search)) {
        return build<applicators::dyadic<extensions::scalar<evaluators::greater_than_or_equal_to>>>();
    } else if(match_pattern<3, patterns::greater_than>(search)) {
        return build<applicators::dyadic<extensions::scalar<evaluators::greater_than>>>();
    }

    /// Monadic array functions.
    else if(match_pattern<2, patterns::ravel>(search)) {
        return build<applicators::monadic<extensions::structural<evaluators::ravel>>>();
    } else if(match_pattern<2, patterns::shape>(search)) {
        return build<applicators::monadic<extensions::structural<evaluators::shape>>>();
    } else if(match_pattern<2, patterns::index_generator>(search)) {
        return build<applicators::monadic<extensions::structural<evaluators::index_generator>>>();
    } else if(match_pattern<2, patterns::table>(search)) {
        return build<applicators::monadic<extensions::structural<evaluators::table>>>();
    }

    /// Dyadic array functions.
    else if(match_pattern<3, patterns::reshape>(search)) {
        return build<applicators::dyadic<extensions::structural<evaluators::reshape>>>();
    } else if(match_pattern<3, patterns::join_1>(search)) {
        return build<applicators::dyadic<extensions::structural<evaluators::join_1>>>();
    } else if(match_pattern<3, patterns::join_2>(search)) {
        return build<applicators::dyadic<extensions::structural<evaluators::join_2>>>();
    }

    /// Operators.
    else if(match_pattern<3, patterns::reduction_1>(search)) {
        return build<applicators::dyadic<extensions::operators<evaluators::reduction>>>();
    }

    else if(match_pattern<3, patterns::index_origin_1>(search)) {
        return build<applicators::monadic<extensions::system_variable<evaluators::index_origin>>>();
    } else if(match_pattern<1, patterns::index_origin_2>(search)) {
        return build<applicators::niladic<extensions::system_variable<evaluators::index_origin>>>();
    } else if(match_pattern<3, patterns::print_precision_1>(search)) {
        return build<applicators::monadic<extensions::system_variable<evaluators::print_precision>>>();
    } else if(match_pattern<1, patterns::print_precision_2>(search)) {
        return build<applicators::niladic<extensions::system_variable<evaluators::print_precision>>>();
    }

    return nullptr;
}

 */
kepler::Token kepler::form_table::evaluate(search_t search, input_t input, kepler::Session* session) {
    auto applicator = lookup(std::move(search), session);
    if(!applicator) {
        throw error(InternalError, "Expected to find form-table evaluator for expression.");
    }
    return applicator->apply(input);
}
