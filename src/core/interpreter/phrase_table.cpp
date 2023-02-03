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

#include "phrase_table.h"
#include "../token.h"
#include "../classifiers.h"
#include <functional>

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
void kepler::phrase_table::evaluators::remove_parenthesis<LP_B_RP_size, LP_B_RP>(List<Token> &stack, Token &result, Session &session) {
    if(classifiers::is(stack[1], NilToken) || classifiers::is(stack[1], BranchToken)) {
        // Signal value-error
        result.set(ValueErrorToken, boost::none);
    }

    stack.erase(stack.begin());
    stack.erase(stack.begin() + 2);
}

template <>
void kepler::phrase_table::evaluators::evaluate_niladic_function<N_size, N>(List<Token> &stack, Token &result, Session &session) {
    Token& N = stack[0];

    /*
     * Token& N = stack[0];

    if(classifiers::is(N, NiladicDefinedFunctionNameToken)) {
        if(session.current_class(N) == NiladicDefinedFunctionToken) {
            boost::optional<Token> token = form_table::form_table_evaluation({N}, {form_table::PatternClass::DFN});
            return optionally_replace(stack, 0, 0, token, result, SyntaxErrorToken);
        } else {
            result.set(SyntaxErrorToken, boost::none);
            return Error;
        }
    } else if (classifiers::is(N, NiladicSystemFunctionNameToken)) {
        boost::optional<Token> token = form_table::form_table_evaluation({N}, {form_table::PatternClass::Content});
        return optionally_replace(stack, 0, 0, token, result, SyntaxErrorToken);
    }

    return Error;
    */
}

template<>
void kepler::phrase_table::evaluators::evaluate_monadic_function<X_F_B_size, X_F_B>(kepler::List<kepler::Token> &stack,
                                                                 kepler::Token &result, kepler::Session &session) {

}

