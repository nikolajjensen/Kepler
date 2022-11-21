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

#pragma once
#include <vector>

#include "Sequence.h"

class Step {
public:
    bool required;
    bool repeat;

public:
    Step(bool required_, bool repeat_) : required(required_), repeat(repeat_) {}
    virtual ~Step() = default;

    virtual unsigned int match(std::vector<char>::iterator& input_cursor, std::vector<char>::iterator& input_end) = 0;
};

class CharStep : public Step {
private:
    std::vector<char> characters;

public:
    explicit CharStep(std::vector<char> && _characters, bool required = true, bool repeat = false);

    unsigned int match(std::vector<char>::iterator& input_cursor, std::vector<char>::iterator& input_end) override;
};

class SequenceStep : public Step {
private:
    std::vector<Sequence *> sequences;

public:
    explicit SequenceStep(std::vector<Sequence *> && sequences_, bool required = true, bool repeat = false);

    unsigned int match(std::vector<char>::iterator& input_cursor, std::vector<char>::iterator& input_end) override;
};