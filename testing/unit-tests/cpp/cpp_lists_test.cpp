/*
 * Copyright (c) 2016 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <pkmn/exception.hpp>
#include <pkmn/database/lists.hpp>

#include "pkmn_boost_unit_test.hpp"

#include <algorithm>

static PKMN_INLINE bool string_in_vector(
    const std::vector<std::string> &vec,
    const std::string &str
) {
    return (std::find(vec.begin(), vec.end(), str) != vec.end());
}

BOOST_AUTO_TEST_CASE(ability_list_test) {
    std::vector<std::string> abilities2, abilities3,
                             abilities4, abilities5,
                             abilities6, abilities7;

    BOOST_CHECK_THROW(
        abilities2 = pkmn::database::get_ability_list(2);
    , pkmn::range_error);
    BOOST_CHECK_THROW(
        abilities7 = pkmn::database::get_ability_list(7);
    , pkmn::range_error);

    abilities3 = pkmn::database::get_ability_list(3);
    BOOST_CHECK(not string_in_vector(abilities3, "Adaptability"));

    abilities4 = pkmn::database::get_ability_list(4);
    BOOST_CHECK(string_in_vector(abilities4, "Adaptability"));
    BOOST_CHECK(not string_in_vector(abilities4, "Analytic"));

    abilities5 = pkmn::database::get_ability_list(5);
    BOOST_CHECK(string_in_vector(abilities5, "Analytic"));
    BOOST_CHECK(not string_in_vector(abilities5, "Aerilate"));

    abilities6 = pkmn::database::get_ability_list(6);
    BOOST_CHECK(string_in_vector(abilities6, "Aerilate"));

    BOOST_CHECK(abilities3.size() > 0);
    BOOST_CHECK(abilities3.size() < abilities4.size());
    BOOST_CHECK(abilities4.size() < abilities5.size());
    BOOST_CHECK(abilities5.size() < abilities6.size());
}

BOOST_AUTO_TEST_CASE(game_list_test) {
    std::vector<std::string> games0, games1,
                             games2, games3,
                             games4, games5,
                             games6, games7;

    /*
     * Make sure invalid generations throw an exception.
     */
    BOOST_CHECK_THROW(
        games0 = pkmn::database::get_game_list(0, true);
    , pkmn::range_error);
    BOOST_CHECK_THROW(
        games7 = pkmn::database::get_game_list(7, true);
    , pkmn::range_error);

    /*
     * Generation I
     */
    games1 = pkmn::database::get_game_list(1, false);
    BOOST_CHECK_EQUAL(games1.size(), 3);
    games1 = pkmn::database::get_game_list(1, true);
    BOOST_CHECK_EQUAL(games1.size(), 3);

    /*
     * Generation II
     */
    games2 = pkmn::database::get_game_list(2, false);
    BOOST_CHECK_EQUAL(games2.size(), 3);
    games2 = pkmn::database::get_game_list(2, true);
    BOOST_CHECK_EQUAL(games2.size(), 6);

    /*
     * Generation III
     */
    games3 = pkmn::database::get_game_list(3, false);
    BOOST_CHECK_EQUAL(games3.size(), 7);
    games3 = pkmn::database::get_game_list(3, true);
    BOOST_CHECK_EQUAL(games3.size(), 13);

    /*
     * Generation IV
     */
    games4 = pkmn::database::get_game_list(4, false);
    BOOST_CHECK_EQUAL(games4.size(), 5);
    games4 = pkmn::database::get_game_list(4, true);
    BOOST_CHECK_EQUAL(games4.size(), 18);

    /*
     * Generation V
     */
    games5 = pkmn::database::get_game_list(5, false);
    BOOST_CHECK_EQUAL(games5.size(), 4);
    games5 = pkmn::database::get_game_list(5, true);
    BOOST_CHECK_EQUAL(games5.size(), 22);

    /*
     * Generation VI
     */
    games6 = pkmn::database::get_game_list(6, false);
    BOOST_CHECK_EQUAL(games6.size(), 4);
    games6 = pkmn::database::get_game_list(6, true);
    BOOST_CHECK_EQUAL(games6.size(), 26);
}

