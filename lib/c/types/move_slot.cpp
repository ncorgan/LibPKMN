/*
 * Copyright (c) 2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <pkmn-c/types/move_slot.h>

#include "cpp_to_c.hpp"
#include "error_internal.hpp"

enum pkmn_error pkmn_move_slots_free(
    struct pkmn_move_slots* p_move_slots
)
{
    PKMN_CHECK_NULL_PARAM(p_move_slots);

    enum pkmn_error error = PKMN_ERROR_NONE;

    pkmn::c::free_pointer_and_set_to_null(&p_move_slots->p_move_slots);
    p_move_slots->length = 0;

    return error;
}
