//
// Copyright 2022 Nikolaj Banke Jensen.
//
// This file is part of Test.
// 
// Test is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Test is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License 
// along with Test. If not, see <https://www.gnu.org/licenses/>.
//

#pragma once

#include "error_handler.h"
#include "../datatypes.h"

namespace kepler {
    namespace lexer {
        typedef List<Char>::const_iterator iterator_type;

        typedef x3::phrase_parse_context<rules::skipper_type>::type phrase_context_type;
        typedef error_handler<iterator_type> error_handler_type;
        typedef x3::context<error_handler_tag, std::reference_wrapper<error_handler_type>, phrase_context_type> context_type;
    };
};