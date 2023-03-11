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
#include "error.h"
#include "core/constants/literals.h"
#include <utility>
#include <numeric>
#include "core/helpers/conversion.h"
#include "core/helpers/array_printer.h"

namespace kepler {

    Array::Array(std::vector<int> shape_, std::vector<element_type> data_) : shape(std::move(shape_)), data(std::move(data_)) {}

    Array::Array(element_type scalar_) : shape(), data({std::move(scalar_)}) {}

    Array Array::major_cells() {
        return n_cells(shape.size() - 1);
    }

    Array Array::n_cells(int n) {
        if(n == 0) {
            return *this;
        }

        int rank = shape.size();

        if(n > rank) throw std::runtime_error("Array of rank " + std::to_string(rank) + " does not have " +
                                              std::to_string(n) + "-cells.");

        if(rank == n) {
            return Array({}, {*this});
        }

        std::vector<int> result_shape = {shape.end() - (rank - n), shape.end()};
        std::vector<int> cell_shape = {shape.begin(), shape.begin() + (rank - n)};

        int size = std::accumulate(cell_shape.begin(), cell_shape.end(), 1, std::multiplies<>());
        int result_size = std::accumulate(result_shape.begin(), result_shape.end(), 1, std::multiplies<>());

        std::vector<element_type> result_data;
        result_shape.reserve(result_size);
        for(int i = 0; i < result_size; ++i) {
            result_data.emplace_back(Array{cell_shape, {data.begin() + i * size, data.begin() + (i + 1) * size}});
        }

        return {result_shape, result_data};
    }

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
        return is_scalar() && !empty() && !holds_alternative<Array>(data[0]);
    }

    bool Array::is_numeric() const {
        return std::all_of(data.begin(), data.end(), [](const Array::element_type& element){
            return holds_alternative<Number>(element);
        });
    }

    bool Array::is_integer_numeric() const {
        return std::all_of(data.begin(), data.end(), [](const Array::element_type& element){
            if(!holds_alternative<Number>(element)) return false;
            auto n = get<Number>(element).real();
            return round(n) == n;
        });
    }

    bool Array::is_boolean() const {
        return std::all_of(data.begin(), data.end(), [](const Array::element_type& element){
            return holds_alternative<Number>(element) && (get<Number>(element) == 0.0 || get<Number>(element) == 1.0);
        });
    }

    std::string Array::to_string() const {
        ArrayPrinter printer;
        return printer(*this);
    }
};