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
#include <iomanip>

struct Outputs : Catch::Matchers::MatcherGenericBase {
    explicit Outputs(std::string const& output_, int print_precision_ = -1) : output(output_), print_precision(print_precision_) {}

    bool match(kepler::Token const & result) const {
        std::stringstream ss;
        kepler::helpers::TokenPrinter p(ss, print_precision);
        p(result);
        return ss.str() == output;
    }

    std::string describe() const override {
        return "should output " + output;
    }

private:
    std::string const& output;
    int print_precision;
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