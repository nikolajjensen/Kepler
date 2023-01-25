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

#pragma once
#include "includes.h"
#include "core/env/session.h"

#include <string>
/*
namespace kepler {
    namespace tui {
        namespace {
            using namespace ftxui;

            // An input box. The user can type text into it.
            class ContextLineBase : public ComponentBase {
            public:
                ContextLineBase(kepler::Session* session)
                              : session_(session), index_(session->activeWorkspace.stateIndicator.size() - 1), offset_(0) {}

                int cursor_position_internal_ = 0;
                int& cursor_position() {
                    int& opt = option_->cursor_position();
                    if (opt != -1) {
                        return opt;
                    }
                    return cursor_position_internal_;
                }

                // Component implementation:
                Element Render() override {
                    int size = GlyphCount(input_content_());

                    cursor_position() = std::max(0, std::min<int>(size, cursor_position()));
                    auto main_decorator = flex | ftxui::size(HEIGHT, EQUAL, 1);
                    bool is_focused = Focused();

                    if (!is_focused) {
                        return vbox({
                            hbox({
                                text(">>>  "),
                                text(input_content_())
                            }) | main_decorator | reflect(box_),
                            text(result_content_())
                        }) | dim;
                    }

                    int index_before_cursor = GlyphPosition(input_content_(), cursor_position());
                    int index_after_cursor = GlyphPosition(input_content_(), 1, index_before_cursor);
                    std::string part_before_cursor = input_content_().substr(0, index_before_cursor);
                    std::string part_at_cursor = " ";
                    if (cursor_position() < size) {
                        part_at_cursor = input_content_().substr(index_before_cursor,
                                                        index_after_cursor - index_before_cursor);
                    }
                    std::string part_after_cursor = input_content_().substr(index_after_cursor);
                    return vbox({
                        hbox({
                            text(">>>  "),
                            text(part_before_cursor),
                            text(part_at_cursor) | focusCursorBarBlinking | reflect(cursor_box_),
                            text(part_after_cursor),
                        }) | flex | frame | bold | main_decorator | reflect(box_),
                        text(result_content_()) | dim
                    });
                }

                bool OnEvent(Event event) override {
                    cursor_position() = std::max(0, std::min<int>((int)input_content_().size(), cursor_position()));

                    if (event.is_mouse()) {
                        return OnMouseEvent(event);
                    }

                    // Backspace.
                    if (event == Event::Backspace) {
                        if (cursor_position() == 0) {
                            return false;
                        }
                        size_t start = GlyphPosition(input_content_(), cursor_position() - 1);
                        size_t end = GlyphPosition(input_content_(), cursor_position());
                        input_content_().erase(start, end - start);
                        cursor_position()--;
                        option_->on_change();
                        return true;
                    }

                    // Delete
                    if (event == Event::Delete) {
                        if (cursor_position() == int(input_content_().size())) {
                            return false;
                        }
                        size_t start = GlyphPosition(input_content_(), cursor_position());
                        size_t end = GlyphPosition(input_content_(), cursor_position() + 1);
                        input_content_().erase(start, end - start);
                        option_->on_change();
                        return true;
                    }

                    // Arrow
                    if (event == Event::ArrowLeft && cursor_position() > 0) {
                        cursor_position()--;
                        return true;
                    }

                    if (event == Event::ArrowRight &&
                        cursor_position() < (int)input_content_().size()) {
                        cursor_position()++;
                        return true;
                    }

                    if(event == Event::ArrowDown && session_->activeWorkspace.stateIndicator.size() - 1 > index_ + offset_) {
                        ++offset_;

                        if(offset_ == 0) {
                            context_().currentLine = tmp_buffer;
                        } else {
                            context_().currentLine = offset_content_();
                        }

                        cursor_position() = std::max(0, std::max<int>((int)input_content_().size(), cursor_position()));

                        return true;
                    }

                    if(event == Event::ArrowUp && index_ + offset_ > 0) {
                        --offset_;
                        context_().currentLine = offset_content_();
                        cursor_position() = std::max(0, std::max<int>((int)input_content_().size(), cursor_position()));
                        return true;
                    }

                    if(event == Event::Return) {
                        // Save the value we have currently taken up.
                        if(offset_ == 0) {
                            context_().currentLine = tmp_buffer;
                        }
                    }

                    // CTRL + Arrow:
                    if (event == Event::ArrowLeftCtrl) {
                        HandleLeftCtrl();
                        return true;
                    }
                    if (event == Event::ArrowRightCtrl) {
                        HandleRightCtrl();
                        return true;
                    }

                    if (event == Event::Home) {
                        cursor_position() = 0;
                        return true;
                    }

                    if (event == Event::End) {
                        cursor_position() = GlyphCount(input_content_());
                        return true;
                    }

                    // Content
                    if (event.is_character()) {
                        size_t start = GlyphPosition(input_content_(), cursor_position());
                        input_content_().insert(start, event.character());
                        cursor_position()++;
                        option_->on_change();
                        return true;
                    }
                    return false;
                }

            private:
                void HandleLeftCtrl() {
                    auto properties = Utf8ToWordBreakProperty(input_content_());

                    // Move left, as long as left is not a word character.
                    while (cursor_position() > 0 &&
                           !IsWordCharacter(properties[cursor_position() - 1])) {
                        cursor_position()--;
                    }

                    // Move left, as long as left is a word character:
                    while (cursor_position() > 0 &&
                           IsWordCharacter(properties[cursor_position() - 1])) {
                        cursor_position()--;
                    }
                }

                void HandleRightCtrl() {
                    auto properties = Utf8ToWordBreakProperty(input_content_());
                    int max = (int)properties.size();

                    // Move right, as long as right is not a word character.
                    while (cursor_position() < max &&
                           !IsWordCharacter(properties[cursor_position()])) {
                        cursor_position()++;
                    }

                    // Move right, as long as right is a word character:
                    while (cursor_position() < max &&
                           IsWordCharacter(properties[cursor_position()])) {
                        cursor_position()++;
                    }
                }

                bool OnMouseEvent(Event event) {
                    hovered_ = box_.Contain(event.mouse().x, event.mouse().y) && CaptureMouse(event);
                    if (!hovered_) {
                        return false;
                    }

                    if (event.mouse().button != Mouse::Left ||
                        event.mouse().motion != Mouse::Pressed) {
                        return false;
                    }

                    TakeFocus();
                    if (input_content_().empty()) {
                        return true;
                    }

                    auto mapping = CellToGlyphIndex(input_content_());
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
                    int target_cell = int(original_cell) + event.mouse().x - cursor_box_.x_min;
                    int target_glyph = target_cell < (int)mapping.size() ? mapping[target_cell]
                                                                         : (int)mapping.size();
                    target_glyph = util::clamp(target_glyph, 0, GlyphCount(input_content_()));
                    if (cursor_position() != target_glyph) {
                        cursor_position() = target_glyph;
                        option_->on_change();
                    }
                    return true;
                }

                bool Focusable() const final { return true; }

                struct visitor : public boost::static_visitor<StringUTF8> {
                    StringUTF8 operator()(Char& c) const {
                        return uni::utf32to8(StringUTF32(1, c));
                    }

                    StringUTF8 operator()(Number& number) const {
                        return number.to_string();
                    }

                    StringUTF8 operator()(List<Char>& list) const {
                        return uni::utf32to8(StringUTF32(list.begin(), list.end()));
                    }

                    StringUTF8 operator()(List<Number>& list) const {
                        visitor v;
                        return v(list[0]);
                    }

                    StringUTF8 operator()(Array array) const {
                        std::stringstream ss;
                        for(auto& list : array.ravelList) {
                            ss << boost::apply_visitor(visitor(), list);
                        }
                        return ss.str();
                    }
                };

                StringUTF8 input_content_() {
                    if(offset_ == 0) {
                        return uni::utf32to8(tmp_buffer);
                    } else {
                        return uni::utf32to8(context_().currentLine);
                    }
                };

                StringUTF8 get_result_content() {
                    std::stringstream ss;
                    if(context_().stack.size() >= 1 && context_().stack[0].content) {
                        ss << boost::apply_visitor(visitor(), context_().stack[0].content.get());
                    }

                    return ss.str();

                    for(auto& token : context_().currentStatement) {
                        switch (token.tokenClass) {
                            case TokenClass::AssignmentArrowToken:
                                ss << "AssignmentArrowToken";
                                break;
                            case TokenClass::DirectIdentifierToken:
                                ss << "DirectIdentifierToken";
                                break;
                            case TokenClass::StatementSeparatorToken:
                                ss << "StatementSeparatorToken";
                                break;
                            case TokenClass::SimpleIdentifierToken:
                                ss << "SimpleIdentifierToken";
                                break;
                            case TokenClass::PrimitiveToken:
                                ss << "PrimitiveToken";
                                break;
                            case TokenClass::DistinguishedIdentifierToken:
                                ss << "DistinguishedIdentifierToken";
                                break;
                            case TokenClass::NumericLiteralToken:
                                ss << "NumericLiteralToken";
                                break;
                            case TokenClass::CharacterLiteralToken:
                                ss << "CharacterLiteralToken";
                                break;
                            case TokenClass::VariableNameToken:
                                ss << "VariableNameToken";
                                break;
                            case TokenClass::NilToken:
                                ss << "NilToken";
                                break;
                            case TokenClass::DyadicOperatorToken:
                                ss << "DyadicOperatorToken";
                                break;
                            case ConstantToken:
                                ss << "ConstantToken";
                                break;
                            case TokenClass::RightParenthesisToken:
                                ss << "RightParenthesisToken";
                                break;
                            case IndexSeparatorToken:
                                ss << "IndexSeparatorToken";
                                break;
                            case PrimitiveFunctionToken:
                                ss << "PrimitiveFunctionToken";
                                break;
                            case UnwindToken:
                                ss << "UnwindToken";
                                break;
                            default:
                                ss << token.tokenClass;
                                break;
                        }

                        ss << " -> ";

                        if(token.content) {
                            ss << boost::apply_visitor(visitor(), token.content.get());
                        }

                        ss << "   \n";
                    }

                    return ss.str();
                }

                kepler::Context& offset_context_() {
                    return context_(offset_);
                }

                kepler::Context& context_(int offset = 0) {
                    return session_->activeWorkspace.stateIndicator[index_ + offset];
                }

                bool hovered_ = false;
                kepler::Session* session_;
                StringUTF32 tmp_buffer;
                unsigned int index_;
                int offset_;

                Box box_;
                Box cursor_box_;
                Ref<InputOption> option_;
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
        Component ContextLine(kepler::Session* session) {
            return Make<ContextLineBase>(session);
        }
    };
};
 */