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
#include <sstream>
#include <utility>
#include <boost/optional.hpp>
#include "error_type.h"
#include "datatypes.h"
#include "core/helpers/printers/token_printer.h"

#include <uni_algo/conv.h>

namespace kepler {

    class error : public std::exception {
    public:
        ErrorType error_type;
        std::string message;
        boost::optional<int> position;
        boost::optional<boost::variant<std::vector<Char>, std::vector<Token>>> input;

        error(ErrorType error_type_,
              std::string message_,
              int position_,
              boost::variant<std::vector<Char>, std::vector<Token>> input_)
              : error_type(error_type_),
                message(std::move(message_)),
                position(position_),
                input(std::move(input_)) {}

        error(ErrorType error_type_,
              std::string message_)
                : error_type(error_type_),
                  message(std::move(message_)),
                  position(boost::none),
                  input(boost::none) {}

        std::string type() const {
            return to_string(error_type);
        }

        std::string why() const {
            return message;
        }

        struct visitor : boost::static_visitor<> {
            std::ostream& stream;

            explicit visitor(std::ostream& stream_) : stream(stream_) {}

            void operator()(const std::vector<Char>& vec) {
                std::string str = uni::utf32to8(std::u32string(vec.begin(), vec.end()));
                stream << str;
            }

            void operator()(const std::vector<Token>& vec) {
                helpers::TokenPrinter pr(stream);
                for(auto& token : vec) {
                    pr(token);
                }
            }
        };

        std::string where() const {
            std::stringstream ss;

            if(input && position) {
                ss << "   ";
                visitor v(ss);
                boost::apply_visitor(v, input.get());
                ss << "\n";

                ss << "   ";
                for (int i = 0; i < position.get(); ++i) {
                    ss << "~";
                }
                ss << "^";
            }

            return ss.str();
        }
    };
};