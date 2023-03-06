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

#include "ast.h"
#include "core/evaluation/node_visitor.h"

namespace kepler {
    Scalar::Scalar(Token token_, std::variant<Number, std::u32string> content_) : token(std::move(token_)), content(std::move(content_)) {}

    std::string Scalar::to_string() const {
        return "Scalar(" + token.to_string() + ")";
    }

    Array Scalar::accept(NodeVisitor &visitor) { return visitor.visit(this); }



    Vector::~Vector() {
        for (auto &node: children) {
            delete node;
        }
        children.clear();
    }

    Vector::Vector(std::vector<ASTNode *> children_) : children(std::move(children_)) {}


    std::string Vector::to_string() const {
        std::stringstream ss;
        ss << "Vector(";
        for (int i = 0; i < children.size(); ++i) {
            ss << children[i]->to_string();
            if (i < children.size() - 1) {
                ss << ", ";
            }
        }
        ss << ")";
        return ss.str();
    }

    Array Vector::accept(NodeVisitor &visitor) { return visitor.visit(this); }



    MonadicOperator::~MonadicOperator() {
        delete child;
    }

    MonadicOperator::MonadicOperator(Token token_, ASTNode<Operation *> *child_) : token(std::move(token_)),
                                                                                   child(child_) {}

    std::string MonadicOperator::to_string() const {
        return "MonadicOperator(" + token.to_string() + " " + child->to_string() + ")";
    }

    Operation* MonadicOperator::accept(NodeVisitor &visitor) { return visitor.visit(this); }




    DyadicOperator::~DyadicOperator() {
        delete left;
        delete right;
    }

    DyadicOperator::DyadicOperator(Token token_, ASTNode<Operation *> *left_, ASTNode<Operation *> *right_) : token(
            std::move(token_)), left(left_), right(right_) {}

    std::string DyadicOperator::to_string() const {
        return "DyadicOperator(" + left->to_string() + " " + token.to_string() + " " + right->to_string() + ")";
    }

    Operation* DyadicOperator::accept(NodeVisitor &visitor) { return visitor.visit(this); }




    Function::Function(Token token_) : token(std::move(token_)) {}

    std::string Function::to_string() const {
        return "Function(" + token.to_string() + ")";
    }

    Operation* Function::accept(NodeVisitor &visitor) { return visitor.visit(this); }




    MonadicFunction::~MonadicFunction() {
        delete function;
        delete omega;
    }

    MonadicFunction::MonadicFunction(ASTNode<Operation *> *function_, ASTNode<Array> *omega_) : function(function_),
                                                                                                omega(omega_) {}

    std::string MonadicFunction::to_string() const {
        return "MonadicFunction(" + function->to_string() + " " + omega->to_string() + ")";
    }

    Array MonadicFunction::accept(NodeVisitor &visitor) { return visitor.visit(this); }




    DyadicFunction::~DyadicFunction() {
        delete function;
        delete alpha;
        delete omega;
    }

    DyadicFunction::DyadicFunction(ASTNode<Operation *> *function_, ASTNode<Array> *alpha_, ASTNode<Array> *omega_)
            : function(function_), alpha(alpha_), omega(omega_) {}

    std::string DyadicFunction::to_string() const {
        return "DyadicFunction(" + function->to_string() + " " + alpha->to_string() + " " + omega->to_string() + ")";
    }

    Array DyadicFunction::accept(NodeVisitor &visitor) { return visitor.visit(this); }




    Assignment::~Assignment() {
        delete value;
    }

    Assignment::Assignment(Token identifier_, ASTNode *value_) : identifier(identifier_), value(value_) {}

    std::string Assignment::to_string() const {
        return "Assignment(" + identifier.to_string() + "←" + value->to_string() + ")";
    }

    Array Assignment::accept(NodeVisitor &visitor) { return visitor.visit(this); }



    Variable::Variable(Token token_) : token(std::move(token_)) {}

    std::string Variable::to_string() const {
        return "Variable(" + token.to_string() + ")";
    }

    Array Variable::accept(NodeVisitor &visitor) { return visitor.visit(this); }




    Statements::~Statements() {
        for (auto &node: children) {
            delete node;
        }
        children.clear();
    }

    Statements::Statements(std::vector<ASTNode<Array> *> children_) : children(children_) {}

    std::string Statements::to_string() const {
        std::stringstream ss;

        ss << "Statements(";
        for (int i = 0; i < children.size(); ++i) {
            ss << children[i]->to_string();
            if (i < children.size() - 1) {
                ss << ", ";
            }
        }
        ss << ")";
        return ss.str();
    }

    Array Statements::accept(NodeVisitor &visitor) { return visitor.visit(this); }
};