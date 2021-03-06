/*
 * Copyright (c) 2017-2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#ifndef POKEMON_TEST_H
#define POKEMON_TEST_H

#include <pkmn-c/pokemon.h>

typedef struct
{
    enum pkmn_ball valid_ball;
    enum pkmn_ball* p_invalid_balls;

    enum pkmn_item valid_item;
    enum pkmn_item* p_invalid_items;

    char* expected_original_location;
    char** valid_locations;
    char** invalid_locations;

    enum pkmn_move* p_moves;
    enum pkmn_move* p_invalid_moves;

    enum pkmn_game* valid_original_games;
    enum pkmn_game* invalid_original_games;
} pkmn_test_values_t;

void pokemon_test_common(
    const struct pkmn_pokemon* p_pokemon,
    pkmn_test_values_t* test_values
);

// Generation I tests

void red_pokemon_test();
void blue_pokemon_test();
void yellow_pokemon_test();

// Generation II tests

void gold_pokemon_test();
void silver_pokemon_test();
void crystal_pokemon_test();

// Game Boy Advance tests

void ruby_pokemon_test();
void sapphire_pokemon_test();
void emerald_pokemon_test();
void firered_pokemon_test();
void leafgreen_pokemon_test();

// Gamecube tests

void colosseum_pokemon_test();
void xd_pokemon_test();

// I/O

void red_pk1_test();
void blue_pk1_test();
void yellow_pk1_test();

void gold_pk2_test();
void silver_pk2_test();
void crystal_pk2_test();

void ruby_3gpkm_test();
void ruby_pk3_test();
void sapphire_3gpkm_test();
void sapphire_pk3_test();
void emerald_3gpkm_test();
void emerald_pk3_test();
void firered_3gpkm_test();
void firered_pk3_test();
void leafgreen_3gpkm_test();
void leafgreen_pk3_test();

void colosseum_ck3_test();
void xd_xk3_test();

void test_outside_3gpkm();

// Form

void red_form_test();
void blue_form_test();
void yellow_form_test();
void gold_form_test();
void silver_form_test();
void crystal_form_test();
void ruby_form_test();
void sapphire_form_test();
void emerald_form_test();
void firered_form_test();
void leafgreen_form_test();
void colosseum_form_test();
void xd_form_test();

// Gender

void gold_gender_test();
void silver_gender_test();
void crystal_gender_test();
void ruby_gender_test();
void sapphire_gender_test();
void emerald_gender_test();
void firered_gender_test();
void leafgreen_gender_test();
void colosseum_gender_test();
void xd_gender_test();

// Unown

void gold_unown_test();
void silver_unown_test();
void crystal_unown_test();
void ruby_unown_test();
void sapphire_unown_test();
void emerald_unown_test();
void firered_unown_test();
void leafgreen_unown_test();
void colosseum_unown_test();
void xd_unown_test();

// Conversions

void gen1_conversions_test();
void gen2_conversions_test();
void gba_conversions_test();
void gcn_conversions_test();

#endif /* POKEMON_TEST_H */
