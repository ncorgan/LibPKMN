/*
 * Copyright (c) 2017-2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "c_test_common.h"

#include <pkmntest-c/misc_comparison.h>
#include <pkmntest-c/pokemon_comparison.h>
#include <pkmntest-c/util.h>

#include <pkmn-c.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef PKMN_C_PLATFORM_WIN32
#    include <windows.h>
#else
#    include <unistd.h>
#endif

#ifdef PKMN_C_PLATFORM_WIN32
#    define FS_SEPARATOR "\\"
#else
#    define FS_SEPARATOR "/"
#endif

#define TOO_LONG_OT_NAME "LibPKMNLibPKMN"
#define PKMN_DEFAULT_TRAINER_PID 1351
#define PKMN_DEFAULT_TRAINER_SID 32123
#define MONEY_MAX_VALUE 999999

#define STRBUFFER_LEN 1024
static char PKMN_TMP_DIR[STRBUFFER_LEN] = {0};
static char PKSAV_TEST_SAVES[STRBUFFER_LEN] = {0};
static char LIBPKMN_TEST_FILES[STRBUFFER_LEN] = {0};

static const enum pkmn_game RIVAL_NAME_SET_GAMES[] =
{
    PKMN_GAME_RUBY,
    PKMN_GAME_SAPPHIRE,
    PKMN_GAME_EMERALD,
    PKMN_GAME_COLOSSEUM,
    PKMN_GAME_XD,
    PKMN_GAME_BLACK,
    PKMN_GAME_WHITE,
    PKMN_GAME_X,
    PKMN_GAME_Y
};
static const size_t NUM_RIVAL_NAME_SET_GAMES =
    sizeof(RIVAL_NAME_SET_GAMES)/sizeof(RIVAL_NAME_SET_GAMES[0]);

static const struct pkmn_game_save empty_game_save =
{
    .game = PKMN_GAME_NONE,
    .p_internal = NULL
};
static const struct pkmn_pokemon empty_pokemon =
{
    .species = PKMN_SPECIES_NONE,
    .game = PKMN_GAME_NONE,
    .p_internal = NULL
};
static const struct pkmn_pokemon_party empty_pokemon_party =
{
    .game = PKMN_GAME_NONE,
    .p_internal = NULL
};
static const struct pkmn_pokemon_pc empty_pokemon_pc =
{
    .game = PKMN_GAME_NONE,
    .p_internal = NULL
};
static const struct pkmn_pokemon_list empty_pokemon_list =
{
    .p_pokemon = NULL,
    .length = 0
};
static const struct pkmn_pokemon_box_list empty_pokemon_box_list =
{
    .p_boxes = NULL,
    .length = 0
};
static const struct pkmn_trainer_info empty_trainer_info =
{
    .p_name = NULL,
    .id = {0},
    .gender = PKMN_GENDER_GENDERLESS
};
static const struct pkmn_item_list empty_item_list =
{
    .p_name = NULL,
    .game = PKMN_GAME_NONE,
    .p_internal = NULL
};
static const struct pkmn_item_bag empty_item_bag =
{
    .game = PKMN_GAME_NONE,
    .pocket_names =
    {
        .pp_strings = NULL,
        .length = 0
    },
    .p_internal = NULL
};
static const struct pkmn_item_slots empty_item_slots =
{
    .p_item_slots = NULL,
    .length = 0
};
static const struct pkmn_attribute_names empty_attribute_names =
{
    .numeric_attribute_names =
    {
        .pp_strings = NULL,
        .length = 0
    },
    .string_attribute_names =
    {
        .pp_strings = NULL,
        .length = 0
    },
    .boolean_attribute_names =
    {
        .pp_strings = NULL,
        .length = 0
    }
};

// Helper functions

static bool is_rival_name_set(enum pkmn_game game)
{
    for(size_t i = 0; i < NUM_RIVAL_NAME_SET_GAMES; ++i)
    {
        if(game == RIVAL_NAME_SET_GAMES[i])
        {
            return true;
        }
    }

    return false;
}

static bool is_male_only(enum pkmn_game game)
{
    return ((game_to_generation(game) <= 2) && (game != PKMN_GAME_CRYSTAL)) ||
           (game == PKMN_GAME_COLOSSEUM) ||
           (game == PKMN_GAME_XD);
}

static bool is_game_gamecube(enum pkmn_game game)
{
    return (game == PKMN_GAME_COLOSSEUM) ||
           (game == PKMN_GAME_XD);
}

static void populate_path_vars()
{
    pkmn_get_tmp_dir(
        PKMN_TMP_DIR,
        sizeof(PKMN_TMP_DIR),
        NULL
    );

    char* value = getenv("PKSAV_TEST_SAVES");
    TEST_ASSERT_NOT_NULL(value);
    snprintf(PKSAV_TEST_SAVES, sizeof(PKSAV_TEST_SAVES), "%s", value);

    value = getenv("LIBPKMN_TEST_FILES");
    TEST_ASSERT_NOT_NULL(value);
    snprintf(LIBPKMN_TEST_FILES, sizeof(LIBPKMN_TEST_FILES), "%s", value);
}

static void compare_string_lists(
    struct pkmn_string_list* p_string_list1,
    struct pkmn_string_list* p_string_list2
)
{
    TEST_ASSERT_NOT_NULL(p_string_list1);
    TEST_ASSERT_NOT_NULL(p_string_list2);

    TEST_ASSERT_EQUAL(p_string_list1->length, p_string_list2->length);

    for(size_t string_index = 0; string_index < p_string_list1->length; ++string_index)
    {
        TEST_ASSERT_EQUAL_STRING(
            p_string_list1->pp_strings[string_index],
            p_string_list2->pp_strings[string_index]
        );
    }
}

/*
 * Actual test functions
 */

