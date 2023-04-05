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

namespace kepler {

    /**
     * The intended use is to inherit from it,
     * so the derived class becomes 'position-tagged'.
     *
     * This is useful for keeping track of some (arbitrarily defined) position.
     */
    struct Position {
    private:
        long pos;

    public:

        /**
         * Creates a new position, but the position itself is -1 (uninitialised).
         *
         * @param pos_ The position.
         */
        Position();

        /**
         * Creates a new position.
         *
         * @param pos_ The position.
         */
        explicit Position(long pos_);

        /**
         * Sets the position.
         *
         * @param new_pos The new position.
         */
        void set_position(long new_pos);

        /**
         * Gets the position.
         *
         * @return The position.
         */
        [[nodiscard]] long get_position() const;
    };
};