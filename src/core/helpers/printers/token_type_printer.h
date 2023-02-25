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
#include <iostream>
#include "core/token_class.h"

namespace kepler::helpers {
    struct TokenTypePrinter {
        std::ostream& stream;

        explicit TokenTypePrinter(std::ostream& stream_) : stream(stream_) {}

        void operator()(TokenClass tokenType) const {
            switch (tokenType) {
                case AssignmentArrowToken:
                    stream << "AssignmentArrowToken";
                    break;
                case AxisErrorToken:
                    stream << "AxisErrorToken";
                    break;
                case BranchToken:
                    stream << "BranchToken";
                    break;
                case BranchArrowToken:
                    stream << "BranchArrowToken";
                    break;
                case CharacterLiteralToken:
                    stream << "CharacterLiteralToken";
                    break;
                case ClearStateIndicatorToken:
                    stream << "ClearStateIndicatorToken";
                    break;
                case ColonToken:
                    stream << "ColonToken";
                    break;
                case CommandCompleteToken:
                    stream << "CommandCompleteToken";
                    break;
                case CommittedValueToken:
                    stream << "CommittedValueToken";
                    break;
                case CompleteIndexListToken:
                    stream << "CompleteIndexListToken";
                    break;
                case ConstantToken:
                    stream << "ConstantToken";
                    break;
                case DefinedFunctionToken:
                    stream << "DefinedFunctionToken";
                    break;
                case DefinedFunctionNameToken:
                    stream << "DefinedFunctionNameToken";
                    break;
                case DefinedDyadicOperatorToken:
                    stream << "DefinedDyadicOperatorToken";
                    break;
                case DefinedDyadicOperatorNameToken:
                    stream << "DefinedDyadicOperatorNameToken";
                    break;
                case DefinedMonadicOperatorToken:
                    stream << "DefinedMonadicOperatorToken";
                    break;
                case DefinedMonadicOperatorNameToken:
                    stream << "DefinedMonadicOperatorNameToken";
                    break;
                case DefinitionErrorToken:
                    stream << "DefinitionErrorToken";
                    break;
                case DistinguishedIdentifierToken:
                    stream << "DistinguishedIdentifierToken";
                    break;
                case DomainErrorToken:
                    stream << "DomainErrorToken";
                    break;
                case DyadicOperatorToken:
                    stream << "DyadicOperatorToken";
                    break;
                case ElidedIndexMarkerToken:
                    stream << "ElidedIndexMarkerToken";
                    break;
                case EscapeToken:
                    stream << "EscapeToken";
                    break;
                case ImplicitErrorToken:
                    stream << "ImplicitErrorToken";
                    break;
                case IncorrectCommandToken:
                    stream << "IncorrectCommandToken";
                    break;
                case IndexErrorToken:
                    stream << "IndexErrorToken";
                    break;
                case IndexSeparatorToken:
                    stream << "IndexSeparatorToken";
                    break;
                case InterruptToken:
                    stream << "InterruptToken";
                    break;
                case LabelToken:
                    stream << "LabelToken";
                    break;
                case LabelNameToken:
                    stream << "LabelNameToken";
                    break;
                case LeftArgumentNameToken:
                    stream << "LeftArgumentNameToken";
                    break;
                case LeftAxisBracketToken:
                    stream << "LeftAxisBracketToken";
                    break;
                case LeftEndOfStatementToken:
                    stream << "LeftEndOfStatementToken";
                    break;
                case LeftIndexBracketToken:
                    stream << "LeftIndexBracketToken";
                    break;
                case LeftOperandNameToken:
                    stream << "LeftOperandNameToken";
                    break;
                case LeftParenthesisToken:
                    stream << "LeftParenthesisToken";
                    break;
                case LengthErrorToken:
                    stream << "LengthErrorToken";
                    break;
                case LimitErrorToken:
                    stream << "LimitErrorToken";
                    break;
                case LocalNameToken:
                    stream << "LocalNameToken";
                    break;
                case MonadicOperatorToken:
                    stream << "MonadicOperatorToken";
                    break;
                case NilToken:
                    stream << "NilToken";
                    break;
                case NiladicDefinedFunctionToken:
                    stream << "NiladicDefinedFunctionToken";
                    break;
                case NiladicDefinedFunctionNameToken:
                    stream << "NiladicDefinedFunctionNameToken";
                    break;
                case NiladicSystemFunctionNameToken:
                    stream << "NiladicSystemFunctionNameToken";
                    break;
                case NotCopiedToken:
                    stream << "NotCopiedToken";
                    break;
                case NotErasedToken:
                    stream << "NotErasedToken";
                    break;
                case NotFoundToken:
                    stream << "NotFoundToken";
                    break;
                case NotSavedToken:
                    stream << "NotSavedToken";
                    break;
                case NumericLiteralToken:
                    stream << "NumericLiteralToken";
                    break;
                case PartialIndexListToken:
                    stream << "PartialIndexListToken";
                    break;
                case PrimitiveToken:
                    stream << "PrimitiveToken";
                    break;
                case PrimitiveFunctionToken:
                    stream << "PrimitiveFunctionToken";
                    break;
                case RankErrorToken:
                    stream << "RankErrorToken";
                    break;
                case ResultNameToken:
                    stream << "ResultNameToken";
                    break;
                case RightArgumentNameToken:
                    stream << "RightArgumentNameToken";
                    break;
                case RightAxisBracketToken:
                    stream << "RightAxisBracketToken";
                    break;
                case RightEndOfStatementToken:
                    stream << "RightEndOfStatementToken";
                    break;
                case RightIndexBracketToken:
                    stream << "RightIndexBracketToken";
                    break;
                case RightOperandNameToken:
                    stream << "RightOperandNameToken";
                    break;
                case RightParenthesisToken:
                    stream << "RightParenthesisToken";
                    break;
                case SemicolonToken:
                    stream << "SemicolonToken";
                    break;
                case SharedVariableToken:
                    stream << "SharedVariableToken";
                    break;
                case SharedVariableNameToken:
                    stream << "SharedVariableNameToken";
                    break;
                case SimpleIdentifierToken:
                    stream << "SimpleIdentifierToken";
                    break;
                case SmallCircleToken:
                    stream << "SmallCircleToken";
                    break;
                case SyntaxErrorToken:
                    stream << "SyntaxErrorToken";
                    break;
                case SystemFunctionNameToken:
                    stream << "SystemFunctionNameToken";
                    break;
                case SystemVariableNameToken:
                    stream << "SystemVariableNameToken";
                    break;
                case UnwindToken:
                    stream << "UnwindToken";
                    break;
                case ValueErrorToken:
                    stream << "ValueErrorToken";
                    break;
                case VariableToken:
                    stream << "VariableToken";
                    break;
                case VariableNameToken:
                    stream << "VariableNameToken";
                    break;
                case StatementSeparatorToken:
                    stream << "StatementSeparatorToken";
                    break;
                default:
                    stream << tokenType;
                    break;
            }
        }
    };
};