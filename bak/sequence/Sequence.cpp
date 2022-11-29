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
#include <iostream>
#include "Step.h"
#include "../UnicodeCharacter.h"

template <typename T>
Sequence<T>::Sequence(std::vector<Step<T> *> & _steps, std::function<void(UnicodeCharacter&)> on_match_) : steps(_steps), on_match(on_match_) {}

template <typename T>
Sequence<T>::~Sequence() {
    for(auto& step : steps) {
        delete step;
    }
    steps.clear();
}

template <typename T>
unsigned int Sequence<T>::match(typename std::vector<T>::iterator& input_cursor, typename std::vector<T>::iterator& input_end) {
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
            tmp_count = (*steps_it)->match(input_cursor, input_end, on_match);
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
        //on_match();
    }

    return counter;
}

/*
template <typename T>
bool Sequence<T>::match(typename std::vector<T> &input) {
    auto begin = input.begin();
    auto end = input.end();
    return match(begin, end) && begin == end;
}
*/

template class Sequence<UnicodeCharacter>;