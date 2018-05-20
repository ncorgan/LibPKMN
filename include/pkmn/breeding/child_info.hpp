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

#include <string>
#include <vector>

namespace pkmn { namespace breeding {

    PKMN_API std::vector<std::string> get_possible_child_species(
        const std::string& mother_species,
        const std::string& father_species,
        const std::string& game
    );

#ifndef SWIG

    PKMN_API std::vector<std::string> get_child_moves(
        const pkmn::pokemon::sptr& mother,
        const pkmn::pokemon::sptr& father,
        const std::string& child_species
    );

#endif

}}

#endif /* PKMN_BREEDING_CHILD_INFO_HPP */