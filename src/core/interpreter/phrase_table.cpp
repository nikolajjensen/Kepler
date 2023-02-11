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
#include "../token.h"
#include "../classifiers.h"
#include <functional>

using namespace kepler;
using namespace kepler::phrase_table;

template <>
void kepler::phrase_table::evaluators::remove_parenthesis<LP_B_RP_size, LP_B_RP>(List<Token> &stack, Session &session) {
    if(classifiers::is(stack[1], NilToken) || classifiers::is(stack[1], BranchToken)) {
        throw kepler::error(ValueError, "Cannot remove parenthesis.");
    }

    helpers::erase(stack, 0, 2);
}

template <>
void kepler::phrase_table::evaluators::evaluate_niladic_function<N_size, N>(List<Token> &stack, Session &session) {
    Token& n = stack[0];

    if(classifiers::is(n, NiladicDefinedFunctionNameToken)) {
        if(session.current_class(n) == NiladicDefinedFunctionToken) {
            n = kepler::form_table::evaluate({kepler::form_table::TableAtomic::DFN}, {&n});
        } else {
            throw kepler::error(SyntaxError, "Undefined niladic function reference.");
        }
    } else if(classifiers::is(n, NiladicSystemFunctionNameToken)) {
        auto evaluator = kepler::form_table::lookup({kepler::form_table::TableAtomic::Func});
        if(evaluator != nullptr) {
            n = evaluator({&n});
        } else {
            throw kepler::error(SyntaxError, "No evaluation sequence.");
        }
    }
}

template<>
void kepler::phrase_table::evaluators::evaluate_monadic_function<X_F_B_size, X_F_B>(kepler::List<kepler::Token> &stack, kepler::Session &session) {
    Token& f = stack[1];
    Token& b = stack[2];

    if(!classifiers::is_value(b)) {
        throw kepler::error(ValueError, "Monadic argument was not a value.");
    }

    if(classifiers::is(b, DefinedFunctionNameToken)) {
        if(session.current_class(f) == DefinedFunctionToken) {
           f = form_table::evaluate({form_table::TableAtomic::DFN, form_table::TableAtomic::Constant}, {&f, &b});
           helpers::erase(stack, 2);
        } else {
            throw kepler::error(SyntaxError, "Undefined monadic function reference.");
        }
    } else if(classifiers::is(f, PrimitiveFunctionToken) || classifiers::is(f, SystemFunctionNameToken)) {
        auto evaluator = kepler::form_table::lookup({&f, kepler::form_table::TableAtomic::Constant});

        if(evaluator != nullptr) {
            b = evaluator({&f, &b});
            helpers::erase(stack, 1);
        } else {
            throw kepler::error(SyntaxError, "No evaluation sequence.");
        }
    }
}

