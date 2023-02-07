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
#include "../token.h"
#include "../classifiers.h"
#include <boost/optional.hpp>
#include "form_table_evaluators.tpp"

using namespace kepler;
using namespace kepler::form_table;

bool kepler::form_table::match(kepler::Token *token, Selection &selection, const pattern_atomic &target) {
    if(selection == Content && token->content) {
        if(const kepler::Token::content_type* content = boost::get<kepler::Token::content_type>(&target)) {
            return *content == token->content.get();
        }
    } else if (selection == Type) {
        if(const TokenType* type = boost::get<TokenType>(&target)) {
            switch (*type) {
                case Constant:
                    return classifiers::is(*token, ConstantToken);
                case CompleteList:
                    return classifiers::is(*token, CompleteIndexListToken);
                case Func:
                    return classifiers::is(*token, PrimitiveFunctionToken)
                           || classifiers::is(*token, DefinedFunctionToken);
                case DFN:
                    return true;
            }
        }
    }

    return false;
}

template<std::size_t S, const pattern<S> &Pattern>
bool kepler::form_table::match_pattern(token_input &input, selector &selector) {
    if(input.size() < S) {
        return false;
    }

    for(int i = 0; i < S; ++i) {
        if(!match(input[i], selector[i], Pattern[i])) {
            return false;
        }
    }

    return true;
}

phrase_evaluator kepler::form_table::lookup(token_input&& input, selector&& selector) {
    // Big if statement where we compare the input to any of the patterns (in .h file)
    if(match_pattern<conjugate_size, conjugate>(input, selector)) {
        return evaluators::conjugate<conjugate_size, conjugate>;
    } else if(match_pattern<negation_size, negation>(input, selector)) {
        return evaluators::negation<negation_size, negation>;
    } else if(match_pattern<direction_size, direction>(input, selector)) {
        return evaluators::direction<direction_size, direction>;
    } else if(match_pattern<plus_size, plus>(input, selector)) {
        return evaluators::plus<plus_size, plus>;
    }

    return nullptr;
}

phrase_evaluator kepler::form_table::lookup(token_input& input, selector&& selector) {
    return lookup(std::move(input), std::move(selector));
}


kepler::Token kepler::form_table::evaluate(token_input&& input, selector&& selector) {
    return lookup(input, std::move(selector))(std::move(input));
}