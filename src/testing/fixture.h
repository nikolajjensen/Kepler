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
#include "core/system.h"
#include "core/session.h"
#include <chrono>

class fixture {
protected:
    kepler::System system;
    kepler::Session* session;

public:
    fixture() : system(), session(system.spawn_session()) {}

protected:
    kepler::Token run(std::string&& input, bool timing = false) {
        auto start = std::chrono::high_resolution_clock::now();
        kepler::Token result = session->immediately_execute(std::move(input));
        auto stop = std::chrono::high_resolution_clock::now();
        if(timing) {
            auto us = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
            std::cout << "Took " << us << " µs (" << (us / 1000.0) << " ms)" << std::endl;
        }
        return result;
    }
};
