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
#include "core/symbol_table.h"
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
        if(std::holds_alternative<ASTNode<Operation_ptr>*>(node->right)) {
            return build_operation(node->token.type, node->left->accept(*this), get<ASTNode<Operation_ptr>*>(node->right)->accept(*this));
        } else if(node->token.type == POWER) {
            return std::make_shared<Power>(node->left->accept(*this), get<ASTNode<Array>*>(node->right)->accept(*this));
        }
    }

    Array Interpreter::visit(MonadicFunction *node) {
        try {
            Operation_ptr f = node->function->accept(*this);
            return (*f)(node->omega->accept(*this));
        } catch (kepler::error& err) {
            err.position = node->function->get_position();
            throw err;
        }
    }

    Array Interpreter::visit(DyadicFunction *node) {
        try {
            return (*node->function->accept(*this))(node->alpha->accept(*this), node->omega->accept(*this));
        } catch (kepler::error& err) {
            err.position = node->function->get_position();
            throw err;
        }
    }

    Operation_ptr Interpreter::visit(AnonymousFunction* node) {
        auto dfn = std::make_shared<DefinedFunction>(node, output_stream);
        node->body->symbol_table->set(constants::recursive_call_id, dfn);
        return dfn;
    }

    Operation_ptr Interpreter::visit(FunctionVariable *node) {
        auto &content = node->identifier.content.value();
        return symbol_table.get<Operation_ptr>({content.begin(), content.end()});
    }

    Array Interpreter::visit(Variable *node) {
        auto &content = node->token.content.value();
        std::u32string identifier = {content.begin(), content.end()};
        return symbol_table.get<Array>(identifier);
    }

    Array Interpreter::visit(FunctionAssignment *node) {
        auto &content = node->identifier.content.value();
        std::u32string identifier = {content.begin(), content.end()};
        if(identifier.starts_with(constants::recursive_call_id)) {
            throw kepler::error(DefinitionError, "Cannot assign a variable to the recursive call symbol.", node->identifier.get_position());
        }
        auto s = node->function->accept(*this);
        symbol_table.set(identifier, s);
        return {{}, {}};
    }

    Array Interpreter::visit(Assignment *node) {
        auto &content = node->identifier.content.value();
        std::u32string identifier = {content.begin(), content.end()};
        Array value = node->value->accept(*this);

        if (identifier.starts_with(U'⎕')) {
            if(identifier.length() == 1) {
                // Print out.
                output_stream << value.to_string(&symbol_table) << std::flush;
                return {{}, {}};
            }

            if (!symbol_table.contains(identifier)) {
                throw kepler::error(DefinitionError, "Distinguished variables are reserved.", node->identifier.get_position());
            }

            constants::check_valid_system_param_value(identifier, value);
        } if(identifier.starts_with(constants::recursive_call_id)) {
            throw kepler::error(DefinitionError, "Cannot assign a variable to the recursive call symbol.", node->identifier.get_position());
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

        if(!results.empty()) {
            return results.back();
        } else {
            return {{}, {}};
        }
    }

    Array Interpreter::visit(Conditional *node) {
        auto condition = node->condition->accept(*this);
        if(condition.empty()) {
            throw kepler::error(SyntaxError, "Condition did not evaluate to a value.", node->condition->get_position());
        }

        if(holds_alternative<Number>(condition.data[0])) {
            if(get<Number>(condition.data[0]).real() != 0) {
                return node->true_case->accept(*this);
            }
        }

        return node->false_case->accept(*this);
    }

    Array Interpreter::interpret() {
        return tree.accept(*this);
    }
};