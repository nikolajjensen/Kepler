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

#include "AtomicStep.h"
#include "../UnicodeCharacter.h"
#include <iostream>

template <typename T>
AtomicStep<T>::AtomicStep(std::vector<T> && _characters, bool required, bool repeat) : Step<T>(required, repeat), characters(_characters) {}

template <typename T>
AtomicStep<T>::~AtomicStep() = default;

template <typename T>
unsigned int AtomicStep<T>::match(typename std::vector<T>::iterator& input_cursor, typename std::vector<T>::iterator& input_end, std::function<void(UnicodeCharacter&)> & on_match) {
    unsigned int match_counter = 0;
    bool success;
    bool round_success;

    do {
        T c = *input_cursor;
        auto char_iterator = characters.begin();

        round_success = false;

        while(!round_success && char_iterator != characters.end()) {
            if(c == *char_iterator) {
                match_counter++;
                on_match(c);
                round_success = true;
            } else {
                char_iterator++;
            }
        }

        if(round_success) {
            input_cursor++;
        }

        success = success || round_success;
    } while (Step<T>::repeat && round_success && input_cursor != input_end);

    if(!success) {
        input_cursor -= match_counter;
        match_counter = 0;
    }

    return match_counter;
}

template class AtomicStep<UnicodeCharacter>;