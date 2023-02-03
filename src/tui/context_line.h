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

            class ContextLineBase : public ComponentBase {
            public:
                ContextLineBase(kepler::Context* context_)
                    : context(context_) {}

                Element Render() override {
                    auto main_decorator = flex | ftxui::size(HEIGHT, EQUAL, 1);
                    auto focus_decorator = (Focused()) ? bold : dim;

                    auto output = hbox({
                        text(">>>  "),
                        text(get_input_string())
                    }) | main_decorator | reflect(box);

                    auto error_element = get_error_element();
                    auto result_string = get_result_string();

                    if(error_element) {
                        output = vbox({
                            output,
                            error_element.get()
                        });
                    }

                    if(!result_string.empty()) {
                        output = vbox({
                            output,
                            text(result_string)
                        });
                    }

                    return output | focus_decorator;
                }

            private:
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

                StringUTF8 get_result_string() {
                    std::stringstream ss;

                    if(context->result.content) {
                        ss << boost::apply_visitor(visitor(), context->result.content.get());
                    }

                    return ss.str();
                }

                boost::optional<Element> get_error_element() {
                    if(!context->error) {
                        return boost::none;
                    }
                    std::string padding = "    ";

                    auto outcome = text(context->error->type() + ": " + context->error->why());

                    if(context->error->where() != -1) {
                        outcome = vbox({
                            outcome,
                            text(padding + get_input_string()),
                            text(padding + std::string(context->error->where(), '~') + '^')
                        });
                    }

                    return outcome;
                }

                StringUTF8 get_input_string() {
                    return uni::utf32to8(context->currentLine);
                }


                kepler::Context* context;

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
        Component ContextLine(kepler::Context* context) {
            return Make<ContextLineBase>(context);
        }
    };
};