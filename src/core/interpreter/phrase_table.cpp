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
#include "form_table_evaluators.tpp"

using namespace kepler;
using namespace kepler::phrase_table;

/*
bool kepler::phrase_table::matchers::is_result(kepler::Token &token) {
    return classifiers::is_result(token);
}

bool kepler::phrase_table::matchers::is_dyadic(kepler::Token &token) {
    return classifiers::is(token, DyadicOperatorToken);
}

bool kepler::phrase_table::matchers::is_func(kepler::Token &token) {
    return classifiers::is(token, DefinedFunctionNameToken)
            || classifiers::is(token, PrimitiveFunctionToken)
            || classifiers::is(token, SystemFunctionNameToken);
}

bool kepler::phrase_table::matchers::is_partial_index_list(kepler::Token &token) {
    return classifiers::is(token, PartialIndexListToken);
}

bool kepler::phrase_table::matchers::is_complete_index_list(kepler::Token &token) {
    return classifiers::is(token, CompleteIndexListToken);
}

bool kepler::phrase_table::matchers::is_left_eos(kepler::Token &token) {
    return classifiers::is(token, LeftEndOfStatementToken);
}

bool kepler::phrase_table::matchers::is_monadic(kepler::Token &token) {
    return classifiers::is(token, MonadicOperatorToken);
}

bool kepler::phrase_table::matchers::is_niladic(kepler::Token &token) {
    return classifiers::is(token, NiladicDefinedFunctionNameToken)
            || classifiers::is(token, NiladicSystemFunctionNameToken);
}

bool kepler::phrase_table::matchers::is_right_eos(kepler::Token &token) {
    return classifiers::is(token, RightEndOfStatementToken);
}

bool kepler::phrase_table::matchers::is_variable(kepler::Token &token) {
    return classifiers::is(token, VariableNameToken)
            || classifiers::is(token, SystemVariableNameToken)
            || classifiers::is(token, SharedVariableNameToken);
}

bool kepler::phrase_table::matchers::is_wildcard(kepler::Token &token) {
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
}

bool kepler::phrase_table::matchers::is_left_paren(kepler::Token &token) {
    return classifiers::is(token, LeftParenthesisToken);
}

bool kepler::phrase_table::matchers::is_right_paren(kepler::Token &token) {
    return classifiers::is(token, RightParenthesisToken);
}

bool kepler::phrase_table::matchers::is_left_bracket(kepler::Token &token) {
    return classifiers::is(token, LeftAxisBracketToken)
            || classifiers::is(token, LeftIndexBracketToken);
}

bool kepler::phrase_table::matchers::is_right_bracket(kepler::Token &token) {
    return classifiers::is(token, RightAxisBracketToken)
           || classifiers::is(token, RightIndexBracketToken);
}

bool kepler::phrase_table::matchers::is_small_circle(kepler::Token &token) {
    return classifiers::is(token, SmallCircleToken);
}

bool kepler::phrase_table::matchers::is_index_separator(kepler::Token &token) {
    return classifiers::is(token, SemicolonToken);
}

bool kepler::phrase_table::matchers::is_assignment_arrow(kepler::Token &token) {
    return classifiers::is(token, AssignmentArrowToken);
}

bool kepler::phrase_table::matchers::is_branch_arrow(kepler::Token &token) {
    return classifiers::is(token, BranchArrowToken);
}

*/


template <>
void kepler::phrase_table::evaluators::remove_parenthesis<LP_B_RP_size, LP_B_RP>(List<Token> &stack, Session &session) {
    if(classifiers::is(stack[1], NilToken) || classifiers::is(stack[1], BranchToken)) {
        // Signal value-error
        //result.set(ValueErrorToken, boost::none);
        throw kepler::error(ValueError, "Cannot remove parenthesis.");
    }

    helpers::erase(stack, 0, 2);
}

template <>
void kepler::phrase_table::evaluators::evaluate_niladic_function<N_size, N>(List<Token> &stack, Session &session) {
    Token& n = stack[0];

    if(classifiers::is(n, NiladicDefinedFunctionNameToken)) {
        if(session.current_class(n) == NiladicDefinedFunctionToken) {
            n = kepler::form_table::evaluators::call_defined_function<form_table::niladic_cdf_size, form_table::niladic_cdf>({&n});
        } else {
            throw kepler::error(SyntaxError, "Undefined niladic function reference.");
        }
    } else if(classifiers::is(n, NiladicSystemFunctionNameToken)) {
        n = kepler::form_table::evaluate({&n}, {kepler::form_table::Content});
    }
}

template<>
void kepler::phrase_table::evaluators::evaluate_monadic_function<X_F_B_size, X_F_B>(kepler::List<kepler::Token> &stack, kepler::Session &session) {
    Token& f = stack[1];
    Token& b = stack[2];
    if(classifiers::is(b, DefinedFunctionNameToken)) {

    } else if(classifiers::is(f, PrimitiveFunctionToken) || classifiers::is(f, SystemFunctionNameToken)) {
        f = kepler::form_table::evaluate({&f, &b}, {kepler::form_table::Content, kepler::form_table::Type});
        helpers::erase(stack, 2);
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