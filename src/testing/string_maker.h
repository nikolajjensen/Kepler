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
#include "core/constants/literals.h"
#include "core/constants/config.h"
#include "core/helpers/printers/error_printer.h"
#include "core/helpers/printers/token_printer.h"
#include <catch2/catch_tostring.hpp>

namespace Catch {
    template <>
    struct StringMaker<kepler::Token> {
        static std::string convert(kepler::Token const & token) {
            std::stringstream ss;
            ss << "\"";

            kepler::helpers::TokenPrinter p(ss, kepler::constants::initial_print_precision);
            p(token);
            ss << "\"";

            return ss.str();
        }
    };

    template <>
    struct StringMaker<kepler::List<kepler::Token>> {
        static std::string convert(kepler::List<kepler::Token> const & tokens) {
            std::stringstream ss;
            kepler::helpers::TokenListDebugPrinter p(ss);
            p(tokens);
            return ss.str();
        }
    };

    template <>
    struct StringMaker<kepler::error> {
        static std::string convert(kepler::error const & err) {
            std::stringstream ss;
            ss << "\"";

            kepler::helpers::ErrorPrinter p(ss);
            p(err);
            ss << "\"";

            return ss.str();
        }
    };
};