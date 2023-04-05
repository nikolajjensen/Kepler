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

#include "file_reader.h"
#include "core/error.h"
#include <fstream>
#include <uni_algo/conv.h>

std::vector<std::vector<kepler::Char>> kepler::read_file(const std::string& path) {
    if(!path.ends_with(".kpl")) {
        throw kepler::Error(FileError, "Only .kpl files are accepted.");
    }

    std::ifstream f(path);

    if(!f.is_open()) {
        throw kepler::Error(FileError, "Could not open the file.");
    }

    std::stringstream ss;
    std::vector<std::vector<kepler::Char>> result;
    for(std::string line; getline(f, line); ) {
        String str = uni::utf8to32u(line);
        result.emplace_back(str.begin(), str.end());
    }
    f.close();
    return result;
}

std::vector<kepler::Char> kepler::concat_lines(const std::vector<std::vector<kepler::Char>>& lines) {
    std::vector<kepler::Char> result;
    for(auto& line : lines) {
        std::copy(line.begin(), line.end(), std::back_inserter(result));
        result.emplace_back(U'\n');
    }
    if(!result.empty()) {
        result.pop_back();
    }
    return result;
}