static void game_save_test_trainer_info(
    struct pkmn_game_save* p_game_save
)
{
    TEST_ASSERT_NOT_NULL(p_game_save);

    enum pkmn_error error = PKMN_ERROR_NONE;

    int generation = game_to_generation(p_game_save->game);

    error = pkmn_game_save_set_trainer_id(
                p_game_save,
                (generation >= 3) ? pkmn_pokemon_default_trainer_id().id
                                  : pkmn_pokemon_default_trainer_id().public_id
            );
    PKMN_TEST_ASSERT_SUCCESS(error);

    error = pkmn_game_save_set_trainer_name(
                p_game_save,
                pkmn_pokemon_default_trainer_name()
            );
    PKMN_TEST_ASSERT_SUCCESS(error);

    error = pkmn_game_save_set_trainer_gender(
                p_game_save,
                PKMN_GENDER_FEMALE
            );
    if(is_male_only(p_game_save->game))
    {
        TEST_ASSERT_EQUAL(PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR, error);
    }
    else
    {
        PKMN_TEST_ASSERT_SUCCESS(error);
    }

    struct pkmn_trainer_info trainer_info = empty_trainer_info;
    error = pkmn_game_save_get_trainer_info(
                p_game_save,
                &trainer_info
            );
    PKMN_TEST_ASSERT_SUCCESS(error);

    TEST_ASSERT_EQUAL_STRING(
        pkmn_pokemon_default_trainer_name(),
        trainer_info.p_name
    );
    TEST_ASSERT_EQUAL(
        (generation >= 3) ? pkmn_pokemon_default_trainer_id().id
                          : pkmn_pokemon_default_trainer_id().public_id,
        trainer_info.id.id
    );
    if(!is_male_only(p_game_save->game))
    {
        TEST_ASSERT_EQUAL(PKMN_GENDER_FEMALE, trainer_info.gender);
    }
    else
    {
        TEST_ASSERT_EQUAL(PKMN_GENDER_MALE, trainer_info.gender);
    }

    error = pkmn_trainer_info_free(&trainer_info);
    PKMN_TEST_ASSERT_SUCCESS(error);
}

static void game_save_test_rival_name(
    struct pkmn_game_save* p_game_save
)
{
    enum pkmn_error error = PKMN_ERROR_NONE;
    char strbuffer[STRBUFFER_LEN] = {0};

    if(is_rival_name_set(p_game_save->game))
    {
        error = pkmn_game_save_set_rival_name(
                    p_game_save,
                    pkmn_pokemon_default_trainer_name()
                );
        TEST_ASSERT_EQUAL(PKMN_ERROR_FEATURE_NOT_IN_GAME_ERROR, error);
    }
    else
    {
        error = pkmn_game_save_set_rival_name(
                    p_game_save,
                    pkmn_pokemon_default_trainer_name()
                );
        PKMN_TEST_ASSERT_SUCCESS(error);

        error = pkmn_game_save_get_rival_name(
                    p_game_save,
                    strbuffer,
                    sizeof(strbuffer),
                    NULL
                );
        PKMN_TEST_ASSERT_SUCCESS(error);
        TEST_ASSERT_EQUAL_STRING(
            strbuffer,
            pkmn_pokemon_default_trainer_name()
        );
    }
}

static void game_save_test_time_played(
    const struct pkmn_game_save* p_game_save
)
{
    TEST_ASSERT_NOT_NULL(p_game_save);

    enum pkmn_error error = PKMN_ERROR_NONE;

    struct pkmn_time_duration time_played_from_save =
    {
        .hours = 0,
        .minutes = 0,
        .seconds = 0,
        .frames = 0
    };

    error = pkmn_game_save_get_time_played(
                p_game_save,
                &time_played_from_save
            );

    if(is_game_gamecube(p_game_save->game))
    {
        TEST_ASSERT_EQUAL(PKMN_ERROR_UNIMPLEMENTED_ERROR, error);

        error = pkmn_game_save_set_time_played(
                    p_game_save,
                    &time_played_from_save
                );
        TEST_ASSERT_EQUAL(PKMN_ERROR_UNIMPLEMENTED_ERROR, error);
    }
    else
    {
        PKMN_TEST_ASSERT_SUCCESS(error);

        // Generation I doesn't have frames.
        int generation = game_to_generation(p_game_save->game);

        struct pkmn_time_duration test_time_duration =
        {
            .hours   = (rand() % 256),
            .minutes = (rand() % 60),
            .seconds = (rand() % 60),
            .frames  = (rand() % 60)
        };

        error = pkmn_game_save_set_time_played(
                    p_game_save,
                    &test_time_duration
                );
        PKMN_TEST_ASSERT_SUCCESS(error);

        error = pkmn_game_save_get_time_played(
                    p_game_save,
                    &time_played_from_save
                );
        PKMN_TEST_ASSERT_SUCCESS(error);

        TEST_ASSERT_EQUAL(
            test_time_duration.hours,
            time_played_from_save.hours
        );
        TEST_ASSERT_EQUAL(
            test_time_duration.minutes,
            time_played_from_save.minutes
        );
        TEST_ASSERT_EQUAL(
            test_time_duration.seconds,
            time_played_from_save.seconds
        );
        if(generation > 1)
        {
            TEST_ASSERT_EQUAL(
                test_time_duration.frames,
                time_played_from_save.frames
            );
        }

        // Test invalid times.
        static const struct pkmn_time_duration invalid_time_durations[] =
        {
            {-1,0,0,0},     // Hours too low
            {999999,0,0,0}, // Hours too high
            {0,-1,0,0},     // Minutes too low
            {0,999999,0,0}, // Minutes too high
            {0,0,-1,0},     // Minutes too low
            {0,0,999999,0}, // Minutes too high
        };
        static const size_t num_invalid_time_durations =
            sizeof(invalid_time_durations)/sizeof(invalid_time_durations[0]);

        for(size_t time_duration_index = 0;
            time_duration_index < num_invalid_time_durations;
            ++time_duration_index)
        {
            error = pkmn_game_save_set_time_played(
                        p_game_save,
                        &invalid_time_durations[time_duration_index]
                    );
            TEST_ASSERT_EQUAL(PKMN_ERROR_OUT_OF_RANGE, error);
        }

        if(generation > 1)
        {
            static const struct pkmn_time_duration invalid_frame_time_durations[] =
            {
                {0,0,0,-1},     // Too low
                {0,0,0,999999}, // Too high
            };
            static const size_t num_invalid_frame_time_durations =
                sizeof(invalid_frame_time_durations)/sizeof(invalid_frame_time_durations[0]);

            for(size_t time_duration_index = 0;
                time_duration_index < num_invalid_frame_time_durations;
                ++time_duration_index)
            {
                error = pkmn_game_save_set_time_played(
                            p_game_save,
                            &invalid_frame_time_durations[time_duration_index]
                        );
                TEST_ASSERT_EQUAL(PKMN_ERROR_OUT_OF_RANGE, error);
            }
        }
    }
}