template<>
void kepler::phrase_table::evaluators::evaluate_monadic_function<X_F_LB_C_RB_B_size, X_F_LB_C_RB_B>(kepler::List<kepler::Token> &stack, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::evaluate_monadic_operator<X_F_M_B_size, X_F_M_B>(kepler::List<kepler::Token> &stack, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::evaluate_monadic_operator<X_F_M_LB_C_RB_B_size, X_F_M_LB_C_RB_B>(kepler::List<kepler::Token> &stack, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::evaluate_monadic_operator<A_F_M_B_size, A_F_M_B>(kepler::List<kepler::Token> &stack, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::evaluate_monadic_operator<A_F_M_LB_C_RB_B_size, A_F_M_LB_C_RB_B>(kepler::List<kepler::Token> &stack, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::evaluate_dyadic_function<A_F_B_size, A_F_B>(kepler::List<kepler::Token> &stack, kepler::Session &session) {
    Token& a = stack[0];
    Token& f = stack[1];
    Token& b = stack[2];

    if(!classifiers::is_value(a) || !classifiers::is_value(b)) {
        throw kepler::error(ValueError, "Expected value operands.");
    }

    if(classifiers::is(f, DefinedFunctionNameToken)) {
        if(session.current_class(f) == DefinedFunctionToken) {
            a = form_table::evaluate({form_table::TableAtomic::Constant, form_table::TableAtomic::DFN, form_table::TableAtomic::Constant}, {&a, &f, &b});
            helpers::erase(stack, 1, 2);
        } else {
            throw kepler::error(SyntaxError, "Undefined reference to dyadic operator.");
        }
    } else if(classifiers::is(f, PrimitiveFunctionToken) || classifiers::is(f, SystemFunctionNameToken)) {
        auto evaluator = form_table::lookup({form_table::TableAtomic::Constant, &f, form_table::TableAtomic::Constant});

        if(evaluator != nullptr) {
            a = evaluator({&a, &f, &b});
            helpers::erase(stack, 1, 2);
        } else {
            throw kepler::error(SyntaxError, "No evaluation sequence.");
        }
    }
}

template <>
void kepler::phrase_table::evaluators::evaluate_dyadic_function<A_F_LB_C_RB_B_size, A_F_LB_C_RB_B>(kepler::List<kepler::Token> &stack, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::evaluate_dyadic_operator<X_F_D_G_B_size, X_F_D_G_B>(kepler::List<kepler::Token> &stack, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::evaluate_dyadic_operator<A_F_D_G_B_size, A_F_D_G_B>(kepler::List<kepler::Token> &stack, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::evaluate_dyadic_operator<A_SM_D_G_B_size, A_SM_D_G_B>(kepler::List<kepler::Token> &stack, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::evaluate_indexed_reference<A_LB_K_RB_size, A_LB_K_RB>(kepler::List<kepler::Token> &stack, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::evaluate_indexed_assignment<V_LB_K_RB_AA_B_size, V_LB_K_RB_AA_B>(kepler::List<kepler::Token> &stack, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::evaluate_assignment<V_AA_B_size, V_AA_B>(kepler::List<kepler::Token> &stack, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::evaluate_variable<V_size, V>(kepler::List<kepler::Token> &stack, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::build_index_list<RB_size, RB>(kepler::List<kepler::Token> &stack, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::build_index_list<IS_I_size, IS_I>(kepler::List<kepler::Token> &stack, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::build_index_list<IS_B_I_size, IS_B_I>(kepler::List<kepler::Token> &stack, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::build_index_list<LB_I_size, LB_I>(kepler::List<kepler::Token> &stack, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::build_index_list<LB_B_I_size, LB_B_I>(kepler::List<kepler::Token> &stack, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::process_end_of_statement<L_R_size, L_R>(kepler::List<kepler::Token> &stack, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::process_end_of_statement<L_B_R_size, L_B_R>(kepler::List<kepler::Token> &stack, kepler::Session &session) {
    helpers::erase(stack, 0, 2);
}

template <>
void kepler::phrase_table::evaluators::process_end_of_statement<L_BA_B_R_size, L_BA_B_R>(kepler::List<kepler::Token> &stack, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::process_end_of_statement<L_BA_R_size, L_BA_R>(kepler::List<kepler::Token> &stack, kepler::Session &session) {

}

bool kepler::phrase_table::match_type(const kepler::Token &token, TokenType type) {
    switch (type) {
        case Result:
            return classifiers::is_result(token);
        case Dyadic:
            return classifiers::is(token, DyadicOperatorToken);
        case Func:
            return classifiers::is(token, DefinedFunctionNameToken)
                   || classifiers::is(token, PrimitiveFunctionToken)
                   || classifiers::is(token, SystemFunctionNameToken);
        case PartialList:
            return classifiers::is(token, PartialIndexListToken);
        case CompleteList:
            return classifiers::is(token, CompleteIndexListToken);
        case LeftEOS:
            return classifiers::is(token, LeftEndOfStatementToken);
        case Monadic:
            return classifiers::is(token, MonadicOperatorToken);
        case Niladic:
            return classifiers::is(token, NiladicDefinedFunctionNameToken)
                   || classifiers::is(token, NiladicSystemFunctionNameToken);
        case RightEOS:
            return classifiers::is(token, RightEndOfStatementToken);
        case Var:
            return classifiers::is(token, VariableNameToken)
                   || classifiers::is(token, SystemVariableNameToken)
                   || classifiers::is(token, SharedVariableNameToken);
        case Wildcard:
            return classifiers::is(token, AssignmentArrowToken)
                   || classifiers::is(token, BranchArrowToken)
                   || classifiers::is(token, DefinedFunctionNameToken)
                   || classifiers::is(token, IndexSeparatorToken)
                   || classifiers::is(token, LeftAxisBracketToken)
                   || classifiers::is(token, LeftEndOfStatementToken)
                   || classifiers::is(token, LeftIndexBracketToken)
                   || classifiers::is(token, LeftParenthesisToken)
                   || classifiers::is(token, PrimitiveFunctionToken)
                   || classifiers::is(token, SystemFunctionNameToken)
                   || classifiers::is(token, RightAxisBracketToken);
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
    if(match<LP_B_RP_size, LP_B_RP>(stack)) {
        return evaluators::remove_parenthesis<LP_B_RP_size, LP_B_RP>;
    } else if(match<N_size, N>(stack)) {
        return evaluators::evaluate_niladic_function<N_size, N>;
    } else if(match<X_F_B_size, X_F_B>(stack)) {
        return evaluators::evaluate_monadic_function<X_F_B_size, X_F_B>;
    } else if(match<X_F_LB_C_RB_B_size, X_F_LB_C_RB_B>(stack)) {
        return evaluators::evaluate_monadic_function<X_F_LB_C_RB_B_size, X_F_LB_C_RB_B>;
    } else if(match<X_F_M_B_size, X_F_M_B>(stack)) {
        return evaluators::evaluate_monadic_operator<X_F_M_B_size, X_F_M_B>;
    } else if(match<X_F_M_LB_C_RB_B_size, X_F_M_LB_C_RB_B>(stack)) {
        return evaluators::evaluate_monadic_operator<X_F_M_LB_C_RB_B_size, X_F_M_LB_C_RB_B>;
    } else if(match<A_F_M_B_size, A_F_M_B>(stack)) {
        return evaluators::evaluate_monadic_operator<A_F_M_B_size, A_F_M_B>;
    } else if(match<A_F_M_LB_C_RB_B_size, A_F_M_LB_C_RB_B>(stack)) {
        return evaluators::evaluate_monadic_operator<A_F_M_LB_C_RB_B_size, A_F_M_LB_C_RB_B>;
    } else if(match<A_F_B_size, A_F_B>(stack)) {
        return evaluators::evaluate_dyadic_function<A_F_B_size, A_F_B>;
    } else if(match<A_F_LB_C_RB_B_size, A_F_LB_C_RB_B>(stack)) {
        return evaluators::evaluate_dyadic_function<A_F_LB_C_RB_B_size, A_F_LB_C_RB_B>;
    } else if(match<X_F_D_G_B_size, X_F_D_G_B>(stack)) {
        return evaluators::evaluate_dyadic_operator<X_F_D_G_B_size, X_F_D_G_B>;
    } else if(match<A_F_D_G_B_size, A_F_D_G_B>(stack)) {
        return evaluators::evaluate_dyadic_operator<A_F_D_G_B_size, A_F_D_G_B>;
    } else if(match<A_SM_D_G_B_size, A_SM_D_G_B>(stack)) {
        return evaluators::evaluate_dyadic_operator<A_SM_D_G_B_size, A_SM_D_G_B>;
    } else if(match<A_LB_K_RB_size, A_LB_K_RB>(stack)) {
        return evaluators::evaluate_indexed_reference<A_LB_K_RB_size, A_LB_K_RB>;
    } else if(match<V_LB_K_RB_AA_B_size, V_LB_K_RB_AA_B>(stack)) {
        return evaluators::evaluate_indexed_assignment<V_LB_K_RB_AA_B_size, V_LB_K_RB_AA_B>;
    } else if(match<V_AA_B_size, V_AA_B>(stack)) {
        return evaluators::evaluate_assignment<V_AA_B_size, V_AA_B>;
    } else if(match<V_size, V>(stack)) {
        return evaluators::evaluate_variable<V_size, V>;
    } else if(match<RB_size, RB>(stack)) {
        return evaluators::build_index_list<RB_size, RB>;
    } else if(match<IS_I_size, IS_I>(stack)) {
        return evaluators::build_index_list<IS_I_size, IS_I>;
    } else if(match<IS_B_I_size, IS_B_I>(stack)) {
        return evaluators::build_index_list<IS_B_I_size, IS_B_I>;
    } else if(match<LB_I_size, LB_I>(stack)) {
        return evaluators::build_index_list<LB_I_size, LB_I>;
    } else if(match<LB_B_I_size, LB_B_I>(stack)) {
        return evaluators::build_index_list<LB_B_I_size, LB_B_I>;
    } else if(match<L_R_size, L_R>(stack)) {
        return {evaluators::process_end_of_statement<L_R_size, L_R>, true};
    } else if(match<L_B_R_size, L_B_R>(stack)) {
        return {evaluators::process_end_of_statement<L_B_R_size, L_B_R>, true};
    } else if(match<L_BA_B_R_size, L_BA_B_R>(stack)) {
        return {evaluators::process_end_of_statement<L_BA_B_R_size, L_BA_B_R>, true};
    } else if(match<L_BA_R_size, L_BA_R>(stack)) {
        return {evaluators::process_end_of_statement<L_BA_R_size, L_BA_R>, true};
    }

    return nullptr;
}