//
// Copyright 2022 Nikolaj Banke Jensen.
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

#include "TokenType.h"
#include <string>

std::ostream& operator<<(std::ostream& os, const TokenType &t) {
    switch (t) {
        case TokenType::AssignmentArrow:
            return os << "AssignmentArrow";
        case TokenType::DirectIdentifier:
            return os << "DirectIdentifier";
        case TokenType::SimpleIdentifier:
            return os << "SimpleIdentifier";
        case TokenType::Primitive:
            return os << "Primitive";
        case TokenType::DistinguishedIdentifier:
            return os << "DistinguishedIdentifier";
        case TokenType::NumericLiteral:
            return os << "NumericLiteral";
        case TokenType::CharacterLiteral:
            return os << "CharacterLiteral";
        default:
            // Maybe we should throw here...
            return os << "UNRECOGNIZED";
    }
}
