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

#include "interpreter.h"

bool kepler::interpreter::interpret(kepler::List<kepler::Token>& tokens, kepler::Token& result) {
    Array first = boost::get<Array>(tokens.at(0).content.get());
    Char operation = boost::get<Char>(tokens.at(1).content.get());
    Array second = boost::get<Array>(tokens.at(2).content.get());

    if(operation == U'+') {
        Number first_num = boost::get<Number>(first.ravelList[0]);
        Number second_num = boost::get<Number>(second.ravelList[0]);

        result.content = List<Number>{Number(first_num.realScalar + second_num.realScalar)};
    }

    return true;
}