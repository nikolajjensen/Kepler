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
    // Forward declaration to avoid circular dependency.
    struct SymbolTable;

    /**
     * Central data structure in Kepler.
     *
     * Represents a multidimensional array of elements.
     * The elements can be of either type String, Number or Array.
     *
     * Elements can be of mixed type.
     *
     * The shape of the array is stored in the shape vector,
     * while the data is stored in the data vector.
     */
    struct Array {
        // Possible types of elements in the array.
        using element_type = std::variant<String, Number, Array>;

        std::vector<unsigned int> shape;
        std::vector<element_type> data;

        /**
         * Creates an Array with the given shape and data.
         *
         * @param shape_ The shape of the array.
         * @param data_ The data of the array.
         */
        Array(std::vector<unsigned int> shape_, std::vector<element_type> data_);

        /**
         * Creates an Array of one element (also called a Scalar)
         * @param scalar_ The value to enclose in the Array.
         */
        explicit Array(element_type scalar_);


        /**
         * Returns the rank of the Array.
         *
         * The rank is the number of dimensions in the Array.
         * It is equal to the length of the shape vector.
         *
         * @return The rank of the Array.
         */
        [[nodiscard]] int rank() const;

        /**
         * Returns the number of elements in the data vector of the Array.
         *
         * @return The number of elements in the Array.
         */
        [[nodiscard]] int size() const;

        /**
         * Returns the product of all elements in the shape vector.
         *
         * @return The product of all elements in the shape vector.
         */
        [[nodiscard]] int flattened_shape() const;

        /**
         * Returns true the data list is empty.
         */
        [[nodiscard]] bool empty() const;

        /**
         * Returns true the shape list is empty.
         */
        [[nodiscard]] bool is_scalar() const;

        /**
         * Returns true the array contains a single element, which is not an array.
         */
        [[nodiscard]] bool is_simple_scalar() const;

        /**
         * Returns true if every element of the Array is a Number.
         */
        [[nodiscard]] bool is_numeric() const;

        /**
         * Returns true if every element of the Array is a Number, and is an integer.
         */
        [[nodiscard]] bool is_integer_numeric() const;

        /**
         * Returns a string representation of the Array.
         *
         * The SymbolTable is used to resolve the print precision '⎕PP',
         * so numbers can be printed with the correct precision.
         *
         * @param symbol_table The SymbolTable to get the print precision from.
         * @return The string representation of the Array.
         */
        std::string to_string(const SymbolTable* symbol_table) const;

        /**
         * Returns true if two Arrays are equal.
         *
         * Equality is defined as having the same shape and data.
         *
         * @param lhs The left-hand Array.
         * @param rhs The right-hand Array.
         * @return True if the Arrays are equal, false otherwise.
         */
        friend bool operator==(const Array& lhs, const Array& rhs) {
            return lhs.shape == rhs.shape && lhs.data == rhs.data;
        }
    };
};