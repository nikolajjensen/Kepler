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
#include "models.h"
#include <uni_algo/conv.h>

namespace kepler {
    namespace lexer {
        namespace model_processing {
            int const TABSIZE = 4;

            struct TokenTypePrinter {
                void operator()(models::TokenType tokenType) const {
                    switch (tokenType) {
                        case models::TokenType::AssignmentArrow:
                            std::cout << "AssignmentArrow";
                            break;
                        case models::TokenType::DirectIdentifier:
                            std::cout << "DirectIdentifier";
                            break;
                        case models::TokenType::StatementSeparator:
                            std::cout << "StatementSeparator";
                            break;
                        case models::TokenType::SimpleIdentifier:
                            std::cout << "SimpleIdentifier";
                            break;
                        case models::TokenType::Primitive:
                            std::cout << "Primitive";
                            break;
                        case models::TokenType::DistinguishedIdentifier:
                            std::cout << "DistinguishedIdentifier";
                            break;
                        case models::TokenType::NumericLiteral:
                            std::cout << "NumericLiteral";
                            break;
                        case models::TokenType::CharacterLiteral:
                            std::cout << "CharacterLiteral";
                            break;
                        case models::TokenType::Unrecognized:
                            std::cout << "Unrecognized";
                            break;
                        default:
                            std::cout << "(Unrecognized TokenType)";
                            break;
                    }
                }
            };

            struct TokenPrinter {
                void operator()(models::Token token) const {
                    std::cout << "Token{"
                              << "type: ";
                    TokenTypePrinter printer;
                    printer(token.type);
                    std::cout << ", "
                              << "content: '";
                    boost::apply_visitor(TokenPrinter(), token.content);
                    std::cout << "'}";
                }

                void operator()(char32_t c) const {
                    std::cout << uni::utf32to8(std::u32string(1, c));
                }

                void operator()(std::u32string str) const {
                    std::cout << uni::utf32to8(str);
                }
            };

            struct TokenListPrinter {
                int indent;

                TokenListPrinter(int indent = 0) : indent(indent) {}

                void operator()(models::TokenList const& tokenList) const {
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
};