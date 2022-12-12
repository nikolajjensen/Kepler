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
#include "context_line.h"
#include "core/env/session.h"

namespace kepler {
    namespace tui {
        namespace {
            using namespace ftxui;

            class REPLContainerBase : public ComponentBase {
            public:
                REPLContainerBase(Component header, kepler::Session* session) : inputs_(), session_(session) {
                    Add(std::move(header));
                    add_line();
                }

                Component ActiveChild() override {
                    if (children_.empty()) {
                        return nullptr;
                    }

                    return children_[children_.size() - 1];
                }

                Element Render() override {
                    Elements elements;
                    for (auto& it : children_) {
                        elements.push_back(it->Render());
                    }
                    if (elements.empty()) {
                        return text("Empty REPL...");
                    }
                    return vbox(elements);
                }

                bool OnEvent(Event event) override {
                    if (ActiveChild() && ActiveChild()->OnEvent(event) && event != Event::Return) {
                        return true;
                    }

                    if(event == Event::Return) {
                        session_->evaluate_line();
                        add_line();
                        return true;
                    }

                    return false;
                }

            private:
                void add_line() {
                    session_->new_context();
                    Add(std::move(ContextLine(session_)));
                }

            protected:
                std::vector<std::string> inputs_;
                kepler::Session* session_;
            };
        };

        Component REPLContainer(Component header, kepler::Session* session) {
            return Make<REPLContainerBase>(std::move(header), std::move(session));
        }
    };
};