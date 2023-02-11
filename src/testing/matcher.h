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
#include "core/token_class.h"
#include "core/token.h"
#include "core/env/printers.h"
#include "core/error/error.h"
#include <iomanip>

struct Outputs : Catch::Matchers::MatcherGenericBase {
    Outputs(std::string const& output_, int print_precision_ = -1) : output(output_), print_precision(print_precision_) {}

    bool match(kepler::Context const & context) const {
        std::stringstream ss;
        kepler::printers::TokenPrinter p(ss, print_precision);
        p(context.result);
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
    Throws(kepler::ErrorType const& error_type_) : error_type(error_type_) {}

    bool match(kepler::Context const & context) const {
        return context.error->error_type == error_type;
    }

    std::string describe() const override {
        return "should be a " + to_string(error_type);
    }

private:
    kepler::ErrorType const& error_type;
};