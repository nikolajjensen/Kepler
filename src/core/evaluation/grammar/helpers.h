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
#include <vector>
#include "context.h"
#include "rules.h"

namespace kepler::grammar::rules::helpers {
    template <typename Atom>
    bool match(rule_type<Atom> rule, const std::vector<Atom>& input, context<Atom>& config, int& head, int stop = -1);

    template <typename Atom>
    bool match(const Atom& atom, const std::vector<Atom>& input, context<Atom>& config, int& head, int stop = -1);

    template <typename Atom>
    bool match(std::vector<Atom>&& atoms, const std::vector<Atom>& input, context<Atom>& config, int& head, int stop = -1);

    template <typename Atom>
    bool check(const Atom& atom, const std::vector<Atom>& input, int& head, int stop = -1);

    template <typename Atom>
    int peek(const Atom& atom, const std::vector<Atom>& input, int& head);
};

// Yes, the .tpp goes here.
#include "helpers.tpp"