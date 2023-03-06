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
#include "core/constants/config.h"
#include "core/session.h"

namespace kepler {
    Operation *Interpreter::visit(Function *node) {
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

    Operation *Interpreter::visit(MonadicOperator *node) {
        return build_operation(node->token.type, node->child->accept(*this));;
    }

    Operation *Interpreter::visit(DyadicOperator *node) {
        return build_operation(node->token.type, node->left->accept(*this), node->right->accept(*this));
    }

    Array Interpreter::visit(MonadicFunction *node) {
        Operation* op = node->function->accept(*this);
        Array result = (*op)(node->omega->accept(*this));
        delete op;
        return result;
    }

    Array Interpreter::visit(DyadicFunction *node) {
        Operation* op = node->function->accept(*this);
        Array result = (*op)(node->alpha->accept(*this), node->omega->accept(*this));
        delete op;
        return result;
    }

    Array Interpreter::visit(Variable *node) {
        auto &content = node->token.content.value();
        std::u32string identifier = {content.begin(), content.end()};

        if (!session.active_workspace.symbol_table.contains(identifier)) {
            throw kepler::error(DefinitionError, "Undefined variable.");
        }

        return session.active_workspace.symbol_table.get(identifier);
    }

    Array Interpreter::visit(Assignment *node) {
        auto &content = node->identifier.content.value();
        std::u32string identifier = {content.begin(), content.end()};
        Array value = node->value->accept(*this);

        if (identifier.starts_with(U'⎕')) {
            if (!session.active_workspace.symbol_table.contains(identifier)) {
                throw kepler::error(DefinitionError, "Distinguished variables are reserved.");
            }

            constants::check_valid_system_param_value(identifier, value);
        }

        session.active_workspace.symbol_table.set(identifier, value);
        return {{},
                {}};
    }

    Array Interpreter::visit(Statements *node) {
        std::vector<Array> results;
        results.reserve(node->children.size());

        for (int i = node->children.size() - 1; i >= 0; --i) {
            results.emplace_back(node->children[i]->accept(*this));
        }

        return results.back();
    }

    Array Interpreter::interpret(ASTNode<Array> *tree) {
        return tree->accept(*this);
    }
};