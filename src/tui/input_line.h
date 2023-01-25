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

#include "includes.h"
#include "core/env/session.h"
#include "core/env/environment.h"

namespace kepler {
    namespace tui {
        namespace {
            using namespace ftxui;

            class InputLineBase : public ComponentBase {
            public:
                InputLineBase(kepler::Session* session_)
                    : session(session_) {}

                int cursor_position_internal_ = 0;
                int& cursor_position() {
                    int& opt = option->cursor_position();
                    if (opt != -1) {
                        return opt;
                    }
                    return cursor_position_internal_;
                }

                Element Render() override {
                    auto main_decorator = flex | ftxui::size(HEIGHT, EQUAL, 1);

                    if(!Focused()) {
                        return hbox({
                            text(">>>  "),
                            text(input)
                        }) | main_decorator | reflect(box) | dim;
                    }

                    int size = GlyphCount(input);
                    int index_before_cursor = GlyphPosition(input, cursor_position());
                    int index_after_cursor = GlyphPosition(input, 1, index_before_cursor);
                    std::string part_before_cursor = input.substr(0, index_before_cursor);
                    std::string part_at_cursor = " ";
                    if (cursor_position() < size) {
                        part_at_cursor = input.substr(index_before_cursor,
                                                                 index_after_cursor - index_before_cursor);
                    }
                    std::string part_after_cursor = input.substr(index_after_cursor);
                    return hbox({
                        text(">>>  "),
                        text(part_before_cursor),
                        text(part_at_cursor) | focusCursorBarBlinking | reflect(cursor_box),
                        text(part_after_cursor),
                    }) | flex | xframe | bold | main_decorator | reflect(box);
                }

                bool OnEvent(Event event) override {
                    cursor_position() = std::max(0, std::min<int>((int)input.size(), cursor_position()));

                    if (event.is_mouse()) {
                        return false;//OnMouseEvent(event);
                    }

                    // Backspace.
                    if (event == Event::Backspace) {
                        if (cursor_position() == 0) {
                            return false;
                        }
                        size_t start = GlyphPosition(input, cursor_position() - 1);
                        size_t end = GlyphPosition(input, cursor_position());
                        input.erase(start, end - start);
                        cursor_position()--;
                        option->on_change();
                        return true;
                    }

                    // Delete
                    if (event == Event::Delete) {
                        if (cursor_position() == int(input.size())) {
                            return false;
                        }
                        size_t start = GlyphPosition(input, cursor_position());
                        size_t end = GlyphPosition(input, cursor_position() + 1);
                        input.erase(start, end - start);
                        option->on_change();
                        return true;
                    }

                    if(event == Event::Return) {
                        trim(input);

                        if(!input.empty()) {
                            session->insert_line(input);
                            return true;
                        }
                    }

                    // Arrow
                    if (event == Event::ArrowLeft && cursor_position() > 0) {
                        cursor_position()--;
                        return true;
                    }

                    if (event == Event::ArrowRight &&
                        cursor_position() < (int)input.size()) {
                        cursor_position()++;
                        return true;
                    }

                    if(event == Event::ArrowDown && rev_index > 0) {
                        --rev_index;

                        if(rev_index == 0) {
                            input = tmp;
                        } else {
                            input = get_input_from_prev_context(rev_index);
                        }

                        cursor_position() = std::max(0, std::max<int>((int)input.size(), cursor_position()));

                        return true;
                    }

                    if(event == Event::ArrowUp && rev_index < session->activeWorkspace.stateIndicator.size()) {
                        ++rev_index;

                        if(rev_index == 1) {
                            // It was 0, now it is 1.
                            tmp = input;
                        }
                        input = get_input_from_prev_context(rev_index);

                        cursor_position() = std::max(0, std::max<int>((int)input.size(), cursor_position()));
                        return true;
                    }

                    // Content
                    if (event.is_character()) {
                        size_t start = GlyphPosition(input, cursor_position());
                        input.insert(start, event.character());
                        cursor_position()++;
                        option->on_change();
                        return true;
                    }

                    return false;
                }

            private:
                StringUTF8 get_input_from_prev_context(int reverse_index = 0) {
                    auto& stateIndicator = session->activeWorkspace.stateIndicator;
                    int index = stateIndicator.size() - reverse_index;

                    return index >= 0 ? uni::utf32to8(stateIndicator[stateIndicator.size() - reverse_index].currentLine) : "ERROR: Negative index.";
                }

                /*
                bool OnMouseEvent(Event event) {
                    hovered = box.Contain(event.mouse().x, event.mouse().y) && CaptureMouse(event);
                    if (!hovered) {
                        return false;
                    }

                    if (event.mouse().button != Mouse::Left ||
                        event.mouse().motion != Mouse::Pressed) {
                        return false;
                    }

                    TakeFocus();
                    if (input.empty()) {
                        return true;
                    }

                    auto mapping = CellToGlyphIndex(input);
                    int original_glyph = cursor_position();
                    original_glyph = util::clamp(original_glyph, 0, int(mapping.size()));
                    size_t original_cell = 0;
                    for (size_t i = 0; i < mapping.size(); i++) {
                        if (mapping[i] == original_glyph) {
                            original_cell = (int)i;
                            break;
                        }
                    }
                    if (mapping[original_cell] != original_glyph) {
                        original_cell = mapping.size();
                    }
                    int target_cell = int(original_cell) + event.mouse().x - cursor_box.x_min;
                    int target_glyph = target_cell < (int)mapping.size() ? mapping[target_cell]
                                                                         : (int)mapping.size();
                    target_glyph = util::clamp(target_glyph, 0, GlyphCount(input));
                    if (cursor_position() != target_glyph) {
                        cursor_position() = target_glyph;
                        option->on_change();
                    }
                    return true;
                }
                 */

                //https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/
                const std::string WHITESPACE = " \n\r\t\f\v";

                void trim(StringUTF8 &s) {
                    size_t start = s.find_first_not_of(WHITESPACE);
                    size_t end = s.find_last_not_of(WHITESPACE);

                    if(start == StringUTF8::npos || end == StringUTF8::npos || start > end) {
                        s = "";
                    } else {
                        s = s.substr(start, end - start + 1);
                    }
                }

                bool Focusable() const final { return true; }

                kepler::Session* session;

                StringUTF8 input;

                StringUTF8 tmp;
                int rev_index = 0;

                bool hovered = false;
                Box box;
                Box cursor_box;
                Ref<InputOption> option;
            };
        };

        /// @brief An input box for editing text.
        /// @param content The editable content.
        /// @param placeholder The text displayed when content is still empty.
        /// @param option Additional optional parameters.
        /// @ingroup component
        /// @see InputBase
        ///
        /// ### Example
        ///
        /// ```cpp
        /// auto screen = ScreenInteractive::FitComponent();
        /// std::string content= "";
        /// std::string placeholder = "placeholder";
        /// Component input = Input(&content, &placeholder);
        /// screen.Loop(input);
        /// ```
        ///
        /// ### Output
        ///
        /// ```bash
        /// placeholder
        /// ```
        Component InputLine(kepler::Session* session) {
            return Make<InputLineBase>(session);
        }
    };
};