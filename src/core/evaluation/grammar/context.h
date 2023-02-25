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

    template <typename Atom, typename Context>
    using rule_type = bool (*)(const std::vector<Atom>& input, Context& context, int& head);

    template <typename Atom>
    class context {
    public:
        ~context() = default;

        virtual void backtrack(int amount) = 0;
    };
};

namespace kepler::grammar {
    class lexer_context : public context<Char> {
    public:
        std::vector<Char> content;
        std::vector<Token> output;

        void backtrack(int amount) override;

        void append(const std::vector<Char>& input, const int& start, const int& end);
        void clear();
        void create(TokenClass cl);

        void apply_semantic_action(rule_type<Char, lexer_context> rule, const std::vector<Char>& input, const int& start, const int& end);

        bool match(rule_type<Char, lexer_context> rule, const std::vector<Char> &input, int &head);
        bool match(const Char &atom, const std::vector<Char> &input, int &head);
        bool match(std::vector<Char> &&atoms, const std::vector<Char> &input, int &head);

        static bool check(const Char& atom, const std::vector<Char>& input, int& head);
        static int peek(const Char& atom, const std::vector<Char>& input, int& head);
    };

    class parser_context : public context<Token> {
    public:
        std::vector<Token> output;

        void backtrack(int amount) override;

        void accept(const std::vector<Token>& input, const int& head);
        void set_class(TokenClass token_class);

        void apply_semantic_action(rule_type<Token, parser_context> rule, const std::vector<Token>& input, const int& head);

        bool match(rule_type<Token, parser_context> rule, const std::vector<Token> &input, int &head);
        bool match(const Token::content_type &content, const std::vector<Token> &input, int &head);
        bool match(std::vector<Token::content_type> &&content, const std::vector<Token> &input, int &head);
        bool match(const TokenClass &token_class, const std::vector<Token> &input, int &head);

        static bool check(TokenClass token_class, const std::vector<Token> &input, int& head);
        static bool check(const Token::content_type &content, const std::vector<Token> &input, int& head);
        static int peek(const Token::content_type& content, const std::vector<Token>& input, int& head);
    };
};
