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

#pragma once

#include "../datatypes.h"
#include "../token.h"

namespace kepler {
    namespace parser {
        void bind_token_class(kepler::Token& token) {
            if(token.tokenClass == TokenClass::SimpleIdentifierToken) {
                // Symbol Table lookup.
            } else if (token.tokenClass == TokenClass::DistinguishedIdentifierToken) {
                // Deal with this...
            }
        }

        void convert_tokens(kepler::List<kepler::Token>& tokens) {
            for(auto& token : tokens) {
                if(token.is_identifier()) {
                    bind_token_class(token);
                } else if (token.is_literal()) {
                    //literal_conversion(token);
                } else if (token.is_primitive()) {
                    // Don't do anything to the token.
                }
                //Potential error handling here...
            }
        }
    };
};