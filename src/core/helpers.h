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
#include "core/token.h"

namespace kepler::helpers {

    /**
     * Returns true if the TokenType is a 'function' according to the grammar of Kepler.
     */
    bool is_function(TokenType type);

    /**
     * Returns true if the TokenType is a 'monadic operator' according to the grammar of Kepler.
     */
    bool is_monadic_operator(TokenType type);

    /**
     * Returns true if the TokenType is a 'monadic function' according to the grammar of Kepler.
     */
    bool is_monadic_function(TokenType type);

    /**
     * Returns true if the TokenType is a 'dyadic operator' according to the grammar of Kepler.
     */
    bool is_dyadic_operator(TokenType type);

    /**
     * Returns true if the TokenType is a 'dyadic function' according to the grammar of Kepler.
     */
    bool is_array_token(TokenType type);

    /**
     * Throws a kepler::Error if the value is not a valid value for the given id.
     *
     * This is used to ensure that system variables, like '⎕IO', are set to valid values.
     * @param id The id of the system variable.
     * @param value The proposed value.
     */
    void check_valid_system_param_value(const String& id, const Array& value);

    /**
     * Throws a kepler::Error if the value is not a valid value for the given id.
     *
     * This is used to ensure that system variables, like '⎕IO', are set to valid values.
     * @param id The id of the system variable.
     * @param value The proposed value.
     */
    void check_valid_system_param_value(const String& id, const Number& value);

    /**
     * Converts a Number to a string, with the given precision.
     * @param num The Number to convert.
     * @param precision The precision to use.
     * @return The string representation of the Number.
     */
    std::string number_to_string(const Number& num, int precision = 10);

    /**
     * Converts a double to a string, with the given precision.
     *
     * @param num
     * @param precision
     * @return
     */
    std::string double_to_string(const double& num, int precision);
};