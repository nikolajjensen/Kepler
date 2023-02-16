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

#include "repl.h"
#include "texts.h"
#include "core/env/printers.h"
#include <iostream>

void kepler::tui::print(std::string str) {
    std::cout << str << std::flush;
}

void kepler::tui::setup() {
    print(welcome_message);
}

void kepler::tui::prompt(std::string& input) {
    print("\n" + input_prompt + " ");
    getline(std::cin, input);
}

void kepler::tui::display_result(Session& session) {
    if(session.current_context->error) {
        kepler::printers::ErrorPrinter ep(std::cout);
        ep(session);
    } else {
        kepler::printers::TokenPrinter tp(std::cout);
        tp(session.current_context->result);
    }
}

void kepler::tui::loop(Session& session) {
    std::string input;

    while(true) {
        prompt(input);
        session.insert_line(input);
        session.evaluate();
        display_result(session);
    }
}

void kepler::tui::repl(Session &session) {
    setup();
    loop(session);
}