//
// Copyright 2023 Nikolaj Banke Jensen.
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

#include "context.h"

namespace kepler::grammar {
    template <typename Atom, typename Context>
    Matcher<Atom, Context>::Matcher(const std::vector<Atom> &input_) : input(input_), context() {}

    template <typename Atom, typename Context>
    bool Matcher<Atom, Context>::match(rule_type<Atom, Context> base_rule) {
        int head = 0;
        if(context.match(base_rule, input, head)) {
            return head == input.size();
        }

        return false;
    }
};