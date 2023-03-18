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
#include "core/symbol_table.h"

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

    MonadicOperator::MonadicOperator(Token token_, ASTNode<Operation_ptr>* child_) : token(std::move(token_)),
                                                                                   child(child_) {}

    std::string MonadicOperator::to_string() const {
        return "MonadicOperator(" + token.to_string() + " " + child->to_string() + ")";
    }

    Operation_ptr MonadicOperator::accept(NodeVisitor &visitor) { return visitor.visit(this); }




    DyadicOperator::~DyadicOperator() {
        delete left;
        delete right;
    }

    DyadicOperator::DyadicOperator(Token token_, Token left_operation_token_, ASTNode<Operation_ptr> *left_, ASTNode<Operation_ptr> *right_) : token(
            std::move(token_)), left_operation_token(std::move(left_operation_token_)), left(left_), right(right_) {}

    std::string DyadicOperator::to_string() const {
        return "DyadicOperator(" + left->to_string() + " " + left_operation_token.to_string() + " " + token.to_string() + " " + right->to_string() + ")";
    }

    Operation_ptr DyadicOperator::accept(NodeVisitor &visitor) { return visitor.visit(this); }




    Function::Function(Token token_) : token(std::move(token_)) {}

    std::string Function::to_string() const {
        return "Function(" + token.to_string() + ")";
    }

    Operation_ptr Function::accept(NodeVisitor &visitor) { return visitor.visit(this); }




    MonadicFunction::~MonadicFunction() {
        delete function;
        delete omega;
    }

    MonadicFunction::MonadicFunction(ASTNode<Operation_ptr> *function_, ASTNode<Array> *omega_) : function(function_),
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

    DyadicFunction::DyadicFunction(ASTNode<Operation_ptr> *function_, ASTNode<Array> *alpha_, ASTNode<Array> *omega_)
            : function(function_), alpha(alpha_), omega(omega_) {}

    std::string DyadicFunction::to_string() const {
        return "DyadicFunction(" + alpha->to_string() + " " + function->to_string() + " " + omega->to_string() + ")";
    }

    Array DyadicFunction::accept(NodeVisitor &visitor) { return visitor.visit(this); }


    AnonymousFunction::AnonymousFunction(Statements *body_) : body(body_) {}

    AnonymousFunction::~AnonymousFunction() {
        delete body->symbol_table;
        delete body;
    }

    std::string AnonymousFunction::to_string() const {
        return "AnonymousFunction(" + body->to_string() + ")";
    }

    Operation_ptr AnonymousFunction::accept(NodeVisitor &visitor) { return visitor.visit(this); }


    FunctionVariable::FunctionVariable(Token identifier_) : identifier(identifier_) {}

    std::string FunctionVariable::to_string() const {
        return "FunctionVariable(" + identifier.to_string() + ")";
    }

    Operation_ptr FunctionVariable::accept(NodeVisitor &visitor) { return visitor.visit(this); }

    FunctionAssignment::FunctionAssignment(Token identifier_, ASTNode<Operation_ptr>* function_) : identifier(identifier_), function(function_) {}
    FunctionAssignment::~FunctionAssignment() {

    }

    std::string FunctionAssignment::to_string() const {
        return "FunctionAssignment(" + identifier.to_string() + " ← " + function->to_string() + ")";
    }

    Array FunctionAssignment::accept(NodeVisitor &visitor) { return visitor.visit(this); }


    Assignment::~Assignment() {
        delete value;
    }

    Assignment::Assignment(Token identifier_, ASTNode *value_) : identifier(identifier_), value(value_) {}

    std::string Assignment::to_string() const {
        return "Assignment(" + identifier.to_string() + " ← " + value->to_string() + ")";
    }

    Array Assignment::accept(NodeVisitor &visitor) { return visitor.visit(this); }



    Variable::Variable(Token token_) : token(std::move(token_)) {}

    std::string Variable::to_string() const {
        return "Variable(" + token.to_string() + ")";
    }

    Array Variable::accept(NodeVisitor &visitor) { return visitor.visit(this); }


    Conditional::~Conditional() {
        delete true_case;
        delete false_case;
        delete condition;
    }

    Conditional::Conditional(
            ASTNode<Array>* condition_,
            ASTNode<Array>* true_case_,
            ASTNode<Array>* false_case_)
            : condition(condition_),
              true_case(true_case_),
              false_case(false_case_) {}

    std::string Conditional::to_string() const {
        return "Conditional(" + condition->to_string() + " ? " + true_case->to_string() + " : " + false_case->to_string() + ")";
    }

    Array Conditional::accept(NodeVisitor &visitor) { return visitor.visit(this); }

    Statements::~Statements() {
        for (auto &node: children) {
            delete node;
        }
        children.clear();

        // Do not delete symbol table here.
        // It is the owner of the "Statements" responsibility to
        // delete the symbol table once ready. (We might need to
        // access variables after evaluation of AST).
    }


    Statements::Statements(std::vector<ASTNode<Array> *> children_, SymbolTable* symbol_table_) : children(std::move(children_)), symbol_table(symbol_table_) {}

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