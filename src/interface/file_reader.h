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
#include <vector>
#include <string>
#include "core/datatypes.h"

namespace kepler {

    /**
     * Reads the given file and returns a vector of lines.
     * Each line is a vector of characters.
     *
     * @param path The path to the file to read.
     * @return The lines in the file.
     * @throws Error if the file could not be read.
     */
    std::vector<std::vector<kepler::Char>> read_file(const std::string& path);

    /**
     * Concatenates the given lines into a single vector of characters.
     * Separates the lines with a newline character.
     *
     * @param lines A vector of lines.
     * @return The concatenated lines.
     */
    std::vector<kepler::Char> concat_lines(const std::vector<std::vector<kepler::Char>>& lines);
};