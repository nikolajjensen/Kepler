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
#include "array_types.h"

#include <boost/variant.hpp>

namespace kepler {
    class Array {
    public:
        typedef boost::variant<Char, Number, boost::recursive_wrapper<Array>> element_type;

        ArrayType type;
        List<int> shape_list;
        List<element_type> ravel_list;

        Array() = default;
        Array(List<int> shapeList, List<element_type> ravelList);
        Array(ArrayType type, List<int> shapeList, List<element_type> ravelList);

        ArrayType sufficient_type() const;
        int rank() const;
        bool is_simple() const;
        bool is_scalar() const;
        bool is_simple_scalar() const;
        Array first_thingy() const;
        Array numeric_scalar_with_value(const Number& num) const;
        int count() const;
        bool is_vector() const;
        bool is_matrix() const;
        int length() const;
        element_type typical_element() const;
        bool is_empty() const;




        template <typename T>
        static Array vectorOf(List<T>&& ravelList);


        template <typename Variant>
        bool contains_at(int i) const {
            return ravel_list[i].type() == typeid(Variant);
        }

        template <typename Variant>
        Variant& get_content(int i = 0) {
            return boost::get<Variant>(ravel_list[i]);
        }

        template <typename Variant>
        const Variant& get_content(int i = 0) const {
            return boost::get<const Variant>(ravel_list[i]);
        }

        friend bool operator==(const Array& lhs, const Array& rhs) {
            return lhs.shape_list == rhs.shape_list && lhs.ravel_list == rhs.ravel_list;
        }

        Array& operator=(const Array& other) {
            this->shape_list = other.shape_list;
            this->ravel_list = other.ravel_list;

            return *this;
        }
    };
};