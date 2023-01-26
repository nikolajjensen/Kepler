
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

#include "tui/context_line_old.h"
#include "tui/repl_container.h"
#include "core/env/environment.h"
#include "core/datatypes.h"
#include "core/lexer/lexer.h"
#include "core/parser/parser.h"
#include "core/interpreter/interpreter.h"
#include "core/parser/token_converter.h"
#include <boost/variant.hpp>

using namespace kepler;
using namespace ftxui;

int main() {
    Environment env = Environment();
    Session* session = env.spawn_session();

    auto screen = ScreenInteractive::Fullscreen();

    auto header_headline = Renderer([]{
        return vbox({
            text("Kepler") | bold,
            text("v1.0"),
        }) | dim | color(Color::Palette16::Cyan);
    });

    auto repl = tui::REPLContainer(header_headline, session, &env);

    auto content = Renderer(repl, [&]{
        return repl->Render();
    });

    screen.Loop(content);
}

/*
int main() {
    Environment env = Environment();
    Session* session = env.spawn_session();
    session->insert_line("1+2");

    env.evaluate(session);

    std::cout << "\n****  " << (true ? "Success" : "Fail") << "  ****" << std::endl;
}
*/
/*
int main() {
    Environment env = Environment();
    Session* session = env.spawn_session();
    //session->insert_line("ABC←FN ⎕⌽[1+0] DEF[1;5 6]×3.45E,⍴'ABC' ⍝COMMENT");
    //session->insert_line("+2");
    //session->insert_line("+2J‾1");
    session->insert_line("+2J1");
    //session->insert_line("ABC←FN");
    printers::TokenListPrinter list_printer;
    printers::TokenPrinter token_printer;

    bool success = true;
    success = success && kepler::lexer::lex(session->currentContext);
    list_printer(session->currentContext->currentStatement);
    success = success && kepler::parser::parse(session->currentContext, session);
    list_printer(session->currentContext->currentStatement);
    kepler::interpreter::interpret(session->currentContext, session);

    token_printer(session->currentContext->result);

    std::cout << "\n****  " << (success ? "Success" : "Fail") << "  ****" << std::endl;
}
*/
/*
namespace x3 = boost::spirit::x3;

int main() {
    using x3::char_;

    auto const left_parenthesis = x3::rule<struct left_parenthesis, std::string>{"left_parenthesis"} = char_('(');
    auto const right_parenthesis = x3::rule<struct right_parenthesis, std::string>{"right_parenthesis"} = char_(')');
    auto const left_axis_bracket = x3::rule<struct left_axis_bracket, std::string>{"left_axis_bracket"} = char_('[');
    auto const right_axis_bracket = x3::rule<struct right_axis_bracket, std::string>{"right_axis_bracket"} = char_(']');

    struct index;
    x3::rule<index, std::string> index = "index";
    struct expression;
    x3::rule<expression, std::string> expression = "expression";
    struct derived_function;
    x3::rule<derived_function, std::string> derived_function = "derived_function";
    struct assignment;
    x3::rule<assignment, std::string> assignment = "assignment";
    struct function;
    x3::rule<function, std::string> function = "function";
    struct axis_specification;
    x3::rule<axis_specification, std::string> axis_specification = "axis_specification";
    struct operation;
    x3::rule<operation, std::string> operation = "operation";
    struct operand;
    x3::rule<operand, std::string> operand = "operand";
    struct statement_class;
    x3::rule<statement_class, std::string> statement = "statement";

    auto const operation_def = ;
    auto const operand_def = (left_axis_bracket >> expression >> right_axis_bracket) | ;
    auto const expression_def = *operation >> operand >> *(+operation >> operand);
    auto const statement_def = -expression;

    BOOST_SPIRIT_DEFINE(statement, index, assignment, function, axis_specification, operation, operand, expression, derived_function)
}
 */

/*
#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>
#include <boost/spirit/home/x3.hpp>
#include <iostream>

namespace x3 = boost::spirit::x3;
using x3::char_;

struct one_class;
x3::rule<one_class, std::string> one = "one";
struct two_class;
x3::rule<two_class, std::string> two = "two";

auto const one_def = char_('A') >> *two;
auto const two_def = char_('B') >> *one;

BOOST_SPIRIT_DEFINE(one, two)

int main() {
    std::string test = "ABC";
    auto it = test.begin();
    auto end = test.end();

    std::string result;

    bool success = x3::parse(it, end, one, result);
    success = success && it == end;

    std::cout << (success ? "Pass" : "Fail") << std::endl;
}
*/