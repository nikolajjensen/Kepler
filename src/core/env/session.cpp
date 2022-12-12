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
#include "../lexer/lexer.h"


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
          currentResult(nullptr),
          comparisonTolerance(comparisonTolerance_),
          randomLink(randomLink_),
          printPrecision(printPrecision_),
          indexOrigin(indexOrigin_),
          latentExpression(latentExpression_) {}



void kepler::Session::evaluate_line() {
    // Evaluate current context and do the whole shebang.
    //sleep(1);
    bool lexing_passed = kepler::lexer::lex(uni::utf8to32u(currentContext->currentLine), currentContext->currentStatement);
    currentResult->content = {lexing_passed ? U'Y' : U'N'};
}

void kepler::Session::new_context() {
    activeWorkspace.stateIndicator.emplace_back();
    currentContext = &(activeWorkspace.stateIndicator[activeWorkspace.stateIndicator.size() - 1]);
    currentStack = &currentContext->stack;
    currentResult = &currentContext->result;
}