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
#include "core/evaluation/node_visitor.h"
#include "core/evaluation/operations/operation.h"
#include "core/token_type.h"
#include "core/evaluation/operations/functions.h"
#include "core/evaluation/operations/pervade.h"
#include "core/evaluation/operations/monadic_operators.h"
#include "core/evaluation/operations/dyadic_operators.h"
#include "core/error.h"

namespace kepler {
    struct SymbolTable;

    struct Interpreter : NodeVisitor {
        template <typename... Args>
        Operation_ptr build_operation(TokenType type, Args... args) {
            if constexpr (sizeof...(args) == 0) {
                if(type == PLUS) {
                    return std::make_shared<Pervade>(std::make_shared<Plus>(&symbol_table));
                } else if(type == MINUS) {
                    return std::make_shared<Pervade>(std::make_shared<Minus>(&symbol_table));
                } else if(type == TIMES) {
                    return std::make_shared<Pervade>(std::make_shared<Times>(&symbol_table));
                } else if(type == DIVIDE) {
                    return std::make_shared<Pervade>(std::make_shared<Divide>(&symbol_table));
                } else if(type == FLOOR) {
                    return std::make_shared<Pervade>(std::make_shared<Floor>(&symbol_table));
                } else if(type == IOTA) {
                    return std::make_shared<Iota>(&symbol_table);
                } else if(type == RHO) {
                    return std::make_shared<Rho>(&symbol_table);
                }
            }

            if constexpr (sizeof...(args) == 1) {
                if(type == COMMUTE) {
                    return std::make_shared<Commute>(args...);
                } else if(type == SLASH) {
                    return std::make_shared<Slash>(args...);
                }
            }

            if constexpr (sizeof...(args) == 2) {
                if(type == JOT) {
                    return std::make_shared<Jot>(args...);
                }
            }

            throw std::runtime_error("Could not find operation " + kepler::to_string(type) + " to be configured with " +
                                     std::to_string(sizeof...(args)) + " operations.");
        }

        Operation_ptr visit(Function *node) override;
        Array visit(Scalar *node) override;
        Array visit(Vector *node) override;
        Operation_ptr visit(MonadicOperator *node) override;
        Operation_ptr visit(DyadicOperator *node) override;
        Array visit(MonadicFunction *node) override;
        Operation_ptr visit(AnonymousFunction *node) override;
        Operation_ptr visit(FunctionVariable *node) override;
        Array visit(DyadicFunction *node) override;
        Array visit(FunctionAssignment *node) override;
        Array visit(Variable *node) override;
        Array visit(Assignment *node) override;
        Array visit(Statements *node) override;


        SymbolTable& symbol_table;
        ASTNode<Array>& tree;

        explicit Interpreter(ASTNode<Array>& tree_, SymbolTable& symbol_table_) : tree(tree_), symbol_table(symbol_table_) {}

        Array interpret();
    };
};
