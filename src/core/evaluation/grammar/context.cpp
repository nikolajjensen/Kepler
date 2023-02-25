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

#include "context.h"
#include "rules.h"

namespace kepler::grammar {

    void lexer_context::backtrack(int amount) {
        content.resize(content.size() - amount);
    }

    void lexer_context::append(const std::vector<Char>& input, const int& start, const int& end) {
        std::copy(input.begin() + start, input.begin() + end, std::back_inserter(content));
    }

    void lexer_context::clear() {
        content.clear();
    }

    void lexer_context::create(TokenClass cl) {
        if(content.size() == 1) {
            output.emplace_back(cl, content.front());
        } else {
            output.emplace_back(cl, content);
        }
        content.clear();
    }

    void lexer_context::apply_semantic_action(rule_type<Char, lexer_context> rule, const std::vector<Char> &input, const int &start, const int &end) {
        if(rule == rules::diamond
           || rule == rules::quote_quad
           || rule == rules::quad
           || rule == rules::lamp
           || rule == rules::del_tilde
           || rule == rules::del
           || rule == rules::blank
           || rule == rules::overbar
           || rule == rules::underbar
           || rule == rules::dot
           || rule == rules::complex_marker
           || rule == rules::exponent_marker
           || rule == rules::quote
           || rule == rules::ideogram
           || rule == rules::digit
           || rule == rules::letter) {

            append(input, start, end);
        } else if(rule == rules::comment
                  || rule == rules::space) {
            clear();
        } else if(rule == rules::primitive) {
            create(PrimitiveToken);
        } else if(rule == rules::character_literal) {
            create(CharacterLiteralToken);
        } else if(rule == rules::numeric_literal) {
            create(NumericLiteralToken);
        } else if(rule == rules::distinguished_identifier) {
            create(DistinguishedIdentifierToken);
        } else if(rule == rules::literal_identifier) {
            create(SimpleIdentifierToken);
        } else if(rule == rules::statement_separator) {
            create(StatementSeparatorToken);
        }
    }

    bool lexer_context::match(rule_type<Char, lexer_context> rule, const std::vector<Char> &input, int &head) {
        int prev_head = head;
        if(head < input.size() && rule(input, *this, head)) {
            apply_semantic_action(rule, input, prev_head, head);
            return true;
        }

        return false;
    }

    bool lexer_context::match(const Char &atom, const std::vector<Char> &input, int &head) {
        if(check(atom, input, head)) {
            head++;
            return true;
        } else {
            return false;
        }
    }

    bool lexer_context::match(std::vector<Char> &&atoms, const std::vector<Char> &input, int &head) {
        return std::any_of(
                atoms.begin(),
                atoms.end(),
                [&](const Char& atom) { return match(atom, input, head); });
    }

    bool lexer_context::check(const Char &atom, const std::vector<Char> &input, int &head) {
        return head < input.size() && input[head] == atom;
    }

    int lexer_context::peek(const Char &atom, const std::vector<Char> &input, int &head) {
        auto begin = input.begin() + head;
        auto end = input.end();
        auto it = std::find(begin, end, atom);
        if(it != end) {
            return std::distance(input.begin(), it);
        }
        return -1;
    }




    void parser_context::backtrack(int amount) {
        output.resize(output.size() - amount);
    }

    void parser_context::accept(const std::vector<Token> &input, const int &head) {
        output.emplace_back(input[head]);
    }

    void parser_context::set_class(TokenClass token_class) {
        if(output.empty()) return;
        output.back().token_class = token_class;
    }

    void parser_context::apply_semantic_action(rule_type<Token, parser_context> rule, const std::vector<Token> &input, const int &head) {
        if(rule == rules::token_operand
           || rule == rules::token_variable
           || rule == rules::token_operation
           || rule == rules::token_dot
           || rule == rules::token_function
           || rule == rules::defined_dyadic_operator
           || rule == rules::defined_monadic_operator)
        {
            accept(input, head);
        } else if(rule == rules::primitive_function) {
            accept(input, head);
            set_class(PrimitiveFunctionToken);
        } else if(rule == rules::dyadic_operator) {
            set_class(DyadicOperatorToken);
        } else if(rule == rules::monadic_operator) {
            set_class(MonadicOperatorToken);
        } else if(rule == rules::axis_monadic_operator) {
            accept(input, head);
            set_class(AxisMonadicOperatorToken);
        } else if(rule == rules::primitive_monadic_operator) {
            set_class(PrimitiveMonadicOperatorToken);
        } else if(rule == rules::primitive_dyadic_operator) {
            set_class(PrimitiveDyadicOperatorToken);
        } else if(rule == rules::diaeresis_jot) {
            accept(input, head);
        } else if(rule == rules::diaeresis_tilde) {
            accept(input, head);
        } else if(rule == rules::left_parenthesis) {
            accept(input, head);
            set_class(LeftParenthesisToken);
        } else if(rule == rules::right_parenthesis) {
            accept(input, head);
            set_class(RightParenthesisToken);
        } else if(rule == rules::left_axis_bracket) {
            accept(input, head);
            set_class(LeftAxisBracketToken);
        } else if(rule == rules::right_axis_bracket) {
            accept(input, head);
            set_class(RightAxisBracketToken);
        } else if(rule == rules::branch_arrow) {
            accept(input, head);
            set_class(BranchArrowToken);
        } else if(rule == rules::assignment_arrow) {
            accept(input, head);
            set_class(AssignmentArrowToken);
        } else if(rule == rules::left_index_bracket) {
            accept(input, head);
            set_class(LeftIndexBracketToken);
        } else if(rule == rules::right_index_bracket) {
            accept(input, head);
            set_class(RightIndexBracketToken);
        } else if(rule == rules::index_separator) {
            accept(input, head);
            set_class(IndexSeparatorToken);
        } else if(rule == rules::small_circle) {
            accept(input, head);
            set_class(SmallCircleToken);
        }
    }

    bool parser_context::match(rule_type<Token, parser_context> rule, const std::vector<Token> &input, int &head) {
        int prev_head = head;
        if(head < input.size() && rule(input, *this, head)) {
            apply_semantic_action(rule, input, prev_head);
            return true;
        }

        return false;
    }

    bool parser_context::match(const Token::content_type &content, const std::vector<Token> &input, int &head) {
        if(check(PrimitiveToken, input, head) && check(content, input, head)) {
            head++;
            return true;
        } else {
            return false;
        }
    }

    bool parser_context::match(std::vector<Token::content_type> &&contents, const std::vector<Token> &input, int &head) {
        return std::any_of(
                contents.begin(),
                contents.end(),
                [&](const Token::content_type& content) { return match(content, input, head); });
    }

    bool parser_context::match(const TokenClass &token_class, const std::vector<Token> &input, int &head) {
        if(check(token_class, input, head)) {
            head++;
            return true;
        } else {
            return false;
        }
    }

    bool parser_context::check(TokenClass token_class, const std::vector<Token> &input, int &head) {
        return head < input.size() && input[head].token_class == token_class;
    }

    bool parser_context::check(const Token::content_type &content, const std::vector<Token> &input, int &head) {
        return head < input.size() && (!input[head].content || input[head].content.get() == content);
    }

    int parser_context::peek(const Token::content_type &content, const std::vector<Token> &input, int &head) {
        auto begin = input.begin() + head;
        auto end = input.end();
        auto it = std::find_if(begin, end, [&](const Token& token) {
            return token.content && token.content.get() == content;
        });
        if(it != end) {
            return std::distance(input.begin(), it);
        }
        return -1;
    }
};