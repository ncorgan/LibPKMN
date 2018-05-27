/*
 * Copyright (c) 2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "cpp_to_c.hpp"
#include "enum_maps.hpp"
#include "error_internal.hpp"

#include "exception_internal.hpp"

#include <pkmn-c/breeding/child_info.h>

#include <pkmn/breeding/child_info.hpp>

enum pkmn_error pkmn_breeding_get_possible_child_species(
    const char* p_mother_species,
    const char* p_father_species,
    const char* p_game,
    struct pkmn_string_list* p_possible_child_species_out
)
{
    PKMN_CHECK_NULL_PARAM(p_mother_species);
    PKMN_CHECK_NULL_PARAM(p_father_species);
    PKMN_CHECK_NULL_PARAM(p_game);
    PKMN_CHECK_NULL_PARAM(p_possible_child_species_out);

    PKMN_CPP_TO_C(
        pkmn::c::string_list_cpp_to_c(
            pkmn::breeding::get_possible_child_species(
                p_mother_species,
                p_father_species,
                p_game
            ),
            p_possible_child_species_out
        );
    )
}

PKMN_C_API enum pkmn_error pkmn_breeding_get_child_moves(
    const struct pkmn_pokemon* p_mother,
    const struct pkmn_pokemon* p_father,
    const char* p_child_species,
    struct pkmn_string_list* p_child_moves_out
)
{
    PKMN_CHECK_NULL_WRAPPER_PARAM(p_mother);
    PKMN_CHECK_NULL_WRAPPER_PARAM(p_father);
    PKMN_CHECK_NULL_PARAM(p_child_species);
    PKMN_CHECK_NULL_PARAM(p_child_moves_out);

    PKMN_CPP_TO_C(
        pkmn::c::string_list_cpp_to_c(
            pkmn::breeding::get_child_moves(
                POKEMON_INTERNAL_RCAST(p_mother->p_internal)->cpp,
                POKEMON_INTERNAL_RCAST(p_father->p_internal)->cpp,
                p_child_species
            ),
            p_child_moves_out
        );
    )
}

enum pkmn_error pkmn_breeding_get_ideal_child_IVs(
    const struct pkmn_pokemon* p_mother,
    const struct pkmn_pokemon* p_father,
    enum pkmn_gender gender,
    int* p_IVs_buffer_out,
    size_t IV_buffer_size,
    size_t* p_actual_num_IVs_out
)
{
    PKMN_CHECK_NULL_WRAPPER_PARAM(p_mother);
    PKMN_CHECK_NULL_WRAPPER_PARAM(p_father);
    PKMN_CHECK_NULL_PARAM(p_IVs_buffer_out);
    // p_actual_num_IVs_out can be NULL

    PKMN_CPP_TO_C(
        const pkmn::c::gender_bimap_t& gender_bimap = pkmn::c::get_gender_bimap();

        pkmn::enforce_value_in_map_keys(
            "Gender",
            gender,
            gender_bimap.right
        );

        pkmn::c::copy_map_to_buffer(
            pkmn::breeding::get_ideal_child_IVs(
                POKEMON_INTERNAL_RCAST(p_mother->p_internal)->cpp,
                POKEMON_INTERNAL_RCAST(p_father->p_internal)->cpp,
                gender_bimap.right.at(gender)
            ),
            pkmn::c::get_stat_bimap(),
            p_IVs_buffer_out,
            IV_buffer_size,
            PKMN_NUM_STATS,
            p_actual_num_IVs_out
        );
    )
}
