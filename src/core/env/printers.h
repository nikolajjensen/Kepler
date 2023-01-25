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

#include "../token_class.h"
#include "../token.h"

#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <iostream>
#include <uni_algo/conv.h>

namespace kepler {
    namespace printers {
        int const TABSIZE = 4;

        struct TokenTypePrinter {
            void operator()(TokenClass tokenType) const {
                switch (tokenType) {
                    case AssignmentArrowToken:
                        std::cout << "AssignmentArrowToken";
                        break;
                    case AxisErrorToken:
                        std::cout << "AxisErrorToken";
                        break;
                    case BranchToken:
                        std::cout << "BranchToken";
                        break;
                    case BranchArrowToken:
                        std::cout << "BranchArrowToken";
                        break;
                    case CharacterLiteralToken:
                        std::cout << "CharacterLiteralToken";
                        break;
                    case ClearStateIndicatorToken:
                        std::cout << "ClearStateIndicatorToken";
                        break;
                    case ColonToken:
                        std::cout << "ColonToken";
                        break;
                    case CommandCompleteToken:
                        std::cout << "CommandCompleteToken";
                        break;
                    case CommittedValueToken:
                        std::cout << "CommittedValueToken";
                        break;
                    case CompleteIndexListToken:
                        std::cout << "CompleteIndexListToken";
                        break;
                    case ConstantToken:
                        std::cout << "ConstantToken";
                        break;
                    case DefinedFunctionToken:
                        std::cout << "DefinedFunctionToken";
                        break;
                    case DefinedFunctionNameToken:
                        std::cout << "DefinedFunctionNameToken";
                        break;
                    case DefinedDyadicOperatorToken:
                        std::cout << "DefinedDyadicOperatorToken";
                        break;
                    case DefinedDyadicOperatorNameToken:
                        std::cout << "DefinedDyadicOperatorNameToken";
                        break;
                    case DefinedMonadicOperatorToken:
                        std::cout << "DefinedMonadicOperatorToken";
                        break;
                    case DefinedMonadicOperatorNameToken:
                        std::cout << "DefinedMonadicOperatorNameToken";
                        break;
                    case DefinitionErrorToken:
                        std::cout << "DefinitionErrorToken";
                        break;
                    case DistinguishedIdentifierToken:
                        std::cout << "DistinguishedIdentifierToken";
                        break;
                    case DomainErrorToken:
                        std::cout << "DomainErrorToken";
                        break;
                    case DyadicOperatorToken:
                        std::cout << "DyadicOperatorToken";
                        break;
                    case ElidedIndexMarkerToken:
                        std::cout << "ElidedIndexMarkerToken";
                        break;
                    case EscapeToken:
                        std::cout << "EscapeToken";
                        break;
                    case ImplicitErrorToken:
                        std::cout << "ImplicitErrorToken";
                        break;
                    case IncorrectCommandToken:
                        std::cout << "IncorrectCommandToken";
                        break;
                    case IndexErrorToken:
                        std::cout << "IndexErrorToken";
                        break;
                    case IndexSeparatorToken:
                        std::cout << "IndexSeparatorToken";
                        break;
                    case InterruptToken:
                        std::cout << "InterruptToken";
                        break;
                    case LabelToken:
                        std::cout << "LabelToken";
                        break;
                    case LabelNameToken:
                        std::cout << "LabelNameToken";
                        break;
                    case LeftArgumentNameToken:
                        std::cout << "LeftArgumentNameToken";
                        break;
                    case LeftAxisBracketToken:
                        std::cout << "LeftAxisBracketToken";
                        break;
                    case LeftEndOfStatementToken:
                        std::cout << "LeftEndOfStatementToken";
                        break;
                    case LeftIndexBracketToken:
                        std::cout << "LeftIndexBracketToken";
                        break;
                    case LeftOperandNameToken:
                        std::cout << "LeftOperandNameToken";
                        break;
                    case LeftParenthesisToken:
                        std::cout << "LeftParenthesisToken";
                        break;
                    case LengthErrorToken:
                        std::cout << "LengthErrorToken";
                        break;
                    case LimitErrorToken:
                        std::cout << "LimitErrorToken";
                        break;
                    case LocalNameToken:
                        std::cout << "LocalNameToken";
                        break;
                    case MonadicOperatorToken:
                        std::cout << "MonadicOperatorToken";
                        break;
                    case NilToken:
                        std::cout << "NilToken";
                        break;
                    case NiladicDefinedFunctionToken:
                        std::cout << "NiladicDefinedFunctionToken";
                        break;
                    case NiladicDefinedFunctionNameToken:
                        std::cout << "NiladicDefinedFunctionNameToken";
                        break;
                    case NiladicSystemFunctionNameToken:
                        std::cout << "NiladicSystemFunctionNameToken";
                        break;
                    case NotCopiedToken:
                        std::cout << "NotCopiedToken";
                        break;
                    case NotErasedToken:
                        std::cout << "NotErasedToken";
                        break;
                    case NotFoundToken:
                        std::cout << "NotFoundToken";
                        break;
                    case NotSavedToken:
                        std::cout << "NotSavedToken";
                        break;
                    case NumericLiteralToken:
                        std::cout << "NumericLiteralToken";
                        break;
                    case PartialIndexListToken:
                        std::cout << "PartialIndexListToken";
                        break;
                    case PrimitiveToken:
                        std::cout << "PrimitiveToken";
                        break;
                    case PrimitiveFunctionToken:
                        std::cout << "PrimitiveFunctionToken";
                        break;
                    case RankErrorToken:
                        std::cout << "RankErrorToken";
                        break;
                    case ResultNameToken:
                        std::cout << "ResultNameToken";
                        break;
                    case RightArgumentNameToken:
                        std::cout << "RightArgumentNameToken";
                        break;
                    case RightAxisBracketToken:
                        std::cout << "RightAxisBracketToken";
                        break;
                    case RightEndOfStatementToken:
                        std::cout << "RightEndOfStatementToken";
                        break;
                    case RightIndexBracketToken:
                        std::cout << "RightIndexBracketToken";
                        break;
                    case RightOperandNameToken:
                        std::cout << "RightOperandNameToken";
                        break;
                    case RightParenthesisToken:
                        std::cout << "RightParenthesisToken";
                        break;
                    case SemicolonToken:
                        std::cout << "SemicolonToken";
                        break;
                    case SharedVariableToken:
                        std::cout << "SharedVariableToken";
                        break;
                    case SharedVariableNameToken:
                        std::cout << "SharedVariableNameToken";
                        break;
                    case SimpleIdentifierToken:
                        std::cout << "SimpleIdentifierToken";
                        break;
                    case SmallCircleToken:
                        std::cout << "SmallCircleToken";
                        break;
                    case SyntaxErrorToken:
                        std::cout << "SyntaxErrorToken";
                        break;
                    case SystemFunctionNameToken:
                        std::cout << "SystemFunctionNameToken";
                        break;
                    case SystemVariableNameToken:
                        std::cout << "SystemVariableNameToken";
                        break;
                    case UnwindToken:
                        std::cout << "UnwindToken";
                        break;
                    case ValueErrorToken:
                        std::cout << "ValueErrorToken";
                        break;
                    case VariableToken:
                        std::cout << "VariableToken";
                        break;
                    case VariableNameToken:
                        std::cout << "VariableNameToken";
                        break;
                    default:
                        std::cout << tokenType;
                        break;
                }
            }
        };

