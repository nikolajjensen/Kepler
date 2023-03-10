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

#pragma once
#include "datatypes.h"
#include <variant>

namespace kepler {
    struct Array {
    public:
        using element_type = std::variant<std::u32string, Number, Array>;

        std::vector<int> shape;
        std::vector<element_type> data;

        Array(std::vector<int> shape_, std::vector<element_type> data_);
        Array(element_type scalar_);

        Array major_cells();
        Array n_cells(int n);
        int rank() const;
        int size() const;
        bool empty() const;
        bool is_scalar() const;
        bool is_simple_scalar() const;
        bool is_numeric() const;
        bool is_boolean() const;
        std::string to_string() const;

        friend bool operator==(const Array& lhs, const Array& rhs) {
            return lhs.shape == rhs.shape && lhs.data == rhs.data;
        }

    private:
        std::string scalar_string(const element_type& element) const;
    };
};