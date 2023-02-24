//
// Copyright 2023 Nikolaj Banke Jensen.
//
// This file is part of Test.
// 
// Test is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Test is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License 
// along with Test. If not, see <https://www.gnu.org/licenses/>.
//

#include "parser.h"
#include "core/constants/literals.h"
#include "core/helpers/printers.h"

using namespace kepler::evaluation;

void Parser::parse() {
    if(statement() != tokens->size()) {
        throw kepler::error(SyntaxError, "Could not parse input.");
    }
}

// If a rule fails, it must backtrack appropriately, such
// that nothing has changed for its caller (and return 0).


// <statement> ::= <branch-arrow>? <expression>?
int Parser::statement() {
    int counter = 0;
    match(&Parser::branch_arrow, &counter);
    match(&Parser::expression, &counter);
    return counter;
}

// <expression> ::= (<operation>* <operand> <operation>?)+
// <expression> ::= <operation>* ((<operand> <operation>+)* | <operand>);
int Parser::expression() {
    int counter = 0;

    while(match(&Parser::operation, &counter)) {}

    bool stop = false;
    int operand_counter = 0;
    while(!stop) {
        if(match(&Parser::operand, &operand_counter)) {
            int operations = 0;
            while(match(&Parser::operation, &operations)) {}
            operand_counter += operations;

            if(operations < 1) {
                // Stop repeating first branch.
                stop = true;
            }
        } else {
            backtrack(operand_counter);
            backtrack(counter);
            return 0;
        }
    }

    counter += operand_counter;

    return counter;
}

int Parser::operation() {
    int counter = 0;

    if(match(&Parser::assignment, &counter)) {}
    else if (match(DefinedFunctionNameToken, &counter)) {}
    else if (match(SystemFunctionNameToken, &counter)) {}
    else if (match(&Parser::derived_function, &counter)) {}

    return counter;
}

int Parser::assignment() {
    int counter = 0;

    if(!(match(VariableNameToken, &counter) || match(SystemVariableNameToken, &counter) || match(SharedVariableNameToken, &counter))) {
        return 0;
    }

    match(&Parser::index, &counter);

    if(!match(&Parser::assignment_arrow, &counter)) {
        backtrack(counter);
        counter = 0;
    }

    return counter;
}

int Parser::derived_function() {
    int counter = 0;

    if(((match(&Parser::small_circle, &counter) || match(&Parser::primitive_function, &counter)) && match(&Parser::dot, &counter) && match(&Parser::primitive_function, &counter))) {
        return counter;
    } else {
        backtrack(counter);
    }

    if(match(&Parser::primitive_function, &counter)) {
        match(&Parser::axis_monadic_operator, &counter);
        match(&Parser::axis_specification, &counter);
        return counter;
    }

    if(match(&Parser::operand, &counter) || match(&Parser::function, &counter)) {
        if(match(&Parser::dyadic_operator, &counter)) {
            if(match(&Parser::operand, &counter) || match(&Parser::function, &counter)) {
                return counter;
            } else {
                backtrack(counter);
            }
        } else if (match(&Parser::monadic_operator, &counter)) {
            return counter;
        } else {
            backtrack(counter);
            counter = 0;
        }
    }

    return counter;
}

int Parser::axis_specification() {
    int counter = 0;

    if(match(&Parser::left_axis_bracket, &counter) && match(&Parser::expression, &counter) && match(&Parser::right_axis_bracket, &counter)) {
        return counter;
    } else {
        backtrack(counter);
        return 0;
    }
}

int Parser::operand() {
    int counter = 0;

    if(match(&Parser::left_parenthesis, &counter) && match(&Parser::expression, &counter) && match(&Parser::right_parenthesis, &counter)) {
        match(&Parser::index, &counter);
        return counter;
    } else {
        backtrack(counter);
    }

    if(match(ConstantToken, &counter)) {}
    else if (match(VariableNameToken, &counter)) {}
    else if (match(SharedVariableNameToken, &counter)) {}
    else if (match(SystemVariableNameToken, &counter)) {}
    else if (match(NiladicSystemFunctionNameToken, &counter)) {}
    else if (match(NiladicDefinedFunctionNameToken, &counter)) {}

    if(counter != 0) {
        match(&Parser::index, &counter);
    }

    return counter;
}

// <index> ::= <left-index-bracket> <index-separator>* ((<expression> <index-separator>+)* | <expression>) <right-index-bracket>
int Parser::index() {
    int counter = 0;

    if(!match(&Parser::left_index_bracket, &counter)) {
        return 0;
    }

    while(match(&Parser::index_separator, &counter)) {}

    bool stop = false;
    while(!stop) {
        if(match(&Parser::expression, &counter)) {
            int separators = 0;
            while(match(&Parser::index_separator, &separators)) { }
            counter += separators;

            if(separators < 1) {
                // Stop repeating this check.
                stop = true;
            }
        } else {
            // Backtrack by 'counter'
            backtrack(counter);
            return 0;
        }
    }

    if(!match(&Parser::right_index_bracket, &counter)) {
        // Backtrack by 'counter'
        backtrack(counter);
        return 0;
    }

    return counter;
}