BOOST_AUTO_TEST_CASE(item_list_test) {
    /*
     * Make sure invalid games fail.
     */
    std::vector<std::string> items_bad;
    BOOST_CHECK_THROW(
        items_bad = pkmn::database::get_item_list("Not a game");
    , std::invalid_argument);

    /*
     * Generation I
     */
    std::vector<std::string> items_rb = pkmn::database::get_item_list("Red");
    std::vector<std::string> items_y  = pkmn::database::get_item_list("Yellow");
    BOOST_CHECK(items_rb == items_y);

    /*
     * Generation II
     */
    std::vector<std::string> items_gs = pkmn::database::get_item_list("Gold");
    std::vector<std::string> items_c  = pkmn::database::get_item_list("Crystal");
    BOOST_CHECK(items_gs.size() < items_c.size());
    BOOST_CHECK(not string_in_vector(items_gs, "GS Ball"));
    BOOST_CHECK(string_in_vector(items_c, "GS Ball"));
    BOOST_CHECK(not string_in_vector(items_gs, "Black Apricorn"));
    BOOST_CHECK(string_in_vector(items_gs, "Blk Apricorn"));

    /*
     * Generation III
     */
    std::vector<std::string> items_rs   = pkmn::database::get_item_list("Ruby");
    std::vector<std::string> items_e    = pkmn::database::get_item_list("Emerald");
    std::vector<std::string> items_frlg = pkmn::database::get_item_list("FireRed");
    std::vector<std::string> items_colo = pkmn::database::get_item_list("Colosseum");
    std::vector<std::string> items_xd   = pkmn::database::get_item_list("XD");

    BOOST_CHECK(not string_in_vector(items_rs, "Magma Emblem"));
    BOOST_CHECK(string_in_vector(items_e, "Magma Emblem"));
    BOOST_CHECK(not string_in_vector(items_frlg, "Magma Emblem"));
    BOOST_CHECK(not string_in_vector(items_colo, "Magma Emblem"));
    BOOST_CHECK(not string_in_vector(items_xd, "Magma Emblem"));

    BOOST_CHECK(not string_in_vector(items_rs, "Helix Fossil"));
    BOOST_CHECK(not string_in_vector(items_e, "Helix Fossil"));
    BOOST_CHECK(string_in_vector(items_frlg, "Helix Fossil"));
    BOOST_CHECK(not string_in_vector(items_colo, "Helix Fossil"));
    BOOST_CHECK(not string_in_vector(items_xd, "Helix Fossil"));

    BOOST_CHECK(not string_in_vector(items_rs, "Time Flute"));
    BOOST_CHECK(not string_in_vector(items_e, "Time Flute"));
    BOOST_CHECK(not string_in_vector(items_frlg, "Time Flute"));
    BOOST_CHECK(string_in_vector(items_colo, "Time Flute"));
    BOOST_CHECK(not string_in_vector(items_xd, "Time Flute"));

    BOOST_CHECK(not string_in_vector(items_rs, "Battle CD 01"));
    BOOST_CHECK(not string_in_vector(items_e, "Battle CD 01"));
    BOOST_CHECK(not string_in_vector(items_frlg, "Battle CD 01"));
    BOOST_CHECK(not string_in_vector(items_colo, "Battle CD 01"));
    BOOST_CHECK(string_in_vector(items_xd, "Battle CD 01"));

    /*
     * Generation IV
     */
    std::vector<std::string> items_dp   = pkmn::database::get_item_list("Diamond");
    std::vector<std::string> items_p    = pkmn::database::get_item_list("Platinum");
    std::vector<std::string> items_hgss = pkmn::database::get_item_list("HeartGold");

    BOOST_CHECK(not string_in_vector(items_dp, "Griseous Orb"));
    BOOST_CHECK(string_in_vector(items_p, "Griseous Orb"));
    BOOST_CHECK(string_in_vector(items_hgss, "Griseous Orb"));

    BOOST_CHECK(not string_in_vector(items_dp, "Dowsing MCHN"));
    BOOST_CHECK(not string_in_vector(items_p, "Dowsing MCHN"));
    BOOST_CHECK(string_in_vector(items_hgss, "Dowsing MCHN"));

    /*
     * Generation V
     */
    std::vector<std::string> items_bw   = pkmn::database::get_item_list("Black");
    std::vector<std::string> items_b2w2 = pkmn::database::get_item_list("Black 2");

    BOOST_CHECK(not string_in_vector(items_bw, "Colress MCHN"));
    BOOST_CHECK(string_in_vector(items_b2w2, "Colress MCHN"));

    /*
     * Generation VI
     */
    std::vector<std::string> items_xy   = pkmn::database::get_item_list("X");
    std::vector<std::string> items_oras = pkmn::database::get_item_list("Omega Ruby");

    BOOST_CHECK(not string_in_vector(items_xy, "Slowbronite"));
    BOOST_CHECK(string_in_vector(items_oras, "Slowbronite"));
}

