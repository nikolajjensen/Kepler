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
#include "func_parser.h"
#include "core/constants/literals.h"

using namespace kepler::evaluation;

int FuncParser::subject_function() {

}

int FuncParser::delta() {
    return match(constants::delta);
}

int FuncParser::left_bracket() {
    return match(constants::left_bracket);
}

int FuncParser::right_bracket() {
    return match(constants::right_bracket);
}

int FuncParser::del() {
    return match(constants::del);
}

int FuncParser::permitted_blanks() {
    int counter = 0;
    while(match(constants::blank)) {}
    return counter;
}

bool FuncParser::match(rule rule, int* counter) {
    if(isAtEnd()) return false;

    int tmp = (this->*rule)();
    if(counter != nullptr) (*counter) += tmp;
    return tmp != 0;
}

bool FuncParser::match(kepler::TokenClass tokenClass, int* counter) {
    if(check(tokenClass)) {
        if(counter != nullptr) (*counter)++;
        advance();
        return true;
    }

    return false;
}

bool FuncParser::match(const kepler::Token::content_type& content, int* counter, kepler::TokenClass tokenClass) {
    if(check(tokenClass) && check(content)) {
        if(counter != nullptr) (*counter)++;
        advance();
        return true;
    }

    return false;
}

bool FuncParser::match(std::initializer_list<kepler::Token::content_type> contents, int* counter, kepler::TokenClass tokenClass) {
    for(auto& content : contents) {
        if(match(content, counter, tokenClass)) {
            return true;
        }
    }

    return false;
}

bool FuncParser::check(kepler::TokenClass tokenClass) {
    if(isAtEnd()) return false;
    return peek().token_class == tokenClass;
}

bool FuncParser::check(const kepler::Token::content_type& content) {
    if(isAtEnd()) { return false; }
    return peek().content.get() == content;
}

void FuncParser::advance() {
    if(!isAtEnd()) current++;
}

void FuncParser::backtrack(int& amount) {
    if(current - amount >= 0) {
        for(int i = 1; i <= amount; ++i) {
            int index = current - i;
        }

        current -= amount;
        amount = 0;
    }
}

// One past the end.
bool FuncParser::isAtEnd() {
    return current >= tokens->size();
}

kepler::Token& FuncParser::peek() {
    return tokens->at(current);
}

kepler::Token& FuncParser::previous() {
    return tokens->at(current - 1);
}