static void game_save_test_attributes(
    struct pkmn_game_save* p_game_save
)
{
    TEST_ASSERT_NOT_NULL(p_game_save);

    enum pkmn_error error = PKMN_ERROR_NONE;

    int generation = game_to_generation(p_game_save->game);
    switch(generation)
    {
        case 1:
        {
            int num_casino_coins = -1;
            error = pkmn_game_save_get_numeric_attribute(
                        p_game_save,
                        "Casino coins",
                        &num_casino_coins
                    );
            PKMN_TEST_ASSERT_SUCCESS(error);
            TEST_ASSERT_TRUE(num_casino_coins >= 0);
            TEST_ASSERT_TRUE(num_casino_coins <= 9999);

            int new_num_casino_coins = (rand() % 10000);
            error = pkmn_game_save_set_numeric_attribute(
                        p_game_save,
                        "Casino coins",
                        new_num_casino_coins
                    );
            PKMN_TEST_ASSERT_SUCCESS(error);

            error = pkmn_game_save_get_numeric_attribute(
                        p_game_save,
                        "Casino coins",
                        &num_casino_coins
                    );
            PKMN_TEST_ASSERT_SUCCESS(error);
            TEST_ASSERT_EQUAL(
                new_num_casino_coins,
                num_casino_coins
            );

            int pikachu_friendship = -1;
            error = pkmn_game_save_get_numeric_attribute(
                        p_game_save,
                        "Pikachu friendship",
                        &pikachu_friendship
                    );
            if(p_game_save->game == PKMN_GAME_YELLOW)
            {
                PKMN_TEST_ASSERT_SUCCESS(error);

                int new_pikachu_friendship = (rand() % 256);
                error = pkmn_game_save_set_numeric_attribute(
                            p_game_save,
                            "Pikachu friendship",
                            new_pikachu_friendship
                        );
                PKMN_TEST_ASSERT_SUCCESS(error);

                error = pkmn_game_save_get_numeric_attribute(
                            p_game_save,
                            "Pikachu friendship",
                            &pikachu_friendship
                        );
                PKMN_TEST_ASSERT_SUCCESS(error);
                TEST_ASSERT_EQUAL(
                    new_pikachu_friendship,
                    pikachu_friendship
                );
            }
            else
            {
                TEST_ASSERT_EQUAL(PKMN_ERROR_INVALID_ARGUMENT, error);
            }

            break;
        }

        case 3:
        {
            if(!is_game_gamecube(p_game_save->game))
            {
                int num_casino_coins = -1;
                error = pkmn_game_save_get_numeric_attribute(
                            p_game_save,
                            "Casino coins",
                            &num_casino_coins
                        );
                PKMN_TEST_ASSERT_SUCCESS(error);
                TEST_ASSERT_TRUE(num_casino_coins >= 0);
                TEST_ASSERT_TRUE(num_casino_coins <= 9999);

                int new_num_casino_coins = (rand() % 10000);
                error = pkmn_game_save_set_numeric_attribute(
                            p_game_save,
                            "Casino coins",
                            new_num_casino_coins
                        );
                PKMN_TEST_ASSERT_SUCCESS(error);

                error = pkmn_game_save_get_numeric_attribute(
                            p_game_save,
                            "Casino coins",
                            &num_casino_coins
                        );
                PKMN_TEST_ASSERT_SUCCESS(error);
                TEST_ASSERT_EQUAL(
                    new_num_casino_coins,
                    num_casino_coins
                );
            }
            break;
        }

        default:
            break;
    }
}

