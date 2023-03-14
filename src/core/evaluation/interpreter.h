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
#include "core/token_type.h"
#include "core/evaluation/operations/functions.h"
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
                    return std::make_shared<Plus>(&symbol_table);
                } else if(type == MINUS) {
                    return std::make_shared<Minus>(&symbol_table);
                } else if(type == TIMES) {
                    return std::make_shared<Times>(&symbol_table);
                } else if(type == DIVIDE) {
                    return std::make_shared<Divide>(&symbol_table);
                } else if(type == FLOOR) {
                    return std::make_shared<Floor>(&symbol_table);
                } else if(type == CEILING) {
                    return std::make_shared<Ceiling>(&symbol_table);
                } else if(type == OR) {
                    return std::make_shared<Or>(&symbol_table);
                } else if(type == AND) {
                    return std::make_shared<And>(&symbol_table);
                } else if(type == NAND) {
                    return std::make_shared<Nand>(&symbol_table);
                } else if(type == NOR) {
                    return std::make_shared<Nor>(&symbol_table);
                } else if(type == RIGHT_TACK) {
                    return std::make_shared<RightTack>(&symbol_table);
                } else if(type == LEFT_TACK) {
                    return std::make_shared<LeftTack>(&symbol_table);
                } else if(type == LESS) {
                    return std::make_shared<Less>(&symbol_table);
                } else if(type == LESSEQ) {
                    return std::make_shared<LessEq>(&symbol_table);
                } else if(type == EQ) {
                    return std::make_shared<Eq>(&symbol_table);
                } else if(type == GREATEREQ) {
                    return std::make_shared<GreaterEq>(&symbol_table);
                } else if(type == GREATER) {
                    return std::make_shared<Greater>(&symbol_table);
                } else if(type == NEQ) {
                    return std::make_shared<Neq>(&symbol_table);
                } else if(type == LSHOE) {
                    return std::make_shared<LeftShoe>(&symbol_table);
                } else if(type == WITHOUT) {
                    return std::make_shared<Not>(&symbol_table);
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
                } else if(type == DIAERESIS) {
                    return std::make_shared<Diaeresis>(args...);
                }
            }

            if constexpr (sizeof...(args) == 2) {
                if(type == JOT) {
                    return std::make_shared<Jot>(args...);
                } else if(type == ATOP) {
                    return std::make_shared<Atop>(args...);
                } else if(type == OVER) {
                    return std::make_shared<Over>(args...);
                }
            }

            throw kepler::error(InternalError, "Could not find operation " + kepler::to_string(type) + " to be configured with " +
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
        Array visit(Conditional *node) override;


        SymbolTable& symbol_table;
        ASTNode<Array>& tree;
        std::ostream& output_stream;

        explicit Interpreter(ASTNode<Array>& tree_, SymbolTable& symbol_table_, std::ostream& output_stream_) : tree(tree_), symbol_table(symbol_table_), output_stream(output_stream_) {}

        Array interpret();
    };
};