BOOST_AUTO_TEST_CASE(location_list_test) {
    std::vector<std::string> locations_bad, locations_gen1,
                             locations_gs, locations_c,
                             locations_rs, locations_e,
                             locations_frlg, locations_colo,
                             locations_xd, locations_dp,
                             locations_pt, locations_hgss,
                             locations_bw, locations_b2w2,
                             locations_xy, locations_oras;

    /*
     * Make sure invalid games fail.
     */
    BOOST_CHECK_THROW(
        locations_bad = pkmn::database::get_location_list("Not a game", true);
    , std::invalid_argument);

    /*
     * Generation I (TODO)
     */
    locations_gen1 = pkmn::database::get_location_list("Red", true);
    /*BOOST_CHECK_GT(locations_gen1.size(), 0);
    BOOST_CHECK(string_in_vector(locations_gen1, "Pallet Town"));
    BOOST_CHECK(string_in_vector(locations_gen1, "Cerulean Cave"));*/

    locations_gen1 = pkmn::database::get_location_list("Red", false);
    /*BOOST_CHECK_GT(locations_gen1.size(), 0);
    BOOST_CHECK(string_in_vector(locations_gen1, "Pallet Town"));
    BOOST_CHECK(string_in_vector(locations_gen1, "Cerulean Cave"));*/

    /*
     * Gold/Silver
     */
    locations_gs = pkmn::database::get_location_list("Silver", true);
    BOOST_CHECK_GT(locations_gs.size(), 0);
    BOOST_CHECK(string_in_vector(locations_gs, "Sprout Tower"));
    BOOST_CHECK(string_in_vector(locations_gs, "Pallet Town"));
    BOOST_CHECK(string_in_vector(locations_gs, "Battle Tower"));

    locations_gs = pkmn::database::get_location_list("Silver", false);
    BOOST_CHECK_GT(locations_gs.size(), 0);
    BOOST_CHECK(string_in_vector(locations_gs, "Sprout Tower"));
    BOOST_CHECK(string_in_vector(locations_gs, "Pallet Town"));
    BOOST_CHECK(not string_in_vector(locations_gs, "Battle Tower"));

    /*
     * Crystal
     */
    locations_c = pkmn::database::get_location_list("Crystal", true);
    BOOST_CHECK_GT(locations_c.size(), 0);
    BOOST_CHECK(string_in_vector(locations_c, "Sprout Tower"));
    BOOST_CHECK(string_in_vector(locations_c, "Pallet Town"));
    BOOST_CHECK(string_in_vector(locations_c, "Battle Tower"));

    locations_c = pkmn::database::get_location_list("Crystal", false);
    BOOST_CHECK_GT(locations_c.size(), 0);
    BOOST_CHECK(string_in_vector(locations_c, "Sprout Tower"));
    BOOST_CHECK(string_in_vector(locations_c, "Pallet Town"));
    BOOST_CHECK(string_in_vector(locations_c, "Battle Tower"));

    /*
     * Ruby/Sapphire
     */
    locations_rs = pkmn::database::get_location_list("Ruby", true);
    BOOST_CHECK_GT(locations_rs.size(), 0);
    BOOST_CHECK(string_in_vector(locations_rs, "New Mauville"));
    BOOST_CHECK(string_in_vector(locations_rs, "Artisan Cave"));
    BOOST_CHECK(string_in_vector(locations_rs, "Pallet Town"));
    BOOST_CHECK(not string_in_vector(locations_rs, "Pyrite Town"));
    BOOST_CHECK(not string_in_vector(locations_rs, "Kaminko's House"));

    locations_rs = pkmn::database::get_location_list("Ruby", false);
    BOOST_CHECK_GT(locations_rs.size(), 0);
    BOOST_CHECK(string_in_vector(locations_rs, "New Mauville"));
    BOOST_CHECK(not string_in_vector(locations_rs, "Artisan Cave"));
    BOOST_CHECK(not string_in_vector(locations_rs, "Pallet Town"));
    BOOST_CHECK(not string_in_vector(locations_rs, "Realgamtwr Dome"));
    BOOST_CHECK(not string_in_vector(locations_rs, "Kaminko's House"));

    /*
     * Emerald
     */
    locations_e = pkmn::database::get_location_list("Emerald", true);
    BOOST_CHECK_GT(locations_e.size(), 0);
    BOOST_CHECK(string_in_vector(locations_e, "New Mauville"));
    BOOST_CHECK(string_in_vector(locations_e, "Artisan Cave"));
    BOOST_CHECK(string_in_vector(locations_e, "Pallet Town"));
    BOOST_CHECK(not string_in_vector(locations_e, "Realgamtwr Dome"));
    BOOST_CHECK(not string_in_vector(locations_e, "Kaminko's House"));

    locations_e = pkmn::database::get_location_list("Emerald", false);
    BOOST_CHECK_GT(locations_e.size(), 0);
    BOOST_CHECK(string_in_vector(locations_e, "New Mauville"));
    BOOST_CHECK(string_in_vector(locations_e, "Artisan Cave"));
    BOOST_CHECK(not string_in_vector(locations_e, "Pallet Town"));
    BOOST_CHECK(not string_in_vector(locations_e, "Realgamtwr Dome"));
    BOOST_CHECK(not string_in_vector(locations_e, "Kaminko's House"));

    /*
     * FireRed/LeafGreen
     */
    locations_frlg = pkmn::database::get_location_list("LeafGreen", true);
    BOOST_CHECK_GT(locations_frlg.size(), 0);
    BOOST_CHECK(string_in_vector(locations_frlg, "New Mauville"));
    BOOST_CHECK(string_in_vector(locations_frlg, "Artisan Cave"));
    BOOST_CHECK(string_in_vector(locations_frlg, "Pallet Town"));
    BOOST_CHECK(not string_in_vector(locations_frlg, "Realgamtwr Dome"));
    BOOST_CHECK(not string_in_vector(locations_frlg, "Kaminko's House"));

    locations_frlg = pkmn::database::get_location_list("LeafGreen", false);
    BOOST_CHECK_GT(locations_frlg.size(), 0);
    BOOST_CHECK(not string_in_vector(locations_frlg, "New Mauville"));
    BOOST_CHECK(not string_in_vector(locations_frlg, "Artisan Cave"));
    BOOST_CHECK(string_in_vector(locations_frlg, "Pallet Town"));
    BOOST_CHECK(not string_in_vector(locations_frlg, "Realgamtwr Dome"));
    BOOST_CHECK(not string_in_vector(locations_frlg, "Kaminko's House"));

    /*
     * Colosseum
     */
    locations_colo = pkmn::database::get_location_list("Colosseum", true);
    BOOST_CHECK_GT(locations_colo.size(), 0);
    BOOST_CHECK(not string_in_vector(locations_colo, "New Mauville"));
    BOOST_CHECK(not string_in_vector(locations_colo, "Artisan Cave"));
    BOOST_CHECK(not string_in_vector(locations_colo, "Pallet Town"));
    BOOST_CHECK(string_in_vector(locations_colo, "Realgamtwr Dome"));
    BOOST_CHECK(string_in_vector(locations_colo, "Kaminko's House"));

    locations_colo = pkmn::database::get_location_list("Colosseum", false);
    BOOST_CHECK_GT(locations_colo.size(), 0);
    BOOST_CHECK(not string_in_vector(locations_colo, "New Mauville"));
    BOOST_CHECK(not string_in_vector(locations_colo, "Artisan Cave"));
    BOOST_CHECK(not string_in_vector(locations_colo, "Pallet Town"));
    BOOST_CHECK(string_in_vector(locations_colo, "Realgamtwr Dome"));
    BOOST_CHECK(not string_in_vector(locations_colo, "Kaminko's House"));

    /*
     * XD
     */
    locations_xd = pkmn::database::get_location_list("XD", true);
    BOOST_CHECK_GT(locations_xd.size(), 0);
    BOOST_CHECK(not string_in_vector(locations_xd, "New Mauville"));
    BOOST_CHECK(not string_in_vector(locations_xd, "Artisan Cave"));
    BOOST_CHECK(not string_in_vector(locations_xd, "Pallet Town"));
    BOOST_CHECK(string_in_vector(locations_xd, "Realgamtwr Dome"));
    BOOST_CHECK(string_in_vector(locations_xd, "Kaminko's House"));

    locations_xd = pkmn::database::get_location_list("XD", false);
    BOOST_CHECK_GT(locations_xd.size(), 0);
    BOOST_CHECK(not string_in_vector(locations_xd, "New Mauville"));
    BOOST_CHECK(not string_in_vector(locations_xd, "Artisan Cave"));
    BOOST_CHECK(not string_in_vector(locations_xd, "Pallet Town"));
    BOOST_CHECK(not string_in_vector(locations_xd, "Realgamtwr Dome"));
    BOOST_CHECK(string_in_vector(locations_xd, "Kaminko's House"));

    /*
     * Diamond/Pearl
     */
    locations_dp = pkmn::database::get_location_list("Diamond", true);
    BOOST_CHECK_GT(locations_dp.size(), 0);
    BOOST_CHECK(string_in_vector(locations_dp, "Route 221"));
    BOOST_CHECK(string_in_vector(locations_dp, "Distortion World"));
    BOOST_CHECK(string_in_vector(locations_dp, "Sinjoh Ruins"));
    BOOST_CHECK(string_in_vector(locations_dp, "PC Tokyo"));

    locations_dp = pkmn::database::get_location_list("Diamond", false);
    BOOST_CHECK_GT(locations_dp.size(), 0);
    BOOST_CHECK(string_in_vector(locations_dp, "Route 221"));
    BOOST_CHECK(not string_in_vector(locations_dp, "Distortion World"));
    BOOST_CHECK(not string_in_vector(locations_dp, "Sinjoh Ruins"));
    BOOST_CHECK(string_in_vector(locations_dp, "PC Tokyo"));

    /*
     * Platinum
     */
    locations_pt = pkmn::database::get_location_list("Platinum", true);
    BOOST_CHECK_GT(locations_pt.size(), 0);
    BOOST_CHECK(string_in_vector(locations_pt, "Route 221"));
    BOOST_CHECK(string_in_vector(locations_pt, "Distortion World"));
    BOOST_CHECK(string_in_vector(locations_pt, "Sinjoh Ruins"));
    BOOST_CHECK(string_in_vector(locations_pt, "PC Tokyo"));

    locations_pt = pkmn::database::get_location_list("Platinum", false);
    BOOST_CHECK_GT(locations_pt.size(), 0);
    BOOST_CHECK(string_in_vector(locations_pt, "Route 221"));
    BOOST_CHECK(string_in_vector(locations_pt, "Distortion World"));
    BOOST_CHECK(not string_in_vector(locations_pt, "Sinjoh Ruins"));
    BOOST_CHECK(string_in_vector(locations_pt, "PC Tokyo"));

    /*
     * HeartGold/SoulSilver
     */
    locations_hgss = pkmn::database::get_location_list("HeartGold", true);
    BOOST_CHECK_GT(locations_hgss.size(), 0);
    BOOST_CHECK(string_in_vector(locations_hgss, "Route 221"));
    BOOST_CHECK(string_in_vector(locations_hgss, "Distortion World"));
    BOOST_CHECK(string_in_vector(locations_hgss, "Sinjoh Ruins"));
    BOOST_CHECK(string_in_vector(locations_hgss, "PC Tokyo"));

    locations_hgss = pkmn::database::get_location_list("HeartGold", false);
    BOOST_CHECK_GT(locations_hgss.size(), 0);
    BOOST_CHECK(not string_in_vector(locations_hgss, "Route 221"));
    BOOST_CHECK(not string_in_vector(locations_hgss, "Distortion World"));
    BOOST_CHECK(string_in_vector(locations_hgss, "Sinjoh Ruins"));
    BOOST_CHECK(string_in_vector(locations_hgss, "PC Tokyo"));

    /*
     * Black/White
     */
    locations_bw = pkmn::database::get_location_list("White", true);
    BOOST_CHECK_GT(locations_bw.size(), 0);
    BOOST_CHECK(string_in_vector(locations_bw, "Cold Storage"));
    BOOST_CHECK(string_in_vector(locations_bw, "PWT"));
    BOOST_CHECK(string_in_vector(locations_bw, "Castelia Sewers"));
    BOOST_CHECK(string_in_vector(locations_bw, "PC Tokyo"));

    locations_bw = pkmn::database::get_location_list("White", false);
    BOOST_CHECK_GT(locations_bw.size(), 0);
    BOOST_CHECK(string_in_vector(locations_bw, "Cold Storage"));
    BOOST_CHECK(not string_in_vector(locations_bw, "PWT"));
    BOOST_CHECK(not string_in_vector(locations_bw, "Castelia Sewers"));
    BOOST_CHECK(string_in_vector(locations_bw, "PC Tokyo"));

    /*
     * Black 2/White 2
     */
    locations_b2w2 = pkmn::database::get_location_list("White 2", true);
    BOOST_CHECK_GT(locations_b2w2.size(), 0);
    BOOST_CHECK(string_in_vector(locations_b2w2, "Cold Storage"));
    BOOST_CHECK(string_in_vector(locations_b2w2, "PWT"));
    BOOST_CHECK(string_in_vector(locations_b2w2, "Castelia Sewers"));
    BOOST_CHECK(string_in_vector(locations_b2w2, "PC Tokyo"));

    locations_b2w2 = pkmn::database::get_location_list("White 2", false);
    BOOST_CHECK_GT(locations_b2w2.size(), 0);
    BOOST_CHECK(not string_in_vector(locations_b2w2, "Cold Storage"));
    BOOST_CHECK(string_in_vector(locations_b2w2, "PWT"));
    BOOST_CHECK(string_in_vector(locations_b2w2, "Castelia Sewers"));
    BOOST_CHECK(string_in_vector(locations_b2w2, "PC Tokyo"));

    /*
     * X/Y
     */
    locations_xy = pkmn::database::get_location_list("X", true);
    BOOST_CHECK_GT(locations_xy.size(), 0);
    BOOST_CHECK(string_in_vector(locations_xy, "Zubat Roost"));
    BOOST_CHECK(string_in_vector(locations_xy, "Route 101"));
    BOOST_CHECK(string_in_vector(locations_xy, "PC Tokyo"));

    locations_xy = pkmn::database::get_location_list("X", false);
    BOOST_CHECK_GT(locations_xy.size(), 0);
    BOOST_CHECK(string_in_vector(locations_xy, "Zubat Roost"));
    BOOST_CHECK(not string_in_vector(locations_xy, "Route 101"));
    BOOST_CHECK(string_in_vector(locations_xy, "PC Tokyo"));

    /*
     * Omega Ruby/Alpha Sapphire
     */
    locations_oras = pkmn::database::get_location_list("Omega Ruby", true);
    BOOST_CHECK_GT(locations_oras.size(), 0);
    BOOST_CHECK(string_in_vector(locations_oras, "Zubat Roost"));
    BOOST_CHECK(string_in_vector(locations_oras, "Route 101"));
    BOOST_CHECK(string_in_vector(locations_oras, "PC Tokyo"));

    locations_oras = pkmn::database::get_location_list("Omega Ruby", false);
    BOOST_CHECK_GT(locations_oras.size(), 0);
    BOOST_CHECK(not string_in_vector(locations_oras, "Zubat Roost"));
    BOOST_CHECK(string_in_vector(locations_oras, "Route 101"));
    BOOST_CHECK(string_in_vector(locations_oras, "PC Tokyo"));
}

