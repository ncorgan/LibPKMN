/*
 * Copyright (c) 2016 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "pokemon_tests_common.hpp"

// Don't create the main in a library
#undef BOOST_TEST_MAIN

#include <boost/assign.hpp>
#include <boost/test/unit_test.hpp>

#include <iostream>

// No database access here
static const std::map<std::string, int> game_generations = boost::assign::map_list_of
    ("Red", 1)
    ("Blue", 1)
    ("Yellow", 1)
    ("Gold", 2)
    ("Silver", 2)
    ("Crystal", 2)
    ("Ruby", 3)
    ("Sapphire", 3)
    ("Emerald", 3)
    ("FireRed", 3)
    ("LeafGreen", 3)
    ("Colosseum", 3)
    ("XD", 3)
    ("Diamond", 4)
    ("Pearl", 4)
    ("Platinum", 4)
    ("HeartGold", 4)
    ("SoulSilver", 4)
    ("Black", 5)
    ("White", 5)
    ("Black 2", 5)
    ("White 2", 5)
    ("X", 6)
    ("Y", 6)
    ("Omega Ruby", 6)
    ("Alpha Sapphire", 6)
;

static const std::vector<std::string> starters = boost::assign::list_of
    ("")("Bulbasaur")("Chikorita")("Treecko")("Turtwig")("Snivy")("Chespin")
;

static const std::vector<std::string> pokemon_with_mega_forms = boost::assign::list_of
    ("")("Venusaur")("Ampharos")("Blaziken")("Lucario")("Audino")("Diancie")
;


namespace pkmntest {

    static void test_invalid_forms(
        const std::string &game
    ) {
        int generation = game_generations.at(game);

        // Make sure Mega forms don't work for Pokémon who were
        // present in the given pre-Generation VI game.
        if(generation < 6) {
            for(int i = 1; i <= generation; ++i) {
                BOOST_CHECK_THROW(
                    (void)pkmn::pokemon::make(
                              pokemon_with_mega_forms.at(i),
                              game,
                              "Mega",
                              5
                          );
                , std::invalid_argument);
            }
        }

        // Make sure forms that didn't appear for Generation I
        // Pokémon until later don't work until the correct
        // generation.
        if(generation >= 1) {
            // Cosplay Pikachu should only work for OR/AS
            static const pkmn::database::pokemon_entry oras_pikachu(
                "Pikachu",
                "Omega Ruby",
                ""
            );
            const std::vector<std::string>& cosplay_forms = oras_pikachu.get_forms();
            for(auto iter = cosplay_forms.begin()+1;
                     iter != cosplay_forms.end();
                     ++iter)
            {
                if(game == "Omega Ruby" or game == "Alpha Sapphire") {
                    (void)pkmn::pokemon::make(
                              "Pikachu",
                              game,
                              *iter,
                              5
                          );
                } else {
                    BOOST_CHECK_THROW(
                        (void)pkmn::pokemon::make(
                                  "Pikachu",
                                  game,
                                  *iter,
                                  5
                              );
                    , std::invalid_argument);
                }
            }
        }
    }

    static void test_invalid_starters(
        const std::string &game
    ) {
        int generation = game_generations.at(game);
        for(int i = (generation+1); i <= 6; ++i) {
            BOOST_CHECK_THROW(
                (void)pkmn::pokemon::make(
                          starters.at(i),
                          game,
                          "",
                          5
                      );
            , std::invalid_argument);
        }
    }

    void test_invalid_pokemon(
        const std::string &game
    ) {
        test_invalid_forms(game);
        test_invalid_starters(game);
    }

}
