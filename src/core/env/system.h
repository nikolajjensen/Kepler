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
#include "session.h"
#include "../datatypes.h"
#include "reduction_style.h"

#include <limits>
#include <string>

namespace kepler {
    namespace System {
        const static Number initialComparisonTolerance = 0.0001;
        const static UnsignedInteger initialIndexOrigin = 1;
        const static List<Token> initialLatentExpression = {};
        const static UnsignedInteger initialPrintPrecision = 3;
        const static Number initialRandomLink = 123;
        const static ReductionStyle reductionStyle = ReductionStyle::EncloseReductionStyle;
        const static StringUTF8 clearWorkspaceIdentifier = "unnamed";
        const static Number positiveNumberLimit = std::numeric_limits<Number>::max();
        const static Number negativeNumberLimit = std::numeric_limits<Number>::min();
        const static Integer positiveIntegerLimit = std::numeric_limits<Integer>::max();
        const static Integer negativeIntegerLimit = std::numeric_limits<Integer>::min();
        const static UnsignedInteger indexLimit = positiveIntegerLimit;
        const static UnsignedInteger countLimit = indexLimit;
        const static UnsignedInteger rankLimit = 15;
        const static UnsignedInteger workspaceNameLengthLimit = 25;
        const static UnsignedInteger identifierLengthLimit = countLimit;
        const static Integer quoteQuadOutputLimit = 1000;
        const static Number comparisonToleranceLimit = 1;
        const static Number integerTolerance = 0.001;
        const static Number realTolerance = 0.00001;
        const static UnsignedInteger fullPrintPrecision = std::to_string(negativeNumberLimit).length();
        const static UnsignedInteger printPrecisionLimit = fullPrintPrecision;
        const static UnsignedInteger exponentFieldWidth = 5;
        const static StringUTF8 indentPrompt = ">>>  ";
        const static StringUTF8 quadPrompt = ">  ";
        const static StringUTF8 functionDefinitionPrompt = indentPrompt;
        const static UnsignedInteger lineLimit = 100;
        const static UnsignedInteger definitionLineLimit = 100;

        kepler::Session new_session();
    };
};