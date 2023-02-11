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
#include <boost/optional.hpp>
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

kepler::form_table::evaluator kepler::form_table::lookup(search_t &&search) {
    if(match_pattern<patterns::monadic, patterns::conjugate>(search)) {
        return [](List<Token*> tokens){
            return applicators::monadic<applicators::scalar<evaluators::conjugate>>()(tokens);
        };
    } else if(match_pattern<patterns::monadic, patterns::negative>(search)) {
        return [](List<Token*> tokens){
            return applicators::monadic<applicators::scalar<evaluators::negative>>()(tokens);
        };
    } else if(match_pattern<patterns::monadic, patterns::direction>(search)) {
        return [](List<Token*> tokens){
            return applicators::monadic<applicators::scalar<evaluators::direction>>()(tokens);
        };
    } else if(match_pattern<patterns::dyadic, patterns::plus>(search)) {
        return [](List<Token*> tokens){
            return applicators::dyadic<applicators::scalar<evaluators::plus>>()(tokens);
        };
    } else if(match_pattern<patterns::dyadic, patterns::divide>(search)) {
        return [](List<Token*> tokens){
            return applicators::dyadic<applicators::scalar<evaluators::divide>>()(tokens);
        };
    } else if(match_pattern<patterns::monadic, patterns::shape>(search)) {
        return [](List<Token*> tokens){
            return applicators::monadic<applicators::array<evaluators::shape>>()(tokens);
        };
    }

    return nullptr;
}

kepler::Token kepler::form_table::evaluate(search_t search, input_t input) {
    auto evaluator = lookup(std::move(search));
    if(evaluator == nullptr) {
        throw error(InternalError, "Expected to find form-table evaluator for expression.");
    }
    return evaluator(std::move(input));
}