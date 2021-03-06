/*
 * Copyright (c) 2017-2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

%module "PKMN"

%include <ruby/ruby_init.i>
PKMN_RUBY_INIT

// Will be called on import

%{
    #include "private_exports.hpp"

    #include <pkmn/enums/enum_to_string.hpp>
%}

namespace pkmn { namespace priv {
    void initialize_database_connection();
}}

%import <Enums.i>
%import <Database.i>
%import <STL.i>

%include <pkmn/enums/enum_to_string.hpp>

// Attribute Maps
%include <ruby/pkmn_attribute_maps.i>

// Daycare
%include <ruby/pkmn_daycare_helpers.i>
%include <ruby/pkmn_daycare.i>

// Item Slot
%include <ruby/pkmn_item_slot.i>

// Item List
%include <ruby/pkmn_item_list.i>

// Item Bag
%include <ruby/pkmn_item_bag.i>

// Pokédex
%include <ruby/pkmn_pokedex_helpers.i>
%include <ruby/pkmn_pokedex.i>

// Pokémon
%include <ruby/pkmn_pokemon_helpers.i>
%include <ruby/pkmn_pokemon.i>

// Pokémon Box
%include <ruby/pkmn_pokemon_box.i>

// Pokémon Party
%include <ruby/pkmn_pokemon_party.i>

// Pokémon PC
%include <ruby/pkmn_pokemon_pc.i>

// Game Save
%include <ruby/pkmn_game_save_helpers.i>
%include <ruby/pkmn_game_save.i>
