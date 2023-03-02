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
#include <utility>

#include "form_table.h"
#include "core/token.h"
#include "core/error.h"
#include "form_table_evaluators.h"

namespace kepler::form_table::extensions {

    struct extension : boost::static_visitor<Token::content_type> {
        std::unique_ptr<evaluators::evaluator> ev;

        explicit extension(std::unique_ptr<evaluators::evaluator> ev_) : ev(std::move(ev_)) {}

        virtual Token::content_type operator()() const {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }

        virtual Char operator()(const Char& input) const {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }

        virtual Array operator()(const Array& input) const {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }

        virtual List<Char> operator()(const List<Char>& input) const {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }

        virtual List<Number> operator()(const List<Number>& input) const {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }

        virtual Char operator()(const Char& lhs, const Char& rhs) const {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }

        virtual Array operator()(const Char& lhs, const Array& rhs) const {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }

        virtual List<Char> operator()(const Char& lhs, const List<Char>& rhs) const {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }

        virtual List<Number> operator()(const Char& lhs, const List<Number>& rhs) const {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }

        virtual Char operator()(const Array& lhs, const Char& rhs) const {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }

        virtual Array operator()(const Array& lhs, const Array& rhs) const {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }

        virtual List<Char> operator()(const Array& lhs, const List<Char>& rhs) const {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }

        virtual List<Number> operator()(const Array& lhs, const List<Number>& rhs) const {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }

        virtual Char operator()(const List<Char>& lhs, const Char& rhs) const {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }

        virtual Array operator()(const List<Char>& lhs, const Array& rhs) const {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }

        virtual List<Char> operator()(const List<Char>& lhs, const List<Char>& rhs) const {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }

        virtual List<Number> operator()(const List<Char>& lhs, const List<Number>& rhs) const {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }

        virtual Char operator()(const List<Number>& lhs, const Char& rhs) const {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }

        virtual Array operator()(const List<Number>& lhs, const Array& rhs) const {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }

        virtual List<Char> operator()(const List<Number>& lhs, const List<Char>& rhs) const {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }

        virtual List<Number> operator()(const List<Number>& lhs, const List<Number>& rhs) const {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }

        virtual Token apply() const {
            return {ConstantToken, (*this)()};
        }

        virtual Token apply(const Token& token) const {
            Token result = token;
            result.content = boost::apply_visitor(*this, result.content.get());
            return result;
        }

        virtual Token apply(const Token& lhs, const Token& rhs) const {
            Token result = lhs;
            result.content = boost::apply_visitor(*this, lhs.content.get(), rhs.content.get());
            return result;
        }
    };

    struct scalar : extension {
        using extension::extension;
        using extension::operator();

        Array operator()(const Array& arr) const override {
            Array result = arr;
            for(auto& element : result.ravel_list) {
                element = boost::apply_visitor(*ev, element);
            }
            return result;
        }

        Array operator()(const Array& lhs, const Array& rhs) const override {
            Array a = lhs;
            for(int i = 0; i < a.ravel_list.size(); ++i) {
                a.ravel_list[i] = boost::apply_visitor(*ev, lhs.ravel_list[i], rhs.ravel_list[i]);
            }
            return a;
        }
    };

    struct structural : extension {
        using extension::extension;
        using extension::operator();

        Array operator()(const Array& arr) const override {
            return (*ev)(arr);
        }
    };

    struct system_variable : extension {
        using extension::extension;
        using extension::operator();

        Token::content_type operator()() const override {
            evaluators::return_type result = (*ev)();
            if(Array* arr = boost::get<Array>(&result)) {
                return *arr;
            } else {
                throw kepler::error(InternalError, "Received unexpected result type from evaluator.");
            }
        }

        Array operator()(const Array& token) const override {
            return (*ev)(token);
        }

        Token apply(const Token& token) const override {
            Token result = token;
            result.token_class = CommittedValueToken;
            result.content = boost::apply_visitor(*this, result.content.get());
            return result;
        }
    };

    struct operators : extension {
        using extension::extension;
        using extension::operator();

        Array operator()(const Token& func, const Array& arr) const {
            return (*ev)(func, arr);
        }

        Token apply(const Token& lhs, const Token& rhs) const override {
            Token result = lhs;
            result.token_class = ConstantToken;
            if(rhs.contains<Array>()) {
                result.content = (*this)(lhs, rhs.get_content<Array>());
            } else {
                result.content = boost::apply_visitor(*this, lhs.content.get(), rhs.content.get());
            }
            return result;
        }
    };

    /*
    struct extension : boost::static_visitor<Token::content_type> {
        evaluators::evaluator evaluator;


        explicit extension(evaluators::evaluator evaluator_) : evaluator(std::move(evaluator_)) {}

        template <typename T>
        T operator()() {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }

        template <typename T>
        T operator()(const T& input) {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }

        template <typename T, typename U>
        T operator()(const T& lhs, const U& rhs) {
            throw kepler::error(InternalError, "Applicator called with unsupported argument.");
        }
    };


    struct scalar : extension {
        using extension::extension;
        using extension::operator();

        Array operator()(const Array& arr) {
            Array result = arr;
            for(auto& element : result.ravel_list) {
                element = boost::apply_visitor(this->evaluator, element);
            }
            return result;
        }

        Array operator()(const Array& lhs, const Array& rhs) {
            Array a = lhs;
            for(int i = 0; i < a.ravel_list.size(); ++i) {
                a.ravel_list[i] = boost::apply_visitor(this->evaluator, lhs.ravel_list[i], rhs.ravel_list[i]);
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

    struct structural : extension {
        using extension::extension;
        using extension::operator();

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

    struct system_variable : extension {
        using extension::extension;
        using extension::operator();

        Token operator()() {
            return this->evaluator.operator()<Token>();
        }

        Token operator()(const Token& token) {
            return this->evaluator(token);
        }
    };

    struct operators : extension {
        using extension::extension;
        using extension::operator();

        Token operator()(const Token& func, const Token& operand) {
            Token result = operand;
            const auto& arr = operand.get_content<Array>();
            auto t = this->evaluator(func, arr);
            result.content = this->evaluator(func, arr);
            return result;
        }
    };
    */
};