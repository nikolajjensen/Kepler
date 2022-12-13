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
#include "rules.h"

namespace kepler {
    namespace parser {
        namespace x3 = boost::spirit::x3;

        namespace parsers {
            struct token : x3::parser<token> {
            private:
                TokenClass token_class;

            public:
                using attribute_type = x3::unused_type;

                token(TokenClass token_class_) : token_class(token_class_) {}

                template <typename Iterator, typename Context, typename RContext, typename Attribute>
                bool parse(Iterator &first, Iterator const& last, Context const& context, RContext const& rContext, Attribute& attr) const {
                    if((*first).tokenClass == token_class) {
                        ++first;
                        return true;
                    }

                    return false;
                }
            };
        };

        namespace rules {

            struct statement_class;
            x3::rule<statement_class, List<Token>> statement = "statement";
            auto const statement_def = parsers::token(TokenClass::ConstantToken);

            BOOST_SPIRIT_DEFINE(statement)
        };

        rules::statement_type const& statement() {
            return rules::statement;
        }
    };
};