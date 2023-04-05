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
#include "core/datatypes.h"
#include "core/array.h"

namespace kepler {

    /**
     * Returns the floor of the given number.
     *
     * Note that this function is defined for complex numbers.
     * The definition follows the one published as part of J's implementation.
     *
     * Source: https://www.jsoftware.com/papers/eem/complexfloor1.htm#0
     *
     * @param number The number to take the floor of.
     * @return The result of taking the floor of the given number.
     */
    Number floor(const Number& number);

    /**
     * Returns the binomial of two numbers.
     *
     * This function is defined in terms of the gamma function,
     * in a similar way to the factorial function.
     *
     * Source: https://help.dyalog.com/latest/Content/Language/Primitive%20Functions/Binomial.htm
     *
     * @param alpha The left argument.
     * @param omega The right argument.
     * @return The binomial of the two numbers.
     */
    Number binomial(const Number& alpha, const Number& omega);

    /**
     * Encloses elements in the subject array according to the partitioning.
     *
     * The behaviour is described in detail on this page:
     * https://aplwiki.com/wiki/Partitioned_Enclose
     *
     * @param partitioning The partitioning to use.
     * @param subject The array to enclose.
     * @return The result of the partitioned enclose operation.
     */
    Array partitioned_enclose(const Array& partitioning, const Array& subject);

    /**
    * Encloses elements in the subject string according to the partitioning.
    *
    * The behaviour is described in detail on this page:
    * https://aplwiki.com/wiki/Partitioned_Enclose
    *
    * @param partitioning The partitioning to use.
    * @param subject The string to enclose.
    * @return The result of the partitioned enclose operation.
    */
    Array partitioned_enclose(const Array& partitioning, const String& subject);

    /**
     * Returns an Array which consists of all elements in alpha, except those in omega.
     *
     * The behaviour is described in detail on this page:
     * https://aplwiki.com/wiki/Without
     *
     * @param alpha The array to remove elements from.
     * @param omega The array of elements to remove.
     * @return The result of the without operation.
     */
    Array without(const Array& alpha, const Array& omega);

    /**
     * Returns a String which consists of all symbols in alpha, except those in omega.
     *
     * The behaviour is described in detail on this page:
     * https://aplwiki.com/wiki/Without
     *
     * @param alpha The String to remove symbols from.
     * @param omega The String of symbols to remove.
     * @return The result of the without operation.
     */
    Array without(const String& alpha, const String& omega);

    /**
     * Performs a reshape operation. A new array is created which has the shape list
     * of alpha, and the elements of omega. If omega does not have enough elements,
     * elements are reused from the beginning.
     *
     * The behaviour is described in detail on this page:
     * https://aplwiki.com/wiki/Reshape
     *
     * @param alpha The Array containing the shape list.
     * @param omega The Array containing the elements to use as fillers.
     * @return The resulting array.
     */
    Array rho(const Array& alpha, const Array& omega);
};