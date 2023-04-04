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

#include "helpers.h"
#include "literals.h"
#include <iomanip>
#include "error.h"

bool kepler::helpers::is_function(TokenType type) {
    return type == PLUS || type == MINUS || type == TIMES || type == DIVIDE || type == FLOOR
           || type == CEILING || type == RIGHT_TACK || type == LEFT_TACK || type == IOTA || type == LESS
           || type == LESS_EQUAL || type == EQUAL || type == GREATER_EQUAL || type == GREATER || type == NOT_EQUAL
           || type == WITHOUT || type == LEFT_SHOE || type == RHO || type == AND || type == OR
           || type == NAND || type == NOR || type == CIRCLE_BAR || type == CIRCLE_STILE || type == QUESTION_MARK
           || type == CIRCLE || type == STAR || type == LOG || type == BAR || type == EXCLAMATION_MARK
           || type == COMMA || type == ARROW_UP;
}

bool kepler::helpers::is_monadic_function(TokenType type) {
    return type == QUESTION_MARK;
}

bool kepler::helpers::is_monadic_operator(TokenType type) {
    return type == COMMUTE || type == DIAERESIS || type == SLASH || type == PRODUCT;
}

bool kepler::helpers::is_dyadic_operator(TokenType type) {
    return type == JOT || type == ATOP || type == OVER || type == PRODUCT || type == POWER;
}

bool kepler::helpers::is_array_token(TokenType type) {
    return type == NUMBER || type == STRING || type == ID || type == ALPHA || type == OMEGA;
}

void kepler::helpers::check_valid_system_param_value(const String &id, const Array &value) {
    if(value.empty() || !std::holds_alternative<Number>(value.data[0])) {
        throw kepler::Error(DomainError, "Invalid system parameter value.");
    }

    return check_valid_system_param_value(id, std::get<Number>(value.data[0]));
}

void kepler::helpers::check_valid_system_param_value(const String &id, const Number &value) {
    if(id == constants::index_origin_id) {
        if(value != 1.0 && value != 0.0) {
            throw kepler::Error(LimitError, "Index origin can only be either 0 or 1.");
        }
    } else if(id == constants::print_precision_id) {
        if(value.real() < 1 || value.real() > 30) {
            throw kepler::Error(LimitError, "Print precision must be between 1 and 30.");
        }
    }
}

std::string kepler::helpers::double_to_string(const double& num, int precision) {
    std::stringstream ss;
    ss << std::setprecision(precision);
    ss << num;

    std::string raw = ss.str();

    if(!raw.empty() && raw.front() == '-') {
        raw.erase(0, 1);
        if(raw != "0") {
            raw.insert(0, "¯");
        }
    }

    auto e_index = raw.find_first_of('e');
    if(e_index != std::string::npos) {
        auto mantissa_string = raw.substr(e_index + 1);
        raw.erase(e_index);

        int mantissa = std::stoi(mantissa_string);

        if(mantissa > 0 && mantissa < precision) {
            raw += std::string(mantissa, '0');
        } else if(mantissa < 0 && -mantissa < precision - 3) {
            raw = "0." + std::string(abs(mantissa) - 1, '0') + raw;
        } else {
            bool negative_mantissa = mantissa_string.front() == '-';
            mantissa_string.erase(0, 1);

            mantissa_string.erase(0, std::min(mantissa_string.find_first_not_of('0'), mantissa_string.size()-1));

            if(negative_mantissa && mantissa_string != "0") {
                mantissa_string.insert(0, "¯");
            }

            raw += "E" + mantissa_string;
        }
    }

    return raw;
}

std::string kepler::helpers::number_to_string(const kepler::Number& num, int precision) {
    String result = uni::utf8to32u(kepler::helpers::double_to_string(num.real(), precision));

    if (num.imag() != 0) {
        result = result + String(1, constants::complex_marker) +
                 uni::utf8to32u(kepler::helpers::double_to_string(num.imag(), precision));
    }

    return uni::utf32to8(result);
}