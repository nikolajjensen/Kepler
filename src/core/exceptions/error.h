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

namespace kepler {
    enum ErrorType {
        SyntaxError,
        ValueError,
        DomainError,
        InternalError
    };

    class error : public std::exception {
    private:
        ErrorType error_type;
        std::string message;
        int position;

    public:
        error(ErrorType error_type_, std::string message_, int position_ = -1) : error_type(error_type_), message(std::move(message_)), position(position_) {}

        std::string type() {
            switch (error_type) {
                case SyntaxError:
                    return "SYNTAX ERROR";
                case ValueError:
                    return "VALUE ERROR";
                case DomainError:
                    return "DOMAIN ERROR";
                case InternalError:
                    return "INTERNAL ERROR";
                default:
                    return "UNDEFINED ERROR";
            }
        }

        std::string why() {
            return message;
        }

        int where() {
            return position;
        }
    };
};