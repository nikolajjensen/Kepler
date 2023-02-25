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

#include "form_table.h"
#include "phrase_table.h"
#include "core/token.h"
#include "core/helpers/classifiers.h"
#include "core/helpers/printers.h"
#include <functional>

using namespace kepler;
using namespace kepler::phrase_table;

template <>
void kepler::phrase_table::evaluators::remove_parenthesis<3, LP_B_RP>(List<Token> &stack, Session &session) {
    if(helpers::is(stack[1], NilToken) || helpers::is(stack[1], BranchToken)) {
        throw kepler::error(ValueError, "Cannot remove parenthesis.");
    }

    kepler::phrase_table::erase(stack, 0, 2);
}

template <>
void kepler::phrase_table::evaluators::evaluate_niladic_function<1, N>(List<Token> &stack, Session &session) {
    Token& n = stack[0];

    if(helpers::is(n, NiladicDefinedFunctionNameToken)) {
        if(session.current_class(n) == NiladicDefinedFunctionToken) {
            n = kepler::form_table::evaluate({kepler::form_table::TableAtomic::DFN}, {&n}, &session);
        } else {
            throw kepler::error(SyntaxError, "Undefined single function reference.");
        }
    } else if(helpers::is(n, NiladicSystemFunctionNameToken)) {
        auto evaluator = kepler::form_table::lookup({&n}, &session);
        if(!evaluator) {
            throw kepler::error(SyntaxError, "No evaluation sequence.");
        }
        n = evaluator->apply({&n});
    }
}

template<>
void kepler::phrase_table::evaluators::evaluate_monadic_function<3, X_F_B>(kepler::List<kepler::Token> &stack, kepler::Session &session) {
    Token& f = stack[1];
    Token& b = stack[2];

    if(!helpers::is_value(b)) {
        throw kepler::error(ValueError, "Monadic argument was not a value.");
    }

    if(helpers::is(b, DefinedFunctionNameToken)) {
        if(session.current_class(f) == DefinedFunctionToken) {
           f = form_table::evaluate({form_table::TableAtomic::DFN, form_table::TableAtomic::Constant}, {&f, &b}, &session);
           kepler::phrase_table::erase(stack, 2);
        } else {
            throw kepler::error(SyntaxError, "Undefined monadic function reference.");
        }
    } else if(helpers::is(f, PrimitiveFunctionToken) || helpers::is(f, SystemFunctionNameToken)) {
        auto evaluator = kepler::form_table::lookup({&f, kepler::form_table::TableAtomic::Constant}, &session);
        if(!evaluator) {
            throw kepler::error(SyntaxError, "No evaluation sequence.");
        }
        b = evaluator->apply({&b});
        kepler::phrase_table::erase(stack, 1);
    }
}

template<>
void kepler::phrase_table::evaluators::evaluate_monadic_function<6, X_F_LB_C_RB_B>(kepler::List<kepler::Token> &stack, kepler::Session &session) {
    throw kepler::error(InternalError, "'evaluate_monadic_function' phrase table evaluator not implemented.");

    Token& f = stack[1];
    Token& b = stack[5];
    Token& c = stack[3];

    if(!helpers::is_value(b)) throw kepler::error(ValueError, "Monadic argument was not a value.");
    if(!helpers::is(f, PrimitiveFunctionToken)) throw kepler::error(SyntaxError, "Expected a primitive function.");
    // Incorrect.
    //if(session.context.index_origin < 0.0) throw kepler::error(ImplicitError, "Index origin must be ≥0. Set it via ⎕IO.");
}

template <>
void kepler::phrase_table::evaluators::evaluate_monadic_operator<4, X_F_M_B>(kepler::List<kepler::Token> &stack, kepler::Session &session) {
    Token& f = stack[1];
    Token& m = stack[2];
    Token& b = stack[3];

    if(!helpers::is_value(b)) throw kepler::error(ValueError, "Operand has no value.");
    if(helpers::is(m, PrimitiveMonadicOperatorToken) || helpers::is(m, AxisMonadicOperatorToken)) {
        auto evaluator = kepler::form_table::lookup({&f, &m, form_table::Constant}, &session);
        if(evaluator == nullptr) {
            throw kepler::error(SyntaxError, "No evaluation sequence.");
        }
        b = evaluator->apply({&f, &b});
        kepler::phrase_table::erase(stack, 1, 2);
    } else {
        throw kepler::error(InternalError, "User-defined operators are not supported.");
    }
}

