/*
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#ifndef INCLUDED_PKMN_CONVERSIONS_GEN3_CONVERSIONS_HPP
#define INCLUDED_PKMN_CONVERSIONS_GEN3_CONVERSIONS_HPP

#include <pksav/gba/pokemon.h>

#include "libpkmgc_includes.hpp"

namespace pkmn { namespace conversions {

    void gba_pc_pokemon_to_gcn(
        const pksav_gba_pc_pokemon_t* from,
        LibPkmGC::GC::Pokemon* to
    );

    void gba_party_pokemon_to_gcn(
        const pksav_gba_party_pokemon_t* from,
        LibPkmGC::GC::Pokemon* to
    );

    void gcn_pokemon_to_gba_pc(
        const LibPkmGC::GC::Pokemon* from,
        pksav_gba_pc_pokemon_t* to
    );

    void gcn_pokemon_to_gba_party(
        const LibPkmGC::GC::Pokemon* from,
        pksav_gba_party_pokemon_t* to
    );

}}

#endif /* INCLUDED_PKMN_CONVERSIONS_GEN3_CONVERSIONS_HPP */