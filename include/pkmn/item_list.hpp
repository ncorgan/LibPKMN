/*
 * Copyright (c) 2016 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef PKMN_ITEM_LIST_HPP
#define PKMN_ITEM_LIST_HPP

#include <pkmn/config.hpp>
#include <pkmn/item_slot.hpp>

#include <pkmn/types/shared_ptr.hpp>

namespace pkmn {

    class PKMN_API item_list {
        public:
            typedef pkmn::shared_ptr<item_list> sptr;

            static sptr make(
                const std::string &name,
                const std::string &game
            );

            #ifndef __DOXYGEN__
            item_list() {};
            virtual ~item_list() {};
            #endif

            virtual std::string get_name() = 0;

            virtual std::string get_game() = 0;

            virtual int get_capacity() = 0;

            virtual int get_num_items() = 0;

            virtual const pkmn::item_slot_t& at(
                int position
            ) = 0;

            virtual const pkmn::item_slots_t& as_vector() = 0;

            #ifndef __DOXYGEN__
            virtual void* get_native() = 0;
            #endif
    };

}

#endif /* PKMN_ITEM_LIST_HPP */