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
     * A Defined Function contains the AnonymousFunction ASTNode (and subtree) which pertains
     * to a specific user-defined function. The DefinedFunction Operation is applied to the
     * arguments in a similar way to primitive functions.
     *
     * Concretely, the DefinedFunction will create a new Interpreter object and use it to evaluate
     * the function body with the given arguments.
     */
    struct DefinedFunction : Operation {
    private:
        AnonymousFunction* function;
        std::ostream& output_stream;

    public:
        explicit DefinedFunction(AnonymousFunction* function, std::ostream& output_stream_);
        ~DefinedFunction();

        Array operator()(const Array& alpha, const Array& omega) override;
        Array operator()(const Array& omega) override;
    };
};