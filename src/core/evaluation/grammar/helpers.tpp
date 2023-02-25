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
#include "helpers.h"
#include "core/constants/literals.h"
#include <algorithm>

namespace kepler::grammar::rules {
    template <typename Atom>
    bool helpers::match(rule_type<Atom> rule, const std::vector<Atom> &input, context<Atom>& context, int &head, int stop) {
        int prev_head = head;
        if(rule(input, context, head)) {
            context.apply_for(rule, input, prev_head, head);
            return true;
        }

        return false;
    }

    template <typename Atom>
    bool helpers::match(const Atom& atom, const std::vector<Atom> &input, context<Atom>& context, int &head, int stop) {
        if(helpers::check(atom, input, head, stop)) {
            head++;
            return true;
        } else {
            return false;
        }
    }

    template<typename Atom>
    bool helpers::match(std::vector<Atom>&& atoms, const std::vector<Atom> &input, context<Atom>& context, int &head, int stop) {
        return std::any_of(
                atoms.begin(),
                atoms.end(),
                [&](const Atom& atom) { return match(atom, input, context, head, stop); });
    }

    template <typename Atom>
    bool helpers::check(const Atom &atom, const std::vector<Atom> &input, int &head, int stop) {
        if(stop != -1 && head > stop) {
            return false;
        }
        return head < input.size() && input[head] == atom;
    }

    template<typename Atom>
    int helpers::peek(const Atom &atom, const std::vector<Atom> &input, int &head) {
        auto begin = input.begin() + head;
        auto end = input.end();
        auto it = std::find(begin, end, atom);
        if(it != end) {
            return std::distance(input.begin(), it);
        }
        return -1;
    }
};