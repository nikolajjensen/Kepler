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
#include <iomanip>

/*
struct EqualsTokenClass : Catch::Matchers::MatcherGenericBase {
    EqualsTokenClass(kepler::TokenClass const& tokenClass_) : tokenClass(tokenClass_) {}

    bool match(kepler::Token const& token) const {
        return token.tokenClass == tokenClass;
    }

    std::string describe() const override {
        return "has token class ???";
    }

private:
    kepler::TokenClass const& tokenClass;
};
struct Contains : Catch::Matchers::MatcherGenericBase {
    Contains(kepler::Token::content_type const& content_) : content(content_) {}

    bool match(kepler::Token const& token) const {
        //kepler::printers::TokenDebugPrinter p;
        //p(token);
        //auto other = kepler::Token(kepler::NilToken, content);
        //p(other);
        return token.content && token.content.get() == content;
    }

    std::string describe() const override {
        return "should contain ???";
    }

private:
    kepler::Token::content_type const& content;
};
*/

struct Outputs : Catch::Matchers::MatcherGenericBase {
    Outputs(std::string const& output_, int print_precision_ = -1) : output(output_), print_precision(print_precision_) {}

    bool match(kepler::Token const& token) const {
        std::stringstream ss;
        kepler::printers::TokenPrinter p(ss, print_precision);
        p(token);
        return ss.str() == output;
    }

    std::string describe() const override {
        return "should output " + output;
    }

private:
    std::string const& output;
    int print_precision;
};