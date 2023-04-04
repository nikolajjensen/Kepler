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
    bool is_function(TokenType type);
    bool is_monadic_operator(TokenType type);
    bool is_monadic_function(TokenType type);
    bool is_dyadic_operator(TokenType type);
    bool is_array_token(TokenType type);

    void check_valid_system_param_value(const std::u32string& id, const Array& value);
    void check_valid_system_param_value(const std::u32string& id, const Number& value);

    std::string number_to_string(const Number& num, int precision = 10);
    std::string double_to_string(const double& num, int precision);
};