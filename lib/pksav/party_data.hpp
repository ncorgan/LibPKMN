/*
 * Copyright (c) 2016 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#ifndef INCLUDED_PKMN_PKSAV_PARTY_DATA_HPP
#define INCLUDED_PKMN_PKSAV_PARTY_DATA_HPP

#include <pksav/gen1/pokemon.h>
#include <pksav/gen2/pokemon.h>

namespace pksav {

    void gen1_pc_pokemon_to_party_data(
        const pksav_gen1_pc_pokemon_t* pc,
        pksav_gen1_pokemon_party_data_t* party_data_out
    );

    void gen2_pc_pokemon_to_party_data(
        const pksav_gen2_pc_pokemon_t* pc,
        pksav_gen2_pokemon_party_data_t* party_data_out
    );

}

#endif /* INCLUDED_PKMN_PKSAV_PARTY_DATA_HPP */