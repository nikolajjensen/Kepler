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
#include "array_type.h"
#include "datatypes.h"

#include <boost/variant.hpp>

namespace kepler {
    class Array {
    public:
        typedef boost::variant<Char, Number, Array> element_type;
        typedef List<element_type> ravel_list_type;

        List<UnsignedInteger> shapeList;
        ravel_list_type ravelList;
        ArrayType type;

        Array() = default;
        Array(List<UnsignedInteger> shapeList, ravel_list_type ravelList);

        Integer rank() const;

        template <typename T>
        static Array vectorOf(List<T>&& ravelList);


        template <typename Variant>
        bool contains_at(int i) const {
            return ravelList[i].type() == typeid(Variant);
        }

        template <typename Variant>
        Variant& get_content(int i = 0) {
            return boost::get<Variant>(ravelList[i]);
        }

        template <typename Variant>
        const Variant& get_content(int i = 0) const {
            return boost::get<const Variant>(ravelList[i]);
        }

        bool empty() const {
            return ravelList.empty();
        }

        friend bool operator==(const Array& lhs, const Array& rhs) {
            return lhs.shapeList == rhs.shapeList && lhs.ravelList == rhs.ravelList;
        }

        Array& operator=(const Array& other) {
            this->shapeList = other.shapeList;
            this->ravelList = other.ravelList;

            return *this;
        }
    };
};