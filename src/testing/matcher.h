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
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_templated.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include "core/token_type.h"
#include "core/token.h"
#include "core/error.h"
#include "core/literals.h"
#include "core/evaluation/ast.h"
#include <iomanip>

/**
 * The Prints struct matches a string to a specific string.
 */
struct Prints : Catch::Matchers::MatcherGenericBase {

    /**
     * @brief Construct a new Prints object.
     *
     * @param output_ The string to match.
     */
    explicit Prints(std::string const& output_) : output(output_) {}

    /**
     * @brief Match a string to a specific string.
     *
     * @param result The string to match.
     * @return true If the strings are equal.
     * @return false If the strings are not equal.
     */
    bool match(std::string const & result) const {
        return result == output;
    }

    /**
     * Produces a string describing why the matcher failed.
     * @return A string describing why the matcher failed.
     */
    std::string describe() const override {
        return "should print " + output;
    }

private:
    std::string const& output;
};

/**
 * The Outputs struct matches a list of tokens to a specific list of tokens.
 */
struct Outputs : Catch::Matchers::MatcherGenericBase {

    /**
     * @brief Construct a new Outputs object.
     *
     * @param output_ The list of tokens to match.
     */
    Outputs(const std::initializer_list<kepler::Token>& output_) : output(output_) {}

    /**
     * @brief Match a list of tokens to a specific list of tokens.
     *
     * @param result The list of tokens to match.
     * @return true If the lists are equal.
     * @return false If the lists are not equal.
     */
    bool match(kepler::List<kepler::Token> const & result) const {
        return kepler::List<kepler::Token>{result.begin() + 1, result.end()} == output;
    }

    /**
     * Produces a string describing why the matcher failed.
     * @return A string describing why the matcher failed.
     */
    std::string describe() const override {
        return "should output \n" + Catch::StringMaker<std::vector<kepler::Token, std::allocator<kepler::Token>>, void>::convert(output);
    }

private:
    kepler::List<kepler::Token> output;
};


/**
 * The Throws struct matches strings or errors to a specific error type.
 */
struct Throws : Catch::Matchers::MatcherGenericBase {

    /**
     * @brief Construct a new Throws object.
     *
     * @param error_type_ The error type to match.
     */
    explicit Throws(kepler::ErrorType const& error_type_) : error_type(error_type_) {}

    /**
     * @brief Match a string to a specific error type.
     * The error_type is converted to a string and then checked if it is contained in the string.
     *
     * @param err The string to match.
     * @return true If the string contains the error type.
     * @return false If the string does not contain the error type.
     */
    bool match(std::string const & err) const{
        return err.find(kepler::to_string(error_type)) != std::string::npos;
    }

    /**
     * @brief Match an error to check if it is of the specific type.
     *
     * @param err The error to match.
     * @return true If the error type matches.
     * @return false If the error type does not match.
     */
    bool match(kepler::Error const & err) const{
        return err.error_type == error_type;
    }

    /**
     * Produces a string describing why the matcher failed.
     * @return A string describing why the matcher failed.
     */
    std::string describe() const override {
        return "should be a " + to_string(error_type);
    }

private:
    kepler::ErrorType const& error_type;
};