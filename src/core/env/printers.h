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
                    case TokenClass::AssignmentArrowToken:
                        std::cout << "AssignmentArrowToken";
                        break;
                    case TokenClass::DirectIdentifierToken:
                        std::cout << "DirectIdentifierToken";
                        break;
                    case TokenClass::StatementSeparatorToken:
                        std::cout << "StatementSeparatorToken";
                        break;
                    case TokenClass::SimpleIdentifierToken:
                        std::cout << "SimpleIdentifierToken";
                        break;
                    case TokenClass::PrimitiveToken:
                        std::cout << "PrimitiveToken";
                        break;
                    case TokenClass::DistinguishedIdentifierToken:
                        std::cout << "DistinguishedIdentifierToken";
                        break;
                    case TokenClass::NumericLiteralToken:
                        std::cout << "NumericLiteralToken";
                        break;
                    case TokenClass::CharacterLiteralToken:
                        std::cout << "CharacterLiteralToken";
                        break;
                    default:
                        std::cout << "(Unrecognized TokenType)";
                        break;
                }
            }
        };

        struct ArrayPrinter {
            void operator()(Array array) const {
                std::cout << "[";
                for(auto& element : array.ravelList) {
                    boost::apply_visitor(ArrayPrinter(), element);
                }
                std::cout << "]";
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
                std::cout << ", "
                          << "content: '";
                if(auto content = token.content) {
                    boost::apply_visitor(TokenPrinter(), *token.content);
                }
                std::cout << "'}";
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