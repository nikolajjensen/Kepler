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
#include "core/evaluation/operations/operation.h"

namespace kepler {
    template <typename T>
    struct ASTNode {
        virtual ~ASTNode() = default;

        virtual T accept(class NodeVisitor &visitor) = 0;
        virtual std::string to_string() const = 0;

        friend std::ostream& operator<<(std::ostream& os, const ASTNode& node) {
            return os << node.to_string();
        }
    };

    struct Scalar : ASTNode<Array> {
        Token token;
        std::variant<Number, std::u32string> content;

        explicit Scalar(Token token_, std::variant<Number, std::u32string> content_);

        std::string to_string() const override;
        Array accept(NodeVisitor &visitor) override;
    };

    struct Vector : ASTNode<Array> {
        std::vector<ASTNode*> children;

        ~Vector() override;
        explicit Vector(std::vector<ASTNode*> children_);

        std::string to_string() const override;
        Array accept(NodeVisitor &visitor) override;
    };

    struct MonadicOperator : ASTNode<Operation*> {
        Token token;
        ASTNode<Operation*>* child;

        ~MonadicOperator();
        explicit MonadicOperator(Token token_, ASTNode<Operation*>* child_);

        std::string to_string() const override;
        Operation* accept(NodeVisitor &visitor) override;
    };

    struct DyadicOperator : ASTNode<Operation*> {
        Token token;
        ASTNode<Operation*>* left;
        ASTNode<Operation*>* right;

        ~DyadicOperator();
        explicit DyadicOperator(Token token_, ASTNode<Operation*>* left_, ASTNode<Operation*>* right_);

        std::string to_string() const override;
        Operation* accept(NodeVisitor &visitor) override;
    };

    struct Function : ASTNode<Operation*> {
        Token token;

        explicit Function(Token token_);

        std::string to_string() const override;
        Operation* accept(NodeVisitor &visitor) override;
    };

    struct MonadicFunction : ASTNode<Array> {
        ASTNode<Operation*>* function;
        ASTNode<Array>* omega;

        ~MonadicFunction() override;
        explicit MonadicFunction(ASTNode<Operation*>* function_, ASTNode<Array>* omega_);

        std::string to_string() const override;
        Array accept(NodeVisitor &visitor) override;
    };

    struct DyadicFunction : ASTNode<Array> {
        ASTNode<Operation*>* function;
        ASTNode<Array>* alpha;
        ASTNode<Array>* omega;

        ~DyadicFunction() override;
        explicit DyadicFunction(ASTNode<Operation*>* function_, ASTNode<Array>* alpha_, ASTNode<Array>* omega_);

        std::string to_string() const override;
        Array accept(NodeVisitor &visitor) override;
    };

    struct Assignment : ASTNode<Array> {
        Token identifier;
        ASTNode<Array>* value;

        ~Assignment() override;
        explicit Assignment(Token identifier_, ASTNode* value_);

        std::string to_string() const override;
        Array accept(NodeVisitor &visitor) override;
    };

    struct Variable : ASTNode<Array> {
        Token token;

        explicit Variable(Token token_);

        std::string to_string() const override;
        Array accept(NodeVisitor &visitor) override;
    };

    struct Statements : ASTNode<Array> {
        std::vector<ASTNode<Array>*> children;

        ~Statements() override;
        explicit Statements(std::vector<ASTNode<Array>*> children_);

        std::string to_string() const override;
        Array accept(NodeVisitor &visitor) override;
    };
};