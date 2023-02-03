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

#include "environment.h"
#include "core/exceptions/error.h"
#include "core/lexer/lexer.h"
#include "core/parser/parser.h"
#include "../interpreter/interpreter.h"

kepler::Environment::Environment() {

}

kepler::Session* kepler::Environment::spawn_session() {
    sessions.emplace_back(Workspace(clearWorkspaceIdentifier),
                          "new_session",
                          initialComparisonTolerance,
                          initialRandomLink,
                          initialPrintPrecision,
                          initialIndexOrigin,
                          initialLatentExpression);

    return &sessions[0];
}