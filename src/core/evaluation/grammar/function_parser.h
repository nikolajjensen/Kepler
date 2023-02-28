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
#include "matcher.h"
#include "context.h"
#include "core/error.h"
#include "core/datatypes.h"
#include "rules.h"

namespace kepler {
    class FunctionParser : public grammar::Matcher<Char, grammar::function_context> {
    public:
        using grammar::Matcher<Char, grammar::function_context>::Matcher;

        void parse() {
            if(!grammar::Matcher<Char, grammar::function_context>::match(grammar::rules::opening_request)) {
                throw kepler::error(DefinitionError, "Could not parse input.");
            }
        }

        Token& get_identifier() {
            return context.identifier;
        }

        std::vector<Char>& get_request() {
            return context.request;
        }
    };
};