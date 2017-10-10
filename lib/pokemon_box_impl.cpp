/*
 * Copyright (c) 2016-2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "pokemon_box_impl.hpp"
#include "pokemon_box_gbaimpl.hpp"
#include "pokemon_box_gcnimpl.hpp"

#include "pokemon_box_gbimpl.hpp"

#include "database/database_common.hpp"
#include "database/id_to_string.hpp"

#include "mem/pokemon_setter.hpp"

#include "misc_common.hpp"

#include <pkmn/exception.hpp>

#include <boost/format.hpp>

#include <stdexcept>

namespace pkmn {

    pokemon_box::sptr pokemon_box::make(
        const std::string &game
    ) {
        int game_id = pkmn::database::game_name_to_id(game);
        int generation = pkmn::database::game_id_to_generation(game_id);

        switch(generation) {
            case 1:
                return pkmn::make_shared<pokemon_box_gen1impl>(game_id);

            case 2:
                return pkmn::make_shared<pokemon_box_gen2impl>(game_id);

            case 3:
                if(game_is_gamecube(game_id)) {
                    return pkmn::make_shared<pokemon_box_gcnimpl>(game_id);
                } else {
                    return pkmn::make_shared<pokemon_box_gbaimpl>(game_id);
                }

            case 4:
            case 5:
            case 6:
                throw pkmn::unimplemented_error();

            default:
                throw std::runtime_error("Invalid game.");
        }
    }
/*
            pkmn::pokemon_list_t _pokemon_list;
            std::string _box_name;

            void* _native;
            bool _our_mem;

            boost::mutex _mem_mutex;

            int _game_id, _generation;
 */
    pokemon_box_impl::pokemon_box_impl(
        int game_id
    ): _pokemon_list(),
        _box_name(""),
        _native(nullptr),
        _our_mem(false),
        _mem_mutex(),
       _game_id(game_id),
       _generation(pkmn::database::game_id_to_generation(game_id))
    {}

    std::string pokemon_box_impl::get_game() {
        return pkmn::database::game_id_to_name(
                   _game_id
               );
    }

    pkmn::pokemon::sptr pokemon_box_impl::get_pokemon(
        int index
    ) {
        int capacity = get_capacity();
        if(index < 0 or index > (capacity-1)) {
            pkmn::throw_out_of_range("index", 0, (capacity-1));
        }

        return _pokemon_list.at(index);
    }

    void pokemon_box_impl::set_pokemon(
        int index,
        pkmn::pokemon::sptr new_pokemon
    ) {
        int capacity = get_capacity();
        if(index < 0 or index > (capacity-1)) {
            pkmn::throw_out_of_range("index", 0, (capacity-1));
        } else if(_pokemon_list.at(index)->get_native_pc_data() == new_pokemon->get_native_pc_data()) {
            throw std::invalid_argument("Cannot set a Pokémon to itself.");
        }

        // Copy the underlying memory to the box.
        pkmn::mem::set_pokemon_in_box(
            dynamic_cast<pokemon_impl*>(new_pokemon.get()),
            this,
            index
        );
    }

    const pkmn::pokemon_list_t& pokemon_box_impl::as_vector() {
        return _pokemon_list;
    }

    void* pokemon_box_impl::get_native() {
        return _native;
    }
}
