/*
 * Copyright (c) 2015-2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

%include <python/python_init.i>
PKMN_PYTHON_INIT

// Will be called on import

%{
    #include <pkmn/enums/enum_to_string.hpp>

    #include <pkmn/utils/paths.hpp>

#include "private_exports.hpp"
%}

namespace pkmn { namespace priv {
    void initialize_database_connection();
}}

// Convert Doxygen docs to Python docstrings
%include <pkmn_python_docstrings.i>

%import <enums_python.i>
%import <database/database_python.i>
%import <stl_python.i>

// Enums
%include <pkmn/enums/enum_to_string.hpp>

// Attribute Maps
%include <python/pkmn_attribute_maps.i>

// Daycare
%include <python/pkmn_daycare_helpers.i>
%include <python/pkmn_daycare.i>

// Item Slot
%include <python/pkmn_item_slot.i>

// Item List
%include <python/pkmn_item_list.i>

// Item Bag
%include <python/pkmn_item_bag.i>

// Pokédex
%include <python/pkmn_pokedex_helpers.i>
%include <python/pkmn_pokedex.i>

// Pokémon
%include <python/pkmn_pokemon_helpers.i>
%include <python/pkmn_pokemon.i>

// Pokémon Box
%include <python/pkmn_pokemon_box.i>

// Pokémon Party
%include <python/pkmn_pokemon_party.i>

// Pokémon PC
%include <python/pkmn_pokemon_pc.i>

// Game Save
%include <python/pkmn_game_save_helpers.i>
%include <python/pkmn_game_save.i>
