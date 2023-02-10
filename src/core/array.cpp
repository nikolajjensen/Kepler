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

kepler::Array::Array(List<UnsignedInteger> shapeList_, ravel_list_type ravelList_) : shapeList(std::move(shapeList_)), ravelList(std::move(ravelList_)), type() {}

kepler::Integer kepler::Array::rank() const {
    return (Integer)shapeList.size();
}

template <typename T>
kepler::Array kepler::Array::vectorOf(List<T>&& raw_ravel) {
    ravel_list_type ravel;
    ravel.reserve(raw_ravel.size());
    for(const auto& input : raw_ravel) {
        ravel.push_back(input);
    }
    if(ravel.size() == 1) {
        return {{}, ravel};
    }
    return Array({(UnsignedInteger)ravel.size()}, ravel);
}

template kepler::Array kepler::Array::vectorOf(List<Char> &&ravel);
template kepler::Array kepler::Array::vectorOf(List<Number> &&ravel);