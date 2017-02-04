/*
 * Copyright (c) 2016 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef PKMN_C_POKEMON_H
#define PKMN_C_POKEMON_H

#include <pkmn-c/config.h>
#include <pkmn-c/error.h>

#include <pkmn-c/database/pokemon_entry.h>

#include <pkmn-c/types/gender.h>
#include <pkmn-c/types/move_slot.h>
#include <pkmn-c/types/string_types.h>

#include <stdint.h>

#define LIBPKMN_OT_ID   2105214279
#define LIBPKMN_OT_NAME "LibPKMN"

#if !defined(PKMN_POKEMON_DECLARED) && !defined(__DOXYGEN__)
struct pkmn_pokemon_t;
typedef struct pkmn_pokemon_t pkmn_pokemon_t;
#define PKMN_POKEMON_DECLARED
#endif

typedef pkmn_pokemon_t* pkmn_pokemon_handle_t;

#ifdef __cplusplus
extern "C" {
#endif

PKMN_API pkmn_error_t pkmn_pokemon_make(
    pkmn_pokemon_handle_t* handle_ptr,
    const char* species,
    const char* game,
    const char* form,
    int level
);

PKMN_API pkmn_error_t pkmn_pokemon_from_file(
    pkmn_pokemon_handle_t* handle_ptr,
    const char* filepath
);

PKMN_API pkmn_error_t pkmn_pokemon_free(
    pkmn_pokemon_handle_t* handle_ptr
);

PKMN_API const char* pkmn_pokemon_strerror(
    pkmn_pokemon_handle_t handle
);

PKMN_API pkmn_error_t pkmn_pokemon_get_species(
    pkmn_pokemon_handle_t handle,
    char* species_out,
    size_t buffer_len
);

PKMN_API pkmn_error_t pkmn_pokemon_get_game(
    pkmn_pokemon_handle_t handle,
    char* game_out,
    size_t buffer_len
);

PKMN_API pkmn_error_t pkmn_pokemon_get_form(
    pkmn_pokemon_handle_t handle,
    char* form_out,
    size_t buffer_len
);

PKMN_API pkmn_error_t pkmn_pokemon_set_form(
    pkmn_pokemon_handle_t handle,
    const char* form
);

PKMN_API pkmn_error_t pkmn_pokemon_get_database_entry(
    pkmn_pokemon_handle_t handle,
    pkmn_database_pokemon_entry_t* database_entry_out
);

PKMN_API pkmn_error_t pkmn_pokemon_get_nickname(
    pkmn_pokemon_handle_t handle,
    char* nickname_out,
    size_t buffer_len
);

PKMN_API pkmn_error_t pkmn_pokemon_set_nickname(
    pkmn_pokemon_handle_t handle,
    const char* nickname
);

PKMN_API pkmn_error_t pkmn_pokemon_is_shiny(
    pkmn_pokemon_handle_t handle,
    bool* is_shiny_out
);

PKMN_API pkmn_error_t pkmn_pokemon_set_shininess(
    pkmn_pokemon_handle_t handle,
    bool value
);

PKMN_API pkmn_error_t pkmn_pokemon_get_held_item(
    pkmn_pokemon_handle_t handle,
    char* held_item_out,
    size_t buffer_len
);

PKMN_API pkmn_error_t pkmn_pokemon_set_held_item(
    pkmn_pokemon_handle_t handle,
    const char* held_item
);

PKMN_API pkmn_error_t pkmn_pokemon_get_trainer_name(
    pkmn_pokemon_handle_t handle,
    char* trainer_name_out,
    size_t buffer_len
);

PKMN_API pkmn_error_t pkmn_pokemon_set_trainer_name(
    pkmn_pokemon_handle_t handle,
    const char* trainer_name
);

PKMN_API pkmn_error_t pkmn_pokemon_get_trainer_public_id(
    pkmn_pokemon_handle_t handle,
    uint16_t* trainer_public_id_out
);

PKMN_API pkmn_error_t pkmn_pokemon_get_trainer_secret_id(
    pkmn_pokemon_handle_t handle,
    uint16_t* trainer_secret_id_out
);

PKMN_API pkmn_error_t pkmn_pokemon_get_trainer_id(
    pkmn_pokemon_handle_t handle,
    uint32_t* trainer_id_out
);

PKMN_API pkmn_error_t pkmn_pokemon_set_trainer_public_id(
    pkmn_pokemon_handle_t handle,
    uint16_t trainer_public_id
);

PKMN_API pkmn_error_t pkmn_pokemon_set_trainer_secret_id(
    pkmn_pokemon_handle_t handle,
    uint16_t trainer_secret_id
);

PKMN_API pkmn_error_t pkmn_pokemon_set_trainer_id(
    pkmn_pokemon_handle_t handle,
    uint32_t trainer_id
);

PKMN_API pkmn_error_t pkmn_pokemon_get_trainer_gender(
    pkmn_pokemon_handle_t handle,
    pkmn_gender_t* trainer_gender_out
);

PKMN_API pkmn_error_t pkmn_pokemon_set_trainer_gender(
    pkmn_pokemon_handle_t handle,
    pkmn_gender_t trainer_gender
);

PKMN_API pkmn_error_t pkmn_pokemon_get_friendship(
    pkmn_pokemon_handle_t handle,
    int* friendship_out
);

PKMN_API pkmn_error_t pkmn_pokemon_set_friendship(
    pkmn_pokemon_handle_t handle,
    int friendship
);

PKMN_API pkmn_error_t pkmn_pokemon_get_ability(
    pkmn_pokemon_handle_t handle,
    char* ability_out,
    size_t buffer_len
);

PKMN_API pkmn_error_t pkmn_pokemon_set_ability(
    pkmn_pokemon_handle_t handle,
    const char* ability
);

PKMN_API pkmn_error_t pkmn_pokemon_get_ball(
    pkmn_pokemon_handle_t handle,
    char* ball_out,
    size_t buffer_len
);

PKMN_API pkmn_error_t pkmn_pokemon_set_ball(
    pkmn_pokemon_handle_t handle,
    const char* ball
);

PKMN_API pkmn_error_t pkmn_pokemon_get_level_met(
    pkmn_pokemon_handle_t handle,
    int* level_met_out
);

PKMN_API pkmn_error_t pkmn_pokemon_set_level_met(
    pkmn_pokemon_handle_t handle,
    int level_met
);

PKMN_API pkmn_error_t pkmn_pokemon_get_location_met(
    pkmn_pokemon_handle_t handle,
    bool as_egg,
    char* location_met_out,
    size_t buffer_len
);

PKMN_API pkmn_error_t pkmn_pokemon_set_location_met(
    pkmn_pokemon_handle_t handle,
    const char* location_met,
    bool as_egg
);

PKMN_API pkmn_error_t pkmn_pokemon_get_original_game(
    pkmn_pokemon_handle_t handle,
    char* original_game_out,
    size_t buffer_len
);

PKMN_API pkmn_error_t pkmn_pokemon_set_original_game(
    pkmn_pokemon_handle_t handle,
    const char* original_game
);

PKMN_API pkmn_error_t pkmn_pokemon_get_personality(
    pkmn_pokemon_handle_t handle,
    uint32_t* personality_out
);

PKMN_API pkmn_error_t pkmn_pokemon_set_personality(
    pkmn_pokemon_handle_t handle,
    uint32_t personality
);

PKMN_API pkmn_error_t pkmn_pokemon_get_experience(
    pkmn_pokemon_handle_t handle,
    int* experience_out
);

PKMN_API pkmn_error_t pkmn_pokemon_set_experience(
    pkmn_pokemon_handle_t handle,
    int experience
);

PKMN_API pkmn_error_t pkmn_pokemon_get_level(
    pkmn_pokemon_handle_t handle,
    int* level_out
);

PKMN_API pkmn_error_t pkmn_pokemon_set_level(
    pkmn_pokemon_handle_t handle,
    int level
);

PKMN_API pkmn_error_t pkmn_pokemon_get_marking_names(
    pkmn_pokemon_handle_t handle,
    pkmn_string_list_t* marking_names_out
);

PKMN_API pkmn_error_t pkmn_pokemon_has_marking(
    pkmn_pokemon_handle_t handle,
    const char* marking,
    bool* has_marking_out
);

PKMN_API pkmn_error_t pkmn_pokemon_set_marking(
    pkmn_pokemon_handle_t handle,
    const char* marking,
    bool value
);

PKMN_API pkmn_error_t pkmn_pokemon_get_ribbon_names(
    pkmn_pokemon_handle_t handle,
    pkmn_string_list_t* ribbon_names_out
);

PKMN_API pkmn_error_t pkmn_pokemon_has_ribbon(
    pkmn_pokemon_handle_t handle,
    const char* ribbon,
    bool* has_ribbon_out
);

PKMN_API pkmn_error_t pkmn_pokemon_set_ribbon(
    pkmn_pokemon_handle_t handle,
    const char* ribbon,
    bool value
);

PKMN_API pkmn_error_t pkmn_pokemon_get_moves(
    pkmn_pokemon_handle_t handle,
    pkmn_move_slots_t* move_slots_out
);

PKMN_API pkmn_error_t pkmn_pokemon_set_move(
    pkmn_pokemon_handle_t handle,
    const char* move,
    int index
);

PKMN_API pkmn_error_t pkmn_pokemon_get_contest_stat_names(
    pkmn_pokemon_handle_t handle,
    pkmn_string_list_t* contest_stat_names_out
);

PKMN_API pkmn_error_t pkmn_pokemon_get_contest_stat(
    pkmn_pokemon_handle_t handle,
    const char* stat,
    int* contest_stat_out
);

PKMN_API pkmn_error_t pkmn_pokemon_set_contest_stat(
    pkmn_pokemon_handle_t handle,
    const char* stat,
    int contest_stat
);

PKMN_API pkmn_error_t pkmn_pokemon_get_EV_names(
    pkmn_pokemon_handle_t handle,
    pkmn_string_list_t* EV_names_out
);

PKMN_API pkmn_error_t pkmn_pokemon_get_EV(
    pkmn_pokemon_handle_t handle,
    const char* stat,
    int* EV_out
);

PKMN_API pkmn_error_t pkmn_pokemon_set_EV(
    pkmn_pokemon_handle_t handle,
    const char* stat,
    int EV
);

PKMN_API pkmn_error_t pkmn_pokemon_get_IV_names(
    pkmn_pokemon_handle_t handle,
    pkmn_string_list_t* IV_names_out
);

PKMN_API pkmn_error_t pkmn_pokemon_get_IV(
    pkmn_pokemon_handle_t handle,
    const char* stat,
    int* IV_out
);

PKMN_API pkmn_error_t pkmn_pokemon_set_IV(
    pkmn_pokemon_handle_t handle,
    const char* stat,
    int IV
);

PKMN_API pkmn_error_t pkmn_pokemon_get_stat_names(
    pkmn_pokemon_handle_t handle,
    pkmn_string_list_t* stat_names_out
);

PKMN_API pkmn_error_t pkmn_pokemon_get_stat(
    pkmn_pokemon_handle_t handle,
    const char* stat_name,
    int* stat_out
);

#ifdef __cplusplus
}
#endif

#endif /* PKMN_C_POKEMON_H */