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
    struct extension : boost::static_visitor<Token::content_type> {
        Evaluator evaluator;
        kepler::Session* session;

        explicit extension(kepler::Session* session_) : evaluator(session_), session(session_) {}

        template <typename T>
        T operator()(const T& input) {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }

        template <typename T, typename U>
        T operator()(const T& lhs, const U& rhs) {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }
    };


    template <typename Evaluator>
    struct scalar : extension<Evaluator> {
        using extension<Evaluator>::extension;
        using extension<Evaluator>::operator();

        Array operator()(const Array& arr) {
            Array result = arr;
            for(auto& element : result.ravelList) {
                element = boost::apply_visitor(this->evaluator, element);
            }
            return result;
        }

        Array operator()(const Array& lhs, const Array& rhs) {
            Array a = lhs;
            for(int i = 0; i < a.ravelList.size(); ++i) {
                a.ravelList[i] = boost::apply_visitor(this->evaluator, lhs.ravelList[i], rhs.ravelList[i]);
            }
            return a;
        }

        Char operator()(const Char& input) {
            return this->evaluator(input);
        }

        Number operator()(const Number& input) {
            return this->evaluator(input);
        }

        Char operator()(const Char& lhs, const Char& rhs) {
            return this->evaluator(lhs, rhs);
        }

        Number operator()(const Number& lhs, const Number& rhs) {
            return this->evaluator(lhs, rhs);
        }

        Token operator()(const Token& token) {
            Token result = token;
            result.content = boost::apply_visitor(*this, token.content.get());
            return result;
        }

        Token operator()(const Token& lhs, const Token& rhs) {
            Token result = lhs;
            result.content = boost::apply_visitor(*this, lhs.content.get(), rhs.content.get());
            return result;
        }
    };

    template <typename Evaluator>
    struct structural : extension<Evaluator> {
        using extension<Evaluator>::extension;
        using extension<Evaluator>::operator();

        Array operator()(const Array& arr) {
            return this->evaluator(arr);
        }

        Token operator()(const Token& token) {
            Token result = token;
            result.content = boost::apply_visitor(*this, token.content.get());
            return result;
        }

        Token operator()(const Token& lhs, const Token& rhs) {
            Token result = lhs;
            result.content = boost::apply_visitor(*this, lhs.content.get(), rhs.content.get());
            return result;
        }
    };

    template <typename Evaluator>
    struct system_variable : extension<Evaluator> {
        using extension<Evaluator>::extension;
        using extension<Evaluator>::operator();

        Token operator()() {
            return this->evaluator();
        }

        Token operator()(const Token& token) {
            return this->evaluator(token);
        }
    };
};