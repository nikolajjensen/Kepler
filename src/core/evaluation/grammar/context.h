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
    class context {
    public:
        using rule_type = bool (*)(const std::vector<Atom>& input, context<Atom>& context, int& head);

        ~context() = default;

        virtual void backtrack(int amount) = 0;
        virtual void apply_semantic_action(rule_type rule, const std::vector<Atom>& input, const int& start, const int& end) = 0;

        template <typename CompType>
        bool comparator(const Atom& atom, const CompType& comp);

        bool match(rule_type rule, const std::vector<Atom> &input, int &head);

        template <typename CompType>
        bool match(const CompType &atom, const std::vector<Atom>& input, int& head);

        template <typename CompType>
        bool match(std::vector<CompType> &&atoms, const std::vector<Atom> &input, int &head);

        template <typename CompType>
        bool check(const CompType& atom, const std::vector<Atom>& input, int& head);

        template <typename CompType>
        int peek(const CompType& atom, const std::vector<Atom>& input, int& head);

    };
};

#include "context.tpp"
#include "core/context.h"

namespace kepler::grammar {
    class generic_char_context : public context<Char> {
        virtual void backtrack(int amount) override;
        virtual void apply_semantic_action(rule_type rule, const std::vector<Char>& input, const int& start, const int& end) override;
    };

    class lexer_context : public generic_char_context {
    public:
        std::vector<Char> content;
        std::vector<Token> output;

        void backtrack(int amount) override;

        void append(const std::vector<Char>& input, const int& start, const int& end);
        void clear();
        void create(TokenClass cl);

        void apply_semantic_action(rule_type rule, const std::vector<Char>& input, const int& start, const int& end) override;
    };

    class parser_context : public context<Token> {
    public:
        std::vector<Token> output;

        void backtrack(int amount) override;

        void accept(const std::vector<Token>& input, const int& head);
        void set_class(TokenClass token_class);

        void apply_semantic_action(rule_type rule, const std::vector<Token>& input, const int& head, const int& end) override;
    };

    class function_context : public generic_char_context {
    public:
        Token identifier;
        std::vector<Char> request;

        void backtrack(int amount) override;

        void apply_semantic_action(rule_type rule, const std::vector<Char>& input, const int& start, const int& end) override;
    };

    class function_editing_context : public generic_char_context {
    public:
        explicit function_editing_context(Token& identifier, Context& context);

        Token& identifier;
        Context& context;

        void backtrack(int amount) override;

        void apply_semantic_action(rule_type rule, const std::vector<Char>& input, const int& start, const int& end) override;
    };
};
