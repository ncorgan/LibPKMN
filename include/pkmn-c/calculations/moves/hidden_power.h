/*
 * Copyright (c) 2016-2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef PKMN_C_CALCULATIONS_MOVES_HIDDEN_POWER_H
#define PKMN_C_CALCULATIONS_MOVES_HIDDEN_POWER_H

#include <pkmn-c/config.h>
#include <pkmn-c/error.h>

#include <pkmn-c/types/hidden_power.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Calculate Hidden Power information in a Generation II game.
 *
 * \param IV_attack Attack IV (0-15)
 * \param IV_defense Defense IV (0-15)
 * \param IV_speed Speed IV (0-15)
 * \param IV_special Special IV (0-15)
 * \param p_hidden_power_out Where to return the Hidden Power information
 * \returns ::PKMN_ERROR_NONE upon successful completion
 * \returns ::PKMN_ERROR_OUT_OF_RANGE if any parameter is [0-15]
 */
PKMN_C_API enum pkmn_error pkmn_calculations_gen2_hidden_power(
    int IV_attack,
    int IV_defense,
    int IV_speed,
    int IV_special,
    struct pkmn_hidden_power* p_hidden_power_out
);

/*!
 * @brief Calculate Hidden Power information in a Generation III+ game.
 *
 * \param IV_HP HP IV (0-31)
 * \param IV_attack Attack IV (0-31)
 * \param IV_defense Defense IV (0-31)
 * \param IV_speed Speed IV (0-31)
 * \param IV_spatk Special Attack IV (0-31)
 * \param IV_spdef Special Defense IV (0-31)
 * \param p_hidden_power_out Where to return the Hidden Power information
 * \returns ::PKMN_ERROR_NONE upon successful completion
 * \returns ::PKMN_ERROR_OUT_OF_RANGE if any parameter is [0-31]
 */
PKMN_C_API enum pkmn_error pkmn_calculations_modern_hidden_power(
    int IV_HP,
    int IV_attack,
    int IV_defense,
    int IV_speed,
    int IV_spatk,
    int IV_spdef,
    struct pkmn_hidden_power* p_hidden_power_out
);

#ifdef __cplusplus
}
#endif

#endif /* PKMN_C_CALCULATIONS_MOVES_HIDDEN_POWER_H */
