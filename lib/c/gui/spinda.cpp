/*
 * Copyright (c) 2017-2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "error_internal.hpp"

#include <pkmn-c/error.h>

#include <pkmn-c/gui/spinda.h>

#include <pkmn/qt/Spinda.hpp>

enum pkmn_error pkmn_gui_generate_spinda_sprite_at_filepath(
    int generation,
    uint32_t personality,
    bool shiny,
    const char* p_filepath
)
{
    PKMN_CHECK_NULL_PARAM(p_filepath);

    PKMN_CPP_TO_C(
        pkmn::qt::GenerateSpindaSpriteAtFilepath(
            generation,
            personality,
            shiny,
            p_filepath
        );
    )
}
