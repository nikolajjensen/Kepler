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
#include "form_table.h"
#include "../exceptions/error.h"
boost::variant<kepler::Number, kepler::Char> kepler::form_table::evaluators::conjugate(boost::variant<Number, Char> &input) {
    if(Number* number = boost::get<Number>(&input)) {
        return conj(*number);
    } else {
        throw kepler::error(DomainError, "Expected a number.");
    }
}
/*

boost::variant<kepler::Number, kepler::Char> kepler::form_table::evaluators::negative(boost::variant<Number, Char> &input) {
    if(Number* number = boost::get<Number>(&input)) {
        return Number(0) - *number;
    } else {
        throw kepler::error(DomainError, "Expected a number.");
    }
}

boost::variant<kepler::Number, kepler::Char> kepler::form_table::evaluators::direction(boost::variant<Number, Char> &input) {
    if(Number* number = boost::get<Number>(&input)) {
        if(*number != 0.0) {
            *number = *number / abs(*number);
        }
        return *number;
    } else {
        throw kepler::error(DomainError, "Expected a number.");
    }
}

boost::variant<kepler::Number, kepler::Char> kepler::form_table::evaluators::plus(boost::variant<Number, Char>& lhs, boost::variant<Number, Char>& rhs) {
    if(Number* lhs_number = boost::get<Number>(&lhs)) {
        if(Number* rhs_number = boost::get<Number>(&rhs)) {
            return *lhs_number + *rhs_number;
        }
    }

    throw kepler::error(DomainError, "Expected a number.");
}

boost::variant<kepler::Number, kepler::Char> kepler::form_table::evaluators::divide(boost::variant<Number, Char>& lhs, boost::variant<Number, Char>& rhs) {
    if(Number* lhs_number = boost::get<Number>(&lhs)) {
        if(Number* rhs_number = boost::get<Number>(&rhs)) {
            if(*rhs_number != 0.0) {
                return *lhs_number / *rhs_number;
            } else {
                throw kepler::error(DomainError, "Divide by 0.");
            }
        }
    }

    throw kepler::error(DomainError, "Expected a number.");
}

kepler::Array kepler::form_table::evaluators::shape(kepler::Array &input) {
    List<Number> ravel;
    ravel.reserve(input.shapeList.size());
    for(auto& dim : input.shapeList) {
        ravel.emplace_back(dim);
    }
    return Array::vectorOf(std::move(ravel));
}
 */