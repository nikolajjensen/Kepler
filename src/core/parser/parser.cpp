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
#include "../characters.h"
#include "token_converter.h"
#include "../env/printers.h"
#include "../interpreter/form_table.h"
#include "../interpreter/form_table_evaluators.tpp"

using namespace kepler::parser;

bool Parser::parse(kepler::Context* context, kepler::Session* session) {
    kepler::parser::convert_tokens(context->currentStatement, *session);
    Parser p(&context->currentStatement);
    bool success = p.parse();

    if(success) {
        context->currentStatement.insert(context->currentStatement.begin(), Token(LeftEndOfStatementToken));
        context->currentStatement.emplace_back(RightEndOfStatementToken);
    }

    return success;
}

bool Parser::parse() {
    return statement() == tokens->size();
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
    while(!stop) {
        if(match(&Parser::operand, &counter)) {
            int operations = 0;
            while(match(&Parser::operation, &operations)) {}
            counter += operations;

            if(operations < 1) {
                // Stop repeating first branch.
                stop = true;
            }
        } else {
            backtrack(counter);
            return 0;
        }
    }

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
        characters::left_caret, characters::less_than_or_equal, characters::equal,
        characters::greater_than_or_equal, characters::right_caret, characters::not_equal,
        characters::down_caret, characters::up_caret, characters::bar,
        characters::divide, characters::plus, characters::multiply,
        characters::query, characters::epsilon, characters::rho,
        characters::tilde, characters::up_arrow, characters::down_arrow,
        characters::iota, characters::circle, characters::star,
        characters::up_stile, characters::down_stile, characters::up_tack,
        characters::down_tack, characters::stile, characters::back_slash,
        characters::comma, characters::slash, characters::del_stile,
        characters::delta_stile, characters::circle_stile, characters::circle_back_slash,
        characters::circle_bar, characters::circle_star, characters::down_caret_tilde,
        characters::up_caret_tilde, characters::quote_dot, characters::quad_divide,
        characters::up_tack_jot, characters::down_tack_jot, characters::back_slash_bar,
        characters::slash_bar, characters::comma_bar
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
    return match({
        characters::slash,
        characters::slash_bar,
        characters::back_slash,
        characters::back_slash_bar
    });
}

int Parser::primitive_monadic_operator() {
    int counter = 0;

    if(match(&Parser::axis_monadic_operator, &counter)) {}
    else if (match(&Parser::diaeresis_tilde, &counter)) {}

    return counter;
}

int Parser::primitive_dyadic_operator() {
    return diaeresis_jot();
}

int Parser::diaeresis_jot() {
    return match(characters::diaeresis_jot);
}

int Parser::diaeresis_tilde() {
    return match(characters::diaeresis_tilde);
}

int Parser::left_parenthesis() {
    return match(characters::left_parenthesis);
}

int Parser::right_parenthesis() {
    return match(characters::right_parenthesis);
}

int Parser::left_axis_bracket() {
    return match(characters::left_bracket);
}

int Parser::right_axis_bracket() {
    return match(characters::right_bracket);
}

int Parser::branch_arrow() {
    return match(characters::right_arrow);
}

int Parser::assignment_arrow() {
    if(match(characters::left_arrow)) {
        set_class(AssignmentArrowToken);
        return true;
    }

    return false;
}

int Parser::left_index_bracket() {
    return match(characters::left_bracket);
}

int Parser::right_index_bracket() {
    return match(characters::right_bracket);
}

int Parser::index_separator() {
    return match(characters::semicolon);
}

int Parser::small_circle() {
    return match(characters::circle);
}

int Parser::dot() {
    return match(characters::dot);
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
    backtrack_log[current - 1] = previous().tokenClass;
    previous().tokenClass = tokenClass;
}

bool Parser::check(kepler::TokenClass tokenClass) {
    if(isAtEnd()) return false;
    return peek().tokenClass == tokenClass;
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
                tokens->at(index).tokenClass = backtrack_log[index];
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

