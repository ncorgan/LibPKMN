/*
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef PKMN_C_CALCULATIONS_NATURE_H
#define PKMN_C_CALCULATIONS_NATURE_H

#include <pkmn-c/config.h>
#include <pkmn-c/error.h>

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//! Returns the nature of a Pokémon with the given personality.
/*!
 * \param personality Personality
 * \param nature_out Where to return the nature
 * \param buffer_len The length of the buffer passed into nature_out
 * \returns ::PKMN_ERROR_NONE upon successful completion
 * \returns ::PKMN_ERROR_NULL_POINTER if nature_out is NULL
 * \returns ::PKMN_ERROR_BUFFER_TOO_SMALL if the buffer passed into nature_out is too short
 */
PKMN_API pkmn_error_t pkmn_calculations_nature(
    uint32_t personality,
    char* nature_out,
    size_t buffer_len
);

#ifdef __cplusplus
}
#endif

#endif /* PKMN_C_CALCULATIONS_NATURE_H */