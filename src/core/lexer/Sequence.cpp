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

#include "Sequence.h"
#include <vector>
#include "Step.h"

Sequence::Sequence(std::vector<Step *> & _steps) : steps(_steps) {}

Sequence::~Sequence() {
    for(auto& step : steps) {
        delete step;
    }
    steps.clear();
}

unsigned int Sequence::match(std::vector<char>::iterator& input_cursor, std::vector<char>::iterator& input_end) {
    auto steps_it = steps.begin();

    unsigned int counter = 0;
    unsigned int tmp_count;
    bool failed = false;

    while(!failed && steps_it < steps.end()) {
        if(input_cursor >= input_end) {
            // We've run out of input, but have more steps to take.
            // Matching should fail if any subsequent step is required.
            failed = (*steps_it)->required;
        } else {
            tmp_count = (*steps_it)->match(input_cursor, input_end);
            counter += tmp_count;
            if(!tmp_count && (*steps_it)->required) {
                // If the step was required, and we didn't match it, we fail.
                failed = true;
            }
        }

        steps_it++;
    }

    if(failed) {
        input_cursor -= counter;
        counter = 0;
    } else {
        //perform_action();
    }

    return counter;
}

bool Sequence::match(std::string &input) {
    auto begin = input.begin();
    auto end = input.end();
    return match(begin, end) && begin == end;
}