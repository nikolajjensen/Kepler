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
#include "core/error/error.h"


#include <uni_algo/conv.h>

kepler::Session::Session(std::string&& session_name_, kepler::config&& config_)
    :   active_workspace(config_.clear_workspace_identifier),
        keyboard_state(OpenKeyboardState),
        session_name(session_name_),
        current_context(nullptr),
        config(config_) {}

void kepler::Session::update_pointers() {
    current_context = &(active_workspace.stateIndicator[active_workspace.stateIndicator.size() - 1]);
}

void kepler::Session::insert_line(StringUTF8 input) {
    active_workspace.addContext(std::move(input));
    update_pointers();
}

void kepler::Session::evaluate() {
    try {
        kepler::lexer::Lexer::lex(current_context);
        kepler::parser::Parser::parse(current_context, this);
        kepler::interpreter::interpret(current_context, this);
    } catch (kepler::error& err) {
        current_context->setError(err);
    }
}

void kepler::Session::lockKeyboard() {
    keyboard_state = LockedKeyboardState;
}

void kepler::Session::openKeyboard() {
    keyboard_state = OpenKeyboardState;
}

kepler::Token& kepler::Session::current_referent(kepler::Token &token) {
    auto& char_list = boost::get<List<Char>>(*token.content);

    kepler::Symbol& symbol_named_by_token = active_workspace.symbolTable.get_by_name(char_list);
    return symbol_named_by_token.referentList.front();
}

kepler::TokenClass kepler::Session::current_class(kepler::Token &token) {
    return current_referent(token).tokenClass;
}