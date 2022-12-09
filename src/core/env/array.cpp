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

kepler::Array::Array(List<UnsignedInteger> shapeList_, List<boost::variant<Char, Number, Array>> ravelList_) : shapeList(shapeList_), ravelList(ravelList_) {}

kepler::UnsignedInteger kepler::Array::rank() {
    return shapeList.size();
}

kepler::Array kepler::Array::vectorOf(List<boost::variant<Char, Number, Array>> ravelList) {
    return Array({(UnsignedInteger)ravelList.size()}, ravelList);
}