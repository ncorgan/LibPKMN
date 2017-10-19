/*
 * Copyright (c) 2016-2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "../pokemon_gen1impl.hpp"
#include "../pokemon_gen2impl.hpp"
#include "../pokemon_gbaimpl.hpp"
#include "../pokemon_gcnimpl.hpp"

#include "../pokemon_party_gcnimpl.hpp"

#include "../misc_common.hpp"
#include "pokemon_setter.hpp"
#include "scoped_lock.hpp"

#include <pkmn/exception.hpp>

#include <pksav/gen1/pokemon.h>
#include <pksav/gen2/pokemon.h>
#include <pksav/gba/pokemon.h>
#include <pksav/common/nds_pokemon.h>

#include <iostream>
#include <stdexcept>

#define GC_RCAST(src_ptr)   (reinterpret_cast<LibPkmGC::GC::Pokemon*>((src_ptr)))
#define COLO_RCAST(src_ptr) (reinterpret_cast<LibPkmGC::Colosseum::Pokemon*>((src_ptr)))
#define XD_RCAST(src_ptr)   (reinterpret_cast<LibPkmGC::XD::Pokemon*>((src_ptr)))

#define COLO_DCAST(src_ptr) (dynamic_cast<LibPkmGC::Colosseum::Pokemon*>((src_ptr)))
#define XD_DCAST(src_ptr)   (dynamic_cast<LibPkmGC::XD::Pokemon*>((src_ptr)))

namespace pkmn { namespace mem {

    void set_pokemon_in_box(
        pokemon_impl* new_pokemon,
        pokemon_box_impl* box,
        int index
    ) {
        pokemon_impl* box_pokemon = dynamic_cast<pokemon_impl*>(
                                        box->_pokemon_list.at(index).get()
                                    );

        // Make sure everything is ready
        pokemon_impl::pokemon_scoped_lock new_pokemon_lock(new_pokemon);
        pokemon_box_impl::pokemon_box_scoped_lock pokemon_box_lock(box);
        pokemon_impl::pokemon_scoped_lock box_pokemon_lock(box_pokemon);

        int game_id = new_pokemon->_database_entry.get_game_id();
        if(game_id != box->_game_id) {
            throw std::invalid_argument("The Pokémon and the box must be from the same game.");
        }

        void* box_ptr = box_pokemon->_native_pc;
        void* box_pc_copy = nullptr;

        switch(new_pokemon->_generation) {
            case 1:
                rcast_equal_alloc<pksav_gen1_pc_pokemon_t>(box_ptr, box_pc_copy);
                rcast_equal<pksav_gen1_pc_pokemon_t>(new_pokemon->_native_pc, box_ptr);
                box->_pokemon_list[index] = pkmn::make_shared<pokemon_gen1impl>(
                                                reinterpret_cast<pksav_gen1_pc_pokemon_t*>(box_ptr),
                                                game_id
                                            );
                // Don't set empty names.
                if(new_pokemon->get_database_entry().get_species_id() > 0) {
                    box->_pokemon_list[index]->set_nickname(new_pokemon->get_nickname());
                    box->_pokemon_list[index]->set_trainer_name(new_pokemon->get_trainer_name());
                }
                break;

            case 2:
                rcast_equal_alloc<pksav_gen2_pc_pokemon_t>(box_ptr, box_pc_copy);
                rcast_equal<pksav_gen2_pc_pokemon_t>(new_pokemon->_native_pc, box_ptr);
                box->_pokemon_list[index] = pkmn::make_shared<pokemon_gen2impl>(
                                                reinterpret_cast<pksav_gen2_pc_pokemon_t*>(box_ptr),
                                                game_id
                                            );
                // Don't set empty names.
                if(new_pokemon->get_database_entry().get_species_id() > 0) {
                    box->_pokemon_list[index]->set_nickname(new_pokemon->get_nickname());
                    box->_pokemon_list[index]->set_trainer_name(new_pokemon->get_trainer_name());
                }
                break;

            case 3:
                if(game_is_gamecube(box_pokemon->_database_entry.get_game_id())) {
                    box_pc_copy = reinterpret_cast<void*>(GC_RCAST(box_ptr)->clone());
                    if(game_id == COLOSSEUM) {
                        *COLO_DCAST(GC_RCAST(box_ptr)) = *COLO_DCAST(GC_RCAST(new_pokemon->_native_pc));
                    } else {
                        *XD_DCAST(GC_RCAST(box_ptr)) = *XD_DCAST(GC_RCAST(new_pokemon->_native_pc));
                    }

                    box->_pokemon_list[index] = pkmn::make_shared<pokemon_gcnimpl>(
                                                    GC_RCAST(box_ptr),
                                                    game_id
                                                );
                } else {
                    rcast_equal_alloc<pksav_gba_pc_pokemon_t>(box_ptr, box_pc_copy);
                    rcast_equal<pksav_gba_pc_pokemon_t>(new_pokemon->_native_pc, box_ptr);
                    box->_pokemon_list[index] = pkmn::make_shared<pokemon_gbaimpl>(
                                                    reinterpret_cast<pksav_gba_pc_pokemon_t*>(box_ptr),
                                                    game_id
                                                );
                }
                break;

            default:
                throw pkmn::unimplemented_error();
        }

        box_pokemon->_native_pc = box_pc_copy;
        box_pokemon->_our_pc_mem = true;

        new_pokemon->_our_pc_mem = false;
    }

}}
