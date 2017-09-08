/*
 * Copyright (c) 2016-2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef PKMN_POKEMON_GEN2IMPL_HPP
#define PKMN_POKEMON_GEN2IMPL_HPP

#include "pokemon_impl.hpp"

#include <pksav/gen2/pokemon.h>

namespace pkmn {

    class pokemon_gen2impl: public pokemon_impl {
        public:
            pokemon_gen2impl() {}
            pokemon_gen2impl(
                pkmn::database::pokemon_entry&& database_entry,
                int level
            );
            pokemon_gen2impl(
                pksav_gen2_pc_pokemon_t* pc,
                int game_id
            );
            pokemon_gen2impl(
                pksav_gen2_party_pokemon_t* party,
                int game_id
            );
            pokemon_gen2impl(
                const pksav_gen2_pc_pokemon_t& pc,
                int game_id
            );
            pokemon_gen2impl(
                const pksav_gen2_party_pokemon_t& party,
                int game_id
            );

            ~pokemon_gen2impl();

            pokemon::sptr to_game(
                const std::string& game
            );

            void set_form(
                const std::string &form
            );

            std::string get_nickname();

            void set_nickname(
                const std::string &nickname
            );

            std::string get_gender();

            void set_gender(
                const std::string &gender
            );

            bool is_shiny();

            void set_shininess(
                bool value
            );

            std::string get_held_item();

            void set_held_item(
                const std::string &held_item
            );

            std::string get_trainer_name();

            void set_trainer_name(
                const std::string &trainer_name
            );

            uint16_t get_trainer_public_id();

            uint16_t get_trainer_secret_id();

            uint32_t get_trainer_id();

            void set_trainer_public_id(
                uint16_t public_id
            );

            void set_trainer_secret_id(
                uint16_t secret_id
            );

            void set_trainer_id(
                uint32_t id
            );

            std::string get_trainer_gender();

            void set_trainer_gender(
                const std::string &gender
            );

            int get_friendship();

            void set_friendship(
                int friendship
            );

            std::string get_ability();

            void set_ability(
                const std::string &ability
            );

            std::string get_ball();

            void set_ball(
                const std::string &ball
            );

            int get_level_met();

            void set_level_met(
                int level
            );

            std::string get_location_met(
                bool as_egg
            );

            void set_location_met(
                const std::string &location,
                bool as_egg
            );

            std::string get_original_game();

            void set_original_game(
                const std::string &game
            );

            uint32_t get_personality();

            void set_personality(
                uint32_t personality
            );

            int get_experience();

            void set_experience(
                int experience
            );

            int get_level();

            void set_level(
                int level
            );

            void set_IV(
                const std::string &stat,
                int value
            );

            void set_marking(
                const std::string &marking,
                bool value
            );

            void set_ribbon(
                const std::string &ribbon,
                bool value
            );

            void set_contest_stat(
                const std::string &stat,
                int value
            );

            void set_move(
                const std::string &move,
                int index
            );

            void set_EV(
                const std::string &stat,
                int value
            );

        private:
            void _populate_party_data();

            void _update_moves(
                int index
            );

            void _update_held_item();
            void _update_EV_map();
            void _update_stat_map();

            void _set_unown_form_from_IVs();
            void _set_unown_IVs_from_form(
                const std::string &form
            );

            std::string _nickname, _trainer_name;
    };

}

#endif /* PKMN_POKEMON_GEN2IMPL_HPP */