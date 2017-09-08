/*
 * Copyright (c) 2016-2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef PKMN_MOVE_SLOT_HPP
#define PKMN_MOVE_SLOT_HPP

#include <pkmn/config.hpp>

#include <string>
#include <vector>

namespace pkmn {

    /*!
     * @brief A slot in an move list.
     *
     * A move list is made up of a list of move slots, each of which contains
     * a unique move type and the PP of that move in the given pocket. This
     * struct represents a single one of those slots.
     */
    struct move_slot {
        /*!
         * @brief Default constructor.
         *
         * The move entry represents an invalid move.
         */
        PKMN_INLINE move_slot():
            move("None"),
            pp(0) {}

        /*!
         * @brief Constructor that takes in copies of each member.
         *
         * This calls the copy constructor for the move entry.
         *
         * \param move_name Move name
         * \param move_pp Move's current PP
         */
        PKMN_INLINE move_slot(
            const std::string& move_name,
            int move_pp
        ): move(move_name),
           pp(move_pp) {}

#ifndef SWIG
        /*!
         * @brief Constructor that takes in references to each member.
         *
         * This calls the move constructor for the move entry.
         *
         * \param move_name Move entry
         * \param move_pp Move's current PP
         */
        PKMN_INLINE move_slot(
            std::string&& move_name,
            int move_pp 
        ): move(std::move(move_name)),
           pp(std::move(move_pp)) {}
#endif

        /*!
         * @brief The move in the given slot.
         */
        std::string move;
        /*!
         * @brief Move's current PP is in the given slot.
         */
        int pp;
    };

    #ifndef SWIG
    /*!
     * @brief Equality check between two move slots.
     */
    PKMN_INLINE bool operator==(
        const move_slot &lhs,
        const move_slot &rhs
    ) {
        return (lhs.move == rhs.move) and \
               (lhs.pp == rhs.pp);
    }

    /*!
     * @brief Inequality check between two move slots.
     */
    PKMN_INLINE bool operator!=(
        const move_slot &lhs,
        const move_slot &rhs
    ) {
        return (lhs.move != rhs.move) or \
               (lhs.pp != rhs.pp);
    }
    #endif /* SWIG */

    /*!
     * @brief List of move slots.
     *
     * This is effectively a vector representation of an move list.
     */
    typedef std::vector<move_slot> move_slots_t;
}

#endif /* PKMN_MOVE_SLOT_HPP */