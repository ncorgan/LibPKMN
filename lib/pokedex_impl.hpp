/*
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef PKMN_POKEDEX_IMPL_HPP
#define PKMN_POKEDEX_IMPL_HPP

#include <pkmn/pokedex.hpp>

#include <boost/thread/lockable_adapter.hpp>
#include <boost/thread/recursive_mutex.hpp>

namespace pkmn
{
    class pokedex_impl: public pokedex,
                        private boost::noncopyable,
                        public boost::basic_lockable_adapter<boost::recursive_mutex>
    {
        public:
            pokedex_impl() {}
            pokedex_impl(
                int game_id
            );

            virtual ~pokedex_impl() {};

            pokedex_impl(pokedex_impl&&) = default;
            pokedex_impl& operator=(pokedex_impl&&) = default;

            std::string get_game() override final;

            void set_has_seen(
                const std::string& species,
                bool has_seen_value
            ) override final;

            const std::vector<std::string>& get_all_seen() override final;

            int get_num_seen() override final;

            void set_has_caught(
                const std::string& species,
                bool has_caught_value
            ) override final;

            const std::vector<std::string>& get_all_caught() override final;

            int get_num_caught() override final;

            void* get_native() override final;

        protected:
            int _game_id;
            int _generation;
            size_t _num_pokemon;

            std::vector<std::string> _all_seen;
            bool _dirty_seen;

            std::vector<std::string> _all_caught;
            bool _dirty_caught;

            void* _native_ptr;
            bool _our_mem;

            void _update_member_vector_with_pksav(
                const uint8_t* native_list,
                std::vector<std::string>& member_vector
            );

            virtual void _set_has_seen(
                int species_id,
                bool has_seen_value
            ) = 0;
            virtual void _set_has_caught(
                int species_id,
                bool has_caught_value
            ) = 0;

            virtual void _update_all_seen() = 0;
            virtual void _update_all_caught() = 0;
    };
}

#endif /* PKMN_POKEDEX_IMPL_HPP */
