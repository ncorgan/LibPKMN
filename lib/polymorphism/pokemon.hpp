/*
 * Copyright (c) 2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#ifndef INCLUDED_PKMN_POLYMORPHISM_POKEMON_HPP
#define INCLUDED_PKMN_POLYMORPHISM_POKEMON_HPP

#include <pkmn/config.hpp>

#include <pkmn/pokemon.hpp>

#include <pkmn/enums/game.hpp>

#include "pokemon_impl.hpp"

namespace pkmn { namespace polymorphism {

    pokemon::sptr pokemon_to_libpkmn_impl(
        const pokemon::sptr& input_pokemon
    );

    pokemon::sptr pokemon_to_libpkmn_impl_of_game(
        const pokemon::sptr& input_pokemon,
        pkmn::e_game game
    );
}}

#endif /* INCLUDED_PKMN_POLYMORPHISM_POKEMON_HPP */