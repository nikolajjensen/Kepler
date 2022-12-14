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
#include "../datatypes.h"

#include <boost/variant.hpp>

namespace kepler {
    class Array {
    public:
        typedef List<boost::variant<Char, Number, boost::recursive_wrapper<Array>>> ravel_list_type;

        List<UnsignedInteger> shapeList;
        ravel_list_type ravelList;
        ArrayType type;

        Array() = default;
        Array(List<UnsignedInteger> shapeList, ravel_list_type ravelList);

        UnsignedInteger rank();

        static Array vectorOf(ravel_list_type ravelList);

        friend bool operator==(const Array& lhs, const Array& rhs) {
            return lhs.shapeList == rhs.shapeList && lhs.ravelList == rhs.ravelList;
        }
    };
};