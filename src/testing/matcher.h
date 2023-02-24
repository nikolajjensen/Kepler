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
#include "core/token_class.h"
#include "core/token.h"
#include "core/helpers/printers.h"
#include "core/error.h"
#include "string_maker.h"
#include "core/constants/literals.h"
#include <iomanip>

struct Prints : Catch::Matchers::MatcherGenericBase {
    explicit Prints(std::string const& output_, kepler::Session* session_) : output(output_), session(session_) {}

    bool match(kepler::Token const & result) const {
        std::stringstream ss;
        kepler::Array& pp = session->get_system_parameter(kepler::constants::PP);
        kepler::helpers::TokenPrinter p(ss, pp.get_content<kepler::Number>(0).real());
        p(result);
        return ss.str() == output;
    }

    std::string describe() const override {
        return "should print " + output;
    }

private:
    std::string const& output;
    kepler::Session* session;
};

struct Outputs : Catch::Matchers::MatcherGenericBase {
    explicit Outputs(kepler::List<kepler::Token> const& output_) : output(output_) {}

    bool match(kepler::List<kepler::Token> const & result) const {
        return result == output;
    }

    std::string describe() const override {
        return "should output \n" + Catch::StringMaker<std::vector<kepler::Token, std::allocator<kepler::Token>>, void>::convert(output);
    }

private:
    kepler::List<kepler::Token> const& output;
};

struct Throws : Catch::Matchers::MatcherGenericBase {
    explicit Throws(kepler::ErrorType const& error_type_) : error_type(error_type_) {}

    bool match(kepler::error const & err) const{
        return err.error_type == error_type;
    }

    std::string describe() const override {
        return "should be a " + to_string(error_type);
    }

private:
    kepler::ErrorType const& error_type;
};