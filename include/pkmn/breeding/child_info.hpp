/*
 * Copyright (c) 2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef PKMN_BREEDING_CHILD_INFO_HPP
#define PKMN_BREEDING_CHILD_INFO_HPP

#include <pkmn/config.hpp>
#include <pkmn/pokemon.hpp>

#include <pkmn/enums/game.hpp>
#include <pkmn/enums/gender.hpp>
#include <pkmn/enums/move.hpp>
#include <pkmn/enums/species.hpp>
#include <pkmn/enums/stat.hpp>

#include <map>
#include <vector>

namespace pkmn { namespace breeding {

    PKMN_API std::vector<pkmn::e_species> get_possible_child_species(
        pkmn::e_species mother_species,
        pkmn::e_species father_species,
        pkmn::e_game game
    );

#ifndef SWIG

    PKMN_API std::vector<pkmn::e_move> get_child_moves(
        const pkmn::pokemon::sptr& mother,
        const pkmn::pokemon::sptr& father,
        pkmn::e_species child_species
    );

    PKMN_API std::map<pkmn::e_stat, int> get_ideal_child_IVs(
        const pkmn::pokemon::sptr& mother,
        const pkmn::pokemon::sptr& father,
        pkmn::e_gender child_gender
    );

#endif

}}

#endif /* PKMN_BREEDING_CHILD_INFO_HPP */
