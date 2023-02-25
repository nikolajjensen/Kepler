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

#include <uni_algo/conv.h>

namespace kepler {
    class error : public std::exception {
    public:
        ErrorType error_type;
        std::string message;
        boost::optional<int> position;
        boost::optional<std::string> input_line;

        error(ErrorType error_type_,
              std::string message_,
              boost::optional<int> position_ = boost::none,
              boost::optional<std::string> input_line_ = boost::none)
              : error_type(error_type_),
                message(std::move(message_)),
                position(position_),
                input_line(std::move(input_line_)) {}

        error(ErrorType error_type_,
              std::string message_,
              boost::optional<int> position_,
              boost::optional<List<Char>> input_line_)
                : error_type(error_type_),
                  message(std::move(message_)),
                  position(position_),
                  input_line(uni::utf32to8(std::u32string(input_line_->begin(), input_line_->end()))) {}

        std::string type() const {
            return to_string(error_type);
        }

        std::string why() const {
            return message;
        }

        std::string where() const {
            std::stringstream ss;

            if(input_line && position) {
                ss << "   " << input_line.get() << "\n";
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