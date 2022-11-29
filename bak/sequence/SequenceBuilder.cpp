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
#include "AtomicStep.h"
#include "SequenceStep.h"
#include "Sequence.h"
#include "../UnicodeCharacter.h"

template <typename T>
SequenceBuilder<T>& SequenceBuilder<T>::one(T element, bool required) {
    steps.emplace_back(new AtomicStep<T>({element}, required, false));
    return *this;
}

template <typename T>
SequenceBuilder<T>& SequenceBuilder<T>::one(Sequence<T>& sequence, bool required) {
    steps.emplace_back(new SequenceStep<T>({&sequence}, required, false));
    return *this;
}

template <typename T>
SequenceBuilder<T>& SequenceBuilder<T>::anyOfEither(std::vector<T> && chars, bool required) {
    steps.emplace_back(new AtomicStep<T>(std::move(chars), required, false));
    return *this;
}

template <typename T>
SequenceBuilder<T>& SequenceBuilder<T>::anyOfEither(std::vector<Sequence<T> *> && sequences, bool required) {
    steps.emplace_back(new SequenceStep<T>(std::move(sequences), required, false));
    return *this;
}

template <typename T>
SequenceBuilder<T>& SequenceBuilder<T>::manyOfEither(std::vector<Sequence<T> *> && sequences, bool required) {
    steps.emplace_back(new SequenceStep<T>(std::move(sequences), required, true));
    return *this;
}

template <typename T>
SequenceBuilder<T>& SequenceBuilder<T>::manyOfEither(std::vector<T> && chars, bool requires_at_least_one) {
    steps.emplace_back(new AtomicStep<T>(std::move(chars), requires_at_least_one, true));
    return *this;
}

template <typename T>
SequenceBuilder<T>& SequenceBuilder<T>::many(T c, bool requires_at_least_one) {
    steps.emplace_back(new AtomicStep<T>({c}, requires_at_least_one, true));
    return *this;
}

template <typename T>
SequenceBuilder<T>& SequenceBuilder<T>::many(Sequence<T>& sequence, bool requires_at_least_one) {
    steps.emplace_back(new SequenceStep<T>({&sequence}, requires_at_least_one, true));
    return *this;
}

template <typename T>
Sequence<T> SequenceBuilder<T>::build(std::function<void(UnicodeCharacter&)> & on_match) {
    return Sequence(steps, on_match);
}

template <typename T>
Sequence<T> SequenceBuilder<T>::build(std::function<void(UnicodeCharacter&)> && on_match) {
    return Sequence(steps, on_match);
}

template class SequenceBuilder<UnicodeCharacter>;