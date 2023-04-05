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
#include <string>

namespace kepler {
    enum ErrorType {
        DefinitionError,
        DomainError,
        FileError,
        InternalError,
        LengthError,
        LimitError,
        NotImplemented,
        RankError,
        SyntaxError,
        ValueError,
    };

    /**
     * Converts an ErrorType to a string.
     *
     * @param error_type The error type.
     * @return The string.
     */
    std::string to_string(ErrorType error_type);
};