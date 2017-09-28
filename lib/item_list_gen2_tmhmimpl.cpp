/*
 * Copyright (c) 2015-2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "item_list_gen2_tmhmimpl.hpp"

#include <pksav/gen2/items.h>

#include <pkmn/database/item_entry.hpp>
#include <pkmn/exception.hpp>

#include <algorithm>
#include <cstdio>
#include <cstring>

BOOST_STATIC_CONSTEXPR int TM01_ID = 305;
BOOST_STATIC_CONSTEXPR int TM50_ID = 354;
BOOST_STATIC_CONSTEXPR int HM01_ID = 397;
BOOST_STATIC_CONSTEXPR int HM07_ID = 403;

static PKMN_CONSTEXPR_OR_INLINE bool ITEM_ID_IS_TM(int num) {
    return (num >= TM01_ID and num <= TM50_ID);
}

static PKMN_CONSTEXPR_OR_INLINE bool ITEM_ID_IS_HM(int num) {
    return (num >= HM01_ID and num <= HM07_ID);
}

#define NATIVE_RCAST reinterpret_cast<pksav_gen2_tmhm_pocket_t*>(_native)

namespace pkmn {

    item_list_gen2_tmhmimpl::item_list_gen2_tmhmimpl(
        int item_list_id,
        int game_id,
        void* ptr
    ): item_list_impl(item_list_id, game_id)
    {
        static const char* TM_FORMAT = "TM%02d";
        static const char* HM_FORMAT = "HM%02d";
        char name[5] = {0};
        for(int i = 1; i <= 50; ++i)
        {
            std::snprintf(name, sizeof(name), TM_FORMAT, i);
            _item_slots[i-1].item = name;
        }
        for(int i = 1; i <= 7; ++i)
        {
            std::snprintf(name, sizeof(name), HM_FORMAT, i);
            _item_slots[50+i-1].item = name;
        }

        if(ptr)
        {
            _native = ptr;
            _our_mem = false;

            _from_native();
        }
        else
        {
            _native = reinterpret_cast<void*>(new pksav_gen2_tmhm_pocket_t);
            std::memset(_native, 0, sizeof(pksav_gen2_tmhm_pocket_t));
            _our_mem = true;
        }
    }

    item_list_gen2_tmhmimpl::~item_list_gen2_tmhmimpl() {
        item_list_scoped_lock lock(this);

        if(_our_mem) {
            delete NATIVE_RCAST;
        }
    }

    int item_list_gen2_tmhmimpl::get_num_items() {
        item_list_scoped_lock lock(this);

        int ret = 0;
        for(int i = 0; i < 50; i++) {
            if(NATIVE_RCAST->tm_count[i] > 0) {
                ++ret;
            }
        }
        for(int i = 0; i < 7; i++) {
            if(NATIVE_RCAST->hm_count[i] > 0) {
                ++ret;
            }
        }

        return ret;
    }

    void item_list_gen2_tmhmimpl::add(
        const std::string &name,
        int amount
    ) {
        if(amount < 1 or amount > 99) {
            pkmn::throw_out_of_range("amount", 1, 99);
        }

        pkmn::database::item_entry item(name, get_game());
        if(item.get_pocket() != get_name()) {
            throw std::invalid_argument("This item is not valid for this list.");
        }

        int item_id = item.get_item_id();
        int position = -1;
        if(ITEM_ID_IS_TM(item_id)) {
            position = item_id - TM01_ID;
        } else if(ITEM_ID_IS_HM(item_id)) {
            position = item_id - 347;
        } else {
            throw std::invalid_argument("Invalid item.");
        }

        int new_amount = _item_slots[position].amount + amount;
        _item_slots[position].amount = std::min<int>(99, new_amount);
        _to_native(position);
    }

    void item_list_gen2_tmhmimpl::remove(
        const std::string &name,
        int amount
    ) {
        if(amount < 1 or amount > 99) {
            pkmn::throw_out_of_range("amount", 1, 99);
        }

        pkmn::database::item_entry item(name, get_game());
        if(item.get_pocket() != get_name()) {
            throw std::invalid_argument("This item is not valid for this list.");
        }

        int item_id = item.get_item_id();
        int position = -1;
        if(ITEM_ID_IS_TM(item_id)) {
            position = item_id - TM01_ID;
        } else if(ITEM_ID_IS_HM(item_id)) {
            position = item_id - 347;
        } else {
            throw std::runtime_error("Invalid item.");
        }

        int new_amount = _item_slots[position].amount - amount;
        _item_slots[position].amount = std::max<int>(0, new_amount);
        _to_native(position);
    }

    void item_list_gen2_tmhmimpl::move(
        PKMN_UNUSED(int position1),
        PKMN_UNUSED(int position2)
    ) {
        throw pkmn::feature_not_in_game_error("Cannot move items in this pocket.");
    }

    void item_list_gen2_tmhmimpl::set_item(
        int position,
        const std::string& item_name,
        int amount
    )
    {
        // Input validation.
        int end_boundary = std::min<int>(_num_items, _capacity-1);
        if(position < 0 or position >= end_boundary)
        {
            pkmn::throw_out_of_range("position", 0, end_boundary);
        }
        pkmn::database::item_entry entry(item_name, get_game());
        if(item_name != "None" and entry.get_pocket() != get_name())
        {
            throw std::invalid_argument("This item does not belong in this pocket.");
        }
        if(amount < 0 or amount > 99)
        {
            pkmn::throw_out_of_range("amount", 0, 99);
        }
        if(item_name != _item_slots[position].item)
        {
            pkmn::throw_invalid_argument<std::string>("item", {_item_slots[position].item});
        }

        // No need to copy everything
        _item_slots[position].amount = amount;
    }

    void item_list_gen2_tmhmimpl::_from_native(
        PKMN_UNUSED(int index)
    ) {
        item_list_scoped_lock lock(this);

        for(size_t i = 0; i < 50; ++i) {
            _item_slots[i].amount = NATIVE_RCAST->tm_count[i];
        }
        for(size_t i = 0; i < 7; ++i) {
            _item_slots[50+i].amount = NATIVE_RCAST->hm_count[i];
        }
    }

    void item_list_gen2_tmhmimpl::_to_native(
        PKMN_UNUSED(int index)
    ) {
        item_list_scoped_lock lock(this);

        for(size_t i = 0; i < 50; ++i) {
            NATIVE_RCAST->tm_count[i] = uint8_t(_item_slots[i].amount);
        }
        for(size_t i = 0; i < 7; ++i) {
            NATIVE_RCAST->hm_count[i] = uint8_t(_item_slots[50+i].amount);
        }
    }
}