static void game_save_test_common_fields(
    struct pkmn_game_save* p_game_save
)
{
    TEST_ASSERT_NOT_NULL(p_game_save);

    int generation = game_to_generation(p_game_save->game);

    enum pkmn_error error = PKMN_ERROR_NONE;

    struct pkmn_pokemon_list pokemon_list = empty_pokemon_list;

    game_save_test_trainer_info(p_game_save);
    game_save_test_rival_name(p_game_save);

    error = pkmn_game_save_set_money(
                p_game_save,
                -1
            );
    TEST_ASSERT_EQUAL(PKMN_ERROR_OUT_OF_RANGE, error);
    error = pkmn_game_save_set_money(
                p_game_save,
                MONEY_MAX_VALUE+1
            );
    TEST_ASSERT_EQUAL(PKMN_ERROR_OUT_OF_RANGE, error);

    const int money = 123456;
    int money_from_game_save = 0;

    error = pkmn_game_save_set_money(
                p_game_save,
                money
            );
    PKMN_TEST_ASSERT_SUCCESS(error);
    error = pkmn_game_save_get_money(
                p_game_save,
                &money_from_game_save
            );
    PKMN_TEST_ASSERT_SUCCESS(error);
    TEST_ASSERT_EQUAL(money, money_from_game_save);

    struct pkmn_pokedex pokedex =
    {
        .game = PKMN_GAME_NONE,
        .p_internal = NULL
    };
    bool has_seen = false;
    bool has_caught = false;

    if(!is_game_gamecube(p_game_save->game))
    {
        error = pkmn_game_save_get_pokedex(
                    p_game_save,
                    &pokedex
                );
        PKMN_TEST_ASSERT_SUCCESS(error);
    }

    // Test the party.
    struct pkmn_pokemon_party pokemon_party = empty_pokemon_party;
    error = pkmn_game_save_get_pokemon_party(
                p_game_save,
                &pokemon_party
            );
    PKMN_TEST_ASSERT_SUCCESS(error);
    TEST_ASSERT_EQUAL(p_game_save->game, pokemon_party.game);
    TEST_ASSERT_EQUAL(6, pokemon_party.capacity);
    TEST_ASSERT_NOT_NULL(pokemon_party.p_internal);

    error = pkmn_pokemon_party_as_list(
                &pokemon_party,
                &pokemon_list
            );
    PKMN_TEST_ASSERT_SUCCESS(error);

    size_t num_pokemon = 0;
    error = pkmn_pokemon_party_get_num_pokemon(
                &pokemon_party,
                &num_pokemon
            );
    PKMN_TEST_ASSERT_SUCCESS(error);
    TEST_ASSERT_TRUE(num_pokemon > 0);
    TEST_ASSERT_TRUE(num_pokemon <= 6);

    for(size_t pokemon_index = 0; pokemon_index < pokemon_party.capacity; ++pokemon_index)
    {
        TEST_ASSERT_EQUAL(
            pokemon_party.game,
            pokemon_list.p_pokemon[pokemon_index].game
        );

        if(pokemon_index < num_pokemon)
        {
            TEST_ASSERT_NOT_EQUAL(
                PKMN_SPECIES_NONE,
                pokemon_list.p_pokemon[pokemon_index].species
            );

            if(!is_game_gamecube(p_game_save->game))
            {
                bool is_egg = false;
                bool is_none = (pokemon_list.p_pokemon[pokemon_index].species == PKMN_SPECIES_NONE);
                bool is_invalid = (pokemon_list.p_pokemon[pokemon_index].species == PKMN_SPECIES_INVALID);

                if(generation >= 2)
                {
                    error = pkmn_pokemon_is_egg(
                                &pokemon_list.p_pokemon[pokemon_index],
                                &is_egg
                            );
                }
                PKMN_TEST_ASSERT_SUCCESS(error);

                if(!is_egg && !is_none && !is_invalid)
                {
                    error = pkmn_pokedex_has_seen(
                                &pokedex,
                                pokemon_list.p_pokemon[pokemon_index].species,
                                &has_seen
                            );
                    PKMN_TEST_ASSERT_SUCCESS(error);
                    TEST_ASSERT_TRUE(has_seen);

                    error = pkmn_pokedex_has_caught(
                                &pokedex,
                                pokemon_list.p_pokemon[pokemon_index].species,
                                &has_caught
                            );
                    PKMN_TEST_ASSERT_SUCCESS(error);
                    TEST_ASSERT_TRUE(has_caught);
                }
            }
        }
        else
        {
            TEST_ASSERT_EQUAL(
                PKMN_SPECIES_NONE,
                pokemon_list.p_pokemon[pokemon_index].species
            );
        }
    }

    error = pkmn_pokemon_list_free(&pokemon_list);
    PKMN_TEST_ASSERT_SUCCESS(error);

    error = pkmn_pokemon_party_free(&pokemon_party);
    PKMN_TEST_ASSERT_SUCCESS(error);

    // Test PC.
    struct pkmn_pokemon_pc pokemon_pc = empty_pokemon_pc;
    error = pkmn_game_save_get_pokemon_pc(
                p_game_save,
                &pokemon_pc
            );
    PKMN_TEST_ASSERT_SUCCESS(error);
    TEST_ASSERT_EQUAL(p_game_save->game, pokemon_pc.game);
    TEST_ASSERT_TRUE(pokemon_pc.capacity > 0);
    TEST_ASSERT_NOT_NULL(pokemon_pc.p_internal);

    struct pkmn_pokemon_box_list pokemon_box_list = empty_pokemon_box_list;
    error = pkmn_pokemon_pc_as_list(
                &pokemon_pc,
                &pokemon_box_list
            );
    PKMN_TEST_ASSERT_SUCCESS(error);
    TEST_ASSERT_NOT_NULL(pokemon_box_list.p_boxes);
    TEST_ASSERT_TRUE(pokemon_box_list.length > 0);

    for(size_t box_index = 0; box_index < pokemon_box_list.length; ++box_index)
    {
        error = pkmn_pokemon_box_as_list(
                    &pokemon_box_list.p_boxes[box_index],
                    &pokemon_list
                );
        PKMN_TEST_ASSERT_SUCCESS(error);
        TEST_ASSERT_NOT_NULL(pokemon_list.p_pokemon);
        TEST_ASSERT_TRUE(pokemon_list.length > 0);

        for(size_t pokemon_index = 0; pokemon_index < pokemon_list.length; ++pokemon_index)
        {
            TEST_ASSERT_EQUAL(
                p_game_save->game,
                pokemon_list.p_pokemon[pokemon_index].game
            );

            if(!is_game_gamecube(p_game_save->game))
            {
                bool is_egg = false;
                bool is_none = (pokemon_list.p_pokemon[pokemon_index].species == PKMN_SPECIES_NONE);
                bool is_invalid = (pokemon_list.p_pokemon[pokemon_index].species == PKMN_SPECIES_INVALID);

                if(generation >= 2)
                {
                    error = pkmn_pokemon_is_egg(
                                &pokemon_list.p_pokemon[pokemon_index],
                                &is_egg
                            );
                }
                PKMN_TEST_ASSERT_SUCCESS(error);

                if(!is_egg && !is_none && !is_invalid)
                {
                    error = pkmn_pokedex_has_seen(
                                &pokedex,
                                pokemon_list.p_pokemon[pokemon_index].species,
                                &has_seen
                            );
                    PKMN_TEST_ASSERT_SUCCESS(error);
                    TEST_ASSERT_TRUE(has_seen);

                    error = pkmn_pokedex_has_caught(
                                &pokedex,
                                pokemon_list.p_pokemon[pokemon_index].species,
                                &has_caught
                            );
                    PKMN_TEST_ASSERT_SUCCESS(error);
                    TEST_ASSERT_TRUE(has_caught);
                }
            }
        }

        error = pkmn_pokemon_list_free(&pokemon_list);
        PKMN_TEST_ASSERT_SUCCESS(error);
    }

    if(!is_game_gamecube(p_game_save->game))
    {
        error = pkmn_pokedex_free(&pokedex);
        PKMN_TEST_ASSERT_SUCCESS(error);
    }

    error = pkmn_pokemon_box_list_free(&pokemon_box_list);
    PKMN_TEST_ASSERT_SUCCESS(error);

    error = pkmn_pokemon_pc_free(&pokemon_pc);
    PKMN_TEST_ASSERT_SUCCESS(error);

    game_save_test_time_played(p_game_save);
}

