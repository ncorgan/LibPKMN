/*
 * Copyright (c) 2016-2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef PKMN_IO_PKM_HPP
#define PKMN_IO_PKM_HPP

#include <pkmn/pokemon.hpp>

#include <string>
#include <vector>

namespace pkmn { namespace io {

    bool vector_is_valid_pkm(
        const std::vector<uint8_t> &buffer,
        int* game_id_out
    );

    pkmn::pokemon::sptr load_pkm(
        const std::vector<uint8_t> &buffer
    );

    pkmn::pokemon::sptr load_pkm(
        const std::string &filepath
    );

}}

#endif /* PKMN_IO_PKM_HPP */
