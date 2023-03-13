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
#include "error_type.h"

std::string kepler::to_string(ErrorType error_type) {
    switch (error_type) {
        case SyntaxError:
            return "SYNTAX ERROR";
        case ValueError:
            return "VALUE ERROR";
        case DomainError:
            return "DOMAIN ERROR";
        case ImplicitError:
            return "IMPLICIT ERROR";
        case RankError:
            return "RANK ERROR";
        case LengthError:
            return "LENGTH ERROR";
        case LimitError:
            return "LIMIT ERROR";
        case InternalError:
            return "INTERNAL ERROR";
        case DefinitionError:
            return "DEFINITION ERROR";
        case FileError:
            return "FILE ERROR";
        case NotImplemented:
            return "NOT IMPLEMENTED";
        default:
            return "UNDEFINED ERROR";
    }
}