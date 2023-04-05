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
#include "interface/conversion.h"
#include "core/helpers.h"

namespace kepler {

    /**
     * The Parser which checks the input list of tokens for syntax errors and then builds an AST.
     */
    class Parser {
    private:
        SymbolTable* symbol_table;

        // Points to any token which the cursor is currently at.
        std::vector<Token>::const_iterator cursor;

        // Points the statement separator of the statement currently being parsed.
        std::vector<Token>::const_iterator flag;

        // Points to the END token before actual input.
        std::vector<Token>::const_iterator before_input;

        // Points to the END token after actual input.
        std::vector<Token>::const_iterator after_input;

        std::vector<Token> _tmp;

        /**
         * Advances the cursor one step.
         *
         * Note that 'advancing' means moving the cursor 'left' (not right).
         */
        void advance();

        /**
         * Returns a reference to the token currently pointed at by the cursor.
         * @return The current token pointed to.
         */
        [[nodiscard]] const Token& current() const;

        /**
         * Returns a reference to the token offset from
         * the current position by 'amount' steps.
         *
         * @param amount Number of steps to offset.
         * @return A reference to the token at the resulting position.
         */
        [[nodiscard]] const Token& peek(int amount = 1) const;

        /**
         * Returns the type of the next token which is not a parenthesis.
         */
        [[nodiscard]] TokenType peek_beyond_parenthesis() const;

        /**
         * Returns true if the cursor is at the end of the input.
         */
        [[nodiscard]] bool at_end() const;

        /**
         * Returns the position of the token pointed to by the iterator given.
         */
        [[nodiscard]] long position(const std::vector<Token>::const_iterator& it) const;

        /**
         * Returns the position of the token currently pointed at by 'current()'.
         */
        [[nodiscard]] long position() const;

        /**
         * Checks if the given token identifies a function.
         *
         * @param token The token to check.
         * @return True if the token identifies a function in the symbol table.
         */
        [[nodiscard]] bool identifies_function(const Token& token) const;

        /**
         * Checks if the current token is of the given type.
         *
         * If it is, the cursor is advanced. If it is not, an Error is thrown.
         *
         * @param type The type to check for.
         * @return True if the current token is of the given type.
         */
        void eat(TokenType type);

        /**
         * Finds the next statement separator in the input, and returns an iterator to it.
         *
         * If none is found, the end iterator is returned.
         *
         * @param current Iterator to the current statement separator.
         * @return An iterator to the next statement separator.
         */
        [[nodiscard]] std::vector<Token>::const_iterator next_separator(std::vector<Token>::const_iterator current) const;

        /**
         * Finds the matching brace for the brace at the given position.
         *
         * If none is found, the begin iterator is returned.
         *
         * @param begin The position of the brace.
         * @return The position of the matching brace.
         */
        [[nodiscard]] std::vector<Token>::const_iterator matching_brace(std::vector<Token>::const_iterator begin) const;

        /**
         * Asserts that every Token of the 'left' type has a matching Token of the 'right' type.
         *
         * A SyntaxError is thrown if this is not the case. The error will have the closest position to
         * where the error occurred, and right_char will be describing the expected Token.
         * @param left The left Token type.
         * @param right The right Token type.
         * @param right_char The character describing the right Token type.
         */
        void assert_matching(const TokenType& left, const TokenType& right, const Char& right_char) const;

        /**
         * Parses user defined functions.
         */
        ASTNode<Operation_ptr>* parse_dfn();

        /**
         * Parses the 'program' rule from the grammar of Kepler.
         */
        Statements* parse_program();

        /**
         * Parses the 'statement_list' rule from the grammar of Kepler.
         */
        Statements* parse_statement_list();

        /**
         * Parses the 'statement' rule from the grammar of Kepler.
         */
        ASTNode<Array>* parse_statement();

        /**
         * Parses the 'vector' rule from the grammar of Kepler.
         */
        ASTNode<Array>* parse_vector();

        /**
         * Parses the 'scalar' rule from the grammar of Kepler.
         */
        ASTNode<Array>* parse_scalar();

        /**
         * Parses the 'function' rule from the grammar of Kepler.
         */
        ASTNode<Operation_ptr>* parse_function();

        /**
         * Parses the 'mop' rule from the grammar of Kepler.
         */
        ASTNode<Operation_ptr>* parse_mop();

        /**
         * Parses the 'f' rule from the grammar of Kepler.
         */
        ASTNode<Operation_ptr>* parse_f();

    public:
        /**
         * Creates a new Parser.
         */
        explicit Parser();

        /**
         * Deletes the previous symbol table used by the Parser, and uses the new one.
         * @param new_table The new table to use.
         */
        void use_table(SymbolTable* new_table);

        /**
         * Parses the input list of tokens and returns an AST.
         * @param input_ The list of tokens to parse.
         * @return The AST.
         */
        Statements* parse(const std::vector<Token>& input_);

        /**
         * Parses the input list of tokens and returns an AST.
         * @param parent_table The parent table to use.
         * @param begin The beginning of the list of tokens to parse.
         * @param end The end of the list of tokens to parse.
         * @return The AST.
         */
        Statements* parse(SymbolTable* parent_table, std::vector<Token>::const_iterator begin, std::vector<Token>::const_iterator end);
    };
};