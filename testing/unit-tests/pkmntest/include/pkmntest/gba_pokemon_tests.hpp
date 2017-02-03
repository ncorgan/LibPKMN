/*
 * Copyright (c) 2016-2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#ifndef GBA_POKEMON_TESTS_HPP
#define GBA_POKEMON_TESTS_HPP

#include <pkmntest/config.hpp>

#include <pkmn/pokemon.hpp>

namespace pkmntest {

    PKMNTEST_API void gba_invalid_pokemon_test(
        const std::string &game
    );

    PKMNTEST_API void gba_unown_form_test(
        const std::string &game
    );

    PKMNTEST_API void gba_pokemon_test(
        pkmn::pokemon::sptr pokemon,
        const std::string &species,
        const std::string &game
    );
}

#endif /* GBA_POKEMON_TESTS_HPP */
