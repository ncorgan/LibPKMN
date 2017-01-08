/*
 * Copyright (c) 2016 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "pokemon_tests_common.h"

#include <pkmntest-c/gen1_pokemon_tests.h>

#include <pkmn-c/pokemon.h>
#include <pkmn-c/database/move_entry.h>

#include <unity.h>

#include <ctype.h>
#include <string.h>

#define STRBUFFER_LEN 1024

void pkmntest_gen1_invalid_pokemon_test(
    const char* game
) {
    test_invalid_pokemon(game);
}

void pkmntest_gen1_friendship_test(
    const char* game
) {
    pkmn_error_t error = PKMN_ERROR_NONE;
    pkmn_pokemon_handle_t pokemon = NULL;
    int friendship = 0;

    error = pkmn_pokemon_make(
                &pokemon,
                "Pikachu",
                game,
                "",
                5
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);

    error = pkmn_pokemon_set_friendship(
                pokemon,
                123
            );
    if(!strcmp(game, "Yellow")) {
        TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
        error = pkmn_pokemon_get_friendship(
                    pokemon,
                    &friendship
                );
        TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
        TEST_ASSERT_EQUAL(friendship, 123);
    } else {
        TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);
        error = pkmn_pokemon_get_friendship(
                    pokemon,
                    &friendship
                );
        TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);
    }

    error = pkmn_pokemon_free(&pokemon);
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    TEST_ASSERT_NULL(pokemon);

    // For Yellow, also check a non-Pikachu
    if(!strcmp(game, "Yellow")) {
        error = pkmn_pokemon_make(
                    &pokemon,
                    "Mewtwo",
                    game,
                    "",
                    70
                );
        TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);

        error = pkmn_pokemon_set_friendship(
                    pokemon,
                    123
                );
        TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);

        error = pkmn_pokemon_get_friendship(
                    pokemon,
                    &friendship
                );
        TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);

        error = pkmn_pokemon_free(&pokemon);
        TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
        TEST_ASSERT_NULL(pokemon);
    }
}

typedef pkmn_error_t (*pokemon_stat_fcn_t)(pkmn_pokemon_handle_t, pkmn_string_list_t*);

static void gen1_pokemon_check_stat_map(
    pkmn_pokemon_handle_t pokemon,
    pokemon_stat_fcn_t stat_fcn
) {
    pkmn_error_t error = PKMN_ERROR_NONE;
    pkmn_string_list_t stat_names;

    error = stat_fcn(
                pokemon,
                &stat_names
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);

    TEST_ASSERT_EQUAL(stat_names.length, 5);
    TEST_ASSERT_EQUAL_STRING(stat_names.strings[0], "Attack");
    TEST_ASSERT_EQUAL_STRING(stat_names.strings[1], "Defense");
    TEST_ASSERT_EQUAL_STRING(stat_names.strings[2], "HP");
    TEST_ASSERT_EQUAL_STRING(stat_names.strings[3], "Special");
    TEST_ASSERT_EQUAL_STRING(stat_names.strings[4], "Speed");

    error = pkmn_string_list_free(&stat_names);
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
}

void pkmntest_gen1_pokemon_test(
    pkmn_pokemon_handle_t pokemon,
    const char* species,
    const char* game
) {
    pkmn_error_t error = PKMN_ERROR_NONE;
    pkmn_database_pokemon_entry_t database_entry;
    char strbuffer[STRBUFFER_LEN] = {0};
    pkmn_gender_t gender = PKMN_GENDERLESS;
    uint32_t trainer_id = 0;
    uint16_t trainer_id_part = 0;

    error = pkmn_pokemon_get_database_entry(
                pokemon,
                &database_entry
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    TEST_ASSERT_EQUAL_STRING(database_entry.name, species);
    TEST_ASSERT_EQUAL_STRING(database_entry.game, game);
    TEST_ASSERT_EQUAL_STRING(database_entry.form, "Standard");

    /*
     * Check starting values, and confirm that we can't query values
     * that didn't exist in Generation I.
     */
    error = pkmn_pokemon_get_species(
                pokemon,
                strbuffer,
                sizeof(strbuffer)
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    TEST_ASSERT_EQUAL_STRING(strbuffer, species);

    error = pkmn_pokemon_get_game(
                pokemon,
                strbuffer,
                sizeof(strbuffer)
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    TEST_ASSERT_EQUAL_STRING(strbuffer, game);

    char expected_nickname[11] = {0};
    for(size_t i = 0; i < strlen(species); ++i) {
        expected_nickname[i] = toupper(species[i]);
    }
    error = pkmn_pokemon_get_nickname(
                pokemon,
                strbuffer,
                sizeof(strbuffer)
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    TEST_ASSERT_EQUAL_STRING(strbuffer, expected_nickname);

    bool shiny = false;
    error = pkmn_pokemon_is_shiny(
                pokemon,
                &shiny
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);

    error = pkmn_pokemon_get_held_item(
                pokemon,
                strbuffer,
                sizeof(strbuffer)
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);

    error = pkmn_pokemon_get_trainer_name(
                pokemon,
                strbuffer,
                sizeof(strbuffer)
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    TEST_ASSERT_EQUAL_STRING(strbuffer, LIBPKMN_OT_NAME);


    error = pkmn_pokemon_get_trainer_public_id(
                pokemon,
                &trainer_id_part
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    TEST_ASSERT_EQUAL(trainer_id_part, (LIBPKMN_OT_ID & 0xFFFF));
    error = pkmn_pokemon_get_trainer_secret_id(
                pokemon,
                &trainer_id_part
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);
    error = pkmn_pokemon_get_trainer_id(
                pokemon,
                &trainer_id
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    TEST_ASSERT_EQUAL(trainer_id, (LIBPKMN_OT_ID & 0xFFFF));

    error = pkmn_pokemon_get_trainer_gender(
                pokemon,
                &gender
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    TEST_ASSERT_EQUAL(gender, PKMN_MALE);

    int friendship = 0;
    error = pkmn_pokemon_get_friendship(
                pokemon,
                &friendship
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);

    error = pkmn_pokemon_get_ability(
                pokemon,
                strbuffer,
                sizeof(strbuffer)
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);

    error = pkmn_pokemon_get_ball(
                pokemon,
                strbuffer,
                sizeof(strbuffer)
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);

    int level_met = 0;
    error = pkmn_pokemon_get_level_met(
                pokemon,
                &level_met
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);

    error = pkmn_pokemon_get_location_met(
                pokemon,
                false,
                strbuffer,
                sizeof(strbuffer)
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);

    error = pkmn_pokemon_get_location_met(
                pokemon,
                true,
                strbuffer,
                sizeof(strbuffer)
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);

    error = pkmn_pokemon_get_original_game(
                pokemon,
                strbuffer,
                sizeof(strbuffer)
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);

    uint32_t personality = 0;
    error = pkmn_pokemon_get_personality(
                pokemon,
                &personality
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);

    int experience_from_database = 0;
    int experience_from_pokemon = 0;
    error = pkmn_database_pokemon_entry_experience_at_level(
                &database_entry,
                30,
                &experience_from_database
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    TEST_ASSERT(experience_from_database > 0);
    error = pkmn_pokemon_get_experience(
                pokemon,
                &experience_from_pokemon
            );
    TEST_ASSERT_EQUAL(experience_from_database, experience_from_pokemon);

    int level = 0;
    error = pkmn_pokemon_get_level(
                pokemon,
                &level
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    TEST_ASSERT_EQUAL(level, 30);

    pkmn_string_list_t marking_names;
    error = pkmn_pokemon_get_marking_names(
                pokemon,
                &marking_names
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);

    bool has_marking = false;
    error = pkmn_pokemon_has_marking(
                pokemon,
                "Circle",
                &has_marking
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);

    pkmn_string_list_t ribbon_names;
    error = pkmn_pokemon_get_ribbon_names(
                pokemon,
                &ribbon_names
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);

    bool has_ribbon = false;
    error = pkmn_pokemon_has_ribbon(
                pokemon,
                "Cool",
                &has_ribbon
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);

    pkmn_string_list_t contest_stat_names;
    error = pkmn_pokemon_get_contest_stat_names(
                pokemon,
                &contest_stat_names
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);

    int contest_stat = 0;
    error = pkmn_pokemon_get_contest_stat(
                pokemon,
                "Cool",
                &contest_stat
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);

    pkmn_move_slots_t move_slots;
    error = pkmn_pokemon_get_moves(
                pokemon,
                &move_slots
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    TEST_ASSERT_EQUAL(move_slots.length, 4);

    for(size_t i = 0; i < move_slots.length; ++i) {
        TEST_ASSERT_EQUAL_STRING(move_slots.move_slots[i].move, "None");
        TEST_ASSERT_EQUAL(move_slots.move_slots[i].pp, 0);
    }

    gen1_pokemon_check_stat_map(
        pokemon,
        pkmn_pokemon_get_EV_names
    );
    gen1_pokemon_check_stat_map(
        pokemon,
        pkmn_pokemon_get_IV_names
    );
    gen1_pokemon_check_stat_map(
        pokemon,
        pkmn_pokemon_get_stat_names
    );

    /*
     * Make sure the getters and setters agree. Also make sure it fails when
     * expected.
     */

    error = pkmn_pokemon_set_nickname(
                pokemon,
                ""
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_INVALID_ARGUMENT);
    error = pkmn_pokemon_set_nickname(
                pokemon,
                "Too long nickname"
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_INVALID_ARGUMENT);
    error = pkmn_pokemon_set_nickname(
                pokemon,
                "foobarbaz"
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    error = pkmn_pokemon_get_nickname(
                pokemon,
                strbuffer,
                sizeof(strbuffer)
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    TEST_ASSERT_EQUAL_STRING(strbuffer, "foobarbaz");

    error = pkmn_pokemon_set_shininess(
                pokemon,
                true
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);
    error = pkmn_pokemon_set_shininess(
                pokemon,
                false
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);

    error = pkmn_pokemon_set_held_item(
                pokemon,
                "Potion"
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);

    error = pkmn_pokemon_set_trainer_name(
                pokemon,
                ""
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_INVALID_ARGUMENT);
    error = pkmn_pokemon_set_trainer_name(
                pokemon,
                "Too long trainer name"
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_INVALID_ARGUMENT);
    error = pkmn_pokemon_set_trainer_name(
                pokemon,
                "foobar"
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    error = pkmn_pokemon_get_trainer_name(
                pokemon,
                strbuffer,
                sizeof(strbuffer)
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    TEST_ASSERT_EQUAL_STRING(strbuffer, "foobar");

    error = pkmn_pokemon_set_trainer_id(
                pokemon,
                10001
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    error = pkmn_pokemon_get_trainer_id(
                pokemon,
                &trainer_id
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    TEST_ASSERT_EQUAL(trainer_id, 10001);
    error = pkmn_pokemon_get_trainer_public_id(
                pokemon,
                &trainer_id_part
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    TEST_ASSERT_EQUAL(trainer_id_part, 10001);

    error = pkmn_pokemon_set_trainer_secret_id(
                pokemon,
                54321
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);
    TEST_ASSERT_EQUAL(trainer_id, 10001);

    error = pkmn_pokemon_set_trainer_gender(
                pokemon,
                PKMN_MALE
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);
    error = pkmn_pokemon_set_friendship(
                pokemon,
                123
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);
    error = pkmn_pokemon_set_ability(
                pokemon,
                ""
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);
    error = pkmn_pokemon_set_ball(
                pokemon,
                "Great Ball"
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);
    error = pkmn_pokemon_set_level_met(
                pokemon,
                78
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);
    error = pkmn_pokemon_set_location_met(
                pokemon,
                "Victory Road",
                false
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);
    error = pkmn_pokemon_set_location_met(
                pokemon,
                "Victory Road",
                true
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);
    error = pkmn_pokemon_set_original_game(
                pokemon,
                "Blue"
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);
    error = pkmn_pokemon_set_marking(
                pokemon,
                "Circle",
                true
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);
    error = pkmn_pokemon_set_ribbon(
                pokemon,
                "Cool",
                false
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR);

    int experience = 0;
    error = pkmn_pokemon_set_experience(
                pokemon,
                12345
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    error = pkmn_pokemon_get_experience(
                pokemon,
                &experience
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    TEST_ASSERT_EQUAL(experience, 12345);

    error = pkmn_pokemon_set_level(
                pokemon,
                45
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    error = pkmn_pokemon_get_level(
                pokemon,
                &level
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    TEST_ASSERT_EQUAL(level, 45);

    error = pkmn_pokemon_set_move(
                pokemon,
                "Ember",
                -1
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_RANGE_ERROR);
    error = pkmn_pokemon_set_move(
                pokemon,
                "Synthesis",
                0
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_INVALID_ARGUMENT);

    error = pkmn_pokemon_get_moves(
                pokemon,
                &move_slots
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    TEST_ASSERT_EQUAL(move_slots.length, 4);
    TEST_ASSERT_EQUAL_STRING(move_slots.move_slots[0].move, "None");
    error = pkmn_move_slots_free(&move_slots);
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);

    static const char* moves[] = {
        "Ember", "Flamethrower", "Slash", "Fire Blast"
    };

    for(size_t i = 0; i < 4; ++i) {
        error = pkmn_pokemon_set_move(
                    pokemon,
                    moves[i],
                    i
                );
        TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    }

    error = pkmn_pokemon_get_moves(
                pokemon,
                &move_slots
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    TEST_ASSERT_EQUAL(move_slots.length, 4);

    pkmn_database_move_entry_t move_entry;
    for(size_t i = 0; i < 4; ++i) {
        TEST_ASSERT_EQUAL_STRING(move_slots.move_slots[i].move, moves[i]);

        error = pkmn_database_get_move_entry(
                    move_slots.move_slots[i].move,
                    game,
                    &move_entry
                );
        TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);

        TEST_ASSERT_EQUAL(move_slots.move_slots[i].pp, move_entry.pp[0]);

        error = pkmn_database_move_entry_free(&move_entry);
        TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    }

    int EV = 0;
    error = pkmn_pokemon_set_EV(
                pokemon,
                "Not a stat",
                1
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_INVALID_ARGUMENT);
    error = pkmn_pokemon_set_EV(
                pokemon,
                "Attack",
                65536
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_RANGE_ERROR);
    error = pkmn_pokemon_set_EV(
                pokemon,
                "Attack",
                12345
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    error = pkmn_pokemon_get_EV(
                pokemon,
                "Not a stat",
                &EV
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_INVALID_ARGUMENT);
    error = pkmn_pokemon_get_EV(
                pokemon,
                "Attack",
                &EV
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    TEST_ASSERT_EQUAL(EV, 12345);

    int IV = 0;
    error = pkmn_pokemon_set_IV(
                pokemon,
                "Not a stat",
                1
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_INVALID_ARGUMENT);
    error = pkmn_pokemon_set_IV(
                pokemon,
                "Attack",
                16
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_RANGE_ERROR);
    error = pkmn_pokemon_set_IV(
                pokemon,
                "Attack",
                12
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    error = pkmn_pokemon_get_IV(
                pokemon,
                "Not a stat",
                &IV
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_INVALID_ARGUMENT);
    error = pkmn_pokemon_get_IV(
                pokemon,
                "Attack",
                &IV
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    TEST_ASSERT_EQUAL(IV, 12);
}
