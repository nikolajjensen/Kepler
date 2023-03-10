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
    struct MonadicOp : Operation {
    protected:
        Operation_ptr op;

    public:
        explicit MonadicOp(Operation_ptr op_);
        explicit MonadicOp(Operation* op_);
    };

    struct Commute : MonadicOp {
        using MonadicOp::MonadicOp;

        Array operator()(const Array& alpha, const Array& omega) override;
        Array operator()(const Array& omega) override;
    };

    struct Slash : MonadicOp {
        using MonadicOp::MonadicOp;

        Array operator()(const Array& alpha, const Array& omega) override;
        Array operator()(const Array& omega) override;
    };
};