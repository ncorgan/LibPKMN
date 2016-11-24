/*
 * Copyright (c) 2016 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "conversions.hpp"
#include "../database/database_common.hpp"

#include <pkmn/calculations/stats.hpp>

#include <pksav/common/stats.h>
#include <pksav/math/endian.h>

#include <boost/config.hpp>
#include <boost/format.hpp>

#include <cstring>
#include <stdexcept>

namespace pksav {

    pkmn::database::sptr _db;

    static int convert_pokemon_game_index(
        int pokemon_index,
        int from_game_id,
        int to_game_id
    ) {
        static BOOST_CONSTEXPR const char* query = \
            "SELECT game_index FROM pokemon_game_indices WHERE version_id=? "
            "AND pokemon_id=(SELECT pokemon_id FROM pokemon_game_indices WHERE "
            "game_index=? AND version_id=?)";

        return pkmn::database::query_db_bind3<int, int, int, int>(
                   _db, query, to_game_id, pokemon_index, from_game_id
               );
    }

    static int pokemon_index_to_base_happiness(
        int pokemon_index,
        int game_id
    ) {
        static BOOST_CONSTEXPR const char* query = \
            "SELECT base_happiness FROM pokemon_species WHERE id="
            "(SELECT species_id FROM pokemon WHERE id="
            "(SELECT pokemon_id FROM pokemon_game_indices WHERE "
            "version_id=? AND game_index=?))";

        return pkmn::database::query_db_bind2<int, int, int>(
                   _db, query, game_id, pokemon_index
               );
    }

    void gen1_pc_pokemon_to_gen2(
        const pksav_gen1_pc_pokemon_t* from,
        pksav_gen2_pc_pokemon_t* to
    ) {
        // Connect to database
        pkmn::database::get_connection(_db);

        std::memset(to, 0, sizeof(*to));
        to->species = uint8_t(convert_pokemon_game_index(
                          pksav_bigendian16(from->species),
                          1, 4
                      ));
        /*
         * The rest of the Gen I fields are laid out identically.
         * Gen I's catch rate corresponds to Gen II's held item.
         */
        std::memcpy(&to->held_item, &from->catch_rate, 26);
        to->friendship = uint8_t(pokemon_index_to_base_happiness(
                             pksav_bigendian16(to->species), 4
                         ));
        // Leave Pokérus field at 0

        /*
         * Leave location caught at 0, Crystal's Poké Seer can't tell where
         * traded Pokémon were caught.
         *
         * TODO: time of day, fix PKSav mask names
         */
        to->caught_data = (to->caught_data & ~PKSAV_GEN2_LEVEL_CAUGHT_MASK)
                        | (from->level << PKSAV_GEN2_LEVEL_CAUGHT_OFFSET);

        to->level = from->level;
    }

    void gen1_party_pokemon_to_gen2(
        const pksav_gen1_party_pokemon_t* from,
        pksav_gen2_party_pokemon_t* to
    ) {
        // PC data
        gen1_pc_pokemon_to_gen2(
            &from->pc,
            &to->pc
        );

        // Party data
        std::memset(&to->party_data, 0, sizeof(to->party_data));
        to->party_data.condition = from->pc.condition;
        // Leave unused field at 0
        to->party_data.current_hp = from->pc.current_hp;
        // The next four fields are identical
        memcpy(&to->party_data.max_hp, &from->party_data.max_hp, 12);
        // TODO: how does Special translate to Sp.Atk, Sp.Def?
    }

    void gen2_pc_pokemon_to_gen1(
        const pksav_gen2_pc_pokemon_t* from,
        pksav_gen1_pc_pokemon_t* to
    ) {
        // Connect to database
        pkmn::database::get_connection(_db);

        std::memset(to, 0, sizeof(*to));
        to->species = uint8_t(convert_pokemon_game_index(
                          pksav_bigendian16(from->species),
                          4, 1
                      ));

        // Current HP

        static BOOST_CONSTEXPR const char* hp_stat_query = \
            "SELECT base_stat FROM pokemon_stats WHERE pokemon_id="
            "(SELECT pokemon_id FROM pokemon_game_indices WHERE "
            "game_index=? AND version_id=1) AND stat_id=1";

        int hp_stat = pkmn::database::query_db_bind1<int, int>(
                          _db, hp_stat_query, from->species
                      );

        uint8_t IV = 0;
        pksav_get_gb_IV(
           const_cast<uint16_t*>(&from->iv_data), // PKSav TODO: make this param a const ptr
           PKSAV_STAT_HP,
           &IV
        );
        to->current_hp = pksav_bigendian16(
                             pkmn::calculations::get_gb_stat(
                                 "HP", from->level, hp_stat,
                                 pksav_bigendian16(from->ev_hp), IV
                             )
                         );

        // Keep status field at 0

        // TODO: make sure we use Generation I types

        static BOOST_CONSTEXPR const char* type1_query = \
            "SELECT game_index FROM type_game_indices WHERE "
            "generation_id=1 AND type_id=(SELECT type_id FROM "
            "pokemon_types WHERE pokemon_id=(SELECT pokemon_id "
            "FROM pokemon_game_indices WHERE version_id=4 AND "
            "game_index=?) AND slot=1)";

        to->types[0] = uint8_t(pkmn::database::query_db_bind1<int, int>(
                                   _db, type1_query,
                                   pksav_bigendian16(from->species)
                              ));

        static BOOST_CONSTEXPR const char* type2_query = \
            "SELECT game_index FROM type_game_indices WHERE "
            "generation_id=1 AND type_id=(SELECT type_id FROM "
            "pokemon_types WHERE pokemon_id=(SELECT pokemon_id "
            "FROM pokemon_game_indices WHERE version_id=4 AND "
            "game_index=?) AND slot=2)";

        int dummy_type2 = 0;
        if(pkmn::database::maybe_query_db_bind1<int, int>(
               _db, type2_query, dummy_type2,
               pksav_bigendian16(from->species)
           ))
        {
            to->types[1] = uint8_t(dummy_type2);
        } else {
            // If a Pokémon has one type, both indices match
            to->types[1] = to->types[0];
        }

        /*
         * The rest of the Gen I fields are laid out identically.
         * Gen I's catch rate corresponds to Gen II's held item.
         */
        std::memcpy(&to->catch_rate, &from->held_item, 26);
    }

    void gen2_party_pokemon_to_gen1(
        const pksav_gen2_party_pokemon_t* from,
        pksav_gen1_party_pokemon_t* to
    ) {
        // PC data
        gen2_pc_pokemon_to_gen1(
            &from->pc,
            &to->pc
        );
    }
}
