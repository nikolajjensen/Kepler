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

namespace kepler {
    Array::Array(List<int> shapeList_, List<element_type> ravelList_)
            : type(MixedType),
              shape_list(std::move(shapeList_)),
              ravel_list(std::move(ravelList_)) {
        type = sufficient_type();
    }

    Array::Array(ArrayType type, List<int> shapeList_, List<element_type> ravelList_)
            : type(type),
              shape_list(std::move(shapeList_)),
              ravel_list(std::move(ravelList_)) {
        if(type != sufficient_type()) {
            throw kepler::error(InternalError, "Sufficient type and given type mismatch.");
        }
    }

    ArrayType Array::sufficient_type() const {
        if(!ravel_list.empty()) {
            if(std::all_of(ravel_list.begin(), ravel_list.end(), [&](const element_type& element){ return element.type() == typeid(Char); })) {
                return CharacterType;
            } else if(std::all_of(ravel_list.begin(), ravel_list.end(), [&](const element_type& element){ return element.type() == typeid(Number); })) {
                return NumericType;
            } else {
                return MixedType;
            }
        } else {
            element_type element = typical_element();
            if(element.type() == typeid(Char)) {
                return CharacterType;
            } else if(element.type() == typeid(Number)) {
                return NumericType;
            } else {
                return MixedType;
            }
        }
    }

    int Array::rank() const {
        return (int)shape_list.size();
    }

    bool Array::is_simple() const {
        return type == CharacterType || type == NumericType;
    }

    bool Array::is_scalar() const {
        return rank() == 0;
    }

    bool Array::is_simple_scalar() const {
        return is_simple() && is_scalar();
    }

    Array Array::first_thingy() const {
        element_type element;
        if(is_empty()) {
            element = typical_element();
        } else {
            element = ravel_list[0];
        }

        if(element.type() == typeid(Number) || element.type() == typeid(Char)) {
            return Array({}, {element});
        } else {
            return boost::get<Array>(element);
        }
    }

    Array Array::numeric_scalar_with_value(const Number &num) const {
        return Array(NumericType, {}, {num});
    }

    int Array::count() const {
        return (int)ravel_list.size();
    }

    bool Array::is_vector() const {
        return rank() == 1;
    }

    bool Array::is_matrix() const {
        return rank() == 2;
    }

    int Array::length() const {
        return count();
    }

    Array::element_type Array::typical_element() const {
        if(type == NumericType) {
            return Number(0);
        } else {
            return constants::blank;
        }
    }

    bool Array::is_empty() const {
        return count() == 0;
    }

    template <typename T>
    Array Array::vectorOf(List<T>&& raw_ravel) {
        List<element_type> ravel;
        ravel.reserve(raw_ravel.size());
        for(const auto& input : raw_ravel) {
            ravel.push_back(input);
        }
        if(ravel.size() == 1) {
            return {{}, ravel};
        }
        return Array({(int)ravel.size()}, ravel);
    }
};

template kepler::Array kepler::Array::vectorOf(List<Char> &&ravel);
template kepler::Array kepler::Array::vectorOf(List<Number> &&ravel);