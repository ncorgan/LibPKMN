/*
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#ifndef INCLUDED_PKMN_PKSAV_ENUM_MAPS_HPP
#define INCLUDED_PKMN_PKSAV_ENUM_MAPS_HPP

#include <pksav/gen1/pokemon.h>
#include <pksav/common/condition.h>

#include <boost/assign.hpp>
#include <boost/bimap.hpp>

#include <string>

namespace pksav {

// Status conditions

typedef boost::bimap<std::string, pksav_gb_condition_t> gb_condition_bimap_t;
static const gb_condition_bimap_t GB_CONDITION_BIMAP =
boost::assign::list_of<gb_condition_bimap_t::relation>
    ("None",      PKSAV_GB_CONDITION_NONE)
    ("Asleep",    PKSAV_GB_CONDITION_ASLEEP)
    ("Poison",    PKSAV_GB_CONDITION_POISON)
    ("Burn",      PKSAV_GB_CONDITION_BURN)
    ("Frozen",    PKSAV_GB_CONDITION_FROZEN)
    ("Paralysis", PKSAV_GB_CONDITION_PARALYZ)
;

typedef boost::bimap<std::string, pksav_condition_mask_t> condition_mask_bimap_t;
static const condition_mask_bimap_t CONDITION_MASK_BIMAP =
boost::assign::list_of<condition_mask_bimap_t::relation>
    ("None",       PKSAV_CONDITION_NONE)
    ("Asleep",     PKSAV_CONDITION_SLEEP_MASK)
    ("Poison",     PKSAV_CONDITION_POISON)
    ("Burn",       PKSAV_CONDITION_BURN)
    ("Frozen",     PKSAV_CONDITION_FROZEN)
    ("Paralysis",  PKSAV_CONDITION_PARALYZ)
    ("Bad Poison", PKSAV_CONDITION_BAD_POISON)
;

// Misc

typedef boost::bimap<std::string, pksav_gen1_type_t> gen1_type_bimap_t;
static const gen1_type_bimap_t GEN1_TYPE_BIMAP =
boost::assign::list_of<gen1_type_bimap_t::relation>
    ("Normal",   PKSAV_GEN1_TYPE_NORMAL)
    ("Fighting", PKSAV_GEN1_TYPE_FIGHTING)
    ("Flying",   PKSAV_GEN1_TYPE_FLYING)
    ("Poison",   PKSAV_GEN1_TYPE_POISON)
    ("Ground",   PKSAV_GEN1_TYPE_GROUND)
    ("Rock",     PKSAV_GEN1_TYPE_ROCK)
    ("Bug",      PKSAV_GEN1_TYPE_BUG)
    ("Ghost",    PKSAV_GEN1_TYPE_GHOST)
    ("Fire",     PKSAV_GEN1_TYPE_FIRE)
    ("Water",    PKSAV_GEN1_TYPE_WATER)
    ("Grass",    PKSAV_GEN1_TYPE_GRASS)
    ("Electric", PKSAV_GEN1_TYPE_ELECTRIC)
    ("Psychic",  PKSAV_GEN1_TYPE_PSYCHIC)
    ("Ice",      PKSAV_GEN1_TYPE_ICE)
    ("Dragon",   PKSAV_GEN1_TYPE_DRAGON)
;

}

#endif /* INCLUDED_PKMN_PKSAV_ENUM_MAPS_HPP */
