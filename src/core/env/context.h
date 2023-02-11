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

#include "mode.h"
#include "../token.h"
#include "../datatypes.h"
#include "defined_function.h"
#include "../error/error.h"

namespace kepler {
    class Context {
    public:
        Mode mode;
        List<Token> stack;
        StringUTF32 currentLine;
        List<Token> currentStatement;
        Token result;
        boost::optional<kepler::error> error;
        DefinedFunction* currentFunction;
        UnsignedInteger currentLineNumber;

        Context();
        Context(kepler::StringUTF8 line);
        Context(kepler::StringUTF32&& line);

        void setError(kepler::error error);
    };
};