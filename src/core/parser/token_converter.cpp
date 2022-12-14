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

#include "token_converter.h"

void kepler::parser::bind_token_class(kepler::Token& token, kepler::Session& session) {
    if(token.tokenClass == TokenClass::SimpleIdentifierToken) {
        TokenClass current_class = session.current_class(token);
        if(current_class == TokenClass::DefinedMonadicOperatorToken) {
            token.tokenClass = TokenClass::DefinedMonadicOperatorNameToken;
        } else if (current_class == TokenClass::DefinedDyadicOperatorToken) {
            token.tokenClass = TokenClass::DefinedDyadicOperatorNameToken;
        } else if (current_class == TokenClass::DefinedFunctionToken) {
            token.tokenClass = TokenClass::DefinedFunctionNameToken;
        } else if (current_class == TokenClass::NiladicDefinedFunctionToken) {
            token.tokenClass = TokenClass::NiladicDefinedFunctionNameToken;
        } else if (current_class == TokenClass::NilToken || current_class == TokenClass::VariableToken) {
            token.tokenClass = TokenClass::VariableNameToken;
        } else if (current_class == TokenClass::SharedVariableToken) {
            token.tokenClass = TokenClass::SharedVariableNameToken;
        } else if (current_class == TokenClass::LabelToken) {
            token.tokenClass = TokenClass::ConstantToken;
            token.content = session.current_referent(token).content;
        } else {
            // Should throw something here, this should never be reached.
            throw "";
        }
    } else if (token.tokenClass == TokenClass::DistinguishedIdentifierToken) {
        // Deal with this...
    }
}

void kepler::parser::literal_conversion(kepler::Token& token, kepler::Session& session) {
    List<Char> content = boost::get<List<Char>>(token.content.get());
    Array vector;

    if(token.tokenClass == TokenClass::CharacterLiteralToken) {
        Array::ravel_list_type char_vector(content.begin(), content.end());
        char_vector.erase(char_vector.begin());
        char_vector.pop_back();
        vector = Array::vectorOf(char_vector);
    } else if(token.tokenClass == TokenClass::NumericLiteralToken) {
        Array::ravel_list_type numeric_vector;

        auto start = content.begin();
        while(start != content.end()) {
            auto end = start;

            while(end != content.end() && *end != U' ') {
                ++end;
            }

            numeric_vector.emplace_back(Number({start, end}));
            start = end;
        }

        vector = Array::vectorOf(numeric_vector);
    }

    token.tokenClass = ConstantToken;
    token.content = vector;
}

void kepler::parser::convert_tokens(kepler::List<kepler::Token>& tokens, kepler::Session& session) {
    for(auto& token : tokens) {
        if(token.is_identifier()) {
            bind_token_class(token, session);
        } else if (token.is_literal()) {
            literal_conversion(token, session);
        }
        // Don't do anything if token is primitive.
        // Potential error handling here (If the above if-statement returns an exception)...
    }
}