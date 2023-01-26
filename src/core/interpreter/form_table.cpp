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
#include <boost/optional.hpp>

using namespace kepler;
using namespace kepler::interpreter;

Token form_table::evaluators::conjugate(List<Token> &operands) {
    Token num = operands[1];
    if(Array* arr = boost::get<Array>(&(num.content).get())) {
        if(Number* n = boost::get<Number>(&(arr->ravelList.front()))) {
            if(n->imaginaryScalar) {
                n->imaginaryScalar.get() *= -1;
            }
        }
    } else {
        num.tokenClass = DomainErrorToken;
        num.content = boost::none;
    }
    return num;
}

bool form_table::match_form(const List<Token> &tokens, const List<PatternClass>& form, const List<Token>& pattern) {
    if(tokens.size() != form.size()) {
        return false;
    }

    bool success = true;
    int index = 0;

    while(success && index < form.size()) {
        const PatternClass& formClass = form[index];
        const Token& token = tokens[index];
        const Token& pattern_token = pattern[index];

        switch (formClass) {
            case Content:
                success = pattern_token.content == pattern_token.content;
                break;
            case DFN:
                success = pattern_token.tokenClass == NiladicDefinedFunctionToken || pattern_token.tokenClass == DefinedFunctionToken;
                break;
            case B:
                success = pattern_token.is(ConstantToken);
                break;
            default:
                success = false;
        }

        ++index;
    }

    return success;
}

boost::optional<Token> form_table::form_table_evaluation(List<Token> &&tokens, List<PatternClass> form) {
    if(tokens.size() != form.size()) {
        std::cerr << "Form table error: Token list is not same length as form." << std::endl;
        return boost::none;
    }

    if(match_form(tokens, form, patterns::conjugate)) {
        return evaluators::conjugate(tokens);
    } /*else if(match_form(tokens, form, patterns::negative)) {
        return evaluators::negative(tokens);
    }*/

    return boost::none;
}

/*
boost::optional<Token> form_table::form_table_evaluation(List<Token>&& tokens, const List<Token> &pattern) {
    if(!match_pattern(tokens, pattern)) {
        return boost::none;
    }

    // Pattern must match, so find the right evaluator, and call it.
    size_t pattern_length = pattern.size();

    if(pattern_length == 2) {
        if(pattern == patterns::conjugate) {
            return kepler::interpreter::form_table::evaluators::conjugate(tokens);
        }
    } else if (pattern_length == 3) {

    }
}
*/