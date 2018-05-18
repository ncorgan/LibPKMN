/*
 * Copyright (c) 2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef PKMN_DAYCARE_GEN2IMPL_HPP
#define PKMN_DAYCARE_GEN2IMPL_HPP

#include "daycare_impl.hpp"

#include <boost/config.hpp>

namespace pkmn {

    class daycare_gen2impl: public daycare_impl
    {
        public:
            daycare_gen2impl(int game_id, void* p_native = nullptr);
            ~daycare_gen2impl();

            void set_levelup_pokemon(
                int position,
                const pkmn::pokemon::sptr& new_pokemon
            ) override final;

            int get_levelup_pokemon_capacity() override final;

            void set_breeding_pokemon(
                int position,
                const pkmn::pokemon::sptr& new_pokemon
            ) override final;

            int get_breeding_pokemon_capacity() override final;

            void _from_native_levelup() override final;
            void _to_native_levelup() override final;

            void _from_native_breeding() override final;
            void _to_native_breeding() override final;

            BOOST_STATIC_CONSTEXPR int LEVELUP_CAPACITY = 2;
            BOOST_STATIC_CONSTEXPR int BREEDING_CAPACITY = 2;
    };
}

#endif /* PKMN_DAYCARE_GEN2IMPL_HPP */
