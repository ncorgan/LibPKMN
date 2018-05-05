/*
 * Copyright (c) 2016-2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef PKMN_POKEMON_GEN2IMPL_HPP
#define PKMN_POKEMON_GEN2IMPL_HPP

#include "pokemon_impl.hpp"

#include <pksav/gen2/pokemon.h>

#include <boost/config/suffix.hpp>

namespace pkmn {

    BOOST_STATIC_CONSTEXPR uint8_t GEN2_EGG_ID = 0xFD;

    class pokemon_gen2impl: public pokemon_impl {
        public:
            pokemon_gen2impl() {}
            pokemon_gen2impl(
                pkmn::database::pokemon_entry&& database_entry,
                int level
            );
            pokemon_gen2impl(
                struct pksav_gen2_pc_pokemon* pc,
                int game_id
            );
            pokemon_gen2impl(
                struct pksav_gen2_party_pokemon* party,
                int game_id
            );
            pokemon_gen2impl(
                const struct pksav_gen2_pc_pokemon& pc,
                int game_id
            );
            pokemon_gen2impl(
                const struct pksav_gen2_party_pokemon& party,
                int game_id
            );

            ~pokemon_gen2impl();

            pokemon::sptr to_game(
                const std::string& game
            ) override final;

            void export_to_file(
                const std::string& filepath
            ) override final;

            void set_form(
                const std::string &form
            ) override final;

            bool is_egg() override final;

            void set_is_egg(
                bool is_egg
            ) override final;

            std::string get_condition() override final;

            void set_condition(
                const std::string& condition
            ) override final;

            std::string get_nickname() override final;

            void set_nickname(
                const std::string &nickname
            ) override final;

            std::string get_gender() override final;

            void set_gender(
                const std::string &gender
            ) override final;

            bool is_shiny() override final;

            void set_shininess(
                bool value
            ) override final;

            std::string get_held_item() override final;

            void set_held_item(
                const std::string &held_item
            ) override final;

            std::string get_nature() override final;

            void set_nature(
                const std::string& nature
            ) override final;

            int get_pokerus_duration() override final;

            void set_pokerus_duration(
                int duration
            ) override final;

            std::string get_original_trainer_name() override final;

            void set_original_trainer_name(
                const std::string &trainer_name
            ) override final;

            uint16_t get_original_trainer_public_id() override final;

            uint16_t get_original_trainer_secret_id() override final;

            uint32_t get_original_trainer_id() override final;

            void set_original_trainer_public_id(
                uint16_t public_id
            ) override final;

            void set_original_trainer_secret_id(
                uint16_t secret_id
            ) override final;

            void set_original_trainer_id(
                uint32_t id
            ) override final;

            std::string get_original_trainer_gender() override final;

            void set_original_trainer_gender(
                const std::string &gender
            ) override final;

            int get_current_trainer_friendship() override final;

            void set_current_trainer_friendship(
                int friendship
            ) override final;

            std::string get_ability() override final;

            void set_ability(
                const std::string &ability
            ) override final;

            std::string get_ball() override final;

            void set_ball(
                const std::string &ball
            ) override final;

            int get_level_met() override final;

            void set_level_met(
                int level
            ) override final;

            std::string get_location_met(
                bool as_egg
            ) override final;

            void set_location_met(
                const std::string &location,
                bool as_egg
            ) override final;

            std::string get_original_game() override final;

            void set_original_game(
                const std::string &game
            ) override final;

            uint32_t get_personality() override final;

            void set_personality(
                uint32_t personality
            ) override final;

            int get_experience() override final;

            void set_experience(
                int experience
            ) override final;

            int get_level() override final;

            void set_level(
                int level
            ) override final;

            void set_IV(
                const std::string &stat,
                int value
            ) override final;

            void set_marking(
                const std::string &marking,
                bool value
            ) override final;

            void set_ribbon(
                const std::string &ribbon,
                bool value
            ) override final;

            void set_contest_stat(
                const std::string &stat,
                int value
            ) override final;

            void set_move(
                const std::string &move,
                int index
            ) override final;

            void set_move_pp(
                int index,
                int pp
            ) override final;

            void set_EV(
                const std::string &stat,
                int value
            ) override final;

            int get_current_hp() override final;

            void set_current_hp(
                int hp
            ) override final;

        private:
            void _populate_party_data() override final;

            void _update_moves(
                int index
            ) override final;

            void _update_EV_map() override final;
            void _update_stat_map() override final;

            void _set_unown_form_from_IVs();
            void _set_unown_IVs_from_form(
                const std::string &form
            );

            std::string _nickname, _trainer_name;

            bool _is_egg;
    };

}

#endif /* PKMN_POKEMON_GEN2IMPL_HPP */
