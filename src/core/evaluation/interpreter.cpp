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

#include "interpreter.h"
#include <memory>
#include "core/constants/config.h"
#include "core/session.h"
#include "core/evaluation/parser/parser.h"
#include "core/evaluation/operations/defined_function.h"

namespace kepler {
    Operation_ptr Interpreter::visit(Function *node) {
        return build_operation(node->token.type);
    }

    Array Interpreter::visit(Scalar *node) {
        if (holds_alternative<std::u32string>(node->content)) {
            return {{},
                    {get<std::u32string>(node->content)}};
        } else if (holds_alternative<Number>(node->content)) {
            return {{},
                    {get<Number>(node->content)}};
        } else {
            throw kepler::error(InternalError, "Expected either a string or number as Scalar.");
        }
    }

    Array Interpreter::visit(Vector *node) {
        std::vector<Array::element_type> scalars;
        scalars.reserve(node->children.size());
        for (auto &child: node->children) {
            scalars.emplace_back(child->accept(*this));
        }
        return {{(int) scalars.size()}, scalars};
    }

    Operation_ptr Interpreter::visit(MonadicOperator *node) {
        return build_operation(node->token.type, node->child->accept(*this));
    }

    Operation_ptr Interpreter::visit(DyadicOperator *node) {
        return build_operation(node->token.type, node->left->accept(*this), node->right->accept(*this));
    }

    Array Interpreter::visit(MonadicFunction *node) {
        return (*node->function->accept(*this))(node->omega->accept(*this));
    }

    Array Interpreter::visit(DyadicFunction *node) {
        return (*node->function->accept(*this))(node->alpha->accept(*this), node->omega->accept(*this));
    }

    Operation_ptr Interpreter::visit(AnonymousFunction* node) {
        return std::make_shared<DefinedFunction>(node);
    }

    Operation_ptr Interpreter::visit(FunctionVariable *node) {
        auto &content = node->identifier.content.value();
        std::u32string identifier = {content.begin(), content.end()};
        return symbol_table.get<Operation_ptr>(identifier);
    }

    Array Interpreter::visit(Variable *node) {
        auto &content = node->token.content.value();
        std::u32string identifier = {content.begin(), content.end()};
        return symbol_table.get<Array>(identifier);
    }

    Array Interpreter::visit(FunctionAssignment *node) {
        auto &content = node->identifier.content.value();
        std::u32string identifier = {content.begin(), content.end()};
        symbol_table.set(identifier, node->function->accept(*this));
        return {{}, {}};
    }

    Array Interpreter::visit(Assignment *node) {
        auto &content = node->identifier.content.value();
        std::u32string identifier = {content.begin(), content.end()};
        Array value = node->value->accept(*this);

        if (identifier.starts_with(U'⎕')) {
            if (!symbol_table.contains(identifier)) {
                throw kepler::error(DefinitionError, "Distinguished variables are reserved.");
            }

            constants::check_valid_system_param_value(identifier, value);
        }

        symbol_table.set(identifier, value);
        return {{}, {}};
    }

    Array Interpreter::visit(Statements *node) {
        std::vector<Array> results;
        results.reserve(node->children.size());

        for (auto& child : node->children) {
            results.emplace_back(child->accept(*this));
        }

        return results.back();
    }

    Array Interpreter::interpret() {
        return tree.accept(*this);
    }


    /*
    Array Interpreter::interpret(std::vector<Token> *tokens) {
        Parser parser(symbol_table, tokens);
        ASTNode<Array>* statement = parser.next();
        while(statement != nullptr) {
            result = statement->accept(*this);
            delete statement;
            statement = parser.next();
        }

        return result;
    }*/
};