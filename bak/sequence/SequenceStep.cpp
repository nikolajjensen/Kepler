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

#include "SequenceStep.h"
#include <iostream>
#include "../UnicodeCharacter.h"

template <typename T>
SequenceStep<T>::SequenceStep(std::vector<Sequence<T> *> && sequences_, bool required, bool repeat) : Step<T>(required, repeat), sequences(sequences_) {}

template <typename T>
SequenceStep<T>::~SequenceStep() = default;

template <typename T>
unsigned int SequenceStep<T>::match(typename std::vector<T>::iterator& input_cursor, typename std::vector<T>::iterator& input_end, std::function<void(
        UnicodeCharacter&)>& on_match) {
    unsigned int match_counter = 0;
    bool success = false;
    bool round_success;

    do {
        auto sequence_iterator = sequences.begin();

        round_success = false;

        while(!round_success && sequence_iterator != sequences.end()) {
            unsigned int tmp_count = (*sequence_iterator)->match(input_cursor, input_end);
            match_counter += tmp_count;

            if(tmp_count) {
                round_success = true;
            }

            sequence_iterator++;
        }

        success = success || round_success;

    } while (Step<T>::repeat && round_success && input_cursor != input_end);

    if(!success) {
        input_cursor -= match_counter;
        match_counter = 0;
    }

    return match_counter;
}

template class SequenceStep<UnicodeCharacter>;