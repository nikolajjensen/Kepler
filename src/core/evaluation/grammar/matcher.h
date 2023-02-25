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
#include <memory>
#include "context.h"

namespace kepler::grammar {
    template <typename Atom, typename Context>
    class Matcher {
    public:
        explicit Matcher(const std::vector<Atom>& input);

        bool match(rule_type<Atom, Context> base_rule);

        const std::vector<Atom>& input;
        Context context;
    };

};

// Yes, .tpp include goes at the bottom.
#include "matcher.tpp"