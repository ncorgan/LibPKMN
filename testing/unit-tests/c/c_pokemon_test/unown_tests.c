/*
 * Copyright (c) 2017-2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <pkmntest-c/util.h>

#include <pkmn-c.h>

#include <unity.h>

#include <ctype.h>
#include <string.h>

static const struct pkmn_pokemon empty_pokemon =
{
    .species = PKMN_SPECIES_NONE,
    .game = PKMN_GAME_NONE,
    .p_internal = NULL
};

#define STRBUFFER_LEN 1024
static char strbuffer[STRBUFFER_LEN] = {0};

static void gen2_unown_test(enum pkmn_game game)
{
    enum pkmn_error error = PKMN_ERROR_NONE;
    struct pkmn_pokemon unown = empty_pokemon;

    struct pkmn_database_pokemon_entry unown_entry;
    error = pkmn_database_get_pokemon_entry(
                PKMN_SPECIES_UNOWN,
                game,
                "",
                &unown_entry
            );
    PKMN_TEST_ASSERT_SUCCESS(error);
    TEST_ASSERT_EQUAL(26, unown_entry.forms.length);

    struct pkmn_stat_enum_map IVs = {NULL, 0};

    for(size_t form_index = 0; form_index < unown_entry.forms.length; ++form_index)
    {
        error = pkmn_pokemon_init(
                    PKMN_SPECIES_UNOWN,
                    game,
                    unown_entry.forms.pp_strings[form_index],
                    5,
                    &unown
                );
        PKMN_TEST_ASSERT_SUCCESS(error);
        TEST_ASSERT_NOT_NULL(unown.p_internal);

        error = pkmn_pokemon_get_form(
                    &unown,
                    strbuffer,
                    sizeof(strbuffer),
                    NULL
                );
        PKMN_TEST_ASSERT_SUCCESS(error);
        TEST_ASSERT_EQUAL_STRING(
            unown_entry.forms.pp_strings[form_index],
            strbuffer
        );

        // Make sure IVs are properly set.
        error = pkmn_pokemon_get_IVs(
                    &unown,
                    &IVs
                );
        PKMN_TEST_ASSERT_SUCCESS(error);

        error = pkmn_calculations_gen2_unown_form(
                    IVs.p_values[PKMN_STAT_ATTACK],
                    IVs.p_values[PKMN_STAT_DEFENSE],
                    IVs.p_values[PKMN_STAT_SPEED],
                    IVs.p_values[PKMN_STAT_SPECIAL],
                    strbuffer,
                    sizeof(strbuffer),
                    NULL
                );
        PKMN_TEST_ASSERT_SUCCESS(error);
        TEST_ASSERT_EQUAL_STRING(
            unown_entry.forms.pp_strings[form_index],
            strbuffer
        );

        error = pkmn_pokemon_get_icon_filepath(
                    &unown,
                    strbuffer,
                    sizeof(strbuffer),
                    NULL
                );
        PKMN_TEST_ASSERT_SUCCESS(error);
        TEST_ASSERT_TRUE(file_exists(strbuffer));

        error = pkmn_pokemon_get_sprite_filepath(
                    &unown,
                    strbuffer,
                    sizeof(strbuffer),
                    NULL
                );
        PKMN_TEST_ASSERT_SUCCESS(error);
        TEST_ASSERT_TRUE(file_exists(strbuffer));

        error = pkmn_stat_enum_map_free(&IVs);
        PKMN_TEST_ASSERT_SUCCESS(error);

        error = pkmn_pokemon_free(&unown);
        PKMN_TEST_ASSERT_SUCCESS(error);
        TEST_ASSERT_NULL(unown.p_internal);
    }

    // Make sure setting IVs properly changes the form.
    error = pkmn_pokemon_init(
                PKMN_SPECIES_UNOWN,
                game,
                "A",
                5,
                &unown
            );
    PKMN_TEST_ASSERT_SUCCESS(error);

    error = pkmn_pokemon_set_IV(
                &unown,
                PKMN_STAT_ATTACK,
                10
            );
    PKMN_TEST_ASSERT_SUCCESS(error);

    error = pkmn_pokemon_set_IV(
                &unown,
                PKMN_STAT_DEFENSE,
                9
            );
    PKMN_TEST_ASSERT_SUCCESS(error);

    error = pkmn_pokemon_set_IV(
                &unown,
                PKMN_STAT_SPEED,
                1
            );
    PKMN_TEST_ASSERT_SUCCESS(error);

    error = pkmn_pokemon_set_IV(
                &unown,
                PKMN_STAT_SPECIAL,
                14
            );
    PKMN_TEST_ASSERT_SUCCESS(error);

    error = pkmn_pokemon_get_form(
                &unown,
                strbuffer,
                sizeof(strbuffer),
                NULL
            );
    PKMN_TEST_ASSERT_SUCCESS(error);
    TEST_ASSERT_EQUAL_STRING("G", strbuffer);

    // Make sure setting the form properly changes the IVs.
    for(size_t form_index = 0; form_index < unown_entry.forms.length; ++form_index)
    {
        error = pkmn_pokemon_set_form(
                    &unown,
                    unown_entry.forms.pp_strings[form_index]
                );
        PKMN_TEST_ASSERT_SUCCESS(error);

        error = pkmn_pokemon_get_form(
                    &unown,
                    strbuffer,
                    sizeof(strbuffer),
                    NULL
                );
        PKMN_TEST_ASSERT_SUCCESS(error);
        TEST_ASSERT_EQUAL_STRING(
            unown_entry.forms.pp_strings[form_index],
            strbuffer
        );

        // Make sure IVs are properly set.
        error = pkmn_pokemon_get_IVs(
                    &unown,
                    &IVs
                );
        PKMN_TEST_ASSERT_SUCCESS(error);

        error = pkmn_calculations_gen2_unown_form(
                    IVs.p_values[PKMN_STAT_ATTACK],
                    IVs.p_values[PKMN_STAT_DEFENSE],
                    IVs.p_values[PKMN_STAT_SPEED],
                    IVs.p_values[PKMN_STAT_SPECIAL],
                    strbuffer,
                    sizeof(strbuffer),
                    NULL
                );
        PKMN_TEST_ASSERT_SUCCESS(error);
        TEST_ASSERT_EQUAL_STRING(
            unown_entry.forms.pp_strings[form_index],
            strbuffer
        );

        error = pkmn_stat_enum_map_free(&IVs);
        PKMN_TEST_ASSERT_SUCCESS(error);
    }

    error = pkmn_pokemon_free(&unown);
    PKMN_TEST_ASSERT_SUCCESS(error);
    TEST_ASSERT_NULL(unown.p_internal);

    error = pkmn_database_pokemon_entry_free(&unown_entry);
    PKMN_TEST_ASSERT_SUCCESS(error);
}

static void gen3_unown_test(enum pkmn_game game)
{
    enum pkmn_error error = PKMN_ERROR_NONE;
    struct pkmn_pokemon unown = empty_pokemon;
    uint32_t personality = 0;

    struct pkmn_database_pokemon_entry unown_entry;
    error = pkmn_database_get_pokemon_entry(
                PKMN_SPECIES_UNOWN,
                game,
                "",
                &unown_entry
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    TEST_ASSERT_EQUAL(unown_entry.forms.length, 28);

    for(size_t form_index = 0;
        form_index < unown_entry.forms.length;
        ++form_index)
    {
        error = pkmn_pokemon_init(
                    PKMN_SPECIES_UNOWN,
                    game,
                    unown_entry.forms.pp_strings[form_index],
                    5,
                    &unown
                );
        TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);

        error = pkmn_pokemon_get_form(
                    &unown,
                    strbuffer,
                    sizeof(strbuffer),
                    NULL
                );
        TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
        TEST_ASSERT_EQUAL_STRING(
            unown_entry.forms.pp_strings[form_index],
            strbuffer
        );

        // Make sure personality is properly set.
        error = pkmn_pokemon_get_personality(
                    &unown,
                    &personality
                );
        TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);

        error = pkmn_calculations_gen3_unown_form(
                    personality,
                    strbuffer,
                    sizeof(strbuffer),
                    NULL
                );
        TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
        TEST_ASSERT_EQUAL_STRING(
            unown_entry.forms.pp_strings[form_index],
            strbuffer
        );

        if((game == PKMN_GAME_COLOSSEUM) || (game == PKMN_GAME_XD))
        {
            error = pkmn_pokemon_get_icon_filepath(
                        &unown,
                        strbuffer,
                        sizeof(strbuffer),
                        NULL
                    );
            PKMN_TEST_ASSERT_SUCCESS(error);
            TEST_ASSERT_TRUE(file_exists(strbuffer));

            error = pkmn_pokemon_get_sprite_filepath(
                        &unown,
                        strbuffer,
                        sizeof(strbuffer),
                        NULL
                    );
            PKMN_TEST_ASSERT_SUCCESS(error);
            TEST_ASSERT_TRUE(file_exists(strbuffer));
        }

        error = pkmn_pokemon_free(&unown);
        TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
        TEST_ASSERT_NULL(unown.p_internal);
    }

    // Make sure setting the personality properly sets the form.
    error = pkmn_pokemon_init(
                PKMN_SPECIES_UNOWN,
                game,
                "A",
                5,
                &unown
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    TEST_ASSERT_NOT_NULL(unown.p_internal);

    error = pkmn_pokemon_set_personality(
                &unown,
                0x4C07DE71
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);

    error = pkmn_pokemon_get_form(
                &unown,
                strbuffer,
                sizeof(strbuffer),
                NULL
            );
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    TEST_ASSERT_EQUAL_STRING("B", strbuffer);

    for(size_t form_index = 0;
        form_index < unown_entry.forms.length;
        ++form_index)
    {
        error = pkmn_pokemon_set_form(
                    &unown,
                    unown_entry.forms.pp_strings[form_index]
                );
        TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);

        error = pkmn_pokemon_get_personality(
                    &unown,
                    &personality
                );
        TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);

        error = pkmn_calculations_gen3_unown_form(
                    personality,
                    strbuffer,
                    sizeof(strbuffer),
                    NULL
                );
        TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
        TEST_ASSERT_EQUAL_STRING(
            unown_entry.forms.pp_strings[form_index],
            strbuffer
        );
    }

    error = pkmn_pokemon_free(&unown);
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
    TEST_ASSERT_NULL(unown.p_internal);

    error = pkmn_database_pokemon_entry_free(&unown_entry);
    TEST_ASSERT_EQUAL(error, PKMN_ERROR_NONE);
}

void gold_unown_test()
{
    gen2_unown_test(PKMN_GAME_GOLD);
}

void silver_unown_test()
{
    gen2_unown_test(PKMN_GAME_SILVER);
}

void crystal_unown_test()
{
    gen2_unown_test(PKMN_GAME_CRYSTAL);
}

void ruby_unown_test()
{
    gen3_unown_test(PKMN_GAME_RUBY);
}

void sapphire_unown_test()
{
    gen3_unown_test(PKMN_GAME_SAPPHIRE);
}

void emerald_unown_test()
{
    gen3_unown_test(PKMN_GAME_EMERALD);
}

void firered_unown_test()
{
    gen3_unown_test(PKMN_GAME_FIRERED);
}

void leafgreen_unown_test()
{
    gen3_unown_test(PKMN_GAME_LEAFGREEN);
}

void colosseum_unown_test()
{
    gen3_unown_test(PKMN_GAME_COLOSSEUM);
}

void xd_unown_test()
{
    gen3_unown_test(PKMN_GAME_XD);
}
