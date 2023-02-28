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

namespace kepler::grammar {
    template <typename Atom>
    bool context<Atom>::match(rule_type rule, const std::vector<Atom> &input, int &head) {
        int prev_head = head;
        if(head < input.size() && rule(input, *this, head)) {
            apply_semantic_action(rule, input, prev_head, head);
            return true;
        }

        return false;
    }

    template <typename Atom>
    template <typename CompType>
    bool context<Atom>::match(const CompType &comp, const std::vector<Atom> &input, int &head) {
        if(check(comp, input, head)) {
            head++;
            return true;
        } else {
            return false;
        }
    }

    template <typename Atom>
    template <typename CompType>
    bool context<Atom>::match(std::vector<CompType> &&atoms, const std::vector<Atom> &input, int &head) {
        return std::any_of(
                atoms.begin(),
                atoms.end(),
                [&](const Char& atom) { return match(atom, input, head); });
    }

    template <typename Atom>
    template <typename CompType>
    bool context<Atom>::check(const CompType &comp, const std::vector<Atom> &input, int &head) {
        return head < input.size() && comparator(input[head], comp);
    }

    template <typename Atom>
    template <typename CompType>
    int context<Atom>::peek(const CompType &atom, const std::vector<Atom> &input, int &head) {
        auto begin = input.begin() + head;
        auto end = input.end();
        auto it = std::find_if(begin, end, [&](const Atom& element) {
            return comparator(element, atom);
        });
        if(it != end) {
            return std::distance(input.begin(), it);
        }
        return -1;
    }
};