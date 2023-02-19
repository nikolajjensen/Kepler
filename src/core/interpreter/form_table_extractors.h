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

#pragma once

#include "form_table.h"
#include "core/token.h"
#include "core/error.h"

namespace kepler::form_table::extractors {
    template <typename Extension>
    struct argument_extractor : boost::static_visitor<Token> {
        Extension extension;
        kepler::Session* session;

        explicit argument_extractor(kepler::Session* session_) : extension(session_), session(session_) {}
    };

    template <typename Extension>
    struct niladic : argument_extractor<Extension> {
        using argument_extractor<Extension>::argument_extractor;

        Token operator()(const List<const Token*>& tokens) {
            if(!tokens.empty()) throw kepler::error(InternalError, "Expected no tokens.");
            return this->extension();
        }
    };

    template <typename Extension>
    struct monadic : argument_extractor<Extension> {
        using argument_extractor<Extension>::argument_extractor;

        Token operator()(const List<const Token*>& tokens) {
            if(tokens.size() != 1) throw kepler::error(InternalError, "Expected only one token.");
            return this->extension(*tokens[0]);
        }
    };

    template <typename Extension>
    struct dyadic : argument_extractor<Extension> {
        using argument_extractor<Extension>::argument_extractor;

        Token operator()(const List<const Token*>& tokens) {
            if(tokens.size() != 2) throw kepler::error(InternalError, "Expected only two tokens.");
            return this->extension(*tokens[0], *tokens[1]);
        }
    };

    template <typename Extension>
    struct triadic : argument_extractor<Extension> {
        using argument_extractor<Extension>::argument_extractor;

        Token operator()(const List<const Token*>& tokens) {
            if(tokens.size() != 3) throw kepler::error(InternalError, "Expected only three tokens.");
            return this->extension(*tokens[0], *tokens[1], *tokens[2]);
        }
    };
};