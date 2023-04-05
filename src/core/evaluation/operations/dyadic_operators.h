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
#include "core/evaluation/ast.h"

namespace kepler {

    /**
     * Represents a dyadic operation.
     *
     * This struct is intended for other dyadic operations to inherit from.
     */
    struct DyadicOp : Operation {
    protected:
        Operation_ptr aalpha;
        Operation_ptr oomega;

    public:
        explicit DyadicOp(Operation_ptr aalpha_, Operation_ptr oomega_);
    };

    /**
     * The Jot operator.
     *
     * ⌽∘⍳¨ 3 4 5
     *  ┌─────┬───────┬─────────┐
     *  │3 2 1│4 3 2 1│5 4 3 2 1│
     *  └─────┴───────┴─────────┘
     *
     *        ¯1 ⌽∘⍳¨ 3 4 5
     *  ┌─────┬───────┬─────────┐
     *  │3 1 2│4 1 2 3│5 1 2 3 4│
     *  └─────┴───────┴─────────┘
     *
     * Credit: http:://dyalog.com
     */
    struct Jot : DyadicOp {
        using DyadicOp::DyadicOp;

        Array operator()(const Array& alpha, const Array& omega) override;
        Array operator()(const Array& omega) override;
    };

    /**
     * The Atop operator.
     *
     *       -⍤÷ 4      ⍝ (  f⍤g y) ≡  f   g y
     *  ¯0.25
     *       12 -⍤÷ 4   ⍝ (x f⍤g y) ≡ (f x g y)
     *  ¯3
     *
     * Credit: http:://dyalog.com
     */
    struct Atop : DyadicOp {
        using DyadicOp::DyadicOp;

        Array operator()(const Array& alpha, const Array& omega) override;
        Array operator()(const Array& omega) override;
    };

    /**
     * The Over operator.
     *
     *       -⍥⌊ 3.6                 ⍝ Same as ∘ or ⍤ monadically
     *  ¯3
     *        5.1 -⍥⌊ 3.6             ⍝ Applies ⌊ to both arguments
     *   2
     *
     * Credit: http:://dyalog.com
     */
    struct Over : DyadicOp {
        using DyadicOp::DyadicOp;

        Array operator()(const Array& alpha, const Array& omega) override;
        Array operator()(const Array& omega) override;
    };

    /**
     * The inner product.
     *
     *      1 2 3 +.× 4 5 6
     * 32
     *
     * Credit: http:://dyalog.com
     */
    struct InnerProduct : DyadicOp {
        using DyadicOp::DyadicOp;

        Array operator()(const Array& alpha, const Array& omega) override;
    };

    /**
     * The Power operator.
     *
     * This is a special case, as it takes a numeric/Array oomega argument (as opposed to another operation).
     *
     *       cube    ⍝ 3D array
     * AB
     * CD
     *
     * EF
     * GH
     *       (↓⍣1) cube   ⍝ split once
     * ┌──┬──┐
     * │AB│CD│
     * ├──┼──┤
     * │EF│GH│
     * └──┴──┘
     *
     * Credit: http:://dyalog.com
     */
    struct Power : Operation {
    protected:
        Operation_ptr aalpha;
        Array oomega;

    public:
        /**
         * Special constructor for the Power operator.
         * @param aalpha_ The function to apply.
         * @param oomega_ A numeric scalar denoting the number of times to apply the function.
         */
        explicit Power(Operation_ptr aalpha_, Array oomega_);

        Array operator()(const Array& omega) override;
    };
};
