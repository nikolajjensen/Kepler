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

namespace kepler {
    struct Func : Operation {
        using Operation::Operation;

        // We hide the following from all evaluators,
        // as they are the base step in evaluation.
    private:
        using Operation::op;

        bool is_configured() const override {
            return symbol_table != nullptr;
        }
    };

    struct Plus : Func {
        using Func::Func;

        Number operator()(Number alpha, Number omega) override;
        Number operator()(Number omega) override;
    };

    struct Minus : Func {
        using Func::Func;

        Number operator()(Number alpha, Number omega) override;
        Number operator()(Number omega) override;
    };

    struct Times : Func {
        using Func::Func;

        Number operator()(Number alpha, Number omega) override;
        Number operator()(Number omega) override;
    };

    struct Divide : Func {
        using Func::Func;

        Number operator()(Number alpha, Number omega) override;
        Number operator()(Number omega) override;
    };

    struct Floor : Func {
        using Func::Func;

        Number operator()(Number alpha, Number omega) override;
        Number operator()(Number omega) override;
    };

    struct Iota : Func {
        using Func::Func;

        Array operator()(Array omega) override;
    };

    struct Rho : Func {
        using Func::Func;

        Array operator()(Array omega) override;
    };
};
