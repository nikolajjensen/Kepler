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

#pragma once
#include "includes.h"
#include "core/env/session.h"

namespace kepler::tui {
    namespace {
        using namespace ftxui;

        class InfoBarBase : public ComponentBase {
        public:
            explicit InfoBarBase(Session* session_) : session(session_) {}

            Element Render() override {
                bool locked = session->keyboardState == KeyboardState::LockedKeyboardState;

                return hbox({
                    text("Keyboard locked: "),
                    text((locked ? "🟥" : "🟩"))
                }) | align_right | xflex_grow;
            }

        protected:
            Session *session;
        };
    };

    Component InfoBar(Session* session);
};
