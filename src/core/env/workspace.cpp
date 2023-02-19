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

#include "workspace.h"

#include <utility>

kepler::Workspace::Workspace(
        StringUTF8 workspace_name_)
        : workspace_name(std::move(workspace_name_)),
          symbol_table(),
          state_indicator(),
          existential_property(WorkspacePresence::AbsentWorkspace) {}

kepler::Context& kepler::Workspace::add_context(kepler::Context &&context) {
    return state_indicator.emplace_back(std::move(context));
}

void kepler::Workspace::pop_context() {
    state_indicator.erase(state_indicator.begin());
}