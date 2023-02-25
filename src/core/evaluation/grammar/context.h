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
#include <map>
#include "core/token.h"
#include "core/token_class.h"

namespace kepler::grammar {

    template <typename Atom>
    class context;

    template <typename Atom>
    using rule_type = bool (*)(const std::vector<Atom>& input, context<Atom>& context, int& head);


    template <typename Atom>
    class context {
    public:
        virtual ~context() = default;
        virtual void apply_for(rule_type<Char> rule, const std::vector<Char>& input, const int& start, const int& end) = 0;
        virtual void backtrack(int amount) = 0;
    };

    class lexer_context : public context<Char> {
    public:
        std::vector<Char> content;
        std::vector<Token> output;

        void append(const std::vector<Char>& input, const int& start, const int& end) {
            std::copy(input.begin() + start, input.begin() + end, std::back_inserter(content));
        }

        void clear() {
            content.clear();
        }

        void create(TokenClass cl) {
            output.emplace_back(cl, content);
            content.clear();
        }

        void apply_for(rule_type<Char> rule, const std::vector<Char>& input, const int& start, const int& end) override;

        virtual void backtrack(int amount) override {
            content.resize(content.size() - amount);
        }
    };
};
