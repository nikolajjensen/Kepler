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

#include "Step.h"

CharStep::CharStep(std::vector<char> && _characters, bool required, bool repeat) : Step(required, repeat), characters(_characters) {}

unsigned int CharStep::match(std::vector<char>::iterator& input_cursor, std::vector<char>::iterator& input_end) {
    unsigned int match_counter = 0;
    bool success;
    bool round_success;

    do {
        char c = *input_cursor;
        auto char_iterator = characters.begin();

        round_success = false;

        while(!round_success && char_iterator != characters.end()) {
            if(c == *char_iterator) {
                match_counter++;
                round_success = true;
            } else {
                char_iterator++;
            }
        }

        if(round_success) {
            input_cursor++;
        }

        success = success || round_success;
    } while (repeat && round_success && input_cursor != input_end);

    if(!success) {
        input_cursor -= match_counter;
        match_counter = 0;
    }

    return match_counter;
}

SequenceStep::SequenceStep(std::vector<Sequence *> && sequences_, bool required, bool repeat) : Step(required, repeat), sequences(sequences_) {}

unsigned int SequenceStep::match(std::vector<char>::iterator& input_cursor, std::vector<char>::iterator& input_end) {
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

    } while (repeat && round_success && input_cursor != input_end);

    if(!success) {
        input_cursor -= match_counter;
        match_counter = 0;
    }

    return match_counter;
}