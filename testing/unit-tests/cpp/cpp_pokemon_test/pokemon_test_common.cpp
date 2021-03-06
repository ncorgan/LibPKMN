/*
 * Copyright (c) 2017-2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "pokemon_test_common.hpp"

#include "private_exports.hpp"
#include "pksav/enum_maps.hpp"
#include "types/rng.hpp"

#include <pkmntest/util.hpp>

#include <pkmn/exception.hpp>
#include <pkmn/enums/enum_to_string.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

#include <limits>

namespace fs = boost::filesystem;

// TODO: test nature, look for other missing coverage

// These are actually one more than the max, but we need this for the modulo.
BOOST_STATIC_CONSTEXPR int GB_EV_MAX     = 65536;
BOOST_STATIC_CONSTEXPR int MODERN_EV_MAX = 256;

BOOST_STATIC_CONSTEXPR int GB_IV_MAX     = 16;
BOOST_STATIC_CONSTEXPR int MODERN_IV_MAX = 32;

BOOST_STATIC_CONSTEXPR int STAT_MAX      = 65536;

static void check_initial_values(
    const pkmn::pokemon::sptr& pokemon
)
{
    pkmn::e_game game = pokemon->get_game();

    int generation = pkmn::priv::game_enum_to_generation(game);
    EXPECT_EQ("Standard", pokemon->get_form());

    EXPECT_EQ(
        pkmn::e_condition::NONE,
        pokemon->get_condition()
    ) << pkmn::condition_to_string(pokemon->get_condition());

    if(generation >= 5)
    {
        EXPECT_EQ(
            pokemon->get_database_entry().get_species_name(),
            pokemon->get_nickname()
        );
    }
    else
    {
        EXPECT_EQ(
            boost::algorithm::to_upper_copy(pokemon->get_database_entry().get_species_name()),
            pokemon->get_nickname()
        );
    }
    EXPECT_EQ(pkmn::pokemon::DEFAULT_TRAINER_NAME, pokemon->get_original_trainer_name());

    if(generation >= 2)
    {
        EXPECT_EQ(pkmn::e_item::NONE, pokemon->get_held_item());
    }

    EXPECT_EQ(pkmn::e_gender::MALE, pokemon->get_original_trainer_gender());
    EXPECT_EQ(uint16_t(pkmn::pokemon::DEFAULT_TRAINER_ID & 0xFFFF), pokemon->get_original_trainer_public_id());

    if(generation >= 3) {
        EXPECT_EQ(uint16_t((pkmn::pokemon::DEFAULT_TRAINER_ID & 0xFFFF0000) >> 16), pokemon->get_original_trainer_secret_id());
        EXPECT_EQ(pkmn::pokemon::DEFAULT_TRAINER_ID, pokemon->get_original_trainer_id());
    } else {
        EXPECT_EQ((pkmn::pokemon::DEFAULT_TRAINER_ID & 0xFFFF), pokemon->get_original_trainer_id());
    }

    if(generation >= 2) {
        EXPECT_EQ(pokemon->get_database_entry().get_base_friendship(), pokemon->get_current_trainer_friendship());
    }

    if(generation >= 3)
    {
        EXPECT_EQ(pkmn::e_ball::POKE_BALL, pokemon->get_ball());

        // There is no distinction between Colosseum and XD in the game storage.
        if((game == pkmn::e_game::COLOSSEUM) || (game == pkmn::e_game::XD))
        {
            EXPECT_EQ(pkmn::e_game::COLOSSEUM, pokemon->get_original_game());
        }
        else
        {
            EXPECT_EQ(game, pokemon->get_original_game());
        }
    }

    EXPECT_EQ(
        pokemon->get_database_entry().get_experience_at_level(30),
        pokemon->get_experience()
    );
    EXPECT_EQ(30, pokemon->get_level());

    if(generation >= 2) {
        EXPECT_EQ(pokemon->get_level(), pokemon->get_level_met());
    }

    EXPECT_TRUE(fs::exists(pokemon->get_icon_filepath()));
    EXPECT_TRUE(fs::exists(pokemon->get_sprite_filepath()));

    EXPECT_EQ(pokemon->get_current_hp(), pokemon->get_stats().at(pkmn::e_stat::HP));
}

static void check_initial_maps(
    const pkmn::pokemon::sptr& pokemon
) {
    int generation = pkmn::priv::game_enum_to_generation(pokemon->get_game());

    const std::map<pkmn::e_stat, int>& EVs = pokemon->get_EVs();
    EXPECT_EQ(1, EVs.count(pkmn::e_stat::HP));
    EXPECT_EQ(1, EVs.count(pkmn::e_stat::ATTACK));
    EXPECT_EQ(1, EVs.count(pkmn::e_stat::DEFENSE));
    EXPECT_EQ(1, EVs.count(pkmn::e_stat::SPEED));
    if(generation >= 3) {
        EXPECT_EQ(0, EVs.count(pkmn::e_stat::SPECIAL));
        EXPECT_EQ(1, EVs.count(pkmn::e_stat::SPECIAL_ATTACK));
        EXPECT_EQ(1, EVs.count(pkmn::e_stat::SPECIAL_DEFENSE));
    } else {
        EXPECT_EQ(1, EVs.count(pkmn::e_stat::SPECIAL));
        EXPECT_EQ(0, EVs.count(pkmn::e_stat::SPECIAL_ATTACK));
        EXPECT_EQ(0, EVs.count(pkmn::e_stat::SPECIAL_DEFENSE));
    }
    for(auto EV_iter = EVs.begin(); EV_iter != EVs.end(); ++EV_iter)
    {
        EXPECT_EQ(EV_iter->second, 0) << int(EV_iter->first);
    }

    const std::map<pkmn::e_stat, int>& IVs = pokemon->get_IVs();
    EXPECT_EQ(1, IVs.count(pkmn::e_stat::HP));
    EXPECT_EQ(1, IVs.count(pkmn::e_stat::ATTACK));
    EXPECT_EQ(1, IVs.count(pkmn::e_stat::DEFENSE));
    EXPECT_EQ(1, IVs.count(pkmn::e_stat::SPEED));
    if(generation >= 3) {
        EXPECT_EQ(0, IVs.count(pkmn::e_stat::SPECIAL));
        EXPECT_EQ(1, IVs.count(pkmn::e_stat::SPECIAL_ATTACK));
        EXPECT_EQ(1, IVs.count(pkmn::e_stat::SPECIAL_DEFENSE));
    } else {
        EXPECT_EQ(1, IVs.count(pkmn::e_stat::SPECIAL));
        EXPECT_EQ(0, IVs.count(pkmn::e_stat::SPECIAL_ATTACK));
        EXPECT_EQ(0, IVs.count(pkmn::e_stat::SPECIAL_DEFENSE));
    }
    for(auto IV_iter = IVs.begin(); IV_iter != IVs.end(); ++IV_iter) {
        EXPECT_GE(IV_iter->second, 0);
        EXPECT_LE(IV_iter->second, (generation >= 3) ? MODERN_IV_MAX : GB_IV_MAX);
    }

    const std::map<pkmn::e_stat, int>& stats = pokemon->get_stats();
    EXPECT_EQ(1, stats.count(pkmn::e_stat::HP));
    EXPECT_EQ(1, stats.count(pkmn::e_stat::ATTACK));
    EXPECT_EQ(1, stats.count(pkmn::e_stat::DEFENSE));
    EXPECT_EQ(1, stats.count(pkmn::e_stat::SPEED));
    if(generation >= 2) {
        EXPECT_EQ(0, stats.count(pkmn::e_stat::SPECIAL));
        EXPECT_EQ(1, stats.count(pkmn::e_stat::SPECIAL_ATTACK));
        EXPECT_EQ(1, stats.count(pkmn::e_stat::SPECIAL_DEFENSE));
    } else {
        EXPECT_EQ(1, stats.count(pkmn::e_stat::SPECIAL));
        EXPECT_EQ(0, stats.count(pkmn::e_stat::SPECIAL_ATTACK));
        EXPECT_EQ(0, stats.count(pkmn::e_stat::SPECIAL_DEFENSE));
    }
    for(auto stat_iter = stats.begin(); stat_iter != stats.end(); ++stat_iter) {
        EXPECT_GE(stat_iter->second, 0);
        EXPECT_LE(stat_iter->second, STAT_MAX);
    }

    if(generation >= 3)
    {
        const std::map<pkmn::e_contest_stat, int>& contest_stats = pokemon->get_contest_stats();
        EXPECT_EQ(1, contest_stats.count(pkmn::e_contest_stat::COOL));
        EXPECT_EQ(1, contest_stats.count(pkmn::e_contest_stat::BEAUTY));
        EXPECT_EQ(1, contest_stats.count(pkmn::e_contest_stat::CUTE));
        EXPECT_EQ(1, contest_stats.count(pkmn::e_contest_stat::SMART));
        EXPECT_EQ(1, contest_stats.count(pkmn::e_contest_stat::TOUGH));
        if(generation == 3)
        {
            EXPECT_EQ(1, contest_stats.count(pkmn::e_contest_stat::FEEL));
            EXPECT_EQ(0, contest_stats.count(pkmn::e_contest_stat::SHEEN));
        }
        else
        {
            EXPECT_EQ(0, contest_stats.count(pkmn::e_contest_stat::FEEL));
            EXPECT_EQ(1, contest_stats.count(pkmn::e_contest_stat::SHEEN));
        }
        for(const auto& contest_stat_iter: contest_stats)
        {
            EXPECT_EQ(0, contest_stat_iter.second);
        }

        const std::map<pkmn::e_marking, bool>& markings = pokemon->get_markings();
        EXPECT_EQ(1, markings.count(pkmn::e_marking::CIRCLE));
        EXPECT_EQ(1, markings.count(pkmn::e_marking::TRIANGLE));
        EXPECT_EQ(1, markings.count(pkmn::e_marking::SQUARE));
        EXPECT_EQ(1, markings.count(pkmn::e_marking::HEART));
        if(generation > 3)
        {
            EXPECT_EQ(1, markings.count(pkmn::e_marking::STAR));
            EXPECT_EQ(1, markings.count(pkmn::e_marking::DIAMOND));
        }
        else
        {
            EXPECT_EQ(0, markings.count(pkmn::e_marking::STAR));
            EXPECT_EQ(0, markings.count(pkmn::e_marking::DIAMOND));
        }
        for(const auto& marking_iter: markings)
        {
            EXPECT_FALSE(marking_iter.second);
        }
    } else {
        EXPECT_THROW(
            pokemon->get_contest_stats();
        , pkmn::feature_not_in_game_error);
        EXPECT_THROW(
            pokemon->get_markings();
        , pkmn::feature_not_in_game_error);
    }
}

static void test_image_filepaths(
    const pkmn::pokemon::sptr& pokemon
) {
    int generation = pkmn::priv::game_enum_to_generation(pokemon->get_game());

    EXPECT_TRUE(fs::exists(pokemon->get_icon_filepath()));

    if(generation >= 2) {
        static const pkmn::e_gender genders[] = {pkmn::e_gender::MALE, pkmn::e_gender::FEMALE};
        static const bool shininess[] = {false, true};

        for(int i = 0; i < 2; ++i) {
            for(int j = 0; j < 2; ++j) {
                pokemon->set_gender(genders[i]);
                pokemon->set_shininess(shininess[j]);
                EXPECT_TRUE(fs::exists(pokemon->get_sprite_filepath()));
            }
        }
    } else {
        EXPECT_TRUE(fs::exists(pokemon->get_sprite_filepath()));
    }
}

static void test_setting_ability(
    const pkmn::pokemon::sptr& pokemon
)
{
    int generation = pkmn::priv::game_enum_to_generation(pokemon->get_game());

    if(generation >= 3)
    {
        pkmn::ability_pair_t abilities = pokemon->get_database_entry().get_abilities();
        ASSERT_NE(pkmn::e_ability::NONE, abilities.first);

        pokemon->set_ability(abilities.first);
        EXPECT_EQ(abilities.first, pokemon->get_ability());
        if(abilities.second != pkmn::e_ability::NONE)
        {
            pokemon->set_ability(abilities.second);
            EXPECT_EQ(abilities.second, pokemon->get_ability());
        }

        if(generation >= 5)
        {
            pkmn::e_ability hidden_ability = pokemon->get_database_entry().get_hidden_ability();
            ASSERT_NE(pkmn::e_ability::NONE, hidden_ability);

            pokemon->set_ability(hidden_ability);
            EXPECT_EQ(hidden_ability, pokemon->get_ability());
        }

        EXPECT_THROW(
            pokemon->set_ability(pkmn::e_ability::NONE);
        , std::invalid_argument);
        EXPECT_THROW(
            pokemon->set_ability(pkmn::e_ability::WONDER_GUARD);
        , std::invalid_argument);
    }
    else
    {
        EXPECT_THROW(
            pokemon->get_ability();
        , pkmn::feature_not_in_game_error);
        EXPECT_THROW(
            pokemon->set_ability(pkmn::e_ability::WONDER_GUARD);
        , pkmn::feature_not_in_game_error);
    }
}

static void test_setting_ball(
    const pkmn::pokemon::sptr& pokemon,
    pkmn::e_ball ball,
    const std::vector<pkmn::e_ball>& invalid_balls
)
{
    int generation = pkmn::priv::game_enum_to_generation(pokemon->get_game());

    if(generation >= 3)
    {
        pokemon->set_ball(ball);
        EXPECT_EQ(ball, pokemon->get_ball());

        for(pkmn::e_ball invalid_ball: invalid_balls)
        {
            EXPECT_THROW(
                pokemon->set_ball(invalid_ball);
            , std::invalid_argument);
        }
    }
    else
    {
        EXPECT_THROW(
            pokemon->get_ball();
        , pkmn::feature_not_in_game_error);
        EXPECT_THROW(
            pokemon->set_ball(pkmn::e_ball::GREAT_BALL);
        , pkmn::feature_not_in_game_error);
    }
}

static void test_setting_condition(
    const pkmn::pokemon::sptr& pokemon
)
{
    int generation = pkmn::priv::game_enum_to_generation(pokemon->get_game());

    if(generation <= 2)
    {
        static const pksav::gb_condition_bimap_t& GB_CONDITION_BIMAP =
            pksav::get_gb_condition_bimap();

        for(const auto& condition_iter: GB_CONDITION_BIMAP.left)
        {
            pokemon->set_condition(condition_iter.first);
            EXPECT_EQ(
                condition_iter.first,
                pokemon->get_condition()
            ) << pkmn::condition_to_string(condition_iter.first) << " "
              << pkmn::condition_to_string(pokemon->get_condition());
        }
    }
    else
    {
        static const pksav::condition_mask_bimap_t& CONDITION_MASK_BIMAP =
            pksav::get_condition_mask_bimap();

        for(const auto& condition_iter: CONDITION_MASK_BIMAP.left)
        {
            pokemon->set_condition(condition_iter.first);
            EXPECT_EQ(
                condition_iter.first,
                pokemon->get_condition()
            ) << pkmn::condition_to_string(condition_iter.first) << " "
              << pkmn::condition_to_string(pokemon->get_condition());
        }
    }
}

static void test_setting_friendship(
    const pkmn::pokemon::sptr& pokemon
) {
    int generation = pkmn::priv::game_enum_to_generation(pokemon->get_game());

    if(generation >= 2) {
        pokemon->set_current_trainer_friendship(123);
        EXPECT_EQ(123, pokemon->get_current_trainer_friendship());
        EXPECT_THROW(
            pokemon->set_current_trainer_friendship(-1);
        , std::out_of_range);
        EXPECT_THROW(
            pokemon->set_current_trainer_friendship(256);
        , std::out_of_range);
    } else {
        EXPECT_THROW(
            pokemon->get_current_trainer_friendship();
        , pkmn::feature_not_in_game_error);
        EXPECT_THROW(
            pokemon->set_current_trainer_friendship(123);
        , pkmn::feature_not_in_game_error);
    }
}

static void test_setting_item(
    const pkmn::pokemon::sptr& pokemon,
    pkmn::e_item item,
    const std::vector<pkmn::e_item>& invalid_items
)
{
    int generation = pkmn::priv::game_enum_to_generation(pokemon->get_game());

    if(generation >= 2)
    {
        pokemon->set_held_item(item);
        EXPECT_EQ(item, pokemon->get_held_item());

        EXPECT_THROW(
            pokemon->set_held_item(pkmn::e_item::INVALID);
        , std::invalid_argument);
        for(pkmn::e_item invalid_item: invalid_items)
        {
            EXPECT_THROW(
                pokemon->set_held_item(invalid_item)
            , std::invalid_argument);
        }
    }
    else
    {
        EXPECT_THROW(
            pokemon->get_held_item();
        , pkmn::feature_not_in_game_error);
        EXPECT_THROW(
            pokemon->set_held_item(pkmn::e_item::POTION)
        , pkmn::feature_not_in_game_error);
    }
}

static void test_setting_levels(
    const pkmn::pokemon::sptr& pokemon
) {
    int generation = pkmn::priv::game_enum_to_generation(pokemon->get_game());

    EXPECT_THROW(
        pokemon->set_level(-1);
    , std::out_of_range);
    EXPECT_THROW(
        pokemon->set_level(101);
    , std::out_of_range);

    int level = 50;
    pokemon->set_level(level);
    EXPECT_EQ(level, pokemon->get_level());
    EXPECT_EQ(level, pokemon->get_database_entry().get_level_at_experience(pokemon->get_experience()));

    int experience = 123456;
    pokemon->set_experience(experience);
    EXPECT_EQ(experience, pokemon->get_experience());
    EXPECT_LT(pokemon->get_database_entry().get_experience_at_level(pokemon->get_level()-1), experience);
    EXPECT_LE(pokemon->get_database_entry().get_experience_at_level(pokemon->get_level()), experience);

    switch(generation) {
        case 1:
            EXPECT_THROW(
                pokemon->set_level(1);
            , std::out_of_range);
            EXPECT_THROW(
                pokemon->get_level_met();
            , pkmn::feature_not_in_game_error);
            EXPECT_THROW(
                pokemon->set_level_met(10);
            , pkmn::feature_not_in_game_error);
            break;

        case 2:
            EXPECT_THROW(
                pokemon->set_level(1);
            , std::out_of_range);
            EXPECT_THROW(
                pokemon->set_level_met(1);
            , std::out_of_range);
            EXPECT_THROW(
                pokemon->set_level_met(101);
            , std::out_of_range);

            pokemon->set_level_met(5);
            EXPECT_EQ(5, pokemon->get_level_met());
            break;

        default:
            EXPECT_THROW(
                pokemon->set_level(-1);
            , std::out_of_range);
            EXPECT_THROW(
                pokemon->set_level_met(-1);
            , std::out_of_range);
            EXPECT_THROW(
                pokemon->set_level_met(101);
            , std::out_of_range);

            pokemon->set_level_met(5);
            EXPECT_EQ(5, pokemon->get_level_met());
            break;
    }
}

static void test_setting_location_met(
    const pkmn::pokemon::sptr& pokemon,
    const std::string& expected_original_location,
    const std::vector<std::string> &locations,
    const std::vector<std::string> &invalid_locations
) {
    int generation = pkmn::priv::game_enum_to_generation(pokemon->get_game());
    ASSERT_GE(locations.size(), 1);

    switch(generation) {
        case 1:
            EXPECT_THROW(
                pokemon->get_location_met(true);
            , pkmn::feature_not_in_game_error);
            EXPECT_THROW(
                pokemon->set_location_met(locations[0], true);
            , pkmn::feature_not_in_game_error);
            EXPECT_THROW(
                pokemon->get_location_met(false);
            , pkmn::feature_not_in_game_error);
            EXPECT_THROW(
                pokemon->set_location_met(locations[0], false);
            , pkmn::feature_not_in_game_error);
            break;

        case 2:
        case 3:
            EXPECT_EQ(expected_original_location, pokemon->get_location_met(false));
            for(int i = 0; i < int(locations.size()); ++i) {
                pokemon->set_location_met(locations[i], false);
                EXPECT_EQ(locations[i], pokemon->get_location_met(false));
            }
            for(int i = 0; i < int(invalid_locations.size()); ++i) {
                EXPECT_THROW(
                    pokemon->set_location_met(invalid_locations[i], false);
                , std::invalid_argument);
            }

            EXPECT_THROW(
                pokemon->get_location_met(true);
            , pkmn::feature_not_in_game_error);
            EXPECT_THROW(
                pokemon->set_location_met(locations[0], true);
            , pkmn::feature_not_in_game_error);
            break;

        default:
            EXPECT_EQ(expected_original_location, pokemon->get_location_met(false));
            EXPECT_EQ(expected_original_location, pokemon->get_location_met(true));
            for(int i = 0; i < int(locations.size()); ++i) {
                pokemon->set_location_met(locations[i], true);
                EXPECT_EQ(locations[i], pokemon->get_location_met(true));

                pokemon->set_location_met(locations[i], false);
                EXPECT_EQ(locations[i], pokemon->get_location_met(false));
            }
            for(int i = 0; i < int(invalid_locations.size()); ++i) {
                EXPECT_THROW(
                    pokemon->set_location_met(invalid_locations[i], true);
                , std::invalid_argument);
                EXPECT_THROW(
                    pokemon->set_location_met(invalid_locations[i], false);
                , std::invalid_argument);
            }
            break;
    }
}

static void test_setting_markings(
    const pkmn::pokemon::sptr& pokemon
) {
    int generation = pkmn::priv::game_enum_to_generation(pokemon->get_game());

    if(generation >= 3) {
        const std::map<pkmn::e_marking, bool>& markings = pokemon->get_markings();
        for(auto markings_iter = markings.begin(); markings_iter != markings.end(); ++markings_iter) {
            std::map<pkmn::e_marking, bool> markings_before = pokemon->get_markings();
            pokemon->set_marking(markings_iter->first, true);

            for(auto markings_before_iter = markings_before.begin();
                markings_before_iter != markings_before.end();
                ++markings_before_iter
            ) {
                if(markings_before_iter->first == markings_iter->first) {
                    EXPECT_TRUE(markings_iter->second);
                } else {
                    EXPECT_EQ(markings_before_iter->second, markings.at(markings_before_iter->first));
                }
            }
        }
    } else {
        EXPECT_THROW(
            pokemon->get_markings();
        , pkmn::feature_not_in_game_error);
        EXPECT_THROW(
            pokemon->set_marking(pkmn::e_marking::CIRCLE, true);
        , pkmn::feature_not_in_game_error);
    }
}

static void test_setting_moves(
    const pkmn::pokemon::sptr& pokemon,
    const std::vector<pkmn::e_move> &moves,
    const std::vector<pkmn::e_move> &invalid_moves
)
{
    ASSERT_EQ(4, moves.size());

    std::vector<pkmn::database::move_entry> move_entries;

    for(int move_index = 0; move_index < 4; ++move_index)
    {
        pokemon->set_move(
            moves[move_index],
            move_index
        );
        move_entries.emplace_back(
            pkmn::database::move_entry(
                moves[move_index],
                pokemon->get_game()
            )
        );
    }

    EXPECT_THROW(
        pokemon->set_move(moves[0], -1);
    , std::out_of_range);
    EXPECT_THROW(
        pokemon->set_move(moves[0], 4);
    , std::out_of_range);

    const pkmn::move_slots_t& move_slots = pokemon->get_moves();
    for(int i = 0; i < 4; ++i)
    {
        EXPECT_EQ(moves[i], move_slots.at(i).move);
        EXPECT_EQ(
            move_entries[i].get_pp(0),
            move_slots.at(i).pp
        );

        pokemon->set_move_pp(i, 0);
        EXPECT_EQ(0, move_slots.at(i).pp);

        int max_pp = move_entries[i].get_pp(3);
        pokemon->set_move_pp(i, max_pp);
        EXPECT_EQ(max_pp, move_slots.at(i).pp);
    }

    for(int i = 0; i < int(invalid_moves.size()); ++i)
    {
        EXPECT_THROW(
            pokemon->set_move(invalid_moves[i], 0);
        , std::invalid_argument);
    }
}

static void test_setting_original_game(
    const pkmn::pokemon::sptr& pokemon,
    const std::vector<pkmn::e_game> &games,
    const std::vector<pkmn::e_game> &invalid_games
) {
    int generation = pkmn::priv::game_enum_to_generation(pokemon->get_game());
    ASSERT_GE(games.size(), 1);

    if(generation >= 3) {
        for(int i = 0; i < int(games.size()); ++i) {
            pokemon->set_original_game(games[i]);
            if((games[i] == pkmn::e_game::COLOSSEUM) || (games[i] == pkmn::e_game::XD))
            {
                EXPECT_EQ(pkmn::e_game::COLOSSEUM, pokemon->get_original_game());
            }
            else
            {
                EXPECT_EQ(games[i], pokemon->get_original_game());
            }
        }
        for(int i = 0; i < int(invalid_games.size()); ++i) {
            EXPECT_THROW(
                pokemon->set_original_game(invalid_games[i]);
            , std::invalid_argument);
        }
    } else {
        EXPECT_THROW(
            pokemon->get_original_game();
        , pkmn::feature_not_in_game_error);
        EXPECT_THROW(
            pokemon->set_original_game(games[0]);
        , pkmn::feature_not_in_game_error);
    }
}

static void test_setting_personality(
    const pkmn::pokemon::sptr& pokemon
) {
    int generation = pkmn::priv::game_enum_to_generation(pokemon->get_game());

    if(generation >= 3) {
        pokemon->set_personality(0x7F3AB3A8);
        EXPECT_EQ(0x7F3AB3A8, pokemon->get_personality());
    } else {
        EXPECT_THROW(
            pokemon->get_personality();
        , pkmn::feature_not_in_game_error);
        EXPECT_THROW(
            pokemon->set_personality(0);
        , pkmn::feature_not_in_game_error);
    }
}

static void test_setting_pokerus(
    const pkmn::pokemon::sptr& pokemon
)
{
    int generation = pkmn::priv::game_enum_to_generation(pokemon->get_game());

    if(generation >= 2)
    {
        EXPECT_THROW(
            pokemon->set_pokerus_duration(-1);
        , std::out_of_range);
        EXPECT_THROW(
            pokemon->set_pokerus_duration(16);
        , std::out_of_range);

        int duration = pkmn::rng<int>().rand(1, 15);
        pokemon->set_pokerus_duration(duration);
        EXPECT_EQ(duration, pokemon->get_pokerus_duration());
    }
    else
    {
        EXPECT_THROW(
            pokemon->get_pokerus_duration();
        , pkmn::feature_not_in_game_error);
        EXPECT_THROW(
            pokemon->set_pokerus_duration(1);
        , pkmn::feature_not_in_game_error);
    }
}

static void test_setting_stats(
    const pkmn::pokemon::sptr& pokemon
) {
    int generation = pkmn::priv::game_enum_to_generation(pokemon->get_game());

    // Make sure setting EVs only impacts the specific EV.
    const std::map<pkmn::e_stat, int>& EVs = pokemon->get_EVs();
    for(auto EVs_iter = EVs.begin(); EVs_iter != EVs.end(); ++EVs_iter) {
        std::map<pkmn::e_stat, int> EVs_before = pokemon->get_EVs();
        int new_value = std::rand() % ((generation >= 3) ? MODERN_EV_MAX : GB_EV_MAX);
        pokemon->set_EV(EVs_iter->first, new_value);

        for(auto EVs_before_iter = EVs_before.begin(); EVs_before_iter != EVs_before.end(); ++EVs_before_iter) {
            if(EVs_before_iter->first == EVs_iter->first) {
                EXPECT_EQ(new_value, EVs_iter->second);
            } else {
                EXPECT_EQ(EVs_before_iter->second, EVs.at(EVs_before_iter->first));
            }
        }
    }

    if(generation >= 3) {
        // Make sure setting IVs only impacts the specific IV.
        const std::map<pkmn::e_stat, int>& IVs = pokemon->get_IVs();
        for(auto IVs_iter = IVs.begin(); IVs_iter != IVs.end(); ++IVs_iter) {
            std::map<pkmn::e_stat, int> IVs_before = pokemon->get_IVs();
            int new_value = std::rand() % MODERN_IV_MAX;
            pokemon->set_IV(IVs_iter->first, new_value);

            for(auto IVs_before_iter = IVs_before.begin(); IVs_before_iter != IVs_before.end(); ++IVs_before_iter) {
                if(IVs_before_iter->first == IVs_iter->first) {
                    EXPECT_EQ(new_value, IVs_iter->second);
                } else {
                    EXPECT_EQ(IVs_before_iter->second, IVs.at(IVs_before_iter->first));
                }
            }
        }

        // Make sure setting contest stats only impacts the specific contest stat.
        const std::map<pkmn::e_contest_stat, int>& contest_stats = pokemon->get_contest_stats();
        for(auto contest_stats_iter = contest_stats.begin(); contest_stats_iter != contest_stats.end(); ++contest_stats_iter)
        {
            std::map<pkmn::e_contest_stat, int> contest_stats_before = pokemon->get_contest_stats();
            int new_value = std::rand() % 255;
            pokemon->set_contest_stat(contest_stats_iter->first, new_value);

            for(auto contest_stats_before_iter = contest_stats_before.begin();
                contest_stats_before_iter != contest_stats_before.end();
                ++contest_stats_before_iter
            ) {
                if(contest_stats_before_iter->first == contest_stats_iter->first) {
                    EXPECT_EQ(new_value, contest_stats_iter->second)
                        << pkmn::contest_stat_to_string(contest_stats_before_iter->first);
                } else {
                    EXPECT_EQ(contest_stats_before_iter->second, contest_stats.at(contest_stats_before_iter->first))
                        << pkmn::contest_stat_to_string(contest_stats_before_iter->first);
                }
            }
        }
    } else {
        // HP is tied to every other IV, so ignore that check.
        const std::map<pkmn::e_stat, int>& IVs = pokemon->get_IVs();
        for(auto IVs_iter = IVs.begin(); IVs_iter != IVs.end(); ++IVs_iter) {
            std::map<pkmn::e_stat, int> IVs_before = pokemon->get_IVs();
            int new_value = std::rand() % GB_IV_MAX;
            pokemon->set_IV(IVs_iter->first, new_value);
            for(auto IVs_before_iter = IVs_before.begin(); IVs_before_iter != IVs_before.end(); ++IVs_before_iter) {
                if(IVs_before_iter->first == IVs_iter->first) {
                    EXPECT_EQ(new_value, IVs_iter->second);
                } else if(IVs_before_iter->first != pkmn::e_stat::HP and IVs_iter->first != pkmn::e_stat::HP) {
                    EXPECT_EQ(IVs_before_iter->second, IVs.at(IVs_before_iter->first));
                }
            }
        }
    }

    // Check bounds for setting current HP.
    const std::map<pkmn::e_stat, int>& stats = pokemon->get_stats();

    EXPECT_THROW(
        pokemon->set_current_hp(-1);
    , std::out_of_range);
    EXPECT_THROW(
        pokemon->set_current_hp(stats.at(pkmn::e_stat::HP)+1);
    , std::out_of_range);

    pokemon->set_current_hp(0);
    EXPECT_EQ(0, pokemon->get_current_hp());

    pokemon->set_current_hp(stats.at(pkmn::e_stat::HP)-1);
    EXPECT_EQ(stats.at(pkmn::e_stat::HP)-1, pokemon->get_current_hp());

    pokemon->set_current_hp(stats.at(pkmn::e_stat::HP));
    EXPECT_EQ(stats.at(pkmn::e_stat::HP), pokemon->get_current_hp());

    // Set the HP stat to lower than the current HP, and make sure it's
    // updated.
    int current_hp = pokemon->get_current_hp();
    pokemon->set_EV(pkmn::e_stat::HP, 0);
    pokemon->set_IV(pkmn::e_stat::HP, 0);
    EXPECT_LE(pokemon->get_current_hp(), current_hp);
}

static void test_setting_trainer_info(
    const pkmn::pokemon::sptr& pokemon
) {
    int generation = pkmn::priv::game_enum_to_generation(pokemon->get_game());

    EXPECT_THROW(
        pokemon->set_nickname(""),
    std::invalid_argument);
    EXPECT_THROW(
        pokemon->set_nickname("Too long nickname"),
    std::invalid_argument);
    pokemon->set_nickname("foobarbaz");
    EXPECT_EQ("foobarbaz", pokemon->get_nickname());

    EXPECT_THROW(
        pokemon->set_original_trainer_name(""),
    std::invalid_argument);
    EXPECT_THROW(
        pokemon->set_original_trainer_name("Too long trainer name"),
    std::invalid_argument);
    pokemon->set_original_trainer_name("foobar");
    EXPECT_EQ("foobar", pokemon->get_original_trainer_name());

    if(generation >= 2) {
        pokemon->set_original_trainer_gender(pkmn::e_gender::MALE);
        EXPECT_EQ(pkmn::e_gender::MALE, pokemon->get_original_trainer_gender());
        pokemon->set_original_trainer_gender(pkmn::e_gender::FEMALE);
        EXPECT_EQ(pkmn::e_gender::FEMALE, pokemon->get_original_trainer_gender());
        EXPECT_THROW(
            pokemon->set_original_trainer_gender(pkmn::e_gender::GENDERLESS);
        , std::invalid_argument);
    } else {
        EXPECT_THROW(
            pokemon->set_original_trainer_gender(pkmn::e_gender::MALE);
        , pkmn::feature_not_in_game_error);
    }

    if(generation >= 3) {
        pokemon->set_original_trainer_id(0x1234ABCD);
        EXPECT_EQ(0x1234ABCD, pokemon->get_original_trainer_id());
        EXPECT_EQ(0xABCD, pokemon->get_original_trainer_public_id());
        EXPECT_EQ(0x1234, pokemon->get_original_trainer_secret_id());

        pokemon->set_original_trainer_public_id(0x1A2B);
        EXPECT_EQ(0x12341A2B, pokemon->get_original_trainer_id());
        EXPECT_EQ(0x1A2B, pokemon->get_original_trainer_public_id());
        EXPECT_EQ(0x1234, pokemon->get_original_trainer_secret_id());

        pokemon->set_original_trainer_secret_id(0x3C4D);
        EXPECT_EQ(0x3C4D1A2B, pokemon->get_original_trainer_id());
        EXPECT_EQ(0x1A2B, pokemon->get_original_trainer_public_id());
        EXPECT_EQ(0x3C4D, pokemon->get_original_trainer_secret_id());
    } else {
        EXPECT_THROW(
            pokemon->set_original_trainer_id(0xFFFF+1)
        , std::out_of_range);
        EXPECT_THROW(
            pokemon->set_original_trainer_secret_id(0xFFFF)
        , pkmn::feature_not_in_game_error);

        pokemon->set_original_trainer_id(0xABCD);
        EXPECT_EQ(0xABCD, pokemon->get_original_trainer_id());
        EXPECT_EQ(0xABCD, pokemon->get_original_trainer_public_id());

        pokemon->set_original_trainer_public_id(0x9876);
        EXPECT_EQ(0x9876, pokemon->get_original_trainer_id());
        EXPECT_EQ(0x9876, pokemon->get_original_trainer_public_id());
    }
}

void pokemon_test_common(
    const pkmn::pokemon::sptr& pokemon,
    const pkmn_test_values_t& test_values
) {
    check_initial_maps(pokemon);
    check_initial_values(pokemon);
    test_setting_ability(pokemon);
    test_setting_ball(
        pokemon,
        test_values.valid_ball,
        test_values.invalid_balls
    );
    test_setting_condition(pokemon);
    test_image_filepaths(pokemon);
    test_setting_friendship(pokemon);
    test_setting_item(
        pokemon,
        test_values.valid_item,
        test_values.invalid_items
    );
    test_setting_levels(pokemon);
    test_setting_location_met(
        pokemon,
        test_values.expected_original_location,
        test_values.valid_locations,
        test_values.invalid_locations
    );
    test_setting_markings(pokemon);
    test_setting_moves(
        pokemon,
        test_values.moves,
        test_values.invalid_moves
    );
    test_setting_original_game(
        pokemon,
        test_values.valid_original_games,
        test_values.invalid_original_games
    );
    test_setting_personality(pokemon);
    test_setting_pokerus(pokemon);
    test_setting_stats(pokemon);
    test_setting_trainer_info(pokemon);
}
