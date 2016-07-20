/*
 * Copyright (c) 2016 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef PKMN_DATABASE_LISTS_HPP
#define PKMN_DATABASE_LISTS_HPP

#include <pkmn/config.hpp>

#include <string>
#include <vector>

namespace pkmn { namespace database {

    PKMN_API std::vector<std::string> get_ability_list(
        int generation,
        const std::string &language
    );

    PKMN_API std::vector<std::string> get_game_list(
        int generation,
        bool include_previous,
        const std::string &language
    );

    PKMN_API std::vector<std::string> get_item_list(
        const std::string &game,
        const std::string &language
    );

    PKMN_API std::vector<std::string> get_location_list(
        const std::string &game,
        bool whole_generation,
        const std::string &language
    );

    PKMN_API std::vector<std::string> get_move_list(
        const std::string &game,
        const std::string &language
    );

    PKMN_API std::vector<std::string> get_nature_list(
        const std::string &language
    );

    PKMN_API std::vector<std::string> get_pokemon_list(
        int generation,
        bool include_previous,
        const std::string &language
    );

    PKMN_API std::vector<std::string> get_region_list(
        const std::string &language
    );

    PKMN_API std::vector<std::string> get_ribbon_list(
        int generation,
        const std::string &language
    );

    PKMN_API std::vector<std::string> get_super_training_medal_list(
        const std::string &language
    );

    PKMN_API std::vector<std::string> get_type_list(
        const std::string &game,
        const std::string &language
    );
}}

#endif /* PKMN_DATABASE_LISTS_HPP */
