//
// Copyright 2022 Nikolaj Banke Jensen.
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

#include <exception>
#include "token_converter.h"
#include "core/helpers/printers.h"
#include "core/constants/characters.h"
#include "core/helpers/classifiers.h"
#include "../interpreter/form_table.h"

void kepler::parser::bind_token_class(kepler::Token& token, kepler::Session& session) {
    if(kepler::classifiers::is(token, SimpleIdentifierToken)){
        TokenClass current_class = session.current_class(token);
        if(current_class == TokenClass::DefinedMonadicOperatorToken) {
            token.token_class = TokenClass::DefinedMonadicOperatorNameToken;
        } else if (current_class == TokenClass::DefinedDyadicOperatorToken) {
            token.token_class = TokenClass::DefinedDyadicOperatorNameToken;
        } else if (current_class == TokenClass::DefinedFunctionToken) {
            token.token_class = TokenClass::DefinedFunctionNameToken;
        } else if (current_class == TokenClass::NiladicDefinedFunctionToken) {
            token.token_class = TokenClass::NiladicDefinedFunctionNameToken;
        } else if (current_class == TokenClass::NilToken || current_class == TokenClass::VariableToken) {
            token.token_class = TokenClass::VariableNameToken;
        } else if (current_class == TokenClass::SharedVariableToken) {
            token.token_class = TokenClass::SharedVariableNameToken;
        } else if (current_class == TokenClass::LabelToken) {
            token.token_class = TokenClass::ConstantToken;
            token.content = session.get_current_referent(token).content;
        } else {
            // Should throw something here, this should never be reached.
            throw kepler::error(InternalError, "bind_token_class error: Unexpected case reached.");
        }
    } else if (token.token_class == TokenClass::DistinguishedIdentifierToken) {
        auto form_one = kepler::form_table::lookup({&token});
        auto form_two = kepler::form_table::lookup({&token, characters::left_arrow, form_table::Constant});
        auto form_three = kepler::form_table::lookup({&token, form_table::Constant});
        auto form_four = kepler::form_table::lookup({form_table::Constant, &token, form_table::Constant});

        if(form_one != nullptr && form_two != nullptr) {
            token.token_class = SystemVariableNameToken;
        } else if(form_one != nullptr && form_two == nullptr) {
            token.token_class = NiladicSystemFunctionNameToken;
        } else if(form_three != nullptr || form_four != nullptr) {
            token.token_class = SystemFunctionNameToken;
        } else {
            throw kepler::error(SyntaxError, "Distinguished identifier is unrecognised.");
        }
    }
}

void kepler::parser::literal_conversion(kepler::Token& token, kepler::Session& session) {
    List<Char> content = boost::get<List<Char>>(token.content.get());
    Array vector;

    if(token.token_class == TokenClass::CharacterLiteralToken) {
        List<Char> char_vector(content.begin(), content.end());
        char_vector.erase(char_vector.begin());
        char_vector.pop_back();
        token.content = Array::vectorOf(std::move(char_vector));
    } else if(token.token_class == TokenClass::NumericLiteralToken) {
        List<Number> numeric_vector;

        auto start = content.begin();
        auto end = content.end();

        while(start != end) {
            while(start != end && *start == characters::blank) { ++start; }
            auto cursor = start;

            do {
                ++cursor;
            } while(cursor != end && *cursor != kepler::characters::blank);

            numeric_vector.emplace_back(number_from_characters({start, cursor}));
            start = cursor;
        }

        token.content = Array::vectorOf(std::move(numeric_vector));
    }

    token.token_class = ConstantToken;
}

void kepler::parser::scalar_conversion(kepler::Token &token) {
    if(token.contains<List<Char>>()) {
        auto& list = token.get_content<List<Char>>();
        token.content = list[0];
    }
}

void kepler::parser::convert_tokens(kepler::List<kepler::Token>& tokens, kepler::Session& session) {
    for(auto& token : tokens) {
        if(classifiers::is_identifier(token)) {
            bind_token_class(token, session);
        } else if (classifiers::is_literal(token)) {
            literal_conversion(token, session);
        } else if (classifiers::is(token, kepler::PrimitiveToken)) {
            scalar_conversion(token);
        }
        // Potential error handling here (If the above if-statement returns an exception)...
    }
}