template <>
void kepler::phrase_table::evaluators::evaluate_monadic_operator<7, X_F_M_LB_C_RB_B>(kepler::List<kepler::Token> &stack, kepler::Session &session) {
    throw kepler::error(InternalError, "'evaluate_monadic_operator' phrase table evaluator not implemented.");
}

template <>
void kepler::phrase_table::evaluators::evaluate_monadic_operator<4, A_F_M_B>(kepler::List<kepler::Token> &stack, kepler::Session &session) {
    throw kepler::error(InternalError, "'evaluate_monadic_operator' phrase table evaluator not implemented.");
}

template <>
void kepler::phrase_table::evaluators::evaluate_monadic_operator<7, A_F_M_LB_C_RB_B>(kepler::List<kepler::Token> &stack, kepler::Session &session) {
    throw kepler::error(InternalError, "'evaluate_monadic_operator' phrase table evaluator not implemented.");
}

template <>
void kepler::phrase_table::evaluators::evaluate_dyadic_function<3, A_F_B>(kepler::List<kepler::Token> &stack, kepler::Session &session) {
    Token& a = stack[0];
    Token& f = stack[1];
    Token& b = stack[2];

    if(!helpers::is_value(a) || !helpers::is_value(b)) {
        throw kepler::error(ValueError, "Expected value operands.");
    }

    if(helpers::is(f, DefinedFunctionNameToken)) {
        if(session.current_class(f) == DefinedFunctionToken) {
            a = form_table::evaluate({form_table::TableAtomic::Constant, form_table::TableAtomic::DFN, form_table::TableAtomic::Constant}, {&a, &b}, &session);
            kepler::phrase_table::erase(stack, 1, 2);
        } else {
            throw kepler::error(SyntaxError, "Undefined reference to dyadic operator.");
        }
    } else if(helpers::is(f, PrimitiveFunctionToken) || helpers::is(f, SystemFunctionNameToken)) {
        auto evaluator = form_table::lookup({form_table::TableAtomic::Constant, &f, form_table::TableAtomic::Constant}, &session);

        if(evaluator != nullptr) {
            a = evaluator->apply({&a, &b});
            kepler::phrase_table::erase(stack, 1, 2);
        } else {
            throw kepler::error(SyntaxError, "No evaluation sequence.");
        }
    }
}

template <>
void kepler::phrase_table::evaluators::evaluate_dyadic_function<6, A_F_LB_C_RB_B>(kepler::List<kepler::Token> &stack, kepler::Session &session) {
    throw kepler::error(InternalError, "'evaluate_dyadic_function' phrase table evaluator not implemented.");
}

template <>
void kepler::phrase_table::evaluators::evaluate_dyadic_operator<5, X_F_D_G_B>(kepler::List<kepler::Token> &stack, kepler::Session &session) {
    throw kepler::error(InternalError, "'evaluate_dyadic_operator' phrase table evaluator not implemented.");
}

template <>
void kepler::phrase_table::evaluators::evaluate_dyadic_operator<5, A_F_D_G_B>(kepler::List<kepler::Token> &stack, kepler::Session &session) {
    throw kepler::error(InternalError, "'evaluate_dyadic_operator' phrase table evaluator not implemented.");
}

template <>
void kepler::phrase_table::evaluators::evaluate_dyadic_operator<5, A_SM_D_G_B>(kepler::List<kepler::Token> &stack, kepler::Session &session) {
    throw kepler::error(InternalError, "'evaluate_dyadic_operator' phrase table evaluator not implemented.");
}

