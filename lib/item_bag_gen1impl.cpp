/*
 * Copyright (c) 2016 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#define RCAST reinterpret_cast<pksav_gen1_item_bag_t*>(_native)

#include "item_bag_gen1impl.hpp"
#include "item_list_gbimpl.hpp"

#include <pkmn/types/shared_ptr.hpp>

namespace pkmn {

    item_bag_gen1impl::item_bag_gen1impl(
        int game_id,
        void* ptr
    ): item_bag_impl(game_id)
    {
        if(ptr) {
            _native = ptr;
            _our_mem = false;
        } else {
            _native = reinterpret_cast<void*>(new pksav_gen1_item_bag_t);
            _our_mem = true;
        }

        _set_ptrs();
    }

    item_bag_gen1impl::item_bag_gen1impl(
        int game_id,
        const pksav_gen1_item_bag_t &item_bag
    ): item_bag_impl(game_id)
    {
        _native = reinterpret_cast<void*>(new pksav_gen1_item_bag_t);
        *RCAST = item_bag;
        _our_mem = true;

        _set_ptrs();
    }

    item_bag_gen1impl::~item_bag_gen1impl() {
        if(_our_mem) {
            delete RCAST;
        }
    }

    void item_bag_gen1impl::_set_ptrs() {
        _item_pockets["Items"] = pkmn::make_shared<item_list_gen1_bagimpl>(
                                     1, _game_id, _native
                                 );
    }
}