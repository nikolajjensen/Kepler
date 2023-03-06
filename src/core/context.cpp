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

#include <utility>
#include "datatypes.h"

kepler::Context::Context(std::u32string&& input)
        : stack(),
          current_line({input.begin(), input.end()}),
          current_statement() {}

          /*
kepler::Context::Context(Mode mode_, List<Char> line_)
        : mode(mode_),
          stack(),
          current_line(std::move(line_)),
          current_statement(),
          current_function(boost::none),
          current_line_number(1) {}

kepler::Context::Context(Mode mode_, List<Char> line_, DefinedFunction function_, int line_number_)
        : mode(mode_),
          stack(),
          current_line(std::move(line_)),
          current_statement(),
          current_function(std::move(function_)),
          current_line_number(line_number_) {}*/