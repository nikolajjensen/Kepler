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

#pragma once
#include "workspace.h"
#include "keyboard_state.h"
#include "config.h"

namespace kepler {
    class Session {
    public:
        Workspace active_workspace;
        KeyboardState keyboard_state;
        std::string session_name;
        Context* current_context;
        Config config;

        Session(std::string&& name, kepler::Config&& config);

        void evaluate();

        void update_pointers();
        void insert_line(StringUTF8 input);

        Token& current_referent(Token& token);
        TokenClass current_class(Token& token);

        void openKeyboard();
        void lockKeyboard();
    };
};