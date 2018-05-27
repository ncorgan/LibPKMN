/*
 * Copyright (c) 2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "error_internal.hpp"

#include <pkmn-c/breeding/compatibility.h>

#include <pkmn/breeding/compatibility.hpp>

enum pkmn_error pkmn_breeding_are_pokemon_species_compatible(
    const char* p_species1,
    const char* p_species2,
    bool* p_are_pokemon_species_compatible_out
)
{
    PKMN_CHECK_NULL_PARAM(p_species1);
    PKMN_CHECK_NULL_PARAM(p_species2);
    PKMN_CHECK_NULL_PARAM(p_are_pokemon_species_compatible_out);

    PKMN_CPP_TO_C(
        *p_are_pokemon_species_compatible_out = pkmn::breeding::are_pokemon_species_compatible(
                                                    p_species1,
                                                    p_species2
                                                );
    )
}
