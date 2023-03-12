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
#include <catch2/catch_tostring.hpp>

namespace Catch {
    template <>
    struct StringMaker<kepler::Token> {
        static std::string convert(kepler::Token const & token) {
            return "\"" + token.to_string() + "\"";
        }
    };

    template <>
    struct StringMaker<kepler::List<kepler::Token>> {
        static std::string convert(kepler::List<kepler::Token> const & tokens) {
            std::stringstream ss;
            ss << "{";
            for(int i = 0; i < tokens.size(); ++i) {
                ss << "[";
                if(i < 10) {
                    ss << " ";
                }
                ss << std::to_string(i) << "]\t\t";
                ss << tokens[i].to_string() << "\n";
            }
            ss << "}\n";
            return ss.str();
        }
    };

    template <>
    struct StringMaker<kepler::Array> {
        static std::string convert(kepler::Array const& arr) {
            return "\n" + arr.to_string() + "\n";
        }
    };

    template <>
    struct StringMaker<kepler::error> {
        static std::string convert(kepler::error const & err) {
            return "\"" + err.to_string() + "\"";
        }
    };
};