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


class SequenceBuilder {
private:
    std::vector<Step *> steps;

public:
    SequenceBuilder() = default;

    SequenceBuilder& one(char c, bool required = true);

    SequenceBuilder& one(Sequence& sequence, bool required = true);

    SequenceBuilder& anyOfEither(std::vector<char> && chars, bool required = true);

    SequenceBuilder& anyOfEither(std::vector<Sequence *> && sequences, bool required = true);

    SequenceBuilder& manyOfEither(std::vector<Sequence *> && sequences, bool required = true);

    SequenceBuilder& manyOfEither(std::vector<char> && chars, bool requires_at_least_one = true);

    SequenceBuilder& many(char c, bool requires_at_least_one = true);

    SequenceBuilder& many(Sequence& sequence, bool requires_at_least_one = true);

    Sequence build();
};