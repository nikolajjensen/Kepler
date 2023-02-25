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
#include <iostream>
#include "core/error.h"

namespace kepler::helpers {
    struct ErrorPrinter {
        std::ostream& stream;
        const std::string padding = "    ";

        explicit ErrorPrinter(std::ostream& stream_) : stream(stream_) {}

        void operator()(const kepler::error& err) const {
            stream << err.type() << ": " << err.why();
            std::string where = err.where();
            if(!where.empty()) {
                stream << "\n" << where;
            }
        }
    };
};