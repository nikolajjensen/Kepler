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
#include "pervade.h"
#include "operation.h"

namespace kepler {

    struct Plus : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
        Array operator()(const Number& omega) override;
    };

    struct Minus : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
        Array operator()(const Number& omega) override;
    };

    struct Times : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
        Array operator()(const Number& omega) override;
    };

    struct Divide : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
        Array operator()(const Number& omega) override;
    };

    struct Ceiling : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
        Array operator()(const Number& omega) override;
    };

    struct Floor : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
        Array operator()(const Number& omega) override;
    };

    struct And : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
        Array operator()(const std::u32string& alpha, const std::u32string& omega) override;
        Array operator()(const Number& omega) override;
    };

    struct Nand : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
        Array operator()(const std::u32string& alpha, const std::u32string& omega) override;
        Array operator()(const Number& omega) override;
    };

    struct Or : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
        Array operator()(const std::u32string& alpha, const std::u32string& omega) override;
        Array operator()(const Number& omega) override;
    };

    struct Nor : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
        Array operator()(const std::u32string& alpha, const std::u32string& omega) override;
        Array operator()(const Number& omega) override;
    };

    struct RightTack : Operation {
        using Operation::Operation;

        Array operator()(const Array& alpha, const Array& omega) override;
        Array operator()(const Array& omega) override;
    };

    struct LeftTack : Operation {
        using Operation::Operation;

        Array operator()(const Array& alpha, const Array& omega) override;
        Array operator()(const Array& omega) override;
    };

    struct Less : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
    };

    struct LessEq : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
    };

    struct Eq : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
        Array operator()(const Char& alpha, const Char& omega) override;
    };

    struct GreaterEq : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
    };

    struct Greater : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number &alpha, const Number &omega) override;
    };

    struct Neq : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
        Array operator()(const Char& alpha, const Char& omega) override;
        Array operator()(const Array& omega) override;
    };

    struct LeftShoe : Operation {
        using Operation::Operation;

        Array operator()(const Array& omega) override;
        Array operator()(const Array& alpha, const Array& omega) override;
    };

    struct Not : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;
        using PervadeMixin<Operation>::operator();

        Array operator()(const Number& omega) override;
        Array operator()(const Array& alpha, const Array& omega) override;
        Array operator()(const std::u32string& alpha, const std::u32string& omega) override;
    };

    struct Iota : Operation {
        using Operation::Operation;

        Array operator()(const Array& omega) override;
    };

    struct Rho : Operation {
        using Operation::Operation;

        Array operator()(const Array& alpha, const Array& omega) override;
        Array operator()(const Array& omega) override;
    };

    struct CircleBar : Operation {
        using Operation::Operation;

        Array operator()(const Number& omega) override;
        Array operator()(const std::u32string& omega) override;

        Array operator()(const Array& alpha, const Array& omega) override;
        Array operator()(const Array& omega) override;
    };

    struct CircleStile : Operation {
        using Operation::Operation;

        Array operator()(const Array& alpha, const Array& omega) override;
        Array operator()(const Array& omega) override;
    };
};
