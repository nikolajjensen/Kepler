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
    class Environment {
    public:
        const Number initialComparisonTolerance = 0.0001;
        const UnsignedInteger initialIndexOrigin = 1;
        const List<Token> initialLatentExpression = {};
        const UnsignedInteger initialPrintPrecision = 3;
        const Number initialRandomLink = 123;
        const ReductionStyle reductionStyle = ReductionStyle::EncloseReductionStyle;
        const StringUTF8 clearWorkspaceIdentifier = "unnamed";
        const Number positiveNumberLimit = Number::numeric_limit_max();
        const Number negativeNumberLimit = Number::numeric_limit_min();
        const Integer positiveIntegerLimit = std::numeric_limits<Integer>::max();
        const Integer negativeIntegerLimit = std::numeric_limits<Integer>::min();
        const UnsignedInteger indexLimit = positiveIntegerLimit;
        const UnsignedInteger countLimit = indexLimit;
        const UnsignedInteger rankLimit = 15;
        const UnsignedInteger workspaceNameLengthLimit = 25;
        const UnsignedInteger identifierLengthLimit = countLimit;
        const Integer quoteQuadOutputLimit = 1000;
        const Number comparisonToleranceLimit = 1;
        const Number integerTolerance = 0.001;
        const Number realTolerance = 0.00001;
        const UnsignedInteger fullPrintPrecision = 64;
        const UnsignedInteger printPrecisionLimit = fullPrintPrecision;
        const UnsignedInteger exponentFieldWidth = 5;
        const StringUTF8 indentPrompt = ">>>  ";
        const StringUTF8 quadPrompt = ">  ";
        const StringUTF8 functionDefinitionPrompt = indentPrompt;
        const UnsignedInteger lineLimit = 100;
        const UnsignedInteger definitionLineLimit = 100;

    private:
        List<Session> sessions;


    public:
        kepler::Session* spawn_session();
        void evaluate(kepler::Session*);

        Environment();
    };
};