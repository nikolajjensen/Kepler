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
#include "operation.h"
#include "core/datatypes.h"
#include "core/evaluation/ast.h"


namespace kepler {

    /**
     * Represents a monadic operation.
     *
     * This struct is intended for other monadic operations to inherit from.
     */
    struct MonadicOp : Operation {
    protected:
        Operation_ptr op;

    public:
        explicit MonadicOp(Operation_ptr op_);
    };

    /**
     * Represents the commutate operator.
     *
     * Monadic:
     *      ⍴⍨ 3      ⍝ ⍵ ⍴ ⍵
     *  3 3 3
     *
     * Dyadic:
     *     2 ⍴⍨ 3     ⍝ ⍵ ⍴ ⍺
     *  2 2 2
     *
     *  Credit: http:://dyalog.com
     */
    struct Commute : MonadicOp {
        using MonadicOp::MonadicOp;

        Array operator()(const Array& alpha, const Array& omega) override;
        Array operator()(const Array& omega) override;
    };

    /**
     * Represents the reduction of an array.
     *
     *       +/ 1 2 3 4 5
     *  15
     *
     *  Credit: http:://dyalog.com
     */
    struct Slash : MonadicOp {
        using MonadicOp::MonadicOp;

        Array operator()(const Array& alpha, const Array& omega) override;
        Array operator()(const Array& omega) override;
    };

    /**
     * Represents the application of a function to every element of an array.
     *
     *       +/¨ (1 2 3 4)(5 6 7)
     *  10 18
     *
     *  Credit: http:://dyalog.com
     */
    struct Diaeresis : MonadicOp {
        using MonadicOp::MonadicOp;

        Array operator()(const Array& alpha, const Array& omega) override;
        Array operator()(const Array& omega) override;
    };

    /**
     * Represents the outer product of two arrays.
     *
     *       1 2 3 ∘.× 4 5 6 7
     *   4  5  6  7
     *   8 10 12 14
     *  12 15 18 21
     *
     *  Credit: http:://dyalog.com
     */
    struct OuterProduct : MonadicOp {
        using MonadicOp::MonadicOp;

        Array operator()(const Array& alpha, const Array& omega) override;
    };
};