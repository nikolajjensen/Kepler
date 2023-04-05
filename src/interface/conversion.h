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
#include <string>
#include "core/datatypes.h"
#include "core/token_type.h"

namespace kepler {

    /**
     * Converts a string to a Number.
     * @param num_str The string to convert.
     * @return The Number representation of the string.
     */
    Number from_string(const std::string& num_str);

    /**
     * Converts a TokenType to a string.
     * @param type The TokenType to convert.
     * @return The string representation of the TokenType.
     */
    std::string to_string(const TokenType& type);
};