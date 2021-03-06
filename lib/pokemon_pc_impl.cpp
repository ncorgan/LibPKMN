/*
 * Copyright (c) 2016-2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "exception_internal.hpp"
#include "pokemon_pc_impl.hpp"
#include "pokemon_pc_gen1impl.hpp"
#include "pokemon_pc_gen2impl.hpp"
#include "pokemon_pc_gbaimpl.hpp"
#include "pokemon_pc_gcnimpl.hpp"

#include "utils/misc.hpp"

#include "database/database_common.hpp"
#include "database/enum_conversions.hpp"
#include "database/id_to_string.hpp"

#include <pkmn/exception.hpp>

#include <boost/thread/lock_guard.hpp>

#include <stdexcept>

namespace pkmn {

    pokemon_pc::sptr pokemon_pc::make(pkmn::e_game game)
    {
        int game_id = pkmn::database::game_enum_to_id(game);
        int generation = pkmn::database::game_id_to_generation(game_id);

        switch(generation) {
            case 1:
                return std::make_shared<pokemon_pc_gen1impl>(game_id);

            case 2:
                return std::make_shared<pokemon_pc_gen2impl>(game_id);

            case 3:
                if(game_is_gamecube(game_id)) {
                    return std::make_shared<pokemon_pc_gcnimpl>(game_id);
                } else {
                    return std::make_shared<pokemon_pc_gbaimpl>(game_id);
                }

            case 4:
            case 5:
            case 6:
                throw pkmn::unimplemented_error();

            default:
                throw std::invalid_argument("Invalid game.");
        };
    }

    pokemon_pc_impl::pokemon_pc_impl(
        int game_id
    ): _p_native(nullptr),
       _game_id(game_id),
       _generation(pkmn::database::game_id_to_generation(game_id))
    {}

    pkmn::e_game pokemon_pc_impl::get_game()
    {
        return pkmn::database::game_id_to_enum(_game_id);
    }

    const pkmn::pokemon_box::sptr& pokemon_pc_impl::get_box(
        int index
    )
    {
        int num_boxes = get_num_boxes();
        pkmn::enforce_bounds("Box index", index, 0, (num_boxes-1));

        boost::lock_guard<pokemon_pc_impl> lock(*this);

        return _box_list.at(index);
    }

    const pkmn::pokemon_box_list_t& pokemon_pc_impl::as_vector()
    {
        boost::lock_guard<pokemon_pc_impl> lock(*this);

        return _box_list;
    }

    const std::vector<std::string>& pokemon_pc_impl::get_box_names()
    {
        if(_generation == 1)
        {
            throw pkmn::feature_not_in_game_error("Box names", "Generation I");
        }

        boost::lock_guard<pokemon_pc_impl> lock(*this);

        _update_box_names();
        return _box_names;
    }

    void* pokemon_pc_impl::get_native()
    {
        boost::lock_guard<pokemon_pc_impl> lock(*this);

        _to_native();

        return _p_native;
    }
}
