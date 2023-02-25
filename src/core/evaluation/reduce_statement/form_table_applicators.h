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
#include <memory>

#include "form_table.h"
#include "core/token.h"
#include "core/error.h"
#include "form_table_extensions.h"

namespace kepler::form_table::applicators {

    struct extractor {
        std::unique_ptr<extensions::extension> ex;

        explicit extractor(std::unique_ptr<extensions::extension> ex_) : ex(std::move(ex_)) {}
        virtual ~extractor() = default;

        virtual Token apply(const List<const Token*>& tokens) const = 0;
    };

    struct niladic : extractor {
        using extractor::extractor;

        Token apply(const List<const Token*>& tokens) const override {
            if(!tokens.empty()) throw kepler::error(InternalError, "Expected no tokens.");
            return ex->apply();
        }
    };

    struct monadic : extractor {
        using extractor::extractor;

        Token apply(const List<const Token*>& tokens) const override {
            if(tokens.size() != 1) throw kepler::error(InternalError, "Expected only two tokens.");
            return ex->apply(*tokens[0]);
        }
    };

    struct dyadic : extractor {
        using extractor::extractor;

        Token apply(const List<const Token*>& tokens) const override {
            if(tokens.size() != 2) throw kepler::error(InternalError, "Expected only two tokens.");
            return ex->apply(*tokens[0], *tokens[1]);
        }
    };

    struct applicator {
        std::unique_ptr<extractor> ar;

        applicator(std::unique_ptr<extractor> ar_)
                : ar(std::move(ar_)) {}

        Token apply(const List<const Token*>& tokens) const {
            return ar->apply(tokens);
        }

        template <typename Ar, typename Ex, typename Ev>
        static applicator construct(kepler::Session* session) {
            return applicator(std::make_unique<Ar>(std::make_unique<Ex>(std::make_unique<Ev>(session))));
        }
    };

    /*
    struct applicator : boost::static_visitor<Token> {
        extensions::extension extension;

        explicit applicator(extensions::extension extension_) : extension(std::move(extension_)) {}

        virtual Token operator()(const List<const Token*>& tokens) {
            throw kepler::error(InternalError, "Expected no tokens.");
        }
    };

    struct niladic : applicator {
        using applicator::applicator;

        Token operator()(const List<const Token*>& tokens) override {
            if(!tokens.empty()) throw kepler::error(InternalError, "Expected no tokens.");
            return (this->extension).operator()<Token>();
        }
    };

    struct monadic : applicator {
        using applicator::applicator;

        Token operator()(const List<const Token*>& tokens) override {
            if(tokens.size() != 1) throw kepler::error(InternalError, "Expected only one token.");
            return this->extension(*tokens[0]);
        }
    };

    struct dyadic : applicator {
        using applicator::applicator;

        Token operator()(const List<const Token*>& tokens) override {
            if(tokens.size() != 2) throw kepler::error(InternalError, "Expected only two tokens.");
            return this->extension(*tokens[0], *tokens[1]);
        }
    };
    */


};