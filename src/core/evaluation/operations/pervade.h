//
// Copyright 2023 Nikolaj Banke Jensen.
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
#include "core/array.h"
#include "core/datatypes.h"

namespace kepler {

    /**
     * Mixin class for operations that pervade over an array.
     *
     * This means that if an operation inherits from PervadeMixin, and
     * does not implement any of the operator()(Array) methods, it will
     * be applied between each element of the array, in the traditional
     * APL way.
     */
    template <typename BASE>
    struct PervadeMixin : BASE {
        using BASE::BASE;
        using BASE::operator();

        /**
         * Pervade over the Array.
         *
         * This applies itself (this) to each element of the Array.
         *
         * @param omega The Array to apply the operation to.
         * @return A new Array with the result.
         */
        virtual Array operator()(const Array& omega);

        /**
         * Pervade over two Arrays.
         *
         * This applies itself (this) between each pair of elements of alpha and omega.
         *
         * If the arrays are equally sized, the operation is applied to each pair of elements.
         * If alpha is scalar, the operation is applied between alpha and every element of omega.
         * If omega is scalar, the operation is applied between every element of alpha and omega.
         *
         * @param alpha The left Array.
         * @param omega The right Array.
         * @return A new Array with the result.
         */
        virtual Array operator()(const Array& alpha, const Array& omega);

        /**
         * Pervade over two Strings.
         *
         * This applies itself (this) between each pair of Chars of alpha and omega.
         *
         * If the Strings are equally sized, the operation is applied to each pair of Chars.
         * If alpha is scalar, the operation is applied between alpha and every Char of omega.
         * If omega is scalar, the operation is applied between every Char of alpha and omega.
         *
         * @param alpha The left String.
         * @param omega The right String.
         * @return A new Array with the result.
         */
        virtual Array operator()(const String& alpha, const String& omega);

    private:
        /**
         * Apply the operation to the single element in the Array.
         */
        Array apply(const Array::element_type& omega);

        /**
         * Apply the operation to the single element in two Arrays.
         */
        Array apply(const Array::element_type& alpha, const Array::element_type& omega);
    };
};

// Include of .tpp file goes at the bottom.
#include "pervade.tpp"