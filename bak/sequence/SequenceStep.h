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
#include "Step.h"
#include "Sequence.h"
#include "../UnicodeCharacter.h"

template <typename T>
class SequenceStep : public Step<T> {
private:
    std::vector<Sequence<T> *> sequences;

public:
    explicit SequenceStep(std::vector<Sequence<T> *> && sequences_, bool required = true, bool repeat = false);
    ~SequenceStep() override;

    unsigned int match(typename std::vector<T>::iterator& input_cursor, typename std::vector<T>::iterator& input_end, std::function<void(
            UnicodeCharacter&)> &) override;
};