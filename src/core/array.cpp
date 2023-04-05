//
// Copyright 2022 Nikolaj Banke Jensen.
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

#include "array.h"
#include <utility>
#include <numeric>
#include <variant>
#include <algorithm>
#include "interface/array_printer.h"
#include "symbol_table.h"
#include "literals.h"

namespace kepler {

    Array::Array(std::vector<unsigned int> shape_, std::vector<element_type> data_) : shape(std::move(shape_)), data(std::move(data_)) {}

    Array::Array(element_type scalar_) : shape(), data({scalar_}) {}

    int Array::rank() const {
        return shape.size();
    }

    bool Array::is_scalar() const {
        return shape.empty();
    }

    int Array::size() const {
        return data.size();
    }

    int Array::flattened_shape() const {
        return std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<>());
    }

    bool Array::empty() const {
        return data.empty();
    }

    bool Array::is_simple_scalar() const {
        return is_scalar() && !empty() && !std::holds_alternative<Array>(data[0]);
    }

    bool Array::is_numeric() const {
        return std::all_of(data.begin(), data.end(), [](const Array::element_type& element){
            return std::holds_alternative<Number>(element);
        });
    }

    bool Array::is_integer_numeric() const {
        return std::all_of(data.begin(), data.end(), [](const Array::element_type& element){
            if(std::holds_alternative<Number>(element)) {
                auto n = std::get<Number>(element).real();
                return round(n) == n;
            } else if(std::holds_alternative<Array>(element)) {
                return std::get<Array>(element).is_integer_numeric();
            }
            return false;
        });
    }

    std::string Array::to_string(const SymbolTable* symbol_table) const {
        auto& arr = symbol_table->get<Array>(constants::print_precision_id);
        ArrayPrinter printer((int)std::get<Number>(arr.data[0]).real());
        return printer(*this);
    }
};