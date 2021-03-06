/*
 * Copyright (c) 2017-2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef PKMN_C_GUI_SPINDA_H
#define PKMN_C_GUI_SPINDA_H

#include <pkmn-c/config.h>
#include <pkmn-c/error.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

PKMN_C_API enum pkmn_error pkmn_gui_generate_spinda_sprite_at_filepath(
    int generation,
    uint32_t personality,
    bool shiny,
    const char* p_filepath
);

#ifdef __cplusplus
}
#endif

#endif /* PKMN_C_GUI_SPINDA_H */