template <>
void kepler::phrase_table::evaluators::evaluate_indexed_reference<4, A_LB_K_RB>(kepler::List<kepler::Token> &stack, kepler::Session &session) {
    throw kepler::error(InternalError, "'evaluate_indexed_reference' phrase table evaluator not implemented.");
}

template <>
void kepler::phrase_table::evaluators::evaluate_indexed_assignment<6, V_LB_K_RB_AA_B>(kepler::List<kepler::Token> &stack, kepler::Session &session) {
    throw kepler::error(InternalError, "'evaluate_indexed_assignment' phrase table evaluator not implemented.");
}

template <>
void kepler::phrase_table::evaluators::evaluate_assignment<3, V_AA_B>(kepler::List<kepler::Token> &stack, kepler::Session &session) {
    Token& v = stack[0];
    Token& b = stack[2];

    if(!helpers::is_value(b)) throw kepler::error(ValueError, "Expected a value to be assigned.");
    if(helpers::is(v, SharedVariableNameToken)) {
        throw kepler::error(InternalError, "Shared Variables are not supported in Kepler.");
    } else if (helpers::is(v, SystemVariableNameToken)) {
        auto evaluator = form_table::lookup({&v, constants::left_arrow, form_table::Constant}, &session);

        if(evaluator != nullptr) {
            v = evaluator->apply({&b});
            kepler::phrase_table::erase(stack, 1, 2);
        } else {
            throw kepler::error(SyntaxError, "No assignment evaluation sequence.");
        }
    } else if (helpers::is(v, VariableNameToken)) {
        if(session.current_class(v) == NilToken || session.current_class(v) == VariableToken) {
            b.token_class = VariableToken;
            session.set_current_referent(v, {b});
            b.token_class = CommittedValueToken;
            kepler::phrase_table::erase(stack, 0, 1);
        } else {
            throw kepler::error(SyntaxError, "No assignment evaluation sequence.");
        }
    }
}

template <>
void kepler::phrase_table::evaluators::evaluate_variable<1, V>(kepler::List<kepler::Token> &stack, kepler::Session &session) {
    Token &v = stack[0];

    if (helpers::is(v, SharedVariableNameToken)) {
        throw kepler::error(InternalError, "Shared Variables are not supported in Kepler.");
    } else if (helpers::is(v, SystemVariableNameToken)) {
        if(session.current_class(v) == NilToken) throw kepler::error(ValueError, "Current class of system variable is nil.");
        v = form_table::evaluate({&v}, {}, &session);
    } else if (helpers::is(v, VariableNameToken)) {
        if(session.current_class(v) == NilToken) throw kepler::error(ValueError, "Undefined variable.");
        if(session.current_class(v) != VariableToken) throw kepler::error(SyntaxError, "Undefined variable");
        v = session.get_current_referent(v);
        v.token_class = ConstantToken;
    }
}

template <>
void kepler::phrase_table::evaluators::build_index_list<1, RB>(kepler::List<kepler::Token> &stack, kepler::Session &session) {
    throw kepler::error(InternalError, "'build_index_list' phrase table evaluator not implemented.");
}

template <>
void kepler::phrase_table::evaluators::build_index_list<2, IS_I>(kepler::List<kepler::Token> &stack, kepler::Session &session) {
    throw kepler::error(InternalError, "'build_index_list' phrase table evaluator not implemented.");
}

template <>
void kepler::phrase_table::evaluators::build_index_list<3, IS_B_I>(kepler::List<kepler::Token> &stack, kepler::Session &session) {
    throw kepler::error(InternalError, "'build_index_list' phrase table evaluator not implemented.");
}

template <>
void kepler::phrase_table::evaluators::build_index_list<2, LB_I>(kepler::List<kepler::Token> &stack, kepler::Session &session) {
    throw kepler::error(InternalError, "'build_index_list' phrase table evaluator not implemented.");
}

template <>
void kepler::phrase_table::evaluators::build_index_list<3, LB_B_I>(kepler::List<kepler::Token> &stack, kepler::Session &session) {
    throw kepler::error(InternalError, "'build_index_list' phrase table evaluator not implemented.");
}

