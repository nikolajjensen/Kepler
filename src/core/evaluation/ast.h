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
#include <string>
#include <iostream>
#include "core/array.h"
#include "core/token.h"
#include "core/datatypes.h"
#include <memory>
#include "core/evaluation/operations/operation.h"
#include "core/position.h"

namespace kepler {
    using Operation_ptr = std::shared_ptr<Operation>;

    template <typename T>

    /**
     * Base class for every node in the AST.
     * @tparam T The result type of evaluating the node.
     */
    struct ASTNode : Position {
        virtual ~ASTNode() = default;

        /**
         * Accepts a visitor and returns the result of visiting the node.
         * @param visitor The visitor to accept.
         * @return The result of visiting the node.
         */
        virtual T accept(class NodeVisitor &visitor) = 0;

        /**
         * Returns a human-readable string representation of the node.
         */
        virtual std::string to_string() const = 0;

        /**
         * Appends a human-readable string representation of the node to the given stream.
         */
        friend std::ostream& operator<<(std::ostream& os, const ASTNode& node) {
            return os << node.to_string();
        }
    };

    /**
     * A node representing single values.
     *
     * These could be Strings or Numbers.
     */
    struct Scalar : ASTNode<Array> {
        Token token;
        std::variant<Number, String> content;

        explicit Scalar(Token token_, std::variant<Number, String> content_);

        std::string to_string() const override;
        Array accept(NodeVisitor &visitor) override;
    };

    /**
     * A node representing a vector of other ASTNodes.
     */
    struct Vector : ASTNode<Array> {
        std::vector<ASTNode*> children;

        ~Vector() override;
        explicit Vector(std::vector<ASTNode*> children_);

        std::string to_string() const override;
        Array accept(NodeVisitor &visitor) override;
    };

    /**
     * A node representing a monadic operator node.
     */
    struct MonadicOperator : ASTNode<Operation_ptr> {
        Token token;
        ASTNode<Operation_ptr>* child;

        ~MonadicOperator();
        explicit MonadicOperator(Token token_, ASTNode<Operation_ptr>* child_);

        std::string to_string() const override;
        Operation_ptr accept(NodeVisitor &visitor) override;
    };

    /**
     * A node representing a dyadic operator node.
     */
    struct DyadicOperator : ASTNode<Operation_ptr> {
        Token token;
        ASTNode<Operation_ptr>* left;
        std::variant<ASTNode<Operation_ptr>*, ASTNode<Array>*> right;

        ~DyadicOperator();
        explicit DyadicOperator(Token token_, ASTNode<Operation_ptr>* left_, std::variant<ASTNode<Operation_ptr>*, ASTNode<Array>*> right_);

        std::string to_string() const override;
        Operation_ptr accept(NodeVisitor &visitor) override;
    };

    /**
     * A node representing a function node.
     */
    struct Function : ASTNode<Operation_ptr> {
        Token token;

        explicit Function(Token token_);

        std::string to_string() const override;
        Operation_ptr accept(NodeVisitor &visitor) override;
    };


    /**
     * A node representing a monadic function node.
     */
    struct MonadicFunction : ASTNode<Array> {
        ASTNode<Operation_ptr>* function;
        ASTNode<Array>* omega;

        ~MonadicFunction() override;
        explicit MonadicFunction(ASTNode<Operation_ptr>* function_, ASTNode<Array>* omega_);

        std::string to_string() const override;
        Array accept(NodeVisitor &visitor) override;
    };

    /**
     * A node representing a dyadic function node.
     */
    struct DyadicFunction : ASTNode<Array> {
        ASTNode<Operation_ptr>* function;
        ASTNode<Array>* alpha;
        ASTNode<Array>* omega;

        ~DyadicFunction() override;
        explicit DyadicFunction(ASTNode<Operation_ptr>* function_, ASTNode<Array>* alpha_, ASTNode<Array>* omega_);

        std::string to_string() const override;
        Array accept(NodeVisitor &visitor) override;
    };

    /**
     * A node representing a function assignment node.
     */
    struct FunctionAssignment : ASTNode<Array> {
        Token identifier;
        ASTNode<Operation_ptr>* function;

        ~FunctionAssignment() override;
        explicit FunctionAssignment(Token identifier, ASTNode<Operation_ptr>* function);

        std::string to_string() const override;
        Array accept(NodeVisitor &visitor) override;
    };

    /**
     * A node representing a variable assignment node.
     */
    struct Assignment : ASTNode<Array> {
        Token identifier;
        ASTNode<Array>* value;

        ~Assignment() override;
        explicit Assignment(Token identifier_, ASTNode<Array>* value_);

        std::string to_string() const override;
        Array accept(NodeVisitor &visitor) override;
    };

    /**
     * A node representing a variable node; a reference to a variable.
     */
    struct Variable : ASTNode<Array> {
        Token token;

        explicit Variable(Token token_);

        std::string to_string() const override;
        Array accept(NodeVisitor &visitor) override;
    };

    /**
     * A node representing a function variable node; a reference to a function variable.
     */
    struct FunctionVariable : ASTNode<Operation_ptr> {
        Token identifier;

        explicit FunctionVariable(Token identifier);

        std::string to_string() const override;
        Operation_ptr accept(NodeVisitor &visitor) override;
    };

    /**
     * A node representing a list of statements. Each statement is another ASTNode.
     *
     * Note that this node also contains a pointer to the symbol table of the current scope.
     */
    struct Statements : ASTNode<Array> {
        std::vector<ASTNode<Array>*> children;
        SymbolTable* symbol_table;

        ~Statements() override;
        explicit Statements(std::vector<ASTNode<Array>*> children_, SymbolTable* symbol_table);

        std::string to_string() const override;
        Array accept(NodeVisitor &visitor) override;
    };

    /**
     * A node representing a user-defined anonymous function node.
     */
    struct AnonymousFunction : ASTNode<Operation_ptr> {
        Statements* body;

        ~AnonymousFunction() override;
        explicit AnonymousFunction(Statements* body);

        std::string to_string() const override;
        Operation_ptr accept(NodeVisitor &visitor) override;
    };

    /**
     * A node representing a conditional node.
     */
    struct Conditional : ASTNode<Array> {
        ASTNode<Array>* condition;
        ASTNode<Array>* true_case;
        ASTNode<Array>* false_case;

        ~Conditional();
        explicit Conditional(ASTNode<Array>* condition, ASTNode<Array>* true_case, ASTNode<Array>* false_case);

        std::string to_string() const override;
        Array accept(NodeVisitor &visitor) override;
    };
};