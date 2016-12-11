/*
 * Copyright (c) 2016 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef PKMN_POKEMON_IMPL_HPP
#define PKMN_POKEMON_IMPL_HPP

#include <pkmn/pokemon.hpp>

#include <pksav/common/stats.h>

#include <boost/assign.hpp>
#include <boost/noncopyable.hpp>
#include <boost/thread/mutex.hpp>

#include <stdexcept>
#include <map>

static const std::map<std::string, pksav_battle_stat_t> pkmn_stats_to_pksav = boost::assign::map_list_of
    ("HP",              PKSAV_STAT_HP)
    ("Attack",          PKSAV_STAT_ATTACK)
    ("Defense",         PKSAV_STAT_DEFENSE)
    ("Speed",           PKSAV_STAT_SPEED)
    ("Special",         PKSAV_STAT_SPECIAL)
    ("Special Attack",  PKSAV_STAT_SPATK)
    ("Special Defense", PKSAV_STAT_SPDEF)
;

#define POKEMON_LOCK_MEMORY_MUTEXES() \
    boost::mutex::scoped_lock native_pc_lock(_native_pc_mutex); \
    boost::mutex::scoped_lock native_party_lock(_native_party_mutex);

namespace pkmn {

    class pokemon_impl: public pokemon, public boost::noncopyable {
        public:
            pokemon_impl() {}
            pokemon_impl(
                int pokemon_index,
                int game_id
            );

            virtual ~pokemon_impl() {}

            std::string get_species();

            std::string get_form();

            std::string get_game();

            const pkmn::database::pokemon_entry& get_database_entry();

            const pkmn::database::item_entry& get_held_item();

            const std::map<std::string, bool>& get_markings();

            const std::map<std::string, bool>& get_ribbons();

            const pkmn::move_slots_t& get_moves();

            const std::map<std::string, int>& get_EVs();

            const std::map<std::string, int>& get_IVs();

            const std::map<std::string, int>& get_stats();

            void* get_native_pc_data();

            void* get_native_party_data();

            // Here so other can lock them
            boost::mutex _native_pc_mutex;
            boost::mutex _native_party_mutex;

        protected:
            pkmn::move_slots_t _moves;
            std::map<std::string, int> _stats, _EVs, _IVs;
            std::map<std::string, bool> _markings, _ribbons;

            pkmn::database::pokemon_entry _database_entry;
            pkmn::database::item_entry _held_item;

            bool _our_pc_mem;
            bool _our_party_mem;

            void* _native_pc;
            void* _native_party;

            virtual void _calculate_stats() = 0;

            virtual void _update_moves(
                int index
            ) = 0;

            void _set_marking(
                const std::string &marking,
                bool value,
                uint8_t* native,
                bool gen3
            );

            template <typename native_type, typename mask_type>
            void _set_ribbon(
                const std::string &ribbon,
                bool value,
                native_type* native,
                const std::map<std::string, mask_type> &masks
            ) {
                if(masks.find(ribbon) == masks.end()) {
                    throw std::invalid_argument("Invalid ribbon.");
                }

                if(value) {
                    *native |= native_type(masks.at(ribbon));
                } else {
                    *native &= ~native_type(masks.at(ribbon));
                }

                _update_ribbons_map();
            }

            virtual void _update_held_item() = 0;
            virtual void _update_markings_map() = 0;
            virtual void _update_ribbons_map() = 0;
            virtual void _update_EV_map() = 0;
            virtual void _update_IV_map() = 0;
            virtual void _update_stat_map() = 0;
    };

}

#endif /* PKMN_POKEMON_IMPL_HPP */