template <>
void kepler::phrase_table::evaluators::process_end_of_statement<2, L_R>(kepler::List<kepler::Token> &stack, kepler::Session &session) {
    throw kepler::error(InternalError, "'process_end_of_statement' phrase table evaluator not implemented.");
}

template <>
void kepler::phrase_table::evaluators::process_end_of_statement<3, L_B_R>(kepler::List<kepler::Token> &stack, kepler::Session &session) {
    kepler::phrase_table::erase(stack, 0, 2);
}

template <>
void kepler::phrase_table::evaluators::process_end_of_statement<4, L_BA_B_R>(kepler::List<kepler::Token> &stack, kepler::Session &session) {
    throw kepler::error(InternalError, "'process_end_of_statement' phrase table evaluator not implemented.");
}

template <>
void kepler::phrase_table::evaluators::process_end_of_statement<3, L_BA_R>(kepler::List<kepler::Token> &stack, kepler::Session &session) {
    throw kepler::error(InternalError, "'process_end_of_statement' phrase table evaluator not implemented.");
}

bool kepler::phrase_table::match_type(const kepler::Token &token, TokenType type) {
    switch (type) {
        case Result:
            return helpers::is_result(token);
        case Dyadic:
            return helpers::is(token, DyadicOperatorToken);
        case Func:
            return helpers::is(token, DefinedFunctionNameToken)
                   || helpers::is(token, PrimitiveFunctionToken)
                   || helpers::is(token, SystemFunctionNameToken);
        case PartialList:
            return helpers::is(token, PartialIndexListToken);
        case CompleteList:
            return helpers::is(token, CompleteIndexListToken);
        case LeftEOS:
            return helpers::is(token, LeftEndOfStatementToken);
        case Monadic:
            return helpers::is(token, MonadicOperatorToken)
                   || helpers::is(token, AxisMonadicOperatorToken)      // <-- Not in ISO.
                   || helpers::is(token, PrimitiveMonadicOperatorToken) // <-- Not in ISO.
                   || helpers::is(token, PrimitiveDyadicOperatorToken); // <-- Not in ISO.
        case Niladic:
            return helpers::is(token, NiladicDefinedFunctionNameToken)
                   || helpers::is(token, NiladicSystemFunctionNameToken);
        case RightEOS:
            return helpers::is(token, RightEndOfStatementToken);
        case Var:
            return helpers::is(token, VariableNameToken)
                   || helpers::is(token, SystemVariableNameToken)
                   || helpers::is(token, SharedVariableNameToken);
        case Wildcard:
            return helpers::is(token, AssignmentArrowToken)
                   || helpers::is(token, BranchArrowToken)
                   || helpers::is(token, DefinedFunctionNameToken)
                   || helpers::is(token, IndexSeparatorToken)
                   || helpers::is(token, LeftAxisBracketToken)
                   || helpers::is(token, LeftEndOfStatementToken)
                   || helpers::is(token, LeftIndexBracketToken)
                   || helpers::is(token, LeftParenthesisToken)
                   || helpers::is(token, PrimitiveFunctionToken)
                   || helpers::is(token, SystemFunctionNameToken)
                   || helpers::is(token, RightAxisBracketToken)
                   || helpers::is(token, MonadicOperatorToken)          // <-- Not in ISO.
                   || helpers::is(token, AxisMonadicOperatorToken)          // <-- Not in ISO.
                   || helpers::is(token, PrimitiveMonadicOperatorToken) // <-- Not in ISO.
                   || helpers::is(token, PrimitiveDyadicOperatorToken); // <-- Not in ISO.
        default:
            return false;
    }
}

