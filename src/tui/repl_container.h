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
#include "input_line.h"
#include "core/env/session.h"
#include "core/env/environment.h"


namespace kepler {
    namespace tui {
        namespace {
            using namespace ftxui;

            class REPLContainerBase : public ComponentBase {
            public:
                REPLContainerBase(Component header_, kepler::Session* session_, kepler::Environment* env_) : header(header_), session(session_), env(env_) {
                    update_children();
                }

                Component ActiveChild() override {
                    if (children_.empty()) {
                        return nullptr;
                    }

                    return children_[children_.size() - 1 - selected];
                }

                void update_children() {
                    DetachAllChildren();

                    Add(header);

                    /*for(unsigned int i = 0; i < session->activeWorkspace.stateIndicator.size(); ++i) {
                        Add(ContextLine(&session->activeWorkspace.stateIndicator[i]) | ((selected == i) ? focus : nothing));
                    }
                    */

                    for(auto& context : session->activeWorkspace.stateIndicator) {
                        Add(ContextLine(&context));
                    }

                    Add(InputLine(session));
                }

                Element Render() override {
                    Elements elements;
                    for (auto& it : children_) {
                        elements.push_back(it->Render());
                    }

                    /*
                    for(unsigned int i = 0; i < children_.size(); ++i) {
                        //auto modifier = ((children_.size() - selected - 1) == i) ? (focus | bgcolor(Color::Yellow)) : nothing;
                        //elements.push_back(Renderer(children_[i], [&]{

                        //}));
                        //elements.push_back((children_[i] | ((selected == i) ? focus : nothing))->Render());

                        if(selected == i) {
                            elements.push_back((children_[i] | focus)->Render());
                        } else {
                            elements.push_back(children_[i]->Render());
                        }
                    }
                     */

                    return vbox(elements) | reflect(box) | yframe;
                }

                bool OnEvent(Event event) override {
                    if(event.is_mouse()) {
                        return OnMouseEvent(event);
                    }

                    if (ActiveChild() && ActiveChild()->OnEvent(event)) {
                        if(event == Event::Return) {
                            env->evaluate(session);
                            update_children();
                        }

                        return true;
                    }

                    return false;
                }

                bool OnMouseEvent(Event event) {
                    if (event.mouse().button == Mouse::WheelDown || event.mouse().button == Mouse::WheelUp) {
                        return OnMouseWheelEvent(event);
                    }

                    return false;
                }

                bool OnMouseWheelEvent(Event event) {
                    if(!box.Contain(event.mouse().x, event.mouse().y)) {
                        return false;
                    }

                    if(event.mouse().button == Mouse::WheelUp) {
                        selected++;
                    } else if(event.mouse().button == Mouse::WheelDown) {
                        selected--;
                    }

                    selected = util::clamp(selected, 0, (int)(children_.size() - 1));

                    return true;
                }

            protected:
                Component header;
                kepler::Session* session;
                kepler::Environment* env;
                int selected = 0;

                Box box;
            };
        };

        Component REPLContainer(Component header, kepler::Session* session, kepler::Environment* env) {
            return Make<REPLContainerBase>(std::move(header), session, env);
        }
    };
};