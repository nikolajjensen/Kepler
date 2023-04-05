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

    /**
     * Represents an error in Kepler.
     *
     * An Error may represent syntax errors, runtime errors, or
     * other errors associated with running the application.
     */
    class Error : public std::exception {
    public:
        ErrorType error_type;
        std::string message;
        long position;
        const std::vector<Char>* input;
        int line;
        std::string file;

        /**
         * Creates a new error with the given type and message.
         *
         * @param error_type The type of error.
         * @param message The error message.
         */
        Error(ErrorType error_type_,
              std::string message_ = "")
                : error_type(error_type_),
                  message(std::move(message_)),
                  position(-2),
                  input(nullptr),
                  line(-1),
                  file("") {}

        /**
         * Creates a new error with the given type, message, and position.
         *
         * @param error_type The type of error.
         * @param message The error message.
         * @param position_ The position of the Error.
         */
        Error(ErrorType error_type_,
              std::string message_,
              long position_)
                : error_type(error_type_),
                  message(std::move(message_)),
                  position(position_),
                  input(nullptr),
                  line(-1),
                  file("") {}

        /**
         * Creates a new error with the given and position.
         *
         * @param error_type The type of error.
         * @param position_ The position of the Error.
         */
        Error(ErrorType error_type_,
              long position_)
                : error_type(error_type_),
                  message(""),
                  position(position_),
                  input(nullptr),
                  line(-1),
                  file("") {}

        /**
         * Creates a new error with the given type, message, position, and input.
         *
         * The input is used to generate a string representation of the error.
         *
         * @param error_type The type of error.
         * @param message The error message.
         * @param position_ The position of the Error.
         * @param input_ The input in which the Error occurred.
         */
        Error(ErrorType error_type_,
              std::string message_,
              long position_,
              const std::vector<Char>* input_)
                : error_type(error_type_),
                  message(std::move(message_)),
                  position(position_),
                  input(input_),
                  line(-1),
                  file("") {}

        /**
         * Returns a string representation of the type of the Error.
         */
        [[nodiscard]] std::string type() const {
            return kepler::to_string(error_type);
        }

        /**
         * Returns the error message.
         */
        [[nodiscard]] std::string why() const {
            return message;
        }

        /**
         * Returns a string representation of the Error.
         *
         * The string representation will always include the type.
         * If a message is available, it will be given.
         * If a position is available, it will be given.
         * If input and position are available, the error is shown in the input.
         * If a file is available, it will shown.
         * If file and line number are available, they will be shown in the input.
         */
        [[nodiscard]] std::string to_string() const {
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

        /**
         * Sets the input associated with the Error.
         * @param input_ The input to associate with the Error.
         */
        void set_input(const std::vector<Char>* input_) {
            input = input_;
        }

        /**
         * Sets the file associated with the Error.
         * @param new_file The path of the file to associate with the Error.
         */
        void set_file(const std::string& new_file) {
            file = new_file;
        }

        /**
         * Sets the line number associated with the Error.
         * @param new_line The line number to associate with the Error.
         */
        void set_line(int new_line) {
            line = new_line;
        }

        /**
         * Returns a string representation of where
         * the error occurred within the input.
         */
        [[nodiscard]] std::string where() const {
            std::stringstream ss;

            if(input != nullptr && position != -2) {
                ss << "   ";
                ss << uni::utf32to8(String(input->begin(), input->end()));
                ss << "\n";

                ss << "  ";
                for (long i = -1; i < position - 1; ++i) {
                    ss << "~";
                }
                ss << "^";
            }

            return ss.str();
        }
    };
};