static void randomize_pokemon(
    struct pkmn_game_save* p_game_save
)
{
    TEST_ASSERT_NOT_NULL(p_game_save);

    enum pkmn_error error = PKMN_ERROR_NONE;

    struct pkmn_item_enum_list item_list =
    {
        .p_enums = NULL,
        .length = 0
    };
    error = pkmn_database_item_list(p_game_save->game, &item_list);
    PKMN_TEST_ASSERT_SUCCESS(error);

    struct pkmn_pokemon_party pokemon_party = empty_pokemon_party;
    error = pkmn_game_save_get_pokemon_party(
                p_game_save,
                &pokemon_party
            );
    PKMN_TEST_ASSERT_SUCCESS(error);

    for(size_t pokemon_index = 0; pokemon_index < pokemon_party.capacity; ++pokemon_index)
    {
        struct pkmn_pokemon pokemon = empty_pokemon;
        get_random_pokemon(
            &pokemon,
            &item_list,
            PKMN_SPECIES_NONE,
            p_game_save->game
        );

        error = pkmn_pokemon_party_set_pokemon(
                    &pokemon_party,
                    pokemon_index,
                    &pokemon
                );
        PKMN_TEST_ASSERT_SUCCESS(error);

        error = pkmn_pokemon_free(&pokemon);
        PKMN_TEST_ASSERT_SUCCESS(error);
    }

    error = pkmn_pokemon_party_free(&pokemon_party);
    PKMN_TEST_ASSERT_SUCCESS(error);

    struct pkmn_pokemon_pc pokemon_pc = empty_pokemon_pc;
    error = pkmn_game_save_get_pokemon_pc(
                p_game_save,
                &pokemon_pc
            );
    PKMN_TEST_ASSERT_SUCCESS(error);

    struct pkmn_pokemon_box_list pokemon_box_list = empty_pokemon_box_list;
    error = pkmn_pokemon_pc_as_list(
                &pokemon_pc,
                &pokemon_box_list
            );
    PKMN_TEST_ASSERT_SUCCESS(error);
    size_t box_capacity = pokemon_box_list.p_boxes[0].capacity;

    for(size_t box_index = 0; box_index < pokemon_pc.capacity; ++box_index)
    {
        for(size_t pokemon_index = 0; pokemon_index < box_capacity; ++pokemon_index)
        {
            struct pkmn_pokemon pokemon = empty_pokemon;
            get_random_pokemon(
                &pokemon,
                &item_list,
                PKMN_SPECIES_NONE,
                p_game_save->game
            );

            error = pkmn_pokemon_box_set_pokemon(
                        &pokemon_box_list.p_boxes[box_index],
                        pokemon_index,
                        &pokemon
                    );
            PKMN_TEST_ASSERT_SUCCESS(error);

            error = pkmn_pokemon_free(&pokemon);
            PKMN_TEST_ASSERT_SUCCESS(error);
        }
    }

    error = pkmn_pokemon_box_list_free(&pokemon_box_list);
    PKMN_TEST_ASSERT_SUCCESS(error);

    error = pkmn_pokemon_pc_free(&pokemon_pc);
    PKMN_TEST_ASSERT_SUCCESS(error);

    error = pkmn_item_enum_list_free(&item_list);
    PKMN_TEST_ASSERT_SUCCESS(error);
}

static void compare_item_lists(
    struct pkmn_item_list* p_item_list1,
    struct pkmn_item_list* p_item_list2
)
{
    TEST_ASSERT_NOT_NULL(p_item_list1);
    TEST_ASSERT_NOT_NULL(p_item_list2);

    enum pkmn_error error = PKMN_ERROR_NONE;

    TEST_ASSERT_EQUAL_STRING(p_item_list1->p_name, p_item_list2->p_name);
    TEST_ASSERT_EQUAL(p_item_list1->game, p_item_list2->game);
    TEST_ASSERT_EQUAL(p_item_list1->capacity, p_item_list2->capacity);

    size_t num_items1 = 0;
    size_t num_items2 = 0;

    error = pkmn_item_list_get_num_items(
                p_item_list1,
                &num_items1
            );
    PKMN_TEST_ASSERT_SUCCESS(error);
    error = pkmn_item_list_get_num_items(
                p_item_list2,
                &num_items2
            );
    PKMN_TEST_ASSERT_SUCCESS(error);
    TEST_ASSERT_EQUAL(num_items1, num_items2);

    struct pkmn_item_slots item_slots1 = empty_item_slots;
    struct pkmn_item_slots item_slots2 = empty_item_slots;

    error = pkmn_item_list_as_list(
                p_item_list1,
                &item_slots1
            );
    PKMN_TEST_ASSERT_SUCCESS(error);
    error = pkmn_item_list_as_list(
                p_item_list2,
                &item_slots2
            );
    PKMN_TEST_ASSERT_SUCCESS(error);

    TEST_ASSERT_EQUAL(item_slots1.length, item_slots2.length);
    for(size_t item_index = 0; item_index < item_slots1.length; ++item_index)
    {
        TEST_ASSERT_EQUAL(
            item_slots1.p_item_slots[item_index].item,
            item_slots2.p_item_slots[item_index].item
        );
        TEST_ASSERT_EQUAL(
            item_slots1.p_item_slots[item_index].amount,
            item_slots2.p_item_slots[item_index].amount
        );
    }

    error = pkmn_item_slots_free(&item_slots2);
    error = pkmn_item_slots_free(&item_slots1);
}

