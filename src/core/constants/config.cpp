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
#include "config.h"
#include "core/constants/literals.h"
#include "core/array.h"
#include "core/error.h"

namespace kepler {
    void constants::check_valid_system_param_value(const std::u32string &id, const Array &value) {
        if(value.empty() || !holds_alternative<Number>(value.data[0])) {
            throw kepler::error(DomainError, "Invalid system parameter value.");
        }

        return check_valid_system_param_value(id, get<Number>(value.data[0]));
    }

    void constants::check_valid_system_param_value(const std::u32string &id, const Number &value) {
        if(id == index_origin_id) {
            if(value != 1.0 && value != 0.0) {
                throw kepler::error(LimitError, "Index origin can only be either 0 or 1.");
            }
        } else if(id == print_precision_id) {
            if(value.real() < 1 || value.real() > 30) {
                throw kepler::error(LimitError, "Print precision must be between 1 and 30.");
            }
        }
    }
};