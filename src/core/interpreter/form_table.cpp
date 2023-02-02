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

using namespace kepler;
using namespace kepler::interpreter;

Token form_table::evaluators::conjugate(List<Token> &operands) {
    Token token = operands[1];
    if(classifiers::is_scalar(token)) {
        auto& arr = token.get_content<Array>();
        if(arr.contains_at<Number>(0)) {
            auto& num = arr.get_content<Number>(0);
            num.conjugate();
        }
    } else {
        token.set(DomainErrorToken, boost::none);
    }

    return token;
}

Token form_table::evaluators::negative(List<Token> &operands) {
    Token token = operands[1];
    if(classifiers::is_scalar(token)) {
        auto& arr = token.get_content<Array>();
        if(arr.contains_at<Number>(0)) {
            auto& num = arr.get_content<Number>(0);
            num = 0 - num;
        }
    } else {
        token.set(DomainErrorToken, boost::none);
    }

    return token;
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
                success = pattern_token.content == token.content;
                break;
            case DFN:
                success = classifiers::is(pattern_token, NiladicDefinedFunctionToken) || classifiers::is(pattern_token, DefinedFunctionToken);
                break;
            case B:
                success = classifiers::is(pattern_token, ConstantToken);
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
    } else if(match_form(tokens, form, patterns::negative)) {
        return evaluators::negative(tokens);
    }

    return boost::none;
}