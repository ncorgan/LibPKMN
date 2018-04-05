/*
 * Copyright (c) 2016-2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#define NATIVE_RCAST (reinterpret_cast<struct pksav_gen2_item_bag*>(_native))

#include "item_bag_gen2impl.hpp"
#include "item_list_gbimpl.hpp"
#include "item_list_gen2_tmhmimpl.hpp"

#include <boost/thread/lock_guard.hpp>

#include <cstring>

namespace pkmn {

    item_bag_gen2impl::item_bag_gen2impl(
        int game_id,
        void* ptr
    ): item_bag_impl(game_id)
    {
        if(ptr)
        {
            _native = ptr;
            _our_mem = false;
        }
        else
        {
            _native = reinterpret_cast<void*>(new struct pksav_gen2_item_bag);
            std::memset(_native, 0, sizeof(struct pksav_gen2_item_bag));
            NATIVE_RCAST->item_pocket.terminator = 0xFF;
            NATIVE_RCAST->key_item_pocket.terminator = 0xFF;
            NATIVE_RCAST->ball_pocket.terminator = 0xFF;
            _our_mem = true;
        }

        _set_ptrs();
    }

    item_bag_gen2impl::item_bag_gen2impl(
        int game_id,
        const struct pksav_gen2_item_bag &item_bag
    ): item_bag_impl(game_id)
    {
        _native = reinterpret_cast<void*>(new struct pksav_gen2_item_bag);
        *NATIVE_RCAST = item_bag;
        _our_mem = true;

        _set_ptrs();
    }

    item_bag_gen2impl::~item_bag_gen2impl()
    {
        boost::lock_guard<item_bag_gen2impl> lock(*this);

        if(_our_mem)
        {
            delete NATIVE_RCAST;
        }
    }

    void item_bag_gen2impl::_set_ptrs()
    {
        bool crystal = (_game_id == 6);

        int item_pocket_id     = crystal ? 10 : 5;
        int ball_pocket_id     = crystal ? 11 : 6;
        //int key_item_pocket_id = crystal ? 12 : 7;
        int tmhm_pocket_id     = crystal ? 13 : 8;

        // TODO: new key item pocket
        _item_pockets["Items"]    = std::make_shared<item_list_gen2_item_pocketimpl>(
                                        item_pocket_id, _game_id, &NATIVE_RCAST->item_pocket
                                    );
        _item_pockets["Balls"]    = std::make_shared<item_list_gen2_ball_pocketimpl>(
                                        ball_pocket_id, _game_id, &NATIVE_RCAST->ball_pocket
                                    );
        _item_pockets["TM/HM"]    = std::make_shared<item_list_gen2_tmhmimpl>(
                                        tmhm_pocket_id, _game_id, &NATIVE_RCAST->tmhm_pocket
                                    );
    }
}
