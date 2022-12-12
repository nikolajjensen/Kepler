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

#include "helpers.h"

// Group together several properties, so they appear to form a similar group.
// For instance, letters are grouped with number and form a single word.
bool kepler::tui::IsWordCharacter(ftxui::WordBreakProperty property) {
    switch (property) {
        case ftxui::WordBreakProperty::ALetter:
        case ftxui::WordBreakProperty::Hebrew_Letter:
        case ftxui::WordBreakProperty::Katakana:
        case ftxui::WordBreakProperty::Numeric:
            return true;

        case ftxui::WordBreakProperty::CR:
        case ftxui::WordBreakProperty::Double_Quote:
        case ftxui::WordBreakProperty::LF:
        case ftxui::WordBreakProperty::MidLetter:
        case ftxui::WordBreakProperty::MidNum:
        case ftxui::WordBreakProperty::MidNumLet:
        case ftxui::WordBreakProperty::Newline:
        case ftxui::WordBreakProperty::Single_Quote:
        case ftxui::WordBreakProperty::WSegSpace:
            // Unsure:
        case ftxui::WordBreakProperty::Extend:
        case ftxui::WordBreakProperty::ExtendNumLet:
        case ftxui::WordBreakProperty::Format:
        case ftxui::WordBreakProperty::Regional_Indicator:
        case ftxui::WordBreakProperty::ZWJ:
            return false;
    }
    return true; // NOT_REACHED();
}