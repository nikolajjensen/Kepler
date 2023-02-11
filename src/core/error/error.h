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
#include <utility>
#include "error_type.h"

namespace kepler {
    class error : public std::exception {
    public:
        ErrorType error_type;
        std::string message;
        int position;

        error(ErrorType error_type_, std::string message_, int position_ = -1) : error_type(error_type_), message(std::move(message_)), position(position_) {}

        std::string type() const {
            return to_string(error_type);
        }

        std::string why() const {
            return message;
        }

        int where() const {
            return position;
        }
    };
};