BOOST_AUTO_TEST_CASE(move_list_test) {
    std::vector<std::string> moves_bad,  moves_gen1,
                             moves_gen2, moves_gba,
                             moves_colo, moves_xd,
                             moves_gen4, moves_gen5,
                             moves_xy,   moves_oras;

    /*
     * Make sure invalid games fail.
     */
    BOOST_CHECK_THROW(
        moves_bad = pkmn::database::get_type_list("Not a game");
    , std::invalid_argument);

    /*
     * Generation I
     */
    moves_gen1 = pkmn::database::get_move_list("Red");
    BOOST_CHECK_EQUAL(moves_gen1.size(), 165);
    BOOST_CHECK_EQUAL(moves_gen1.front(), "Pound");
    BOOST_CHECK_EQUAL(moves_gen1.back(), "Struggle");

    /*
     * Generation II
     */
    moves_gen2 = pkmn::database::get_move_list("Gold");
    BOOST_CHECK_EQUAL(moves_gen2.size(), 251);
    BOOST_CHECK_EQUAL(moves_gen2.front(), "Pound");
    BOOST_CHECK_EQUAL(moves_gen2.back(), "Beat Up");

    /*
     * Game Boy Advance
     */
    moves_gba = pkmn::database::get_move_list("Sapphire");
    BOOST_CHECK_EQUAL(moves_gba.size(), 354);
    BOOST_CHECK_EQUAL(moves_gba.front(), "Pound");
    BOOST_CHECK_EQUAL(moves_gba.back(), "Psycho Boost");

    /*
     * Colosseum
     */
    moves_colo = pkmn::database::get_move_list("Colosseum");
    BOOST_CHECK_EQUAL(moves_colo.size(), 355);
    BOOST_CHECK_EQUAL(moves_colo.front(), "Pound");
    BOOST_CHECK_EQUAL(moves_colo.back(), "Shadow Rush");

    /*
     * XD
     */
    moves_xd = pkmn::database::get_move_list("XD");
    BOOST_CHECK_EQUAL(moves_xd.size(), 372);
    BOOST_CHECK_EQUAL(moves_xd.front(), "Pound");
    BOOST_CHECK_EQUAL(moves_xd.back(), "Shadow Sky");

    /*
     * Generation IV
     */
    moves_gen4 = pkmn::database::get_move_list("SoulSilver");
    BOOST_CHECK_EQUAL(moves_gen4.size(), 467);
    BOOST_CHECK_EQUAL(moves_gen4.front(), "Pound");
    BOOST_CHECK_EQUAL(moves_gen4.back(), "Shadow Force");

    /*
     * Generation V
     */
    moves_gen5 = pkmn::database::get_move_list("White");
    BOOST_CHECK_EQUAL(moves_gen5.size(), 559);
    BOOST_CHECK_EQUAL(moves_gen5.front(), "Pound");
    BOOST_CHECK_EQUAL(moves_gen5.back(), "Fusion Bolt");

    /*
     * X/Y
     */
    moves_xy = pkmn::database::get_move_list("Y");
    BOOST_CHECK_EQUAL(moves_xy.size(), 617);
    BOOST_CHECK_EQUAL(moves_xy.front(), "Pound");
    BOOST_CHECK_EQUAL(moves_xy.back(), "Light of Ruin");

    /*
     * Omega Ruby/Alpha Sapphire
     */
    moves_oras = pkmn::database::get_move_list("Omega Ruby");
    BOOST_CHECK_EQUAL(moves_oras.size(), 621);
    BOOST_CHECK_EQUAL(moves_oras.front(), "Pound");
    BOOST_CHECK_EQUAL(moves_oras.back(), "Hyperspace Fury");
}