template<>
void kepler::phrase_table::evaluators::evaluate_monadic_function<X_F_LB_C_RB_B_size, X_F_LB_C_RB_B>(kepler::List<kepler::Token> &stack,
                                                                                 kepler::Token &result, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::evaluate_monadic_operator<X_F_M_B_size, X_F_M_B>(kepler::List<kepler::Token> &stack,
                                                                 kepler::Token &result, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::evaluate_monadic_operator<X_F_M_LB_C_RB_B_size, X_F_M_LB_C_RB_B>(kepler::List<kepler::Token> &stack,
                                                                                   kepler::Token &result, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::evaluate_monadic_operator<A_F_M_B_size, A_F_M_B>(kepler::List<kepler::Token> &stack,
                                                                                           kepler::Token &result, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::evaluate_monadic_operator<A_F_M_LB_C_RB_B_size, A_F_M_LB_C_RB_B>(kepler::List<kepler::Token> &stack,
                                                                                           kepler::Token &result, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::evaluate_dyadic_function<A_F_B_size, A_F_B>(kepler::List<kepler::Token> &stack,
                                                                                        kepler::Token &result, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::evaluate_dyadic_function<A_F_LB_C_RB_B_size, A_F_LB_C_RB_B>(kepler::List<kepler::Token> &stack,
                                                                 kepler::Token &result, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::evaluate_dyadic_operator<X_F_D_G_B_size, X_F_D_G_B>(kepler::List<kepler::Token> &stack,
                                                                                          kepler::Token &result, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::evaluate_dyadic_operator<A_F_D_G_B_size, A_F_D_G_B>(kepler::List<kepler::Token> &stack,
                                                                                          kepler::Token &result, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::evaluate_dyadic_operator<A_SM_D_G_B_size, A_SM_D_G_B>(kepler::List<kepler::Token> &stack,
                                                                                          kepler::Token &result, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::evaluate_indexed_reference<A_LB_K_RB_size, A_LB_K_RB>(kepler::List<kepler::Token> &stack,
                                                                  kepler::Token &result, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::evaluate_indexed_assignment<V_LB_K_RB_AA_B_size, V_LB_K_RB_AA_B>(kepler::List<kepler::Token> &stack,
                                                                   kepler::Token &result, kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::evaluate_assignment<V_AA_B_size, V_AA_B>(kepler::List<kepler::Token> &stack, kepler::Token &result,
                                                           kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::evaluate_variable<V_size, V>(kepler::List<kepler::Token> &stack, kepler::Token &result,
                                                         kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::build_index_list<RB_size, RB>(kepler::List<kepler::Token> &stack, kepler::Token &result,
                                                                     kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::build_index_list<IS_I_size, IS_I>(kepler::List<kepler::Token> &stack, kepler::Token &result,
                                                        kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::build_index_list<IS_B_I_size, IS_B_I>(kepler::List<kepler::Token> &stack, kepler::Token &result,
                                                                       kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::build_index_list<LB_I_size, LB_I>(kepler::List<kepler::Token> &stack, kepler::Token &result,
                                                                       kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::build_index_list<LB_B_I_size, LB_B_I>(kepler::List<kepler::Token> &stack, kepler::Token &result,
                                                                       kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::process_end_of_statement<L_R_size, L_R>(kepler::List<kepler::Token> &stack, kepler::Token &result,
                                                        kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::process_end_of_statement<L_B_R_size, L_B_R>(kepler::List<kepler::Token> &stack, kepler::Token &result,
                                                                              kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::process_end_of_statement<L_BA_B_R_size, L_BA_B_R>(kepler::List<kepler::Token> &stack, kepler::Token &result,
                                                                              kepler::Session &session) {

}

template <>
void kepler::phrase_table::evaluators::process_end_of_statement<L_BA_R_size, L_BA_R>(kepler::List<kepler::Token> &stack, kepler::Token &result,
                                                                              kepler::Session &session) {

}


bool kepler::phrase_table::match_type(kepler::Token &token, TokenType type) {
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


template <std::size_t S, const pattern_type<S>& Pattern>
bool kepler::phrase_table::match(kepler::List<kepler::Token> &tokens) {
    if(tokens.size() < S) {
        return false;
    }

    for(int i = 0; i < S; ++i) {
        if(const TokenType* cl = boost::get<TokenType>(&Pattern[i])) {
            if(!match_type(tokens[i], *cl)) { return false; }
        } else if(const Token::content_type* content = boost::get<Token::content_type>(&Pattern[i])) {
            if(tokens[i].content.get() != *content) { return false; }
        }
    }

    return true;
}

phrase_evaluator_type kepler::phrase_table::lookup(List<Token> &stack, Token &result, Session &session) {
    if(match<LP_B_RP_size, LP_B_RP>(stack)) {
        return evaluators::remove_parenthesis<LP_B_RP_size, LP_B_RP>;
    }

    return nullptr;
}

/*
phrase_evaluator_type kepler::phrase_table::lookup(List<Token> &stack, Token &result, Session &session) {
    size_t stack_size = stack.size();

    if(stack_size >= 3
            && matchers::is_left_paren(stack[0])
            && matchers::is_result(stack[1])
            && matchers::is_right_paren(stack[2])) {
        return evaluators::remove_parenthesis<Pattern::LP_B_RP>;
    } else if(stack_size >= 1
            && matchers::is_niladic(stack[0])) {
        return evaluators::evaluate_niladic_function<Pattern::N>;
    } else if(stack_size >= 3
            && matchers::is_wildcard(stack[0])
            && matchers::is_func(stack[1])
            && matchers::is_result(stack[2])) {
        return evaluators::evaluate_monadic_function<Pattern::X_F_B>;
    } else if(stack_size >= 6
            && matchers::is_wildcard(stack[0])
            && matchers::is_func(stack[1])
            && matchers::is_result(stack[2])
            && matchers::is_left_bracket(stack[2])
            && matchers::is_complete_index_list(stack[3])
            && matchers::is_right_bracket(stack[4])
            && matchers::is_result(stack[5])) {
        return evaluators::evaluate_monadic_function<Pattern::X_F_LB_C_RB_B>;
    } else if(stack_size >= 4
            && matchers::is_wildcard(stack[0])
            && matchers::is_func(stack[1])
            && matchers::is_monadic(stack[2])
            && matchers::is_result(stack[3])) {
        return evaluators::evaluate_monadic_operator<Pattern::X_F_M_B>;
    } else if(stack_size >= 7
            && matchers::is_wildcard(stack[0])
            && matchers::is_func(stack[1])
            && matchers::is_monadic(stack[2])
            && matchers::is_left_bracket(stack[3])
            && matchers::is_complete_index_list(stack[4])
            && matchers::is_right_bracket(stack[5])
            && matchers::is_result(stack[6])) {
        return evaluators::evaluate_monadic_operator<Pattern::X_F_M_LB_C_RB_B>;
    } else if(stack_size >= 4
            && matchers::is_result(stack[0])
            && matchers::is_func(stack[1])
            && matchers::is_monadic(stack[2])
            && matchers::is_result(stack[3])) {
        return evaluators::evaluate_monadic_operator<Pattern::A_F_M_B>;
    } else if(stack_size >= 7
            && matchers::is_result(stack[0])
            && matchers::is_func(stack[1])
            && matchers::is_monadic(stack[2])
            && matchers::is_left_bracket(stack[3])
            && matchers::is_complete_index_list(stack[4])
            && matchers::is_right_bracket(stack[5])
            && matchers::is_result(stack[6])) {
        return evaluators::evaluate_monadic_operator<Pattern::A_F_M_LB_C_RB_B>;
    } else if(stack_size >= 3
            && matchers::is_result(stack[0])
            && matchers::is_func(stack[1])
            && matchers::is_result(stack[2])) {
        return evaluators::evaluate_dyadic_function<Pattern::A_F_B>;
    } else if(stack_size >= 6
            && matchers::is_result(stack[0])
            && matchers::is_func(stack[1])
            && matchers::is_left_bracket(stack[2])
            && matchers::is_complete_index_list(stack[3])
            && matchers::is_right_bracket(stack[4])
            && matchers::is_result(stack[5])) {
        return evaluators::evaluate_dyadic_function<Pattern::A_F_LB_C_RB_B>;
    } else if(stack_size >= 5
            && matchers::is_wildcard(stack[0])
            && matchers::is_func(stack[1])
            && matchers::is_dyadic(stack[2])
            && matchers::is_func(stack[3])
            && matchers::is_result(stack[4])) {
        return evaluators::evaluate_dyadic_operator<Pattern::X_F_D_G_B>;
    } else if(stack_size >= 5
            && matchers::is_result(stack[0])
            && matchers::is_func(stack[1])
            && matchers::is_dyadic(stack[2])
            && matchers::is_func(stack[3])
            && matchers::is_result(stack[4])) {
        return evaluators::evaluate_dyadic_operator<Pattern::A_F_D_G_B>;
    } else if(stack_size >= 5
            && matchers::is_result(stack[0])
            && matchers::is_small_circle(stack[1])
            && matchers::is_dyadic(stack[2])
            && matchers::is_func(stack[3])
            && matchers::is_result(stack[4])) {
        return evaluators::evaluate_dyadic_operator<Pattern::A_SM_D_G_B>;
    } else if(stack_size >= 4
              && matchers::is_result(stack[0])
              && matchers::is_left_bracket(stack[1])
              && matchers::is_complete_index_list(stack[2])
              && matchers::is_right_bracket(stack[3])) {
        return evaluators::evaluate_indexed_reference<Pattern::A_LB_K_RB>;
    } else if(stack_size >= 6
              && matchers::is_variable(stack[0])
              && matchers::is_left_bracket(stack[1])
              && matchers::is_complete_index_list(stack[2])
              && matchers::is_right_bracket(stack[3])
              && matchers::is_assignment_arrow(stack[4])
              && matchers::is_result(stack[5])) {
        return evaluators::evaluate_indexed_assignment<Pattern::V_LB_K_RB_AA_B>;
    } else if(stack_size >= 3
              && matchers::is_variable(stack[0])
              && matchers::is_assignment_arrow(stack[1])
              && matchers::is_result(stack[2])) {
        return evaluators::evaluate_assignment<Pattern::V_AA_B>;
    } else if(stack_size >= 1
              && matchers::is_variable(stack[0])) {
        return evaluators::evaluate_variable<Pattern::V>;
    } else if(stack_size >= 1
              && matchers::is_right_bracket(stack[0])) {
        return evaluators::build_index_list<Pattern::RB>;
    } else if(stack_size >= 2
              && matchers::is_index_separator(stack[0])
              && matchers::is_partial_index_list(stack[1])) {
        return evaluators::build_index_list<Pattern::IS_I>;
    } else if(stack_size >= 3
              && matchers::is_index_separator(stack[0])
              && matchers::is_result(stack[1])
              && matchers::is_partial_index_list(stack[2])) {
        return evaluators::build_index_list<Pattern::IS_B_I>;
    } else if(stack_size >= 2
               && matchers::is_left_bracket(stack[0])
               && matchers::is_partial_index_list(stack[1])) {
        return evaluators::build_index_list<Pattern::LB_I>;
    } else if(stack_size >= 3
              && matchers::is_left_bracket(stack[0])
              && matchers::is_result(stack[1])
              && matchers::is_partial_index_list(stack[2])) {
        return evaluators::build_index_list<Pattern::LB_B_I>;
    } else if(stack_size >= 2
              && matchers::is_left_eos(stack[0])
              && matchers::is_right_eos(stack[1])) {
        return evaluators::process_end_of_statement<Pattern::L_R>;
    } else if(stack_size >= 3
              && matchers::is_left_eos(stack[0])
              && matchers::is_result(stack[1])
              && matchers::is_right_eos(stack[2])) {
        return evaluators::process_end_of_statement<Pattern::L_B_R>;
    } else if(stack_size >= 4
              && matchers::is_left_eos(stack[0])
              && matchers::is_branch_arrow(stack[1])
              && matchers::is_result(stack[2])
              && matchers::is_right_eos(stack[3])) {
        return evaluators::process_end_of_statement<Pattern::L_BA_B_R>;
    } else if(stack_size >= 3
              && matchers::is_left_eos(stack[0])
              && matchers::is_branch_arrow(stack[1])
              && matchers::is_right_eos(stack[2])) {
        return evaluators::process_end_of_statement<Pattern::L_BA_R>;
    }

    return nullptr;
}
 */