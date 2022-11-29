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
class SequenceBuilder {
private:
    std::vector<Step<T> *> steps;

public:
    SequenceBuilder() = default;

    SequenceBuilder& one(T, bool required = true);

    SequenceBuilder& one(Sequence<T>&, bool required = true);

    SequenceBuilder& anyOfEither(std::vector<T> &&, bool required = true);

    SequenceBuilder& anyOfEither(std::vector<Sequence<T> *> &&, bool required = true);

    SequenceBuilder& manyOfEither(std::vector<Sequence<T> *> &&, bool required = true);

    SequenceBuilder& manyOfEither(std::vector<T> &&, bool requires_at_least_one = true);

    SequenceBuilder& many(T, bool requires_at_least_one = true);

    SequenceBuilder& many(Sequence<T>&, bool requires_at_least_one = true);

    Sequence<T> build(std::function<void(UnicodeCharacter&)> &);
    Sequence<T> build(std::function<void(UnicodeCharacter&)> &&);
};