        struct ArrayPrinter {
            void operator()(Array array) const {
                std::cout << "[";
                for(size_t i = 0; i < array.ravelList.size(); ++i) {
                    boost::apply_visitor(ArrayPrinter(), array.ravelList[i]);

                    if(i != array.ravelList.size() - 1) {
                        std::cout << ", ";
                    }
                }
                std::cout << "]";
            }

            void operator()(Char& c) const {
                std::cout << uni::utf32to8(StringUTF32(1, c));
            }

            template <typename T>
            void operator()(T& element) const {
                std::cout << element;
            }
        };

        struct TokenPrinter {
            void operator()(Token token) const {
                std::cout << "Token{"
                          << "class: ";
                TokenTypePrinter printer;
                printer(token.tokenClass);

                if(token.content) {
                    std::cout << ", "
                              << "content: '";
                    boost::apply_visitor(TokenPrinter(), *token.content);
                    std::cout << "'";

                }
                std::cout << "}";
            }

            void operator()(Char c) const {
                std::cout << uni::utf32to8(std::u32string(1, c));
            }

            void operator()(List<Char> chars) const {
                std::cout << uni::utf32to8(std::u32string(chars.begin(), chars.end()));
            }

            void operator()(Array array) const {
                ArrayPrinter printer;
                printer(array);
            }

            void operator()(List<Number> numbers) const {
                std::cout << "[";
                for(auto& number : numbers) {
                    std::cout << number << " ";
                }
                std::cout << "]";
            }
        };

        struct TokenListPrinter {
            int indent;

            TokenListPrinter(int indent = 0) : indent(indent) {}

            void operator()(List<Token> const& tokenList) const {
                std::cout << "{" << std::endl;
                for(size_t i = 0; i < tokenList.size(); ++i) {
                    tab(TABSIZE);
                    std::cout << i << ":\t\t";
                    TokenPrinter printer;
                    printer(tokenList[i]);
                    std::cout << "\n";
                }
                std::cout << "}" << std::endl;
            }

            void tab(int spaces) const {
                for (int i = 0; i < spaces; ++i)
                    std::cout << ' ';
            }
        };
    };
};