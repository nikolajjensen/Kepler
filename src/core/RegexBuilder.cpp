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

#include <re2/re2.h>
#include <uni_algo/conv.h>
#include "RegexBuilder.h"
#include "Character.h"
/*
RegexBuilder::RegexBuilder() : content() {}

RegexBuilder* RegexBuilder::create() const {
    return new RegexBuilder();
}

re2::RE2 RegexBuilder::build() const {
    return re2::RE2(content);
}

RegexBuilder* RegexBuilder::matchAtStart() {
    this->content.append("^");
    return this;
}

RegexBuilder* RegexBuilder::matchOne(Character c) {
    content += "[";
    for(auto& rep : c.representations) {
        content += rep;
    }
    content += "]";
}*/