template <std::size_t S, const pattern<S>& Pattern>
bool kepler::phrase_table::match(const kepler::List<kepler::Token> &tokens) {
    if(tokens.size() < S) {
        return false;
    }

    for(int i = 0; i < S; ++i) {
        if(const TokenType* cl = boost::get<TokenType>(&Pattern[i])) {
            if(!match_type(tokens[i], *cl)) { return false; }
        } else if(const Token::content_type* content = boost::get<Token::content_type>(&Pattern[i])) {
            if(!tokens[i].content.is_initialized()) { return false; }
            if(tokens[i].content.get() != *content) { return false; }
        }
    }

    return true;
}

lookup_result kepler::phrase_table::lookup(List<Token> &stack) {
    if(match<3, LP_B_RP>(stack)) {
        return evaluators::remove_parenthesis<3, LP_B_RP>;
    } else if(match<1, N>(stack)) {
        return evaluators::evaluate_niladic_function<1, N>;
    } else if(match<3, X_F_B>(stack)) {
        return evaluators::evaluate_monadic_function<3, X_F_B>;
    } else if(match<6, X_F_LB_C_RB_B>(stack)) {
        return evaluators::evaluate_monadic_function<6, X_F_LB_C_RB_B>;
    } else if(match<4, X_F_M_B>(stack)) {
        return evaluators::evaluate_monadic_operator<4, X_F_M_B>;
    } else if(match<7, X_F_M_LB_C_RB_B>(stack)) {
        return evaluators::evaluate_monadic_operator<7, X_F_M_LB_C_RB_B>;
    } else if(match<4, A_F_M_B>(stack)) {
        return evaluators::evaluate_monadic_operator<4, A_F_M_B>;
    } else if(match<7, A_F_M_LB_C_RB_B>(stack)) {
        return evaluators::evaluate_monadic_operator<7, A_F_M_LB_C_RB_B>;
    } else if(match<3, A_F_B>(stack)) {
        return evaluators::evaluate_dyadic_function<3, A_F_B>;
    } else if(match<6, A_F_LB_C_RB_B>(stack)) {
        return evaluators::evaluate_dyadic_function<6, A_F_LB_C_RB_B>;
    } else if(match<5, X_F_D_G_B>(stack)) {
        return evaluators::evaluate_dyadic_operator<5, X_F_D_G_B>;
    } else if(match<5, A_F_D_G_B>(stack)) {
        return evaluators::evaluate_dyadic_operator<5, A_F_D_G_B>;
    } else if(match<5, A_SM_D_G_B>(stack)) {
        return evaluators::evaluate_dyadic_operator<5, A_SM_D_G_B>;
    } else if(match<4, A_LB_K_RB>(stack)) {
        return evaluators::evaluate_indexed_reference<4, A_LB_K_RB>;
    } else if(match<6, V_LB_K_RB_AA_B>(stack)) {
        return evaluators::evaluate_indexed_assignment<6, V_LB_K_RB_AA_B>;
    } else if(match<3, V_AA_B>(stack)) {
        return evaluators::evaluate_assignment<3, V_AA_B>;
    } else if(match<1, V>(stack)) {
        return evaluators::evaluate_variable<1, V>;
    } else if(match<1, RB>(stack)) {
        return evaluators::build_index_list<1, RB>;
    } else if(match<2, IS_I>(stack)) {
        return evaluators::build_index_list<2, IS_I>;
    } else if(match<3, IS_B_I>(stack)) {
        return evaluators::build_index_list<3, IS_B_I>;
    } else if(match<2, LB_I>(stack)) {
        return evaluators::build_index_list<2, LB_I>;
    } else if(match<3, LB_B_I>(stack)) {
        return evaluators::build_index_list<3, LB_B_I>;
    } else if(match<2, L_R>(stack)) {
        return {evaluators::process_end_of_statement<2, L_R>, true};
    } else if(match<3, L_B_R>(stack)) {
        return {evaluators::process_end_of_statement<3, L_B_R>, true};
    } else if(match<4, L_BA_B_R>(stack)) {
        return {evaluators::process_end_of_statement<4, L_BA_B_R>, true};
    } else if(match<3, L_BA_R>(stack)) {
        return {evaluators::process_end_of_statement<3, L_BA_R>, true};
    }

    return nullptr;
}