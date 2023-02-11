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

#include "form_table.h"
#include "../token.h"
#include "../error/error.h"

namespace kepler::form_table::applicators {
    template <typename Evaluator>
    struct scalar : boost::static_visitor<Token::content_type> {
        Array operator()(Array& arr) const {
            for(auto& element : arr.ravelList) {
                element = boost::apply_visitor(Evaluator(), element);
            }
            return arr;
        }

        Array operator()(Array& lhs, Array& rhs) const {
            Array a = lhs;
            for(int i = 0; i < a.ravelList.size(); ++i) {
                a.ravelList[i] = boost::apply_visitor(Evaluator(), lhs.ravelList[i], rhs.ravelList[i]);
            }
            return a;
        }

        Char operator()(Char& input) const {
            return Evaluator()(input);
        }

        Number operator()(Number& input) const {
            return Evaluator()(input);
        }

        Char operator()(Char& lhs, Char& rhs) const {
            return Evaluator()(lhs, rhs);
        }

        Number operator()(Number& lhs, Number& rhs) const {
            return Evaluator()(lhs, rhs);
        }

        template <typename T>
        T operator()(T& input) const {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }

        template <typename T, typename U>
        T operator()(T& lhs, U& rhs) const {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }
    };

    template <typename Evaluator>
    struct array : boost::static_visitor<Token::content_type> {
        Array operator()(Array& arr) const {
            return Evaluator()(arr);
        }

        template <typename T>
        T operator()(T& input) const {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }

        template <typename T, typename U>
        T operator()(T& lhs, U& rhs) const {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }
    };

    template <typename Extension>
    struct monadic : boost::static_visitor<Token> {
        Token operator()(List<Token*>& tokens) {
            kepler::Token operand = *tokens[1];
            operand.content = boost::apply_visitor(Extension(), operand.content.get());
            return operand;
        }
    };

    template <typename Extension>
    struct dyadic : boost::static_visitor<Token> {
        Token operator()(List<Token*>& tokens) {
            kepler::Token lhs = *tokens[0];
            kepler::Token rhs = *tokens[2];
            kepler::Token result = lhs;
            result.content = boost::apply_visitor(Extension(), lhs.content.get(), rhs.content.get());
            return result;
        }
    };
};