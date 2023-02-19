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

#include <iostream>
#include <boost/preprocessor.hpp>

namespace kepler {
    enum TokenClass {
        AssignmentArrowToken,
        AxisErrorToken,
        BranchToken,
        BranchArrowToken,
        CharacterLiteralToken,
        ClearStateIndicatorToken,
        ColonToken,
        CommandCompleteToken,
        CommittedValueToken,
        CompleteIndexListToken,
        ConstantToken,
        DefinedFunctionToken,
        DefinedFunctionNameToken,
        DefinedDyadicOperatorToken,
        DefinedDyadicOperatorNameToken,
        DefinedMonadicOperatorToken,
        DefinedMonadicOperatorNameToken,
        DefinitionErrorToken,
        DistinguishedIdentifierToken,
        DomainErrorToken,
        DyadicOperatorToken,
        ElidedIndexMarkerToken,
        EscapeToken,
        ImplicitErrorToken,
        IncorrectCommandToken,
        IndexErrorToken,
        IndexSeparatorToken,
        InterruptToken,
        LabelToken,
        LabelNameToken,
        LeftArgumentNameToken,
        LeftAxisBracketToken,
        LeftEndOfStatementToken,
        LeftIndexBracketToken,
        LeftOperandNameToken,
        LeftParenthesisToken,
        LengthErrorToken,
        LimitErrorToken,
        LocalNameToken,
        MonadicOperatorToken,
        NilToken,
        NiladicDefinedFunctionToken,
        NiladicDefinedFunctionNameToken,
        NiladicSystemFunctionNameToken,
        NotCopiedToken,
        NotErasedToken,
        NotFoundToken,
        NotSavedToken,
        NumericLiteralToken,
        PartialIndexListToken,
        PrimitiveToken,
        PrimitiveFunctionToken,
        RankErrorToken,
        ResultNameToken,
        RightArgumentNameToken,
        RightAxisBracketToken,
        RightEndOfStatementToken,
        RightIndexBracketToken,
        RightOperandNameToken,
        RightParenthesisToken,
        SemicolonToken,
        SharedVariableToken,
        SharedVariableNameToken,
        SimpleIdentifierToken,
        SmallCircleToken,
        SyntaxErrorToken,
        SystemFunctionNameToken,
        SystemVariableNameToken,
        UnwindToken,
        ValenceErrorToken,
        ValueErrorToken,
        VariableToken,
        VariableNameToken,

        //Not present in ISO-13751:2001
        DirectIdentifierToken,
        StatementSeparatorToken,
    };
};