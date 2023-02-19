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
#include "core/error/error.h"
#include "session.h"

#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <iostream>
#include <uni_algo/conv.h>
#include <iomanip>

namespace kepler {
    namespace printers {
        int const TABSIZE = 4;

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
                    default:
                        stream << tokenType;
                        break;
                }
            }
        };

        struct ArrayPrinter {
            std::ostream& stream;
            int print_precision;

            explicit ArrayPrinter(std::ostream& stream_, int print_precision_ = -1) : stream(stream_), print_precision(print_precision_) {}

            void operator()(const Array& array) const {
                //stream << std::setprecision(print_precision);

                if(array.shapeList.size() == 0) {
                    boost::apply_visitor(*this, array.ravelList[0]);
                } if(array.shapeList.size() == 1) {
                    for(int e = 0; e < array.shapeList[0]; ++e) {
                        boost::apply_visitor(*this, array.ravelList[e]);
                        if(e < array.shapeList[0] - 1) {
                            stream << " ";
                        }
                    }
                } else if(array.shapeList.size() == 2) {
                    for(int row = 0; row < array.shapeList[0]; ++row) {
                        for(int col = 0; col < array.shapeList[1]; ++col) {
                            boost::apply_visitor(*this, array.ravelList[row * array.shapeList[0] + col]);
                            if(col < array.shapeList[1] - 1) {
                                stream << " ";
                            }
                        }
                    }
                }
            }

            void operator()(const Char& c) const {
                stream << uni::utf32to8(StringUTF32(1, c));
            }

            void operator()(const Number& n) const {
                stream << number_to_string(n, print_precision);
            }
        };

        struct ErrorPrinter {
            std::ostream& stream;
            const std::string padding = "    ";

            explicit ErrorPrinter(std::ostream& stream_) : stream(stream_) {}

            void operator()(const kepler::error& err) const {
                stream << err.type() << ": " << err.why();
                std::string where = err.where();
                if(!where.empty()) {
                    stream << "\n" << where;
                }
            }
        };

        struct TokenPrinter {
            std::ostream& stream;
            int print_precision;

            explicit TokenPrinter(std::ostream& stream_, int print_precision_ = -1) : stream(stream_), print_precision(print_precision_) {}

            void operator()(const Token& token) const {
                if(token.content) {
                    boost::apply_visitor(*this, token.content.get());
                }
            }

            void operator()(const Char& c) const {
                stream << uni::utf32to8(std::u32string(1, c));
            }

            void operator()(const List<Char>& chars) const {
                stream << uni::utf32to8(std::u32string(chars.begin(), chars.end()));
            }

            void operator()(const Array& array) const {
                ArrayPrinter printer(stream, print_precision);
                printer(array);
            }

            void operator()(const List<Number>& numbers) const {
                for(int i = 0; i < numbers.size(); ++i) {
                    stream << number_to_string(numbers[i], print_precision);
                    if(i < numbers.size() - 1) {
                        stream << " ";
                    }
                }
            }
        };

        struct ArrayDebugPrinter {
            std::ostream& stream;

            explicit ArrayDebugPrinter(std::ostream& stream_) : stream(stream_) {}

            void operator()(const Array& array) const {
                stream << "<Array>[";
                if(array.shapeList.size() == 0) {
                    boost::apply_visitor(*this, array.ravelList[0]);
                } if(array.shapeList.size() == 1) {
                    for(int e = 0; e < array.shapeList[0]; ++e) {
                        boost::apply_visitor(*this, array.ravelList[e]);
                        if(e < array.shapeList[0] - 1) {
                            stream << " ";
                        }
                    }
                } else if(array.shapeList.size() == 2) {
                    for(int row = 0; row < array.shapeList[0]; ++row) {
                        for(int col = 0; col < array.shapeList[1]; ++col) {
                            boost::apply_visitor(*this, array.ravelList[row * array.shapeList[0] + col]);
                            if(col < array.shapeList[1] - 1) {
                                stream << " ";
                            }
                        }
                    }
                }
                stream << "]";
            }

            void operator()(const Char& c) const {
                stream << uni::utf32to8(StringUTF32(1, c));
            }

            void operator()(const Number& num) const {
                stream << number_to_string(num);
            }
        };

        struct TokenDebugPrinter {
            std::ostream& stream;

            explicit TokenDebugPrinter(std::ostream& stream_) : stream(stream_) {}

            void operator()(const Token& token) const {
                stream << "Token{";
                TokenTypePrinter printer(stream);
                printer(token.token_class);

                if(token.content) {
                    stream << ", ";
                    boost::apply_visitor(*this, token.content.get());

                }
                stream << "}";
            }

            void operator()(const Char& c) const {
                stream << "<Char>" << uni::utf32to8(std::u32string(1, c));
            }

            void operator()(const List<Char>& chars) const {
                stream << "<List<Char>>" << uni::utf32to8(std::u32string(chars.begin(), chars.end()));
            }

            void operator()(const Array& array) const {
                ArrayDebugPrinter printer(stream);
                printer(array);
            }

            void operator()(const List<Number>& numbers) const {
                stream << "<List<Number>>[";
                for(int i = 0; i < numbers.size(); ++i) {
                    stream << number_to_string(numbers[i]);
                    if(i < numbers.size() - 1) {
                        stream << " ";
                    }
                }
                stream << "]";
            }
        };
    };
};