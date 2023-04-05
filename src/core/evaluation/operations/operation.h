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
#include "core/token.h"
#include <memory>

namespace kepler {
    struct SymbolTable;

    /**
     * Represents an arbitrary Operation to be applied to some data.
     *
     * Concrete operations can inherit from this class, and implement whichever
     * of the operator() methods they need. In this way, any arguments they do
     * not support will be handled by the default implementation, which throws
     * a DomainError.
     */
    struct Operation {
    protected:
        // The symbol table to use when evaluating arguments.
        SymbolTable* symbol_table;

    public:
        /**
         * Creates a new Operation.
         *
         * @param symbol_table The symbol table to use.
         */
        explicit Operation(SymbolTable* symbol_table);

        /**
         * Applies an operation to a single argument.
         * @param omega The Array to apply the operation to.
         * @return The result of applying the operation.
         */
        virtual Array operator()(const Array& omega);

        /**
         * Applies an operation to a single argument.
         * @param omega The Number to apply the operation to.
         * @return The result of applying the operation.
         */
        virtual Array operator()(const Number& omega);

        /**
         * Applies an operation to a single argument.
         * @param omega The String to apply the operation to.
         * @return The result of applying the operation.
         */
        virtual Array operator()(const String& omega);

        /**
         * Applies an operation to two arguments.
         * @param alpha The Array left argument.
         * @param omega The Array right argument.
         * @return The result of applying the operation.
         */
        virtual Array operator()(const Array& alpha, const Array& omega);

        /**
         * Applies an operation to two arguments.
         * @param alpha The Array left argument.
         * @param omega The Number right argument.
         * @return The result of applying the operation.
         */
        virtual Array operator()(const Array& alpha, const Number& omega);

        /**
         * Applies an operation to two arguments.
         * @param alpha The Array left argument.
         * @param omega The String right argument.
         * @return The result of applying the operation.
         */
        virtual Array operator()(const Array& alpha, const String& omega);

        /**
         * Applies an operation to two arguments.
         * @param alpha The Number left argument.
         * @param omega The Number right argument.
         * @return The result of applying the operation.
         */
        virtual Array operator()(const Number& alpha, const Number& omega);

        /**
         * Applies an operation to two arguments.
         * @param alpha The Number left argument.
         * @param omega The Array right argument.
         * @return The result of applying the operation.
         */
        virtual Array operator()(const Number& alpha, const Array& omega);

        /**
         * Applies an operation to two arguments.
         * @param alpha The Number left argument.
         * @param omega The String right argument.
         * @return The result of applying the operation.
         */
        virtual Array operator()(const Number& alpha, const String& omega);

        /**
         * Applies an operation to two arguments.
         * @param alpha The String left argument.
         * @param omega The String right argument.
         * @return The result of applying the operation.
         */
        virtual Array operator()(const String& alpha, const String& omega);

        /**
         * Applies an operation to two arguments.
         * @param alpha The String left argument.
         * @param omega The Number right argument.
         * @return The result of applying the operation.
         */
        virtual Array operator()(const String& alpha, const Number& omega);

        /**
         * Applies an operation to two arguments.
         * @param alpha The String left argument.
         * @param omega The Array right argument.
         * @return The result of applying the operation.
         */
        virtual Array operator()(const String& alpha, const Array& omega);

        /**
         * Applies an operation to two arguments.
         * @param alpha The Char left argument.
         * @param omega The Char right argument.
         * @return The result of applying the operation.
         */
        virtual Array operator()(const Char& alpha, const Char& omega);
    };
};