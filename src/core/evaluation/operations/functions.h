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
    /*
     * Note that the functions mentioned here have relatively short comments.
     * This is due to their descriptions being ubiquitous in the APL language,
     * and thus not needing to be repeated here.
     */

    /**
     * Represents 'conjugate' and 'plus'.
     */
    struct Plus : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
        Array operator()(const Number& omega) override;
    };

    /**
     * Represents 'negative' and 'minus'.
     */
    struct Minus : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
        Array operator()(const Number& omega) override;
    };

    /**
     * Represents 'direction' and 'multiply'.
     */
    struct Times : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
        Array operator()(const Number& omega) override;
    };

    /**
     * Represents 'reciprocal' and 'divide'.
     */
    struct Divide : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
        Array operator()(const Number& omega) override;
    };

    /**
     * Represents 'ceiling' and 'maximum'.
     */
    struct Ceiling : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
        Array operator()(const Number& omega) override;
    };

    /**
     * Represents 'floor' and 'minimum'.
     */
    struct Floor : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
        Array operator()(const Number& omega) override;
    };

    /**
     * Represents 'and'.
     */
    struct And : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
        Array operator()(const String& alpha, const String& omega) override;
        Array operator()(const Number& omega) override;
    };

    /**
     * Represents 'nand'.
     */
    struct Nand : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
        Array operator()(const String& alpha, const String& omega) override;
        Array operator()(const Number& omega) override;
    };

    /**
     * Represents 'or'.
     */
    struct Or : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
        Array operator()(const String& alpha, const String& omega) override;
        Array operator()(const Number& omega) override;
    };

    /**
     * Represents 'nor'.
     */
    struct Nor : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
        Array operator()(const String& alpha, const String& omega) override;
        Array operator()(const Number& omega) override;
    };

    /**
     * Represents 'same' (return the unchanged argument) and 'right' (return right argument).
     */
    struct RightTack : Operation {
        using Operation::Operation;

        Array operator()(const Array& alpha, const Array& omega) override;
        Array operator()(const Array& omega) override;
    };

    /**
     * Represents 'same' (return the unchanged argument) and 'left' (return left argument).
     */
    struct LeftTack : Operation {
        using Operation::Operation;

        Array operator()(const Array& alpha, const Array& omega) override;
        Array operator()(const Array& omega) override;
    };

    /**
     * Represents 'less than'.
     */
    struct Less : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
    };

    /**
     * Represents 'less than or equal'.
     */
    struct LessEq : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
    };

    /**
     * Represents 'equal'.
     */
    struct Eq : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
        Array operator()(const Char& alpha, const Char& omega) override;
    };

    /**
     * Represents 'greater than or equal'.
     */
    struct GreaterEq : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
    };

    /**
     * Represents 'greater than'.
     */
    struct Greater : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number &alpha, const Number &omega) override;
    };

    /**
     * Represents 'unique mask' and 'not equal'.
     */
    struct Neq : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& alpha, const Number& omega) override;
        Array operator()(const Char& alpha, const Char& omega) override;
        Array operator()(const Array& omega) override;
    };

    /**
     * Represents 'enclose' and 'partitioned enclose'.
     */
    struct LeftShoe : Operation {
        using Operation::Operation;

        Array operator()(const Array& omega) override;
        Array operator()(const Array& alpha, const Array& omega) override;
    };

    /**
     * Represents 'not' and 'without'.
     */
    struct Not : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;
        using PervadeMixin<Operation>::operator();

        Array operator()(const Number& omega) override;
        Array operator()(const Array& alpha, const Array& omega) override;
        Array operator()(const String& alpha, const String& omega) override;
    };

    /**
     * Represents 'iota' (index generation).
     */
    struct Iota : Operation {
        using Operation::Operation;

        Array operator()(const Array& omega) override;
    };

    /**
     * Represents 'shape' and 'reshape'.
     */
    struct Rho : Operation {
        using Operation::Operation;

        Array operator()(const Array& alpha, const Array& omega) override;
        Array operator()(const Array& omega) override;
    };

    /**
     * Represents 'reverse first' and 'rotate first'.
     */
    struct CircleBar : Operation {
        using Operation::Operation;
        using Operation::operator();

        Array operator()(const Number& omega) override;
        Array operator()(const String& omega) override;
        Array operator()(const Number& shift, const String& omega) override;
        Array operator()(const Number& shift, const Number& omega) override;

        Array operator()(const Array& alpha, const Array& omega) override;
        Array operator()(const Array& omega) override;
    };

    /**
     * Represents 'reverse' and 'rotate'.
     */
    struct CircleStile : Operation {
        using Operation::Operation;
        using Operation::operator();

        Array operator()(const Number& omega) override;
        Array operator()(const String& omega) override;
        Array operator()(const Number& shift, const String& omega) override;
        Array operator()(const Number& shift, const Number& omega) override;

        Array operator()(const Array& alpha, const Array& omega) override;
        Array operator()(const Array& omega) override;
    };

    /**
     * Represents 'ravel'.
     */
    struct Comma : Operation {
        using Operation::Operation;

        Array operator()(const Array& omega) override;
    };

    /**
     * Represents 'mix' and 'take'.
     */
    struct ArrowUp : Operation {
        using Operation::Operation;

        Array operator()(const Array& omega) override;
        Array operator()(const Array& alpha, const Array& omega) override;
    };

    /**
     * Represents 'roll' (random number generator).
     */
    struct Roll : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& omega) override;
    };

    /**
     * Represents 'exponential' and 'power'.
     */
    struct Star : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& omega) override;
        Array operator()(const Number& alpha, const Number& omega) override;
    };

    /**
     * Represents 'natural logarithm' and 'logarithm'.
     */
    struct Log : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& omega) override;
        Array operator()(const Number& alpha, const Number& omega) override;
    };

    /**
     * Represents 'magnitude' and 'residue/modulus'.
     */
    struct Bar : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& omega) override;
        Array operator()(const Number& alpha, const Number& omega) override;
    };

    /**
     * Represents 'factorial' and 'binomial'.
     */
    struct ExclamationMark : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& omega) override;
        Array operator()(const Number& alpha, const Number& omega) override;
    };

    /**
     * Represents 'pi times' and 'circular functions'.
     */
    struct Circle : PervadeMixin<Operation> {
        using PervadeMixin<Operation>::PervadeMixin;

        Array operator()(const Number& omega) override;
        Array operator()(const Number& alpha, const Number& omega) override;
    };
};
