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
    struct Session;

    struct Interpreter : NodeVisitor {
        Session& session;

        explicit Interpreter(Session& session_) : session(session_) {}

        template <typename... Args>
        Operation* build_operation(TokenType type, Args... args) {
            if constexpr (sizeof...(args) == 0) {
                if(type == PLUS) {
                    return new Pervade(new Plus(&session));
                } else if(type == MINUS) {
                    return new Pervade(new Minus(&session));
                } else if(type == TIMES) {
                    return new Pervade(new Times(&session));
                } else if(type == DIVIDE) {
                    return new Pervade(new Divide(&session));
                } else if(type == FLOOR) {
                    return new Pervade(new Floor(&session));
                } else if(type == IOTA) {
                    return new Iota(&session);
                } else if(type == RHO) {
                    return new Rho(&session);
                }
            }

            if constexpr (sizeof...(args) == 1) {
                if(type == COMMUTE) {
                    return new Commute(args...);
                } else if(type == SLASH) {
                    return new Slash(args...);
                }
            }

            if constexpr (sizeof...(args) == 2) {
                if(type == JOT) {
                    return new Jot(args...);
                }
            }

            throw std::runtime_error("Could not find operation " + kepler::to_string(type) + " to be configured with " +
                                     std::to_string(sizeof...(args)) + " operations.");
        }

        Operation* visit(Function *node) override;
        Array visit(Scalar *node) override;
        Array visit(Vector *node) override;
        Operation* visit(MonadicOperator *node) override;
        Operation* visit(DyadicOperator *node) override;
        Array visit(MonadicFunction *node) override;
        Array visit(DyadicFunction *node) override;
        Array visit(Variable *node) override;
        Array visit(Assignment *node) override;
        Array visit(Statements *node) override;

        Array interpret(ASTNode<Array>* tree);
    };
};