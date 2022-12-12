
#define BOOST_SPIRIT_X3_UNICODE
#include <iostream>
#include "core/lexer/rules.h"
#include "core/lexer/config.h"

#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>
#include <boost/spirit/home/x3.hpp>
#include <uni_algo/conv.h>

#include "core/datatypes.h"
#include "core/env/printers.h"


#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Input, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/component_options.hpp"  // for InputOption
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for text, hbox, separator, Element, operator|, vbox, border
#include <vector>

#include "tui/context_line.h"
#include "tui/repl_container.h"
#include "core/env/system.h"

int main() {
    kepler::Session session = kepler::System::new_session();


    using namespace ftxui;
    auto screen = ScreenInteractive::Fullscreen();

    auto header_headline = Renderer([]{
        return vbox({
            //text("Kepler") | bold,
            text("v1.0"),
        }) | dim | color(Color::CadetBlue);
    });

    auto repl = kepler::tui::REPLContainer(header_headline, &session);

    auto content = Renderer(repl, [&]{
        return repl->Render();
    });

    screen.Loop(content);
}