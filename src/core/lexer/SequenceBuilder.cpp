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

#include "SequenceBuilder.h"

#include <vector>
#include "Step.h"
#include "Sequence.h"

SequenceBuilder& SequenceBuilder::one(char c, bool required) {
    steps.emplace_back(new CharStep({c}, required, false));
    return *this;
}

SequenceBuilder& SequenceBuilder::one(Sequence& sequence, bool required) {
    steps.emplace_back(new SequenceStep({&sequence}, required, false));
    return *this;
}

SequenceBuilder& SequenceBuilder::anyOfEither(std::vector<char> && chars, bool required) {
    steps.emplace_back(new CharStep(std::move(chars), required, false));
    return *this;
}

SequenceBuilder& SequenceBuilder::anyOfEither(std::vector<Sequence *> && sequences, bool required) {
    steps.emplace_back(new SequenceStep(std::move(sequences), required, false));
    return *this;
}

SequenceBuilder& SequenceBuilder::manyOfEither(std::vector<Sequence *> && sequences, bool required) {
    steps.emplace_back(new SequenceStep(std::move(sequences), required, true));
    return *this;
}

SequenceBuilder& SequenceBuilder::manyOfEither(std::vector<char> && chars, bool requires_at_least_one) {
    steps.emplace_back(new CharStep(std::move(chars), requires_at_least_one, true));
    return *this;
}

SequenceBuilder& SequenceBuilder::many(char c, bool requires_at_least_one) {
    steps.emplace_back(new CharStep({c}, requires_at_least_one, true));
    return *this;
}

SequenceBuilder& SequenceBuilder::many(Sequence& sequence, bool requires_at_least_one) {
    steps.emplace_back(new SequenceStep({&sequence}, requires_at_least_one, true));
    return *this;
}

Sequence SequenceBuilder::build() {
    return Sequence(steps);
}