/*
 * Copyright (c) 2016 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "database_common.hpp"
#include "id_to_index.hpp"
#include "id_to_string.hpp"

#include <pkmn/database/item_entry.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/config.hpp>
#include <boost/format.hpp>

#include <stdexcept>

namespace pkmn { namespace database {

    static pkmn::database::sptr _db;

    static int version_group_id_to_item_list_id(
        int item_id,
        int version_group_id
    ) {
        if(item_id == 0 or version_group_id == 0) {
            return 0;
        }

        static BOOST_CONSTEXPR const char* query = \
            "SELECT libpkmn_list_id FROM veekun_pocket_to_libpkmn_list "
            "WHERE version_group_id=? AND veekun_pocket_id=(SELECT "
            "pocket_id FROM item_categories WHERE id=(SELECT category_id "
            "FROM items WHERE id=?))";

        return pkmn::database::query_db_bind2<int, int, int>(
                   _db, query, version_group_id, item_id
               );
    }

    /*
     * Veekun's database does not distinguish berries from other healing items,
     * but they go in separate pockets in every game past Generation II, so this
     * overrides the database query.
     */
    BOOST_STATIC_CONSTEXPR int BERRY_LIST_IDS[] = {
        -1, // None
        -1, // Red/Blue
        -1, // Yellow
        5,  // Gold/Silver
        10, // Crystal
        18, // Ruby/Sapphire
        24, // Emerald
        30, // FireRed/LeafGreen
        37, // Diamond/Pearl
        45, // Platinum
        53, // HeartGold/SoulSilver
        60, // Black/White
        66, // Colosseum
        73, // XD
        79, // Black 2/White 2
        84, // X/Y
        89  // Omega Ruby/Alpha Sapphire
    };

    item_entry::item_entry(
        int item_index,
        int game_id
    ):
        _item_index(item_index),
        _game_id(game_id),
        _none(item_index == 0)
    {
        // Connect to database
        pkmn::database::get_connection(_db);

        // Get item information. This also serves as input validation.
        try {
            _item_id = pkmn::database::item_index_to_id(
                           _item_index, _game_id
                       );
            _invalid = false;
        } catch(const std::invalid_argument&) {
            _item_id = -1;
            _invalid = true;
        }

        /*
         * Get version information. This gives us the information we need
         * to get version-specific information.
         */
        _generation = pkmn::database::game_id_to_generation(
                          _game_id
                      );
        _version_group_id = pkmn::database::game_id_to_version_group(
                                _game_id
                            );

        if(_invalid) {
            _item_list_id = -1;
        } else {
            // Overrides
            std::string name = this->get_name();
            if(name.find("Berry") != std::string::npos) {
                _item_list_id = BERRY_LIST_IDS[_version_group_id];
            } else {
                _item_list_id = pkmn::database::version_group_id_to_item_list_id(
                                    _item_id, _version_group_id
                                );
            }
        }
    }

    item_entry::item_entry(
        const std::string &item_name,
        const std::string &game_name
    ):
        _none(item_name == "None"),
        _invalid(false)
    {
        // Connect to database
        pkmn::database::get_connection(_db);

        /*
         * Get version information. This validates the game input and gives
         * us the information we need to get version-specific information.
         */
        _game_id = pkmn::database::game_name_to_id(
                       game_name
                   );
        _generation = pkmn::database::game_id_to_generation(
                          _game_id
                      );
        _version_group_id = pkmn::database::game_id_to_version_group(
                                _game_id
                            );

        _item_id = pkmn::database::item_name_to_id(
                       item_name
                   );
        _item_index = pkmn::database::item_id_to_index(
                          _item_id, _game_id
                      );
        _item_list_id = pkmn::database::version_group_id_to_item_list_id(
                            _item_id, _version_group_id
                        );

        // Overrides
        if(item_name.find("Berry") != std::string::npos) {
            _item_list_id = BERRY_LIST_IDS[_version_group_id];
        } else {
            _item_list_id = pkmn::database::version_group_id_to_item_list_id(
                                _item_id, _version_group_id
                            );
        }
    }

    std::string item_entry::get_name() const {
        if(_none) {
            return "None";
        } else if(_invalid) {
            return str(boost::format("Invalid (0x%x)") % _item_index);
        }

        return pkmn::database::item_id_to_name(
                   _item_id, _version_group_id
               );
    }

    std::string item_entry::get_game() const {
        return pkmn::database::game_id_to_name(
                   _game_id
               );
    }

    std::string item_entry::get_category() const {
        if(_none) {
            return "None";
        } else if(_invalid) {
            return "Unknown";
        }

        static BOOST_CONSTEXPR const char* query = \
            "SELECT name FROM item_category_prose WHERE item_category_id="
            "(SELECT category_id FROM items WHERE id=?) AND local_language_id=9";

        return pkmn::database::query_db_bind1<std::string, int>(
                   _db, query, _item_id
               );
    }

    std::string item_entry::get_pocket() const {
        if(_none) {
            return "None";
        } else if(_invalid) {
            return "Unknown";
        }

        return pkmn::database::item_list_id_to_name(
                   _item_list_id
               );
    }

    // TM/HM detection
    BOOST_STATIC_CONSTEXPR int TM01  = 305;
    BOOST_STATIC_CONSTEXPR int HM08  = 404;
    BOOST_STATIC_CONSTEXPR int TM93  = 659;
    BOOST_STATIC_CONSTEXPR int TM95  = 661;
    BOOST_STATIC_CONSTEXPR int TM96  = 745;
    BOOST_STATIC_CONSTEXPR int TM100 = 749;
    BOOST_STATIC_CONSTEXPR bool item_id_is_tmhm(
        int item_id
    ) {
        return (item_id >= TM01 and item_id <= HM08) or
               (item_id >= TM93 and item_id <= TM95) or
               (item_id >= TM96 and item_id <= TM100);
    }

    std::string item_entry::get_description() const {
        if(_none) {
            return "None";
        } else if(_invalid) {
            return get_name();
        }

        /*
         * If the item is a TM/HM, ignore what the database shows
         * as the description and show what move it teaches.
         *
         * For Gamecube games, use Ruby/Sapphire to check since
         * the indices are the same, and the database doesn't
         * know those items are in the Gamecube games.
         *
         * For Generation VI, the database has some TMs associated with
         * XY but not ORAS, so just use XY for any queries.
         */
        if(item_id_is_tmhm(_item_id)) {
            BOOST_STATIC_CONSTEXPR int RS   = 5;
            BOOST_STATIC_CONSTEXPR int ORAS = 15;

            int version_group_id = _version_group_id;
            if(version_group_id == 12 or version_group_id == 13) {
                version_group_id = RS;
            } else if(version_group_id == 16) {
                version_group_id = ORAS;
            }

            static BOOST_CONSTEXPR const char* tmhm_move_query =
                "SELECT name FROM move_names WHERE local_language_id=9 AND move_id="
                "(SELECT move_id FROM machines WHERE version_group_id=? "
                "AND item_id=?)";

            std::string move_name = pkmn::database::query_db_bind2<std::string, int, int>(
                                        _db, tmhm_move_query, version_group_id, _item_id
                                    );

            static boost::format tmhm_desc("Teaches the move %s.");
            return str(tmhm_desc % move_name.c_str());

        } else {
            /*
             * Veekun's database has no item flavor text for Generations I-II,
             * so if this entry corresponds to one of those games, the query
             * will likely fail. In that case, fall back on the flavor text
             * from X/Y.
             */

            static BOOST_CONSTEXPR const char* main_query = \
                "SELECT flavor_text FROM item_flavor_text WHERE item_id=? "
                "AND version_group_id=? AND language_id=9";

            std::string from_db = "";
            if(not pkmn::database::maybe_query_db_bind2<std::string, int, int>(
                   _db, main_query, from_db, _item_id, _version_group_id
              ))
            {
                static BOOST_CONSTEXPR const char* fallback_query = \
                    "SELECT flavor_text FROM item_flavor_text WHERE item_id=? "
                    "AND version_group_id=15 AND language_id=9";

                from_db = pkmn::database::query_db_bind1<std::string, int>(
                              _db, fallback_query, _item_id
                          );
            }

            return fix_veekun_whitespace(from_db);
        }
    }

    int item_entry::get_cost() const {
        if(_none or _invalid) {
            return -1;
        }

        static BOOST_CONSTEXPR const char* query = \
            "SELECT cost FROM items WHERE id=?";

        return pkmn::database::query_db_bind1<int, int>(
                   _db, query, _item_id
               );
    }

    bool item_entry::holdable() const {
        // Items could not be held in Generation I
        if(_none or _invalid or _generation == 1) {
            return false;
        }

        /*
         * Veekun's database is horribly inconsistent in its item flags,
         * probably due to contributors not caring. Rather than go through
         * and fix all of it, it's easier just to fake it here and pretend
         * we queried the database.
         */
        std::string name = this->get_name();
        if(name.find("Ball") != std::string::npos and _item_id != 1013) { // GS Ball
            return true;
        } else if(name.find("Berry") != std::string::npos) {
            return true;
        } else if(boost::algorithm::ends_with(name, "ite") and
                  (name.find("Meteor") == std::string::npos))
        {
            return true;
        }

        static BOOST_CONSTEXPR const char* query = \
            "SELECT item_flag_id FROM item_flag_map WHERE "
            "item_id=? AND item_flag_id IN (5,6,7)";

        PKMN_UNUSED(int result);
        return pkmn::database::maybe_query_db_bind1<int, int>(
                   _db, query, result, _item_id
               );
    }

    int item_entry::get_fling_power() const {
        // Fling was introduced in Generation IV
        if(_none or _invalid or _generation < 4) {
            return -1;
        }

        static BOOST_CONSTEXPR const char* query = \
            "SELECT fling_power FROM items WHERE id=?";

        return pkmn::database::query_db_bind1<int, int>(
                   _db, query, _item_id
               );
    }

    std::string item_entry::get_fling_effect() const {
        // Fling was introduced in Generation IV
        if(_none or _generation < 4) {
            return "None";
        } else if(_invalid) {
            return "Unknown";
        }

        static BOOST_CONSTEXPR const char* query = \
            "SELECT effect FROM item_fling_effect_prose WHERE "
            "local_language_id=9 AND item_fling_effect_id="
            "(SELECT fling_effect_id FROM items WHERE id=?)";

        // Allow for no fling effect
        std::string ret;
        if(pkmn::database::maybe_query_db_bind1<std::string, int>(
               _db, query, ret, _item_id
           ))
        {
            return ret;
        } else {
            return "None";
        }
    }

}}
