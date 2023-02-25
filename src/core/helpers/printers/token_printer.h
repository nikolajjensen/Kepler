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
#include "core/token.h"
#include "array_printer.h"
#include "token_type_printer.h"

namespace kepler::helpers {
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

    struct TokenListDebugPrinter {
        std::ostream& stream;

        explicit TokenListDebugPrinter(std::ostream& stream_) : stream(stream_) {}

        void operator()(const List<Token>& tokens) const {
            TokenDebugPrinter printer(stream);

            stream << "{\n";
            for(int i = 0; i < tokens.size(); ++i) {
                stream << "\t[" << i << "]\t";
                if(i < 10) {
                    stream << "\t";
                }
                printer(tokens[i]);
                stream << "\n";
            }
            stream << "}\n";
        }
    };
};