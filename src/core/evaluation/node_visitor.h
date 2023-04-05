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
#include "core/evaluation/operations/operation.h"
#include "core/evaluation/ast.h"


namespace kepler {

    /**
     * Abstract base class for all node visitors.
     *
     * Any class that inherits from this class must implement all the visit methods,
     * and as such that class can be used to visit any node in the AST.
     */
    struct NodeVisitor {

        /**
         * Visit a scalar node.
         * @param node Node to visit
         * @return The result of visiting the node.
         */
        virtual Array visit(Scalar* node) = 0;

        /**
         * Visit a vector node.
         * @param node Node to visit
         * @return The result of visiting the node.
         */
        virtual Array visit(Vector* node) = 0;

        /**
         * Visit a monadic operator node.
         * @param node Node to visit
         * @return The result of visiting the node.
         */
        virtual Operation_ptr visit(MonadicOperator* node) = 0;

        /**
         * Visit a dyadic operator node.
         * @param node Node to visit
         * @return The result of visiting the node.
         */
        virtual Operation_ptr visit(DyadicOperator* node) = 0;

        /**
         * Visit a function node.
         * @param node Node to visit
         * @return The result of visiting the node.
         */
        virtual Operation_ptr visit(Function* node) = 0;

        /**
         * Visit an anonymous function node.
         * @param node Node to visit
         * @return The result of visiting the node.
         */
        virtual Operation_ptr visit(AnonymousFunction* node) = 0;

        /**
         * Visit a monadic function node.
         * @param node Node to visit
         * @return The result of visiting the node.
         */
        virtual Array visit(MonadicFunction* node) = 0;

        /**
         * Visit a function assignment node.
         * @param node Node to visit
         * @return The result of visiting the node.
         */
        virtual Array visit(FunctionAssignment* node) = 0;

        /**
         * Visit a function variable node.
         * @param node Node to visit
         * @return The result of visiting the node.
         */
        virtual Operation_ptr visit(FunctionVariable* node) = 0;

        /**
         * Visit a dyadic function node.
         * @param node Node to visit
         * @return The result of visiting the node.
         */
        virtual Array visit(DyadicFunction* node) = 0;

        /**
         * Visit an assignment node.
         * @param node Node to visit
         * @return The result of visiting the node.
         */
        virtual Array visit(Assignment* node) = 0;

        /**
         * Visit a variable node.
         * @param node Node to visit
         * @return The result of visiting the node.
         */
        virtual Array visit(Variable* node) = 0;

        /**
         * Visit a statement node.
         * @param node Node to visit
         * @return The result of visiting the node.
         */
        virtual Array visit(Statements* node) = 0;

        /**
         * Visit a conditional node.
         * @param node Node to visit
         * @return The result of visiting the node.
         */
        virtual Array visit(Conditional* node) = 0;
    };
};