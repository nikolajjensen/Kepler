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
#include <uni_algo/conv.h>

namespace kepler {
    class error : public std::exception {
    public:
        ErrorType error_type;
        std::string message;
        long position;
        const std::vector<Char>* input;
        int line;
        std::string file;

        error(ErrorType error_type_,
              std::string message_ = "")
                : error_type(error_type_),
                  message(std::move(message_)),
                  position(-2),
                  input(nullptr),
                  line(-1),
                  file("") {}

        error(ErrorType error_type_,
              std::string message_,
              long position_)
                : error_type(error_type_),
                  message(std::move(message_)),
                  position(position_),
                  input(nullptr),
                  line(-1),
                  file("") {}

        error(ErrorType error_type_,
              long position_)
                : error_type(error_type_),
                  message(""),
                  position(position_),
                  input(nullptr),
                  line(-1),
                  file("") {}

        error(ErrorType error_type_,
              std::string message_,
              long position_,
              const std::vector<Char>* input_)
                : error_type(error_type_),
                  message(std::move(message_)),
                  position(position_),
                  input(input_),
                  line(-1),
                  file("") {}

        std::string type() const {
            return kepler::to_string(error_type);
        }

        std::string why() const {
            return message;
        }

       std::string to_string() const {
            std::stringstream ss;
            if(!file.empty()) {
                ss << file;

                if(line != -1) {
                    ss << ":" << std::to_string(line);
                }

                ss << ": ";
            }

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

        void set_input(const std::vector<Char>* input_) {
            input = input_;
        }

        void set_file(const std::string& new_file) {
            file = new_file;
        }

        void set_line(int new_line) {
            line = new_line;
        }

        std::string where() const {
            std::stringstream ss;

            if(input != nullptr && position != -2) {
                ss << "   ";
                ss << uni::utf32to8(std::u32string(input->begin(), input->end()));
                ss << "\n";

                ss << "  ";
                for (long i = -1; i < position - 1; ++i) {
                    ss << "~";
                }
                ss << "^";// << "   " << position;
            }

            return ss.str();
        }
    };
};