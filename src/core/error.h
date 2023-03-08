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
#include <iostream>
#include <sstream>
#include <utility>
#include "error_type.h"
#include "datatypes.h"
#include "core/token.h"
#include <optional>
#include <variant>
#include <uni_algo/conv.h>

namespace kepler {

    class error : public std::exception {
    public:
        ErrorType error_type;
        std::string message;
        long position;
        std::vector<Char>* input;

        error(ErrorType error_type_,
              std::string message_)
                : error_type(error_type_),
                  message(std::move(message_)),
                  position(-1),
                  input(nullptr) {}

        error(ErrorType error_type_,
              std::string message_,
              long position_)
                : error_type(error_type_),
                  message(std::move(message_)),
                  position(position_),
                  input(nullptr) {}

        error(ErrorType error_type_,
              long position_)
                : error_type(error_type_),
                  message(""),
                  position(position_),
                  input(nullptr) {}

        error(ErrorType error_type_,
              std::string message_,
              long position_,
              std::vector<Char>* input_)
                : error_type(error_type_),
                  message(std::move(message_)),
                  position(position_),
                  input(input_) {}

        std::string type() const {
            return kepler::to_string(error_type);
        }

        std::string why() const {
            return message;
        }

        std::string to_string() const {
            std::stringstream ss;
            ss << type();

            if(!why().empty()) {
                ss << ": " << why();
            }

            std::string details = where();
            if(!details.empty()) {
                ss << "\n" << details;
            }

            return ss.str();
        }

        void set_input(std::vector<Char>* input_) {
            input = input_;
        }

        /*
        struct visitor : boost::static_visitor<> {
            std::ostream& stream;

            explicit visitor(std::ostream& stream_) : stream(stream_) {}

            void operator()(const std::vector<Char>& vec) {
                std::string str = uni::utf32to8(std::u32string(vec.begin(), vec.end()));
                stream << str;
            }

            void operator()(const std::vector<Token>& vec) {
                //helpers::TokenPrinter pr(stream);
                //for(auto& token : vec) {
                //    pr(token);
                //}
            }
        };
         */

        std::string where() const {
            std::stringstream ss;

            if(input != nullptr && position != -1) {
                ss << "   ";
                ss << uni::utf32to8(std::u32string(input->begin(), input->end()));
                ss << "\n";

                ss << "  ~";
                for (int i = 0; i < position - 1; ++i) {
                    ss << "~";
                }
                ss << "^";// << "   " << position;
            }

            return ss.str();
        }
    };
};