BOOST_AUTO_TEST_CASE(nature_list_test) {
    std::vector<std::string> natures = pkmn::database::get_nature_list();
    BOOST_CHECK_EQUAL(natures.size(), 25);
    BOOST_CHECK_EQUAL(natures.front(), "Hardy");
    BOOST_CHECK_EQUAL(natures.back(), "Quirky");
}

BOOST_AUTO_TEST_CASE(pokemon_list_test) {
    std::vector<std::string> pokemon0, pokemon1,
                             pokemon2, pokemon3,
                             pokemon4, pokemon5,
                             pokemon6, pokemon7;

    BOOST_CHECK_THROW(
        pokemon0 = pkmn::database::get_pokemon_list(0, true);
    , pkmn::range_error);
    BOOST_CHECK_THROW(
        pokemon7 = pkmn::database::get_pokemon_list(7, true);
    , pkmn::range_error);

    /*
     * Generation I
     */
    pokemon1 = pkmn::database::get_pokemon_list(1, true);
    BOOST_CHECK_EQUAL(pokemon1.size(), 151);
    BOOST_CHECK_EQUAL(pokemon1.front(), "Bulbasaur");
    BOOST_CHECK_EQUAL(pokemon1.back(), "Mew");

    pokemon1 = pkmn::database::get_pokemon_list(1, false);
    BOOST_CHECK_EQUAL(pokemon1.size(), 151);
    BOOST_CHECK_EQUAL(pokemon1.front(), "Bulbasaur");
    BOOST_CHECK_EQUAL(pokemon1.back(), "Mew");

    /*
     * Generation II
     */
    pokemon2 = pkmn::database::get_pokemon_list(2, true);
    BOOST_CHECK_EQUAL(pokemon2.size(),  251);
    BOOST_CHECK_EQUAL(pokemon2.front(), "Bulbasaur");
    BOOST_CHECK_EQUAL(pokemon2.back(),  "Celebi");

    pokemon2 = pkmn::database::get_pokemon_list(2, false);
    BOOST_CHECK_EQUAL(pokemon2.size(),  100);
    BOOST_CHECK_EQUAL(pokemon2.front(), "Chikorita");
    BOOST_CHECK_EQUAL(pokemon2.back(),  "Celebi");

    /*
     * Generation III
     */
    pokemon3 = pkmn::database::get_pokemon_list(3, true);
    BOOST_CHECK_EQUAL(pokemon3.size(),  386);
    BOOST_CHECK_EQUAL(pokemon3.front(), "Bulbasaur");
    BOOST_CHECK_EQUAL(pokemon3.back(),  "Deoxys");

    pokemon3 = pkmn::database::get_pokemon_list(3, false);
    BOOST_CHECK_EQUAL(pokemon3.size(),  135);
    BOOST_CHECK_EQUAL(pokemon3.front(), "Treecko");
    BOOST_CHECK_EQUAL(pokemon3.back(),  "Deoxys");

    /*
     * Generation IV
     */
    pokemon4 = pkmn::database::get_pokemon_list(4, true);
    BOOST_CHECK_EQUAL(pokemon4.size(),  493);
    BOOST_CHECK_EQUAL(pokemon4.front(), "Bulbasaur");
    BOOST_CHECK_EQUAL(pokemon4.back(),  "Arceus");

    pokemon4 = pkmn::database::get_pokemon_list(4, false);
    BOOST_CHECK_EQUAL(pokemon4.size(),  107);
    BOOST_CHECK_EQUAL(pokemon4.front(), "Turtwig");
    BOOST_CHECK_EQUAL(pokemon4.back(),  "Arceus");

    /*
     * Generation V
     */
    pokemon5 = pkmn::database::get_pokemon_list(5, true);
    BOOST_CHECK_EQUAL(pokemon5.size(),  649);
    BOOST_CHECK_EQUAL(pokemon5.front(), "Bulbasaur");
    BOOST_CHECK_EQUAL(pokemon5.back(),  "Genesect");

    pokemon5 = pkmn::database::get_pokemon_list(5, false);
    BOOST_CHECK_EQUAL(pokemon5.size(),  156);
    BOOST_CHECK_EQUAL(pokemon5.front(), "Victini");
    BOOST_CHECK_EQUAL(pokemon5.back(),  "Genesect");

    /*
     * Generation VI
     */
    pokemon6 = pkmn::database::get_pokemon_list(6, true);
    BOOST_CHECK_EQUAL(pokemon6.size(),  721);
    BOOST_CHECK_EQUAL(pokemon6.front(), "Bulbasaur");
    BOOST_CHECK_EQUAL(pokemon6.back(),  "Volcanion");

    pokemon6 = pkmn::database::get_pokemon_list(6, false);
    BOOST_CHECK_EQUAL(pokemon6.size(),  72);
    BOOST_CHECK_EQUAL(pokemon6.front(), "Chespin");
    BOOST_CHECK_EQUAL(pokemon6.back(),  "Volcanion");
}

