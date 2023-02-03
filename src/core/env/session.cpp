//
// Copyright 2022 Nikolaj Banke Jensen.
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

#include "session.h"
#include "core/lexer/lexer.h"
#include "core/parser/parser.h"
#include "core/parser/token_converter.h"
#include "core/interpreter/interpreter.h"
#include "core/exceptions/error.h"


#include <uni_algo/conv.h>

kepler::Session::Session(
        kepler::Workspace workspace,
        kepler::StringUTF8 sessionName_,
        Number comparisonTolerance_,
        Number randomLink_,
        UnsignedInteger printPrecision_,
        UnsignedInteger indexOrigin_,
        List<Token> latentExpression_)
        : activeWorkspace(workspace),
          sessionName(sessionName_),
          currentContext(nullptr),
          currentStack(nullptr),
          comparisonTolerance(comparisonTolerance_),
          randomLink(randomLink_),
          printPrecision(printPrecision_),
          indexOrigin(indexOrigin_),
          latentExpression(latentExpression_) {}


void kepler::Session::update_pointers() {
    currentContext = &(activeWorkspace.stateIndicator[activeWorkspace.stateIndicator.size() - 1]);
    currentStack = &currentContext->stack;
}

void kepler::Session::insert_line(StringUTF8 input) {
    activeWorkspace.addContext(std::move(input));
    update_pointers();
}

void kepler::Session::evaluate() {
    try {
        kepler::lexer::Lexer::lex(currentContext);
        kepler::parser::Parser::parse(currentContext, this);
        kepler::interpreter::interpret(currentContext, this);
    } catch (kepler::error& err) {
        currentContext->setError(err);
    }
}

/*
void kepler::Session::evaluate_line() {
    // Evaluate current context and do the whole shebang.
    //sleep(1);
    bool lexing_passed = kepler::lexer::lex(uni::utf8to32u(currentContext->currentLine), currentContext->currentStatement);
    bool parsing_passed = kepler::parser::parse(currentContext->currentStatement, *this);
    bool interpret_passed = kepler::interpreter::interpret(currentContext->currentStatement, currentContext->result);
    //currentResult->content = Char(parsing_passed ? U'Y' : U'N');
}
*/
/*
void kepler::Session::new_context() {
    activeWorkspace.stateIndicator.emplace_back();
    currentContext = &(activeWorkspace.stateIndicator[activeWorkspace.stateIndicator.size() - 1]);
    currentStack = &currentContext->stack;
    currentResult = &currentContext->result;
}
*/

kepler::Token& kepler::Session::current_referent(kepler::Token &token) {
    List<Char>& char_list = boost::get<List<Char>>(*token.content);

    kepler::Symbol& symbol_named_by_token = activeWorkspace.symbolTable.get_by_name(char_list);
    return symbol_named_by_token.referentList.front();
}

kepler::TokenClass kepler::Session::current_class(kepler::Token &token) {
    return current_referent(token).tokenClass;
}