int Parser::primitive_function() {
    if(match({
                     constants::left_caret, constants::less_than_or_equal, constants::equal,
                     constants::greater_than_or_equal, constants::right_caret, constants::not_equal,
                     constants::down_caret, constants::up_caret, constants::bar,
                     constants::divide, constants::plus, constants::multiply,
                     constants::query, constants::epsilon, constants::rho,
                     constants::tilde, constants::up_arrow, constants::down_arrow,
                     constants::iota, constants::circle, constants::star,
                     constants::up_stile, constants::down_stile, constants::up_tack,
                     constants::down_tack, constants::stile, constants::back_slash,
                     constants::comma, constants::slash, constants::del_stile,
                     constants::delta_stile, constants::circle_stile, constants::circle_back_slash,
                     constants::circle_bar, constants::circle_star, constants::down_caret_tilde,
                     constants::up_caret_tilde, constants::quote_dot, constants::quad_divide,
                     constants::up_tack_jot, constants::down_tack_jot, constants::back_slash_bar,
                     constants::slash_bar, constants::comma_bar
    })) {
        set_class(kepler::PrimitiveFunctionToken);
        return true;
    }

    return false;
}

int Parser::function() {
    int counter = 0;

    if(match(&Parser::primitive_function, &counter)) {}
    else if (match(&Parser::derived_function, &counter)) {}
    else if (match(DefinedFunctionNameToken, &counter)) {}
    else if (match(SystemFunctionNameToken, &counter)) {}

    return counter;
}

int Parser::dyadic_operator() {
    int counter = 0;

    if(match(&Parser::primitive_dyadic_operator, &counter)) {}
    else if (match(DefinedDyadicOperatorNameToken, &counter)) {}

    if(counter != 0) {
        set_class(kepler::DyadicOperatorToken);
    }

    return counter;
}

int Parser::monadic_operator() {
    int counter = 0;

    if(match(&Parser::primitive_monadic_operator, &counter)) {}
    else if (match(DefinedMonadicOperatorNameToken, &counter)) {}

    if(counter != 0) {
        set_class(kepler::MonadicOperatorToken);
    }

    return counter;
}

int Parser::axis_monadic_operator() {
    if(match({
                         constants::slash,
                         constants::slash_bar,
                         constants::back_slash,
                         constants::back_slash_bar
    })) {
        set_class(AxisMonadicOperatorToken);
        return true;
    }

    return false;
}

int Parser::primitive_monadic_operator() {
    int counter = 0;

    if(match(&Parser::axis_monadic_operator, &counter)) {}
    else if (match(&Parser::diaeresis_tilde, &counter)) {}

    if(counter) {
        set_class(PrimitiveMonadicOperatorToken);
    }

    return counter;
}

int Parser::primitive_dyadic_operator() {
    if(diaeresis_jot()) {
        set_class(PrimitiveDyadicOperatorToken);
        return true;
    }
    return false;
}

int Parser::diaeresis_jot() {
    return match(constants::diaeresis_jot);
}

int Parser::diaeresis_tilde() {
    return match(constants::diaeresis_tilde);
}

int Parser::left_parenthesis() {
    return match(constants::left_parenthesis);
}

int Parser::right_parenthesis() {
    return match(constants::right_parenthesis);
}

int Parser::left_axis_bracket() {
    return match(constants::left_bracket);
}

int Parser::right_axis_bracket() {
    return match(constants::right_bracket);
}

int Parser::branch_arrow() {
    return match(constants::right_arrow);
}

int Parser::assignment_arrow() {
    if(match(constants::left_arrow)) {
        set_class(AssignmentArrowToken);
        return true;
    }

    return false;
}

int Parser::left_index_bracket() {
    return match(constants::left_bracket);
}

int Parser::right_index_bracket() {
    return match(constants::right_bracket);
}

int Parser::index_separator() {
    return match(constants::semicolon);
}

int Parser::small_circle() {
    return match(constants::circle);
}

int Parser::dot() {
    return match(constants::dot);
}

bool Parser::match(rule rule, int* counter) {
    if(isAtEnd()) return false;

    int tmp = (this->*rule)();
    if(counter != nullptr) (*counter) += tmp;
    return tmp != 0;
}

bool Parser::match(kepler::TokenClass tokenClass, int* counter) {
    if(check(tokenClass)) {
        if(counter != nullptr) (*counter)++;
        advance();
        return true;
    }

    return false;
}

bool Parser::match(const kepler::Token::content_type& content, int* counter, kepler::TokenClass tokenClass) {
    if(check(tokenClass) && check(content)) {
        if(counter != nullptr) (*counter)++;
        advance();
        return true;
    }

    return false;
}

bool Parser::match(std::initializer_list<kepler::Token::content_type> contents, int* counter, kepler::TokenClass tokenClass) {
    for(auto& content : contents) {
        if(match(content, counter, tokenClass)) {
            return true;
        }
    }

    return false;
}

void Parser::set_class(kepler::TokenClass tokenClass) {
    backtrack_log[current - 1] = previous().token_class;
    previous().token_class = tokenClass;
}

bool Parser::check(kepler::TokenClass tokenClass) {
    if(isAtEnd()) return false;
    return peek().token_class == tokenClass;
}

bool Parser::check(const kepler::Token::content_type& content) {
    if(isAtEnd()) { return false; }
    return peek().content.get() == content;
}

void Parser::advance() {
    if(!isAtEnd()) current++;
}

void Parser::backtrack(int& amount) {
    if(current - amount >= 0) {
        for(int i = 1; i <= amount; ++i) {
            int index = current - i;
            if(backtrack_log.contains(index)) {
                tokens->at(index).token_class = backtrack_log[index];
                backtrack_log.erase(index);
            }
        }

        current -= amount;
        amount = 0;
    }
}

// One past the end.
bool Parser::isAtEnd() {
    return current >= tokens->size();
}

kepler::Token& Parser::peek() {
    return tokens->at(current);
}

kepler::Token& Parser::previous() {
    return tokens->at(current - 1);
}