BOOST_AUTO_TEST_CASE(region_list_test) {
    std::vector<std::string> regions = pkmn::database::get_region_list();
    BOOST_CHECK_EQUAL(regions.size(), 7);
    BOOST_CHECK_EQUAL(regions.front(), "Kanto");
    BOOST_CHECK_EQUAL(regions[3], "Orre");
    BOOST_CHECK_EQUAL(regions.back(), "Kalos");
}

BOOST_AUTO_TEST_CASE(ribbon_list_test) {
    // TODO: make sure function checks for bad generation
    //       test good cases
}

BOOST_AUTO_TEST_CASE(super_training_medal_list_test) {
    std::vector<std::string> super_training_medals = \
        pkmn::database::get_super_training_medal_list();

    BOOST_CHECK_EQUAL(super_training_medals.size(), 30);
}

BOOST_AUTO_TEST_CASE(type_list_test) {
    std::vector<std::string> types_bad,  types_gen1,
                             types_gen2, types_gba,
                             types_gcn,  types_gen4,
                             types_gen5, types_gen6;

    /*
     * Make sure invalid games fail.
     */
    BOOST_CHECK_THROW(
        types_bad = pkmn::database::get_type_list("Not a game");
    , std::invalid_argument);

    /*
     * Generation I
     */
    types_gen1 = pkmn::database::get_type_list("Red");

    BOOST_CHECK_EQUAL(types_gen1.size(), 15);
    BOOST_CHECK(not string_in_vector(types_gen1, "Dark"));
    BOOST_CHECK(not string_in_vector(types_gen1, "Steel"));
    BOOST_CHECK(not string_in_vector(types_gen1, "???"));
    BOOST_CHECK(not string_in_vector(types_gen1, "Shadow"));
    BOOST_CHECK(not string_in_vector(types_gen1, "Fairy"));

    /*
     * Generation II
     */
    types_gen2 = pkmn::database::get_type_list("Silver");
    BOOST_CHECK_EQUAL(types_gen2.size(), 18);
    BOOST_CHECK(string_in_vector(types_gen2, "Dark"));
    BOOST_CHECK(string_in_vector(types_gen2, "Steel"));
    BOOST_CHECK(string_in_vector(types_gen2, "???"));
    BOOST_CHECK(not string_in_vector(types_gen2, "Shadow"));
    BOOST_CHECK(not string_in_vector(types_gen2, "Fairy"));

    /*
     * Game Boy Advance
     */
    types_gba = pkmn::database::get_type_list("Emerald");
    BOOST_CHECK_EQUAL(types_gba.size(), 18);
    BOOST_CHECK(string_in_vector(types_gba, "Dark"));
    BOOST_CHECK(string_in_vector(types_gba, "Steel"));
    BOOST_CHECK(string_in_vector(types_gba, "???"));
    BOOST_CHECK(not string_in_vector(types_gba, "Shadow"));
    BOOST_CHECK(not string_in_vector(types_gba, "Fairy"));

    /*
     * Gamecube
     */
    types_gcn = pkmn::database::get_type_list("XD");
    BOOST_CHECK_EQUAL(types_gcn.size(), 19);
    BOOST_CHECK(string_in_vector(types_gcn, "Dark"));
    BOOST_CHECK(string_in_vector(types_gcn, "Steel"));
    BOOST_CHECK(string_in_vector(types_gcn, "???"));
    BOOST_CHECK(string_in_vector(types_gcn, "Shadow"));
    BOOST_CHECK(not string_in_vector(types_gcn, "Fairy"));

    /*
     * Generation IV
     */
    types_gen4 = pkmn::database::get_type_list("Platinum");
    BOOST_CHECK_EQUAL(types_gen4.size(), 18);
    BOOST_CHECK(string_in_vector(types_gen4, "Dark"));
    BOOST_CHECK(string_in_vector(types_gen4, "Steel"));
    BOOST_CHECK(string_in_vector(types_gen4, "???"));
    BOOST_CHECK(not string_in_vector(types_gen4, "Shadow"));
    BOOST_CHECK(not string_in_vector(types_gen4, "Fairy"));

    /*
     * Generation V
     */
    types_gen5 = pkmn::database::get_type_list("White 2");
    BOOST_CHECK_EQUAL(types_gen5.size(), 17);
    BOOST_CHECK(string_in_vector(types_gen5, "Dark"));
    BOOST_CHECK(string_in_vector(types_gen5, "Steel"));
    BOOST_CHECK(not string_in_vector(types_gen5, "???"));
    BOOST_CHECK(not string_in_vector(types_gen5, "Shadow"));
    BOOST_CHECK(not string_in_vector(types_gen5, "Fairy"));

    /*
     * Generation VI
     */
    types_gen6 = pkmn::database::get_type_list("X");
    BOOST_CHECK_EQUAL(types_gen6.size(), 18);
    BOOST_CHECK(string_in_vector(types_gen6, "Dark"));
    BOOST_CHECK(string_in_vector(types_gen6, "Steel"));
    BOOST_CHECK(not string_in_vector(types_gen6, "???"));
    BOOST_CHECK(not string_in_vector(types_gen6, "Shadow"));
    BOOST_CHECK(string_in_vector(types_gen6, "Fairy"));
}