static void compare_item_bags(
    struct pkmn_item_bag* p_item_bag1,
    struct pkmn_item_bag* p_item_bag2
)
{
    TEST_ASSERT_NOT_NULL(p_item_bag1);
    TEST_ASSERT_NOT_NULL(p_item_bag2);

    enum pkmn_error error = PKMN_ERROR_NONE;

    compare_string_lists(
        &p_item_bag1->pocket_names,
        &p_item_bag2->pocket_names
    );

    for(size_t pocket_index = 0; pocket_index < p_item_bag1->pocket_names.length; ++pocket_index)
    {
        struct pkmn_item_list pocket1 = empty_item_list;
        struct pkmn_item_list pocket2 = empty_item_list;

        error = pkmn_item_bag_get_pocket(
                    p_item_bag1,
                    p_item_bag1->pocket_names.pp_strings[pocket_index],
                    &pocket1
                );
        PKMN_TEST_ASSERT_SUCCESS(error);
        error = pkmn_item_bag_get_pocket(
                    p_item_bag2,
                    p_item_bag1->pocket_names.pp_strings[pocket_index],
                    &pocket2
                );
        PKMN_TEST_ASSERT_SUCCESS(error);

        compare_item_lists(&pocket1, &pocket2);

        error = pkmn_item_list_free(&pocket2);
        PKMN_TEST_ASSERT_SUCCESS(error);

        error = pkmn_item_list_free(&pocket1);
        PKMN_TEST_ASSERT_SUCCESS(error);
    }
}

static void compare_pokemon_lists(
    struct pkmn_pokemon_list* p_pokemon_list1,
    struct pkmn_pokemon_list* p_pokemon_list2
)
{
    TEST_ASSERT_NOT_NULL(p_pokemon_list1);
    TEST_ASSERT_NOT_NULL(p_pokemon_list2);

    TEST_ASSERT_EQUAL(p_pokemon_list1->length, p_pokemon_list2->length);
    for(size_t pokemon_index = 0; pokemon_index < p_pokemon_list1->length; ++pokemon_index)
    {
        compare_pokemon(
            &p_pokemon_list1->p_pokemon[pokemon_index],
            &p_pokemon_list2->p_pokemon[pokemon_index]
        );
    }
}

