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
        throw kepler::error(FileError, "Only .kpl files are accepted.");
    }

    std::ifstream f(path);

    if(!f.is_open()) {
        throw kepler::error(FileError, "Could not open the file.");
    }


    std::stringstream ss;

    std::vector<std::vector<kepler::Char>> result;

    for(std::string line; getline(f, line); ) {
        std::u32string str = uni::utf8to32u(line);
        result.emplace_back(str.begin(), str.end());
    }

    f.close();

    return result;
}

std::vector<kepler::Char> kepler::read_file_whole(const std::string &path) {
    if(!path.ends_with(".kpl")) {
        throw kepler::error(FileError, "Only .kpl files are accepted.");
    }

    std::ifstream f(path);

    if(!f.is_open()) {
        throw kepler::error(FileError, "Could not open the file.");
    }

    std::stringstream ss;
    ss << f.rdbuf();
    auto str = uni::utf8to32(ss.str());
    return {str.begin(), str.end()};
}