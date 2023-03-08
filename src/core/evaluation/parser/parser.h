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
#include "core/token.h"
#include <vector>
#include "core/token_type.h"
#include "core/evaluation/ast.h"
#include "core/helpers/conversion.h"
#include "core/helpers/classifiers.h"

namespace kepler {
    /*
    class StatementList {
    private:
        // https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp
        struct StatementIterator {
            using iterator_category = std::forward_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = Token;
            using pointer           = Token*;  // or also value_type*
            using reference         = Token&;  // or also value_type&

            StatementIterator(pointer ptr) : m_ptr(ptr) {}

            reference operator*() const { return *m_ptr; }
            pointer operator->() const { return m_ptr; }

            // Prefix
            StatementIterator& operator++() { m_ptr++; return *this; }

            // Postfix
            StatementIterator operator++(int) { StatementIterator tmp = *this; ++(*this); return tmp; }


            friend bool operator==(const StatementIterator& a, const StatementIterator& b) { return a.m_ptr == b.m_ptr; }
            friend bool operator!=(const StatementIterator& a, const StatementIterator& b) { return a.m_ptr != b.m_ptr; }


        private:
            pointer m_ptr;
        };

        std::vector<Token>* list;

    public:
        StatementList(std::vector<Token>* list_) : list(list_) {}

        StatementIterator begin() { return StatementIterator(&(*list)[0]); }
        StatementIterator end() { return StatementIterator(&(*list)[list->size()]); }
    };
    */

    class Parser {
    private:
        // https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp
        struct StatementIterator {
            using iterator_category = std::forward_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = Token;
            using pointer           = ASTNode<Array>**;  // or also value_type*
            using reference         = ASTNode<Array>*&;  // or also value_type&

            StatementIterator(pointer ptr) : m_ptr(ptr) {}

            reference operator*() const { return *m_ptr; }
            pointer operator->() const { return m_ptr; }

            // Prefix
            StatementIterator& operator++() { m_ptr++; return *this; }

            // Postfix
            StatementIterator operator++(int) { StatementIterator tmp = *this; ++(*this); return tmp; }


            friend bool operator==(const StatementIterator& a, const StatementIterator& b) { return a.m_ptr == b.m_ptr; }
            friend bool operator!=(const StatementIterator& a, const StatementIterator& b) { return a.m_ptr != b.m_ptr; }


        private:
            pointer m_ptr;
        };

        SymbolTable* symbol_table;
        std::vector<Token>::const_iterator cursor;
        std::vector<Token>::const_iterator begin;
        std::vector<Token>::const_iterator end;

        void advance();
        const Token& current();
        bool at_end();
        void eat(TokenType type);
        TokenType peek();
        TokenType peek_beyond_parenthesis();

        bool identifies_function(Token token);
        std::vector<Token>::const_iterator next_separator(const std::vector<Token>::const_iterator& current);
        std::vector<Token>::const_iterator matching_brace(const std::vector<Token>::const_iterator& begin);

        ASTNode<Operation_ptr>* parse_dfn();
        ASTNode<Array>* parse_argument();

        Statements* parse_program();
        Statements* parse_statement_list();
        ASTNode<Array>* parse_statement();
        ASTNode<Array>* parse_vector();
        ASTNode<Array>* parse_scalar();
        ASTNode<Operation_ptr>* parse_function();
        ASTNode<Operation_ptr>* parse_mop();
        ASTNode<Operation_ptr>* parse_f();

    public:
        explicit Parser(SymbolTable& parent_table, const std::vector<Token>& input_);
        explicit Parser(SymbolTable& parent_table, std::vector<Token>::const_iterator begin, std::vector<Token>::const_iterator end);
        explicit Parser(const std::vector<Token>& input_);

        void use_table(SymbolTable* new_table);

        Statements* parse();
    };
};