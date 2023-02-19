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

#include "context.h"
#include "../datatypes.h"

kepler::Context::Context()
        : mode(Mode::ImmediateExecutionMode),
          stack(),
          current_line(),
          currentStatement(),
          currentFunction(boost::none),
          currentLineNumber(1) {}

kepler::Context::Context(Mode mode_, List<Char> line_)
        : mode(mode_),
          stack(),
          current_line(std::move(line_)),
          currentStatement(),
          currentFunction(boost::none),
          currentLineNumber(1) {}