static void compare_game_saves(
    struct pkmn_game_save* p_game_save1,
    struct pkmn_game_save* p_game_save2
)
{
    TEST_ASSERT_NOT_NULL(p_game_save1);
    TEST_ASSERT_NOT_NULL(p_game_save2);

    enum pkmn_error error = PKMN_ERROR_NONE;

    struct pkmn_pokemon_list pokemon_list1 = empty_pokemon_list;
    struct pkmn_pokemon_list pokemon_list = empty_pokemon_list;

    TEST_ASSERT_EQUAL(
        p_game_save1->game,
        p_game_save2->game
    );

    int generation = game_to_generation(p_game_save1->game);

    // Compare bags.

    struct pkmn_item_bag item_bag1 = empty_item_bag;
    struct pkmn_item_bag item_bag2 = empty_item_bag;

    error = pkmn_game_save_get_item_bag(
                p_game_save1,
                &item_bag1
            );
    PKMN_TEST_ASSERT_SUCCESS(error);
    error = pkmn_game_save_get_item_bag(
                p_game_save2,
                &item_bag2
            );
    PKMN_TEST_ASSERT_SUCCESS(error);
    compare_item_bags(&item_bag1, &item_bag2);

    error = pkmn_item_bag_free(&item_bag2);
    PKMN_TEST_ASSERT_SUCCESS(error);
    error = pkmn_item_bag_free(&item_bag1);
    PKMN_TEST_ASSERT_SUCCESS(error);

    // Compare item PCs (if applicable).
    if((generation <= 3) || !is_game_gamecube(p_game_save1->game))
    {
        struct pkmn_item_list item_pc1 = empty_item_list;
        struct pkmn_item_list item_pc = empty_item_list;

        error = pkmn_game_save_get_item_pc(
                    p_game_save1,
                    &item_pc1
                );
        PKMN_TEST_ASSERT_SUCCESS(error);
        error = pkmn_game_save_get_item_pc(
                    p_game_save2,
                    &item_pc
                );
        PKMN_TEST_ASSERT_SUCCESS(error);

        compare_item_lists(&item_pc1, &item_pc);

        error = pkmn_item_list_free(&item_pc);
        PKMN_TEST_ASSERT_SUCCESS(error);
        error = pkmn_item_list_free(&item_pc1);
        PKMN_TEST_ASSERT_SUCCESS(error);
    }

    // Compare parties.

    struct pkmn_pokemon_party pokemon_party1 = empty_pokemon_party;
    struct pkmn_pokemon_party pokemon_party = empty_pokemon_party;

    error = pkmn_game_save_get_pokemon_party(
                p_game_save1,
                &pokemon_party1
            );
    PKMN_TEST_ASSERT_SUCCESS(error);
    error = pkmn_game_save_get_pokemon_party(
                p_game_save2,
                &pokemon_party
            );
    PKMN_TEST_ASSERT_SUCCESS(error);

    error = pkmn_pokemon_party_as_list(
                &pokemon_party1,
                &pokemon_list1
            );
    PKMN_TEST_ASSERT_SUCCESS(error);
    error = pkmn_pokemon_party_as_list(
                &pokemon_party,
                &pokemon_list
            );
    PKMN_TEST_ASSERT_SUCCESS(error);

    compare_pokemon_lists(&pokemon_list1, &pokemon_list);

    error = pkmn_pokemon_list_free(&pokemon_list);
    PKMN_TEST_ASSERT_SUCCESS(error);
    error = pkmn_pokemon_list_free(&pokemon_list1);

    error = pkmn_pokemon_party_free(&pokemon_party);
    PKMN_TEST_ASSERT_SUCCESS(error);
    error = pkmn_pokemon_party_free(&pokemon_party1);
    PKMN_TEST_ASSERT_SUCCESS(error);

    // Compare Pokémon PCs.

    struct pkmn_pokemon_pc pokemon_pc1 = empty_pokemon_pc;
    struct pkmn_pokemon_pc pokemon_pc = empty_pokemon_pc;

    error = pkmn_game_save_get_pokemon_pc(
                p_game_save1,
                &pokemon_pc1
            );
    PKMN_TEST_ASSERT_SUCCESS(error);
    error = pkmn_game_save_get_pokemon_pc(
                p_game_save1,
                &pokemon_pc
            );
    PKMN_TEST_ASSERT_SUCCESS(error);

    struct pkmn_pokemon_box_list pokemon_box_list1 = empty_pokemon_box_list;
    struct pkmn_pokemon_box_list pokemon_box_list = empty_pokemon_box_list;

    error = pkmn_pokemon_pc_as_list(
                &pokemon_pc1,
                &pokemon_box_list1
            );
    PKMN_TEST_ASSERT_SUCCESS(error);
    error = pkmn_pokemon_pc_as_list(
                &pokemon_pc,
                &pokemon_box_list
            );
    PKMN_TEST_ASSERT_SUCCESS(error);

    for(size_t box_index = 0; box_index < pokemon_box_list1.length; ++box_index)
    {
        error = pkmn_pokemon_box_as_list(
                    &pokemon_box_list1.p_boxes[box_index],
                    &pokemon_list1
                );
        PKMN_TEST_ASSERT_SUCCESS(error);
        error = pkmn_pokemon_box_as_list(
                    &pokemon_box_list.p_boxes[box_index],
                    &pokemon_list
                );
        PKMN_TEST_ASSERT_SUCCESS(error);

        compare_pokemon_lists(&pokemon_list1, &pokemon_list);

        error = pkmn_pokemon_list_free(&pokemon_list);
        PKMN_TEST_ASSERT_SUCCESS(error);
        error = pkmn_pokemon_list_free(&pokemon_list1);
        PKMN_TEST_ASSERT_SUCCESS(error);
    }

    error = pkmn_pokemon_box_list_free(&pokemon_box_list);
    PKMN_TEST_ASSERT_SUCCESS(error);
    error = pkmn_pokemon_box_list_free(&pokemon_box_list1);
    PKMN_TEST_ASSERT_SUCCESS(error);

    error = pkmn_pokemon_pc_free(&pokemon_pc);
    PKMN_TEST_ASSERT_SUCCESS(error);
    error = pkmn_pokemon_pc_free(&pokemon_pc1);
    PKMN_TEST_ASSERT_SUCCESS(error);

    // Compare attributes.

    struct pkmn_attribute_names attribute_names1 = empty_attribute_names;
    error = pkmn_game_save_get_attribute_names(
                p_game_save1,
                &attribute_names1
            );
    PKMN_TEST_ASSERT_SUCCESS(error);

    struct pkmn_attribute_names attribute_names2 = empty_attribute_names;
    error = pkmn_game_save_get_attribute_names(
                p_game_save2,
                &attribute_names2
            );
    PKMN_TEST_ASSERT_SUCCESS(error);

    compare_attribute_names(
        &attribute_names1,
        &attribute_names2
    );

    for(size_t attribute_index = 0;
        attribute_index < attribute_names1.numeric_attribute_names.length;
        ++attribute_index)
    {
        int attribute_value1 = 0;
        int attribute_value2 = 0;

        error = pkmn_game_save_get_numeric_attribute(
                    p_game_save1,
                    attribute_names1.numeric_attribute_names.pp_strings[attribute_index],
                    &attribute_value1
                );
        PKMN_TEST_ASSERT_SUCCESS(error);

        error = pkmn_game_save_get_numeric_attribute(
                    p_game_save2,
                    attribute_names2.numeric_attribute_names.pp_strings[attribute_index],
                    &attribute_value2
                );
        PKMN_TEST_ASSERT_SUCCESS(error);

        TEST_ASSERT_EQUAL(attribute_value1, attribute_value2);
    }

    for(size_t attribute_index = 0;
        attribute_index < attribute_names1.string_attribute_names.length;
        ++attribute_index)
    {
        char attribute_value1[STRBUFFER_LEN] = {0};
        char attribute_value2[STRBUFFER_LEN] = {0};

        error = pkmn_game_save_get_string_attribute(
                    p_game_save1,
                    attribute_names1.string_attribute_names.pp_strings[attribute_index],
                    attribute_value1,
                    sizeof(attribute_value1),
                    NULL
                );
        PKMN_TEST_ASSERT_SUCCESS(error);

        error = pkmn_game_save_get_string_attribute(
                    p_game_save2,
                    attribute_names2.string_attribute_names.pp_strings[attribute_index],
                    attribute_value2,
                    sizeof(attribute_value2),
                    NULL
                );
        PKMN_TEST_ASSERT_SUCCESS(error);

        TEST_ASSERT_EQUAL_STRING(attribute_value1, attribute_value2);
    }

    for(size_t attribute_index = 0;
        attribute_index < attribute_names1.boolean_attribute_names.length;
        ++attribute_index)
    {
        bool attribute_value1 = 0;
        bool attribute_value2 = 0;

        error = pkmn_game_save_get_boolean_attribute(
                    p_game_save1,
                    attribute_names1.boolean_attribute_names.pp_strings[attribute_index],
                    &attribute_value1
                );
        PKMN_TEST_ASSERT_SUCCESS(error);

        error = pkmn_game_save_get_boolean_attribute(
                    p_game_save2,
                    attribute_names2.boolean_attribute_names.pp_strings[attribute_index],
                    &attribute_value2
                );
        PKMN_TEST_ASSERT_SUCCESS(error);

        TEST_ASSERT_EQUAL(attribute_value1, attribute_value2);
    }

    error = pkmn_attribute_names_free(&attribute_names1);
    PKMN_TEST_ASSERT_SUCCESS(error);

    error = pkmn_attribute_names_free(&attribute_names2);
    PKMN_TEST_ASSERT_SUCCESS(error);
}

