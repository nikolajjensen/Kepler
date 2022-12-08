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

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>

namespace kepler {
    namespace lexer {
        namespace x3 = boost::spirit::x3;

        template <typename Iterator>
        using error_handler = x3::error_handler<Iterator>;

        using error_handler_tag = x3::error_handler_tag;

        struct error_handler_base {
            error_handler_base() = default;

            template <typename Iterator, typename Exception, typename Context>
            x3::error_handler_result on_error(Iterator& first, Iterator const& last, Exception const& x, Context const& context);
        };

        template <typename Iterator, typename Exception, typename Context>
        inline x3::error_handler_result error_handler_base::on_error(Iterator& first, Iterator const& last, Exception const& x, Context const& context) {
            std::string message = "SyntaxError: Expected " + x.which() + " here:";
            auto& error_handler = x3::get<error_handler_tag>(context).get();
            error_handler(x.where(), message);
            return x3::error_handler_result::fail;
        }
    };
};