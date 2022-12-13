
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
#include "core/datatypes.h"
#include "core/lexer/lexer.h"
#include <boost/variant.hpp>

using namespace kepler;
using namespace ftxui;

int main() {
    Session session = System::new_session();


    auto screen = ScreenInteractive::Fullscreen();

    auto header_headline = Renderer([]{
        return vbox({
            //text("Kepler") | bold,
            text("v1.0"),
        }) | dim | color(Color::CadetBlue);
    });

    auto repl = tui::REPLContainer(header_headline, &session);

    auto content = Renderer(repl, [&]{
        return repl->Render();
    });

    screen.Loop(content);
}

/*
int main() {
    StringUTF32 test = U"1+2";
    List<Token> tokens;
    bool lex_success = lexer::lex(test, tokens);

    printers::TokenListPrinter printer;
    printer(tokens);
}
 */