static void test_game_save(
    enum pkmn_game_save_type save_type,
    enum pkmn_game game,
    const char* subdir,
    const char* filename
)
{
    TEST_ASSERT_NOT_NULL(subdir);
    TEST_ASSERT_NOT_NULL(filename);

    enum pkmn_error error = PKMN_ERROR_NONE;
    char strbuffer[STRBUFFER_LEN] = {0};

    enum pkmn_game_save_type save_type_from_file = PKMN_GAME_SAVE_TYPE_NONE;

    struct pkmn_game_save game_save = empty_game_save;

    char save_filepath[STRBUFFER_LEN] = {0};
    snprintf(
        save_filepath,
        sizeof(save_filepath),
        "%s%s%s%s%s",
        is_game_gamecube(game) ? LIBPKMN_TEST_FILES : PKSAV_TEST_SAVES,
        FS_SEPARATOR, subdir, FS_SEPARATOR, filename
    );

    error = pkmn_game_save_detect_type(
                save_filepath,
                &save_type_from_file
            );
    PKMN_TEST_ASSERT_SUCCESS(error);
    TEST_ASSERT_EQUAL(save_type, save_type_from_file);

    error = pkmn_game_save_init_from_file(
                save_filepath,
                &game_save
            );
    PKMN_TEST_ASSERT_SUCCESS(error);
    TEST_ASSERT_NOT_NULL(game_save.p_internal);
    TEST_ASSERT_EQUAL(game, game_save.game);

    error = pkmn_game_save_get_filepath(
                &game_save,
                strbuffer,
                sizeof(strbuffer),
                NULL
            );
    PKMN_TEST_ASSERT_SUCCESS(error);
    TEST_ASSERT_EQUAL_STRING(save_filepath, strbuffer);

    game_save_test_common_fields(&game_save);
    game_save_test_attributes(&game_save);
    randomize_pokemon(&game_save);

    char tmp_save_filepath[STRBUFFER_LEN] = {0};
    snprintf(
        tmp_save_filepath,
        sizeof(tmp_save_filepath),
        "%s%s%d_%d.sav",
        PKMN_TMP_DIR,
        FS_SEPARATOR,
        (int)game,
        rand()
    );

    error = pkmn_game_save_save_as(
                &game_save,
                tmp_save_filepath
            );
    PKMN_TEST_ASSERT_SUCCESS(error);

    struct pkmn_game_save game_save2 = empty_game_save;
    error = pkmn_game_save_init_from_file(
                tmp_save_filepath,
                &game_save2
            );
    PKMN_TEST_ASSERT_SUCCESS(error);
    TEST_ASSERT_NOT_NULL(game_save.p_internal);

    error = pkmn_game_save_get_filepath(
                &game_save2,
                strbuffer,
                sizeof(strbuffer),
                NULL
            );
    PKMN_TEST_ASSERT_SUCCESS(error);
    TEST_ASSERT_EQUAL_STRING(tmp_save_filepath, strbuffer);
    compare_game_saves(
        &game_save,
        &game_save2
    );

#ifdef PKMN_C_PLATFORM_WIN32
    TEST_ASSERT_NOT_EQUAL(DeleteFile(tmp_save_filepath), 0);
#else
    TEST_ASSERT_EQUAL(remove(tmp_save_filepath), 0);
#endif

    error = pkmn_game_save_free(&game_save2);
    PKMN_TEST_ASSERT_SUCCESS(error);
    TEST_ASSERT_NULL(game_save2.p_internal);

    error = pkmn_game_save_free(&game_save);
    PKMN_TEST_ASSERT_SUCCESS(error);
    TEST_ASSERT_NULL(game_save.p_internal);
}

#define PKMN_C_GAME_SAVE_TEST(save_type, game_enum, game, subdir, filename) \
{ \
    Unity.CurrentTestName = "c_game_save_test_" game; \
    ++Unity.NumberOfTests; \
    if(TEST_PROTECT()) { \
        test_game_save(save_type, game_enum, subdir, filename); \
    } \
    UnityConcludeTest(); \
}

PKMN_C_TEST_MAIN(
    populate_path_vars();
    PKMN_C_GAME_SAVE_TEST(PKMN_GAME_SAVE_TYPE_RED_BLUE, PKMN_GAME_RED, "Red", "red_blue", "pokemon_red.sav");
    PKMN_C_GAME_SAVE_TEST(PKMN_GAME_SAVE_TYPE_YELLOW, PKMN_GAME_YELLOW, "Yellow", "yellow", "pokemon_yellow.sav");
    PKMN_C_GAME_SAVE_TEST(PKMN_GAME_SAVE_TYPE_GOLD_SILVER, PKMN_GAME_GOLD, "Gold", "gold_silver", "pokemon_gold.sav");
    PKMN_C_GAME_SAVE_TEST(PKMN_GAME_SAVE_TYPE_CRYSTAL, PKMN_GAME_CRYSTAL, "Crystal", "crystal", "pokemon_crystal.sav");
    PKMN_C_GAME_SAVE_TEST(PKMN_GAME_SAVE_TYPE_RUBY_SAPPHIRE, PKMN_GAME_RUBY, "Ruby", "ruby_sapphire", "pokemon_ruby.sav");
    PKMN_C_GAME_SAVE_TEST(PKMN_GAME_SAVE_TYPE_EMERALD, PKMN_GAME_EMERALD, "Emerald", "emerald", "pokemon_emerald.sav");
    PKMN_C_GAME_SAVE_TEST(PKMN_GAME_SAVE_TYPE_FIRERED_LEAFGREEN, PKMN_GAME_FIRERED, "FireRed", "firered_leafgreen", "pokemon_firered.sav");
    PKMN_C_GAME_SAVE_TEST(PKMN_GAME_SAVE_TYPE_COLOSSEUM_XD, PKMN_GAME_COLOSSEUM, "Colosseum", "gamecube_saves", "pokemon_colosseum.gci");
    PKMN_C_GAME_SAVE_TEST(PKMN_GAME_SAVE_TYPE_COLOSSEUM_XD, PKMN_GAME_XD, "XD", "gamecube_saves", "pokemon_xd.gci");
)
