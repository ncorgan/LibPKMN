/*
 * Copyright (c) 2016-2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "utils/floating_point_comparison.hpp"

#include <pkmn/calculations/form.hpp>
#include <pkmn/calculations/gender.hpp>
#include <pkmn/calculations/nature.hpp>
#include <pkmn/calculations/personality.hpp>
#include <pkmn/calculations/shininess.hpp>
#include <pkmn/calculations/size.hpp>
#include <pkmn/calculations/spinda_spots.hpp>
#include <pkmn/calculations/stats.hpp>

#include <pkmn/calculations/moves/critical_hit.hpp>
#include <pkmn/calculations/moves/damage.hpp>
#include <pkmn/calculations/moves/hidden_power.hpp>
#include <pkmn/calculations/moves/modifiers.hpp>
#include <pkmn/calculations/moves/natural_gift.hpp>
#include <pkmn/calculations/moves/power.hpp>

#include <pkmn/enums/enum_to_string.hpp>

#include <pkmn/database/lists.hpp>
#include <pkmn/database/move_entry.hpp>
#include <pkmn/database/pokemon_entry.hpp>

#include <pkmn/exception.hpp>
#include <pkmn/pokemon.hpp>

#include <boost/assign.hpp>

#include <gtest/gtest.h>

#include <random>
#include <ctime>
#include <limits>

TEST(cpp_calculations_test, brine_power_test)
{
    // Test invalid inputs.
    EXPECT_THROW(
        pkmn::calculations::brine_power(0, 2);
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::brine_power(0, 0);
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::brine_power(-2,-1);
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::brine_power(2,1);
    , std::out_of_range);

    const int max_hp = 10;
    const int half_hp = max_hp / 2;

    EXPECT_EQ(
        130,
        pkmn::calculations::brine_power(half_hp - 1, max_hp)
    );
    EXPECT_EQ(
        130,
        pkmn::calculations::brine_power(half_hp, max_hp)
    );
    EXPECT_EQ(
        65,
        pkmn::calculations::brine_power(half_hp + 1, max_hp)
    );
}

TEST(cpp_calculations_test, crush_grip_power_test)
{
    // Test invalid inputs.
    EXPECT_THROW(
        pkmn::calculations::crush_grip_power(0, 1, 5)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::crush_grip_power(2, 1, 5)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::crush_grip_power(1, 2, 3)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::crush_grip_power(1, 2, 7)
    , std::out_of_range);

    EXPECT_EQ(
        1,
        pkmn::calculations::crush_grip_power(1, 200, 4)
    );
    EXPECT_EQ(
        121,
        pkmn::calculations::crush_grip_power(200, 200, 4)
    );

    for(int generation = 5; generation <= 6; ++generation)
    {
        EXPECT_EQ(
            1,
            pkmn::calculations::crush_grip_power(1, 200, generation)
        );
        EXPECT_EQ(
            120,
            pkmn::calculations::crush_grip_power(200, 200, generation)
        );
    }
}

TEST(cpp_calculations_test, echoed_voice_powers_test)
{
    static const std::vector<int> expected_results = {40, 80, 120, 160, 200};
    EXPECT_EQ(expected_results, pkmn::calculations::echoed_voice_powers());
}

TEST(cpp_calculations_test, electro_ball_power_test)
{
    // Test invalid parameters.

    EXPECT_THROW(
        pkmn::calculations::electro_ball_power(0, 100)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::electro_ball_power(100, 0)
    , std::out_of_range);

    // Test expected results.

    struct electro_ball_power_test_params
    {
        int attacker_speed;
        int target_speed;
        int expected_power;
    };
    static const std::vector<electro_ball_power_test_params> test_cases =
    {
        {100, 101, 40},
        {100, 100, 60},
        {100, 51, 60},
        {100, 50, 80},
        {100, 34, 80},
        {100, 33, 120},
        {100, 32, 120},
        {100, 25, 150}
    };

    for(const auto& test_case: test_cases)
    {
        EXPECT_EQ(
            test_case.expected_power,
            pkmn::calculations::electro_ball_power(
                test_case.attacker_speed,
                test_case.target_speed
            )
        );
    }
}

TEST(cpp_calculations_test, eruption_power_test)
{
    // Test invalid inputs.
    EXPECT_THROW(
        pkmn::calculations::eruption_power(0, 1);
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::eruption_power(1, 0);
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::eruption_power(2, 1);
    , std::out_of_range);

    EXPECT_EQ(
        1,
        pkmn::calculations::eruption_power(1, 500)
    );
    EXPECT_EQ(
        75,
        pkmn::calculations::eruption_power(250, 500)
    );
    EXPECT_EQ(
        150,
        pkmn::calculations::eruption_power(500, 500)
    );
}

TEST(cpp_calculations_test, flail_power_test)
{
    // Test invalid inputs.
    EXPECT_THROW(
        pkmn::calculations::flail_power(0, 1);
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::flail_power(1, 0);
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::flail_power(2, 1);
    , std::out_of_range);

    struct flail_power_test_params
    {
        int attacker_current_hp;
        int attacker_max_hp;
        int expected_power;
    };

    static const std::vector<flail_power_test_params> test_params =
    {
        {1, 500, 200},
        {20, 500, 200},

        {21, 500, 150},
        {52, 500, 150},

        {53, 500, 100},
        {104, 500, 100},

        {105, 500, 80},
        {177, 500, 80},

        {178, 500, 40},
        {343, 500, 40},

        {344, 500, 20},
        {500, 500, 20}
    };
    for(const auto& test_param: test_params)
    {
        EXPECT_EQ(
            test_param.expected_power,
            pkmn::calculations::flail_power(
                test_param.attacker_current_hp,
                test_param.attacker_max_hp
            )
        );
    }
}

TEST(cpp_calculations_test, fling_power_test)
{
    // Test invalid inputs.
    EXPECT_THROW(
        pkmn::calculations::fling_power(pkmn::e_item::INVALID)
    , std::invalid_argument);

    struct fling_power_test_params
    {
        pkmn::e_item held_item;
        int expected_power;
    };

    static const std::vector<fling_power_test_params> test_params =
    {
        {pkmn::e_item::ORAN_BERRY, 10},
        {pkmn::e_item::HEALTH_WING, 20},
        {pkmn::e_item::POTION, 30},
        {pkmn::e_item::ICY_ROCK, 40},
        {pkmn::e_item::DUBIOUS_DISC, 50},
        {pkmn::e_item::DAMP_ROCK, 60},
        {pkmn::e_item::DRAGON_FANG, 70},
        {pkmn::e_item::DUSK_STONE, 80},
        {pkmn::e_item::THICK_CLUB, 90},
        {pkmn::e_item::RARE_BONE, 100},
        {pkmn::e_item::IRON_BALL, 130}
    };

    for(const auto& test_param: test_params)
    {
        EXPECT_EQ(
            test_param.expected_power,
            pkmn::calculations::fling_power(test_param.held_item)
        );
    }
}

TEST(cpp_calculations_test, frustration_power_test)
{
    // Test invalid inputs.
    EXPECT_THROW(
        pkmn::calculations::frustration_power(-1)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::frustration_power(256)
    , std::out_of_range);

    // Source: Bulbapedia
    EXPECT_EQ(102, pkmn::calculations::frustration_power(0));
    EXPECT_EQ(1, pkmn::calculations::frustration_power(255));
}

TEST(cpp_calculations_test, fury_cutter_powers_test)
{
    // Test invalid inputs.
    EXPECT_THROW(
        pkmn::calculations::fury_cutter_powers(1)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::fury_cutter_powers(10)
    , std::out_of_range);

    static const std::vector<int> gen_2_4_powers = {10, 20, 40, 80, 160};
    static const std::vector<int> gen5_powers = {20, 40, 80, 160};
    static const std::vector<int> gen6_powers = {40, 80, 160};

    EXPECT_EQ(
        gen_2_4_powers,
        pkmn::calculations::fury_cutter_powers(2)
    );
    EXPECT_EQ(
        gen_2_4_powers,
        pkmn::calculations::fury_cutter_powers(3)
    );
    EXPECT_EQ(
        gen_2_4_powers,
        pkmn::calculations::fury_cutter_powers(4)
    );
    EXPECT_EQ(
        gen5_powers,
        pkmn::calculations::fury_cutter_powers(5)
    );
    EXPECT_EQ(
        gen6_powers,
        pkmn::calculations::fury_cutter_powers(6)
    );
}

TEST(cpp_calculations_test, grass_knot_power_test)
{
    // Test invalid inputs.
    EXPECT_THROW(
        pkmn::calculations::grass_knot_power(-1.0f)
    , std::out_of_range);

    struct grass_knot_power_test_params
    {
        float target_weight;
        int expected_power;
    };

    static const std::vector<grass_knot_power_test_params> test_params =
    {
        {5.0f, 20},
        {15.0f, 40},
        {35.0f, 60},
        {75.0f, 80},
        {150.0f, 100},
        {250.0f, 120}
    };

    for(const auto& test_param: test_params)
    {
        EXPECT_EQ(
            test_param.expected_power,
            pkmn::calculations::grass_knot_power(test_param.target_weight)
        );
    }
}

TEST(cpp_calculations_test, gyro_ball_power_test)
{
    // Test invalid inputs.
    EXPECT_THROW(
        pkmn::calculations::gyro_ball_power(0, 50)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::gyro_ball_power(50, 0)
    , std::out_of_range);

    EXPECT_EQ(150, pkmn::calculations::gyro_ball_power(1, 500));
    EXPECT_EQ(50, pkmn::calculations::gyro_ball_power(100, 200));
    EXPECT_EQ(1, pkmn::calculations::gyro_ball_power(500, 1));
}

TEST(cpp_calculations_test, heat_crash_power_test)
{
    // Test invalid inputs
    EXPECT_THROW(
        pkmn::calculations::heat_crash_power(0.0f, 1.0f)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::heat_crash_power(1.0f, 0.0f)
    , std::out_of_range);

    struct heat_crash_power_test_params
    {
        float attacker_weight;
        float target_weight;
        int expected_power;
    };

    static const std::vector<heat_crash_power_test_params> test_params =
    {
        {200.0f, 200.0f, 40},
        {200.0f, 100.1f, 40},
        {200.0f, 100.0f, 60},
        {200.0f, 66.7f, 60},
        {200.0f, 66.6f, 80},
        {200.0f, 50.1f, 80},
        {200.0f, 50.0f, 100},
        {200.0f, 40.1f, 100},
        {200.0f, 40.0f, 120}
    };

    for(const auto& test_param: test_params)
    {
        EXPECT_EQ(
            test_param.expected_power,
            pkmn::calculations::heat_crash_power(
                test_param.attacker_weight,
                test_param.target_weight
            )
        );
    }
}

TEST(cpp_calculations_test, heavy_slam_power_test)
{
    // Test invalid inputs
    EXPECT_THROW(
        pkmn::calculations::heavy_slam_power(0.0f, 1.0f)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::heavy_slam_power(1.0f, 0.0f)
    , std::out_of_range);

    struct heavy_slam_power_test_params
    {
        float attacker_weight;
        float target_weight;
        int expected_power;
    };

    static const std::vector<heavy_slam_power_test_params> test_params =
    {
        {200.0f, 200.0f, 40},
        {200.0f, 100.1f, 40},
        {200.0f, 100.0f, 60},
        {200.0f, 66.7f, 60},
        {200.0f, 66.6f, 80},
        {200.0f, 50.1f, 80},
        {200.0f, 50.0f, 100},
        {200.0f, 40.1f, 100},
        {200.0f, 40.0f, 120}
    };

    for(const auto& test_param: test_params)
    {
        EXPECT_EQ(
            test_param.expected_power,
            pkmn::calculations::heavy_slam_power(
                test_param.attacker_weight,
                test_param.target_weight
            )
        );
    }
}

TEST(cpp_calculations_test, ice_ball_powers_test)
{
    const std::vector<int> expected_values = {30, 60, 120, 240, 480};
    EXPECT_EQ(expected_values, pkmn::calculations::ice_ball_powers());
}

TEST(cpp_calculations_test, low_kick_power_test)
{
    // Test invalid inputs.
    EXPECT_THROW(
        pkmn::calculations::low_kick_power(-1.0f, 1)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::low_kick_power(1.0f, 0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::low_kick_power(1.0f, 10)
    , std::out_of_range);

    struct low_kick_power_test_params
    {
        float target_weight;
        int expected_power;
    };
    static const std::vector<low_kick_power_test_params> test_params =
    {
        {0.1f, 20},
        {9.9f, 20},
        {10.0f, 40},
        {24.9f, 40},
        {25.0f, 60},
        {49.9f, 60},
        {50.0f, 80},
        {99.9f, 80},
        {100.0f, 100},
        {199.9f, 100},
        {200.0f, 120},
        {1000.0f, 120}
    };

    for(const auto& test_param: test_params)
    {
        for(int generation = 1; generation <= 6; ++generation)
        {
            if(generation <= 2)
            {
                // Generation I-II only have one set power,
                // regardless of target weight.
                EXPECT_EQ(
                    50,
                    pkmn::calculations::low_kick_power(
                        test_param.target_weight,
                        generation
                    )
                );
            }
            else
            {
                EXPECT_EQ(
                    test_param.expected_power,
                    pkmn::calculations::low_kick_power(
                        test_param.target_weight,
                        generation
                    )
                );
            }
        }
    }
}

TEST(cpp_calculations_test, power_trip_power_test)
{
    // Test invalid inputs.
    EXPECT_THROW(
        pkmn::calculations::power_trip_power(-1,0,0,0,0,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::power_trip_power(7,0,0,0,0,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::power_trip_power(0,-1,0,0,0,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::power_trip_power(0,7,0,0,0,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::power_trip_power(0,0,-1,0,0,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::power_trip_power(0,0,7,0,0,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::power_trip_power(0,0,0,-1,0,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::power_trip_power(0,0,0,7,0,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::power_trip_power(0,0,0,0,-1,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::power_trip_power(0,0,0,0,7,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::power_trip_power(0,0,0,0,0,-1,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::power_trip_power(0,0,0,0,0,7,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::power_trip_power(0,0,0,0,0,0,-1)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::power_trip_power(0,0,0,0,0,0,7)
    , std::out_of_range);

    EXPECT_EQ(20, pkmn::calculations::power_trip_power(0,0,0,0,0,0,0));
    EXPECT_EQ(440, pkmn::calculations::power_trip_power(0,1,2,3,4,5,6));
    EXPECT_EQ(860, pkmn::calculations::power_trip_power(6,6,6,6,6,6,6));
}

TEST(cpp_calculations_test, punishment_power_test)
{
    // Test invalid inputs.
    EXPECT_THROW(
        pkmn::calculations::punishment_power(-1,0,0,0,0,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::punishment_power(7,0,0,0,0,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::punishment_power(0,-1,0,0,0,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::punishment_power(0,7,0,0,0,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::punishment_power(0,0,-1,0,0,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::punishment_power(0,0,7,0,0,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::punishment_power(0,0,0,-1,0,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::punishment_power(0,0,0,7,0,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::punishment_power(0,0,0,0,-1,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::punishment_power(0,0,0,0,7,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::punishment_power(0,0,0,0,0,-1,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::punishment_power(0,0,0,0,0,7,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::punishment_power(0,0,0,0,0,0,-1)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::punishment_power(0,0,0,0,0,0,7)
    , std::out_of_range);

    EXPECT_EQ(60, pkmn::calculations::punishment_power(0,0,0,0,0,0,0));
    EXPECT_EQ(200, pkmn::calculations::punishment_power(0,1,2,3,4,5,6));
    EXPECT_EQ(200, pkmn::calculations::punishment_power(6,6,6,6,6,6,6));
}

TEST(cpp_calculations_test, return_power_test)
{
    // Test invalid inputs.
    EXPECT_THROW(
        pkmn::calculations::return_power(-1)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::return_power(256)
    , std::out_of_range);

    // Source: Bulbapedia
    EXPECT_EQ(1, pkmn::calculations::return_power(0));
    EXPECT_EQ(102, pkmn::calculations::return_power(255));
}

TEST(cpp_calculations_test, reversal_power_test)
{
    // Test invalid inputs.
    EXPECT_THROW(
        pkmn::calculations::reversal_power(0, 1);
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::reversal_power(1, 0);
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::reversal_power(2, 1);
    , std::out_of_range);

    struct reversal_power_test_params
    {
        int attacker_current_hp;
        int attacker_max_hp;
        int expected_power;
    };

    static const std::vector<reversal_power_test_params> test_params =
    {
        {1, 500, 200},
        {20, 500, 200},

        {21, 500, 150},
        {52, 500, 150},

        {53, 500, 100},
        {104, 500, 100},

        {105, 500, 80},
        {177, 500, 80},

        {178, 500, 40},
        {343, 500, 40},

        {344, 500, 20},
        {500, 500, 20}
    };
    for(const auto& test_param: test_params)
    {
        EXPECT_EQ(
            test_param.expected_power,
            pkmn::calculations::reversal_power(
                test_param.attacker_current_hp,
                test_param.attacker_max_hp
            )
        );
    }
}

TEST(cpp_calculations_test, rollout_powers_test)
{
    const std::vector<int> expected_values = {30, 60, 120, 240, 480};
    EXPECT_EQ(expected_values, pkmn::calculations::rollout_powers());
}

TEST(cpp_calculations_test, spit_up_power_test)
{
    // Test invalid inputs.
    EXPECT_THROW(
        pkmn::calculations::spit_up_power(-1)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::spit_up_power(4)
    , std::out_of_range);

    EXPECT_EQ(0, pkmn::calculations::spit_up_power(0));
    EXPECT_EQ(100, pkmn::calculations::spit_up_power(1));
    EXPECT_EQ(200, pkmn::calculations::spit_up_power(2));
    EXPECT_EQ(300, pkmn::calculations::spit_up_power(3));
}

TEST(cpp_calculations_test, stored_power_power_test)
{
    // Test invalid inputs.
    EXPECT_THROW(
        pkmn::calculations::stored_power_power(-1,0,0,0,0,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::stored_power_power(7,0,0,0,0,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::stored_power_power(0,-1,0,0,0,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::stored_power_power(0,7,0,0,0,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::stored_power_power(0,0,-1,0,0,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::stored_power_power(0,0,7,0,0,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::stored_power_power(0,0,0,-1,0,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::stored_power_power(0,0,0,7,0,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::stored_power_power(0,0,0,0,-1,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::stored_power_power(0,0,0,0,7,0,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::stored_power_power(0,0,0,0,0,-1,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::stored_power_power(0,0,0,0,0,7,0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::stored_power_power(0,0,0,0,0,0,-1)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::stored_power_power(0,0,0,0,0,0,7)
    , std::out_of_range);

    EXPECT_EQ(20, pkmn::calculations::stored_power_power(0,0,0,0,0,0,0));
    EXPECT_EQ(440, pkmn::calculations::stored_power_power(0,1,2,3,4,5,6));
    EXPECT_EQ(860, pkmn::calculations::stored_power_power(6,6,6,6,6,6,6));
}

TEST(cpp_calculations_test, triple_kick_powers_test)
{
    static const std::vector<int> expected_values = {10, 20, 30};
    EXPECT_EQ(expected_values, pkmn::calculations::triple_kick_powers());
}

TEST(cpp_calculations_test, trump_card_power_test)
{
    // Test invalid inputs.
    EXPECT_THROW(
        pkmn::calculations::trump_card_power(-1)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::trump_card_power(9)
    , std::out_of_range);

    static const std::vector<int> expected_results =
    {
        200, 80, 60, 50, 40, 40, 40, 40, 40
    };
    for(int remaining_pp = 0;
        remaining_pp < int(expected_results.size());
        ++remaining_pp
    )
    {
        EXPECT_EQ(
            expected_results[remaining_pp],
            pkmn::calculations::trump_card_power(remaining_pp)
        );
    }
}

TEST(cpp_calculations_test, water_spout_power_test)
{
    // Test invalid inputs.
    EXPECT_THROW(
        pkmn::calculations::water_spout_power(0, 1);
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::water_spout_power(1, 0);
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::water_spout_power(2, 1);
    , std::out_of_range);

    EXPECT_EQ(
        1,
        pkmn::calculations::water_spout_power(1, 500)
    );
    EXPECT_EQ(
        75,
        pkmn::calculations::water_spout_power(250, 500)
    );
    EXPECT_EQ(
        150,
        pkmn::calculations::water_spout_power(500, 500)
    );
}

TEST(cpp_calculations_test, wring_out_power_test)
{
    // Test invalid inputs.
    EXPECT_THROW(
        pkmn::calculations::wring_out_power(0, 1, 5)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::wring_out_power(2, 1, 5)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::wring_out_power(1, 2, 3)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::wring_out_power(1, 2, 7)
    , std::out_of_range);

    EXPECT_EQ(
        1,
        pkmn::calculations::wring_out_power(1, 200, 4)
    );
    EXPECT_EQ(
        121,
        pkmn::calculations::wring_out_power(200, 200, 4)
    );

    for(int generation = 5; generation <= 6; ++generation)
    {
        EXPECT_EQ(
            1,
            pkmn::calculations::wring_out_power(1, 200, generation)
        );
        EXPECT_EQ(
            120,
            pkmn::calculations::wring_out_power(200, 200, generation)
        );
    }
}

TEST(cpp_calculations_test, gen1_critical_hit_chance_test)
{
    // Test invalid parameters.
    EXPECT_THROW(
        pkmn::calculations::gen1_critical_hit_chance(0, false, false)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::gen1_critical_hit_chance(256, false, false)
    , std::out_of_range);

    // In Generation I, make sure there is never a guaranteed chance for
    // a critical hit.
    EXPECT_FALSE(pkmn::fp_compare_greater(
        pkmn::calculations::gen1_critical_hit_chance(255, true, true),
        (255.0f / 256.0f)
    ));
}

TEST(cpp_calculations_test, critical_hit_chance_test)
{
    // Test invalid parameters.
    EXPECT_THROW(
        pkmn::calculations::critical_hit_chance(1, 0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::critical_hit_chance(10, 0)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::critical_hit_chance(2, -1)
    , std::out_of_range);

    struct critical_hit_chance_test_params
    {
        int generation;
        int stage;
        float expected_result;
    };
    static const std::vector<critical_hit_chance_test_params> test_params =
    {
        {2, 0, 0.0625f}, {2, 1, 0.125f}, {2, 2, 0.25f}, {2, 3, 0.333f}, {2, 4, 0.5f},
        {3, 0, 0.0625f}, {3, 1, 0.125f}, {3, 2, 0.25f}, {3, 3, 0.333f}, {3, 4, 0.5f},
        {4, 0, 0.0625f}, {4, 1, 0.125f}, {4, 2, 0.25f}, {4, 3, 0.333f}, {4, 4, 0.5f},
        {5, 0, 0.0625f}, {5, 1, 0.125f}, {5, 2, 0.25f}, {5, 3, 0.333f}, {5, 4, 0.5f},
        {6, 0, 0.0625f}, {6, 1, 0.125f}, {6, 2, 0.5f},  {6, 3, 1.0f},   {6, 4, 1.0f},
    };

    for(const auto& test_param: test_params)
    {
        EXPECT_DOUBLE_EQ(
            test_param.expected_result,
            pkmn::calculations::critical_hit_chance(
                test_param.generation,
                test_param.stage
            )
        );
    }
}

TEST(cpp_calculations_test, gen1_critical_hit_modifier_test)
{
    // Test invalid parameters.
    EXPECT_THROW(
        pkmn::calculations::gen1_critical_hit_modifier(-1)
    , std::out_of_range);

    EXPECT_THROW(
        pkmn::calculations::gen1_critical_hit_modifier(256)
    , std::out_of_range);

    // The critical hit modifier is level-dependent in Generation I.
    EXPECT_DOUBLE_EQ(
        1.5f,
        pkmn::calculations::gen1_critical_hit_modifier(5)
    );
    EXPECT_DOUBLE_EQ(
        1.8f,
        pkmn::calculations::gen1_critical_hit_modifier(20)
    );
    EXPECT_DOUBLE_EQ(
        1.95f,
        pkmn::calculations::gen1_critical_hit_modifier(95)
    );
}

TEST(cpp_calculations_test, critical_hit_modifier_test)
{
    // Test invalid parameters.
    EXPECT_THROW(
        pkmn::calculations::critical_hit_modifier(1)
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::critical_hit_modifier(10)
    , std::out_of_range);

    // Past Generation I, the modifier is constant, depending on the generation.
    EXPECT_DOUBLE_EQ(
        2.0f,
        pkmn::calculations::critical_hit_modifier(2)
    );
    EXPECT_DOUBLE_EQ(
        2.0f,
        pkmn::calculations::critical_hit_modifier(3)
    );
    EXPECT_DOUBLE_EQ(
        2.0f,
        pkmn::calculations::critical_hit_modifier(4)
    );
    EXPECT_DOUBLE_EQ(
        2.0f,
        pkmn::calculations::critical_hit_modifier(5)
    );
    EXPECT_DOUBLE_EQ(
        1.5f,
        pkmn::calculations::critical_hit_modifier(6)
    );
}

TEST(cpp_calculations_test, damage_test)
{
    // Source: https://bulbapedia.bulbagarden.net/wiki/Damage#Example

    // Only taking types into account
    //
    // "Imagine a level 75 Glaceon...with an effective Attack stat of 123
    // uses Ice Fang (an Ice-type physical move with a power of 65) against
    // a Garchomp with an effective Defense stat of 163 in Generation VI,
    // and does not land a critical hit."
    //
    // The article itself results in the wrong value, but the value I'm
    // testing for below was based on its equations.
    static const int level = 75;
    static const int ice_fang_base_power = 65;
    static const float modifier_against_dragon_ground = 6.0f;
    static const int glaceon_l75_attack = 123;
    static const int garchomp_l75_defense = 163;

    int damage = pkmn::calculations::damage(
                     level,
                     ice_fang_base_power,
                     glaceon_l75_attack,
                     garchomp_l75_defense,
                     modifier_against_dragon_ground
                 );
    EXPECT_EQ(200, damage);
}

TEST(cpp_calculations_test, type_damage_modifier_test)
{
    // Test invalid inputs.

    // Invalid generation
    EXPECT_THROW(
        (void)pkmn::calculations::type_damage_modifier(
                  -1,
                  pkmn::e_type::NORMAL,
                  pkmn::e_type::NORMAL
              )
    , std::out_of_range);
    EXPECT_THROW(
        (void)pkmn::calculations::type_damage_modifier(
                  8,
                  pkmn::e_type::NORMAL,
                  pkmn::e_type::NORMAL
              )
    , std::out_of_range);

    // Invalid type for a given generation
    struct invalid_type_for_generation_t
    {
        int generation;
        pkmn::e_type type;
    };

    static const std::vector<invalid_type_for_generation_t> invalid_types_for_generation =
    {
        {1, pkmn::e_type::DARK}, {1, pkmn::e_type::STEEL},
        {5, pkmn::e_type::FAIRY},
        {3, pkmn::e_type::QUESTION_MARK}, {5, pkmn::e_type::QUESTION_MARK},
        {2, pkmn::e_type::SHADOW}, {4, pkmn::e_type::SHADOW}
    };

    for(const auto& invalid_params: invalid_types_for_generation)
    {
        // Invalid attacking type
        EXPECT_THROW(
            (void)pkmn::calculations::type_damage_modifier(
                      invalid_params.generation,
                      invalid_params.type,
                      pkmn::e_type::NORMAL
                  );
        , std::invalid_argument);

        // Invalid defending type
        EXPECT_THROW(
            (void)pkmn::calculations::type_damage_modifier(
                      invalid_params.generation,
                      pkmn::e_type::NORMAL,
                      invalid_params.type
                  );
        , std::invalid_argument);
    }

    // Check that changes between generations are properly
    // implemented.

    struct modifier_changes_t
    {
        pkmn::e_type attacking_type;
        pkmn::e_type defending_type;

        int old_generation;
        float old_modifier;

        int new_generation;
        float new_modifier;
    };

    static const std::vector<modifier_changes_t> modifier_changes_between_generations =
    {
        {pkmn::e_type::BUG,    pkmn::e_type::POISON,  1, 2.0f, 2, 0.5f},
        {pkmn::e_type::POISON, pkmn::e_type::BUG,     1, 2.0f, 2, 1.0f},
        {pkmn::e_type::GHOST,  pkmn::e_type::PSYCHIC, 1, 0.0f, 2, 2.0f},
        {pkmn::e_type::ICE,    pkmn::e_type::FIRE,    1, 1.0f, 2, 0.5f},
        {pkmn::e_type::GHOST,  pkmn::e_type::STEEL,   5, 0.5f, 6, 1.0f},
        {pkmn::e_type::DARK,   pkmn::e_type::STEEL,   5, 0.5f, 6, 1.0f},
    };

    for(const auto& modifier_changes: modifier_changes_between_generations)
    {
        EXPECT_DOUBLE_EQ(
            modifier_changes.old_modifier,
            pkmn::calculations::type_damage_modifier(
                modifier_changes.old_generation,
                modifier_changes.attacking_type,
                modifier_changes.defending_type
            )
        ) << modifier_changes.old_generation << " "
          << pkmn::type_to_string(modifier_changes.attacking_type) << " "
          << pkmn::type_to_string(modifier_changes.defending_type);
        EXPECT_DOUBLE_EQ(
            modifier_changes.new_modifier,
            pkmn::calculations::type_damage_modifier(
                modifier_changes.new_generation,
                modifier_changes.attacking_type,
                modifier_changes.defending_type
            )
        ) << modifier_changes.new_generation << " "
          << pkmn::type_to_string(modifier_changes.attacking_type) << " "
          << pkmn::type_to_string(modifier_changes.defending_type);
    }
}

TEST(cpp_calculations_test, gen2_unown_form_test) {
    /*
     * Make sure expected exceptions are thrown.
     */
    EXPECT_THROW(
        (void)pkmn::calculations::gen2_unown_form(
                  -1, 0, 0, 0
              );
    , std::out_of_range);
    EXPECT_THROW(
        (void)pkmn::calculations::gen2_unown_form(
                  16, 0, 0, 0
              );
    , std::out_of_range);
    EXPECT_THROW(
        (void)pkmn::calculations::gen2_unown_form(
                  0, -1, 0, 0
              );
    , std::out_of_range);
    EXPECT_THROW(
        (void)pkmn::calculations::gen2_unown_form(
                  0, 16, 0, 0
              );
    , std::out_of_range);
    EXPECT_THROW(
        (void)pkmn::calculations::gen2_unown_form(
                  0, 0, -1, 0
              );
    , std::out_of_range);
    EXPECT_THROW(
        (void)pkmn::calculations::gen2_unown_form(
                  0, 0, 16, 0
              );
    , std::out_of_range);
    EXPECT_THROW(
        (void)pkmn::calculations::gen2_unown_form(
                  0, 0, 0, -1
              );
    , std::out_of_range);
    EXPECT_THROW(
        (void)pkmn::calculations::gen2_unown_form(
                  0, 0, 0, 16
              );
    , std::out_of_range);

    /*
     * Make sure known good inputs result in expected results.
     *
     * Source: http://bulbapedia.bulbagarden.net/wiki/Individual_values#Unown.27s_letter
     */
    std::string form1 = pkmn::calculations::gen2_unown_form(
                            10, 9, 1, 14
                        );
    EXPECT_EQ("G", form1);

    std::string form2 = pkmn::calculations::gen2_unown_form(
                            5, 15, 10, 5
                        );
    EXPECT_EQ("S", form2);
}

TEST(cpp_calculations_test, gen3_unown_form_test) {
    /*
     * Make sure known good inputs result in expected results.
     *
     * Source: http://www.smogon.com/ingame/rng/pid_iv_creation#unown_shape
     */
    std::string form = pkmn::calculations::gen3_unown_form(
                           0x4C07DE71
                       );
    EXPECT_EQ("B", form);
}

TEST(cpp_calculations_test, wurmple_becomes_silcoon_test) {
    /*
     * Make sure known good inputs result in expected results.
     *
     * Source: http://www.smogon.com/ingame/rng/pid_iv_creation#silcoon_cascoon
     */
    bool before_gen5_1 = pkmn::calculations::wurmple_becomes_silcoon(
        0x5CF4091C, true
    );
    EXPECT_TRUE(before_gen5_1);
    bool before_gen5_2 = pkmn::calculations::wurmple_becomes_silcoon(
        0x091C5CF4, true
    );
    EXPECT_FALSE(before_gen5_2);

    bool gen5_1 = pkmn::calculations::wurmple_becomes_silcoon(
        0x091C5CF4, false
    );
    EXPECT_TRUE(gen5_1);
    bool gen5_2 = pkmn::calculations::wurmple_becomes_silcoon(
        0x5CF4091C, false
    );
    EXPECT_FALSE(gen5_2);
}

TEST(cpp_calculations_test, gen2_gender_test)
{
    /*
     * Make sure expected exceptions are thrown.
     */
    EXPECT_THROW(
       (void)pkmn::calculations::gen2_pokemon_gender(
                 pkmn::e_species::NONE, 0
             );
    , std::invalid_argument);
    EXPECT_THROW(
        pkmn::calculations::gen2_pokemon_gender(
            pkmn::e_species::BULBASAUR, -1
        );
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::gen2_pokemon_gender(
            pkmn::e_species::BULBASAUR, 16
        );
    , std::out_of_range);

    /*
     * Make sure known good inputs result in expected results.
     */

    /*
     * All male
     */
    pkmn::e_gender nidorino1_gender = pkmn::calculations::gen2_pokemon_gender(
                                          pkmn::e_species::NIDORINO, 0
                                      );
    EXPECT_EQ(pkmn::e_gender::MALE, nidorino1_gender);
    pkmn::e_gender nidorino2_gender = pkmn::calculations::gen2_pokemon_gender(
                                       pkmn::e_species::NIDORINO, 15
                                   );
    EXPECT_EQ(pkmn::e_gender::MALE, nidorino2_gender);

    /*
     * 87.5% male, 12.5% female
     */
    pkmn::e_gender charmander1_gender = pkmn::calculations::gen2_pokemon_gender(
                                            pkmn::e_species::CHARMANDER, 1
                                        );
    EXPECT_EQ(pkmn::e_gender::FEMALE, charmander1_gender);
    pkmn::e_gender charmander2_gender = pkmn::calculations::gen2_pokemon_gender(
                                            pkmn::e_species::CHARMANDER, 2
                                        );
    EXPECT_EQ(pkmn::e_gender::MALE, charmander2_gender);

    /*
     * 75% male, 25% female
     */
    pkmn::e_gender growlithe1_gender = pkmn::calculations::gen2_pokemon_gender(
                                           pkmn::e_species::GROWLITHE, 3
                                       );
    EXPECT_EQ(pkmn::e_gender::FEMALE, growlithe1_gender);
    pkmn::e_gender growlithe2_gender = pkmn::calculations::gen2_pokemon_gender(
                                           pkmn::e_species::GROWLITHE, 4
                                       );
    EXPECT_EQ(pkmn::e_gender::MALE, growlithe2_gender);

    /*
     * 50% male, 50% female
     */
    pkmn::e_gender pidgey1_gender = pkmn::calculations::gen2_pokemon_gender(
                                        pkmn::e_species::PIDGEY, 6
                                    );
    EXPECT_EQ(pkmn::e_gender::FEMALE, pidgey1_gender);
    pkmn::e_gender pidgey2_gender = pkmn::calculations::gen2_pokemon_gender(
                                        pkmn::e_species::PIDGEY, 7
                                    );
    EXPECT_EQ(pkmn::e_gender::MALE, pidgey2_gender);

    /*
     * 25% male, 75% female
     */
    pkmn::e_gender vulpix1_gender = pkmn::calculations::gen2_pokemon_gender(
                                        pkmn::e_species::VULPIX, 11
                                    );
    EXPECT_EQ(pkmn::e_gender::FEMALE, vulpix1_gender);
    pkmn::e_gender vulpix2_gender = pkmn::calculations::gen2_pokemon_gender(
                                        pkmn::e_species::VULPIX, 12
                                    );
    EXPECT_EQ(pkmn::e_gender::MALE, vulpix2_gender);

    /*
     * All female
     */
    pkmn::e_gender nidorina1_gender = pkmn::calculations::gen2_pokemon_gender(
                                          pkmn::e_species::NIDORINA, 0
                                      );
    EXPECT_EQ(pkmn::e_gender::FEMALE, nidorina1_gender);
    pkmn::e_gender nidorina2_gender = pkmn::calculations::gen2_pokemon_gender(
                                          pkmn::e_species::NIDORINA, 15
                                      );
    EXPECT_EQ(pkmn::e_gender::FEMALE, nidorina2_gender);

    /*
     * Genderless
     */
    pkmn::e_gender magnemite1_gender = pkmn::calculations::gen2_pokemon_gender(
                                           pkmn::e_species::MAGNEMITE, 0
                                       );
    EXPECT_EQ(pkmn::e_gender::GENDERLESS, magnemite1_gender);
    pkmn::e_gender magnemite2_gender = pkmn::calculations::gen2_pokemon_gender(
                                           pkmn::e_species::MAGNEMITE, 15
                                       );
    EXPECT_EQ(pkmn::e_gender::GENDERLESS, magnemite2_gender);
}

TEST(cpp_calculations_test, modern_gender_test)
{
    /*
     * Make sure expected exceptions are thrown
     */
    EXPECT_THROW(
        (void)pkmn::calculations::modern_pokemon_gender(
                  pkmn::e_species::NONE, 0
              );
    , std::invalid_argument);

    /*
     * Make sure known good inputs result in expected results.
     */

    /*
     * All male
     */
    pkmn::e_gender nidorino1_gender = pkmn::calculations::modern_pokemon_gender(
                                          pkmn::e_species::NIDORINO, 0
                                      );
    EXPECT_EQ(pkmn::e_gender::MALE, nidorino1_gender);
    pkmn::e_gender nidorino2_gender = pkmn::calculations::modern_pokemon_gender(
                                          pkmn::e_species::NIDORINO,
                                          std::numeric_limits<uint32_t>::max()
                                      );
    EXPECT_EQ(pkmn::e_gender::MALE, nidorino2_gender);

    /*
     * 87.5% male, 12.5% female
     */
    pkmn::e_gender charmander1_gender = pkmn::calculations::modern_pokemon_gender(
                                            pkmn::e_species::CHARMANDER, 30
                                        );
    EXPECT_EQ(pkmn::e_gender::FEMALE, charmander1_gender);
    pkmn::e_gender charmander2_gender = pkmn::calculations::modern_pokemon_gender(
                                            pkmn::e_species::CHARMANDER, 31
                                        );
    EXPECT_EQ(pkmn::e_gender::MALE, charmander2_gender);

    /*
     * 75% male, 25% female
     */
    pkmn::e_gender growlithe1_gender = pkmn::calculations::modern_pokemon_gender(
                                           pkmn::e_species::GROWLITHE, 63
                                       );
    EXPECT_EQ(pkmn::e_gender::FEMALE, growlithe1_gender);
    pkmn::e_gender growlithe2_gender = pkmn::calculations::modern_pokemon_gender(
                                           pkmn::e_species::GROWLITHE, 64
                                       );
    EXPECT_EQ(pkmn::e_gender::MALE, growlithe2_gender);

    /*
     * 50% male, 50% female
     */
    pkmn::e_gender pidgey1_gender = pkmn::calculations::modern_pokemon_gender(
                                        pkmn::e_species::PIDGEY, 126
                                    );
    EXPECT_EQ(pkmn::e_gender::FEMALE, pidgey1_gender);
    pkmn::e_gender pidgey2_gender = pkmn::calculations::modern_pokemon_gender(
                                        pkmn::e_species::PIDGEY, 127
                                    );
    EXPECT_EQ(pkmn::e_gender::MALE, pidgey2_gender);

    /*
     * 25% male, 75% female
     */
    pkmn::e_gender vulpix1_gender = pkmn::calculations::modern_pokemon_gender(
                                        pkmn::e_species::VULPIX, 190
                                    );
    EXPECT_EQ(pkmn::e_gender::FEMALE, vulpix1_gender);
    pkmn::e_gender vulpix2_gender = pkmn::calculations::modern_pokemon_gender(
                                        pkmn::e_species::VULPIX, 191
                                    );
    EXPECT_EQ(pkmn::e_gender::MALE, vulpix2_gender);

    /*
     * All female
     */
    pkmn::e_gender nidorina1_gender = pkmn::calculations::modern_pokemon_gender(
                                          pkmn::e_species::NIDORINA, 0
                                      );
    EXPECT_EQ(pkmn::e_gender::FEMALE, nidorina1_gender);
    pkmn::e_gender nidorina2_gender = pkmn::calculations::modern_pokemon_gender(
                                          pkmn::e_species::NIDORINA,
                                          std::numeric_limits<uint32_t>::max()
                                      );
    EXPECT_EQ(pkmn::e_gender::FEMALE, nidorina2_gender);

    /*
     * Genderless
     */
    pkmn::e_gender magnemite1_gender = pkmn::calculations::modern_pokemon_gender(
                                           pkmn::e_species::MAGNEMITE, 0
                                       );
    EXPECT_EQ(pkmn::e_gender::GENDERLESS, magnemite1_gender);
    pkmn::e_gender magnemite2_gender = pkmn::calculations::modern_pokemon_gender(
                                           pkmn::e_species::MAGNEMITE,
                                          std::numeric_limits<uint32_t>::max()
                                       );
    EXPECT_EQ(pkmn::e_gender::GENDERLESS, magnemite2_gender);
}

TEST(cpp_calculations_test, gen2_hidden_power_test)
{
    pkmn::calculations::hidden_power hidden_power;

    /*
     * Make sure expected exceptions are thrown
     */
    EXPECT_THROW(
        hidden_power = pkmn::calculations::gen2_hidden_power(
                           -1, 0, 0, 0
                       );
    , std::out_of_range);
    EXPECT_THROW(
        hidden_power = pkmn::calculations::gen2_hidden_power(
                           16, 0, 0, 0
                       );
    , std::out_of_range);
    EXPECT_THROW(
        hidden_power = pkmn::calculations::gen2_hidden_power(
                           0, -1, 0, 0
                       );
    , std::out_of_range);
    EXPECT_THROW(
        hidden_power = pkmn::calculations::gen2_hidden_power(
                           0, 16, 0, 0
                       );
    , std::out_of_range);
    EXPECT_THROW(
        hidden_power = pkmn::calculations::gen2_hidden_power(
                           0, 0, -1, 0
                       );
    , std::out_of_range);
    EXPECT_THROW(
        hidden_power = pkmn::calculations::gen2_hidden_power(
                           0, 0, 16, 0
                       );
    , std::out_of_range);
    EXPECT_THROW(
        hidden_power = pkmn::calculations::gen2_hidden_power(
                           0, 0, 0, -1
                       );
    , std::out_of_range);
    EXPECT_THROW(
        hidden_power = pkmn::calculations::gen2_hidden_power(
                           0, 0, 0, 16
                       );
    , std::out_of_range);

    /*
     * Make sure known good inputs result in expected results.
     *
     * Source: http://bulbapedia.bulbagarden.net/wiki/Hidden_Power_(move)/Calculation#Generation_II
     */
    hidden_power = pkmn::calculations::gen2_hidden_power(
                       15, 15, 15, 14
                   );
    EXPECT_EQ(pkmn::e_type::DARK, hidden_power.type) << pkmn::type_to_string(hidden_power.type);
    EXPECT_EQ(69, hidden_power.base_power); // Nice
}

TEST(cpp_calculations_test, modern_hidden_power_test)
{
    pkmn::calculations::hidden_power hidden_power;

    /*
     * Make sure expected exceptions are thrown
     */
    EXPECT_THROW(
        hidden_power = pkmn::calculations::modern_hidden_power(
                           -1, 0, 0, 0, 0, 0
                       );
    , std::out_of_range);
    EXPECT_THROW(
        hidden_power = pkmn::calculations::modern_hidden_power(
                           32, 0, 0, 0, 0, 0
                       );
    , std::out_of_range);
    EXPECT_THROW(
        hidden_power = pkmn::calculations::modern_hidden_power(
                           0, -1, 0, 0, 0, 0
                       );
    , std::out_of_range);
    EXPECT_THROW(
        hidden_power = pkmn::calculations::modern_hidden_power(
                           0, 32, 0, 0, 0, 0
                       );
    , std::out_of_range);
    EXPECT_THROW(
        hidden_power = pkmn::calculations::modern_hidden_power(
                           0, 0, -1, 0, 0, 0
                       );
    , std::out_of_range);
    EXPECT_THROW(
        hidden_power = pkmn::calculations::modern_hidden_power(
                           0, 0, 32, 0, 0, 0
                       );
    , std::out_of_range);
    EXPECT_THROW(
        hidden_power = pkmn::calculations::modern_hidden_power(
                           0, 0, 0, -1, 0, 0
                       );
    , std::out_of_range);
    EXPECT_THROW(
        hidden_power = pkmn::calculations::modern_hidden_power(
                           0, 0, 0, 32, 0, 0
                       );
    , std::out_of_range);
    EXPECT_THROW(
        hidden_power = pkmn::calculations::modern_hidden_power(
                           0, 0, 0, 0, -1, 0
                       );
    , std::out_of_range);
    EXPECT_THROW(
        hidden_power = pkmn::calculations::modern_hidden_power(
                           0, 0, 0, 0, 32, 0
                       );
    , std::out_of_range);
    EXPECT_THROW(
        hidden_power = pkmn::calculations::modern_hidden_power(
                           0, 0, 0, 0, 0, -1
                       );
    , std::out_of_range);
    EXPECT_THROW(
        hidden_power = pkmn::calculations::modern_hidden_power(
                           0, 0, 0, 0, 0, 32
                       );
    , std::out_of_range);

    /*
     * Make sure known good inputs result in expected results.
     *
     * Source: http://bulbapedia.bulbagarden.net/wiki/Hidden_Power_(move)/Calculation#Generation_III_to_VI
     */
    hidden_power = pkmn::calculations::modern_hidden_power(
                       30, 31, 31, 31, 30, 31
                   );
    EXPECT_EQ(pkmn::e_type::GRASS, hidden_power.type) << pkmn::type_to_string(hidden_power.type);
    EXPECT_EQ(70, hidden_power.base_power);
}

TEST(cpp_calculations_test, natural_gift_test)
{
    // Test invalid generations.
    EXPECT_THROW(
        pkmn::calculations::natural_gift_stats(
            pkmn::e_item::CHERI_BERRY,
            3
        );
    , std::out_of_range);
    EXPECT_THROW(
        pkmn::calculations::natural_gift_stats(
            pkmn::e_item::CHERI_BERRY,
            7
        );
    , std::out_of_range);

    // Test invalid items.
    EXPECT_THROW(
        pkmn::calculations::natural_gift_stats(
            pkmn::e_item::POTION,
            4
        );
    , std::invalid_argument);

    // Make sure differences between generations are reflected.
    struct test_params_t
    {
        pkmn::e_item item;

        pkmn::e_type type;
        int gen4_power;
        int gen5_power;
        int gen6_power;
    };
    static const std::vector<test_params_t> test_params =
    {
        {pkmn::e_item::CHERI_BERRY, pkmn::e_type::FIRE,     60, 60, 80},
        {pkmn::e_item::NANAB_BERRY, pkmn::e_type::WATER,    70, 70, 90},
        {pkmn::e_item::BELUE_BERRY, pkmn::e_type::ELECTRIC, 80, 80, 100}
    };

    pkmn::calculations::natural_gift stats;
    for(const auto& param: test_params)
    {
        stats = pkmn::calculations::natural_gift_stats(
                    param.item,
                    4
                );
        EXPECT_EQ(param.type, stats.type)
            << pkmn::type_to_string(param.type) << " vs "
            << pkmn::type_to_string(stats.type);
        EXPECT_EQ(param.gen4_power, stats.base_power)
            << pkmn::item_to_string(param.item);

        stats = pkmn::calculations::natural_gift_stats(
                    param.item,
                    5
                );
        EXPECT_EQ(param.type, stats.type)
            << pkmn::type_to_string(param.type) << " vs "
            << pkmn::type_to_string(stats.type);
        EXPECT_EQ(param.gen5_power, stats.base_power)
            << pkmn::item_to_string(param.item);

        stats = pkmn::calculations::natural_gift_stats(
                    param.item,
                    6
                );
        EXPECT_EQ(param.type, stats.type)
            << pkmn::type_to_string(param.type) << " vs "
            << pkmn::type_to_string(stats.type);
        EXPECT_EQ(param.gen6_power, stats.base_power)
            << pkmn::item_to_string(param.item);
    }
}

TEST(cpp_calculations_test, nature_test)
{
    const std::vector<pkmn::e_nature> natures = pkmn::database::get_nature_list();

    for(pkmn::e_nature nature: natures)
    {
        const uint32_t personality = ((std::rand() % 50000) * 1000) + static_cast<uint32_t>(nature) - 1;

        EXPECT_EQ(nature, pkmn::calculations::nature(personality));
    }
}

static const std::vector<pkmn::e_gender> genders = {pkmn::e_gender::MALE, pkmn::e_gender::FEMALE};
static const std::vector<bool> bools = {true, false};

struct personality_test_data
{
    pkmn::e_species species;
    std::vector<pkmn::e_gender> genders;
    std::vector<pkmn::e_ability> abilities;
};

static void personality_test(
    const std::vector<personality_test_data>& test_values
)
{
    const std::vector<pkmn::e_nature> natures = pkmn::database::get_nature_list();

    for(const personality_test_data& test_params: test_values)
    {
        for(pkmn::e_nature nature: natures)
        {
            for(pkmn::e_ability ability: test_params.abilities)
            {
                if(ability != pkmn::e_ability::NONE)
                {
                    for(pkmn::e_gender gender: test_params.genders)
                    {
                        for(bool bool_val: bools)
                        {
                            uint32_t personality = pkmn::calculations::generate_personality(
                                                       test_params.species,
                                                       pkmn::pokemon::DEFAULT_TRAINER_ID,
                                                       bool_val,
                                                       ability,
                                                       gender,
                                                       nature
                                                   );
                            EXPECT_EQ(
                                bool_val,
                                pkmn::calculations::modern_shiny(
                                    personality,
                                    pkmn::pokemon::DEFAULT_TRAINER_ID
                                )
                            );
                            EXPECT_EQ(
                                gender,
                                pkmn::calculations::modern_pokemon_gender(
                                    test_params.species,
                                    personality
                                )
                            );
                            EXPECT_EQ(
                               nature,
                               pkmn::calculations::nature(personality)
                            );
                        }
                    }
                }
            }
        }
    }
}

TEST(cpp_calculations_test, personality_test)
{
    // Test invalid ability.
    EXPECT_THROW(
        (void)pkmn::calculations::generate_personality(
                  pkmn::e_species::CHARMANDER,
                  pkmn::pokemon::DEFAULT_TRAINER_ID,
                  true,
                  pkmn::e_ability::NONE,
                  pkmn::e_gender::MALE,
                  pkmn::e_nature::QUIET
              );
    , std::invalid_argument);
    EXPECT_THROW(
        (void)pkmn::calculations::generate_personality(
                  pkmn::e_species::CHARMANDER,
                  pkmn::pokemon::DEFAULT_TRAINER_ID,
                  true,
                  pkmn::e_ability::NONE,
                  pkmn::e_gender::MALE,
                  pkmn::e_nature::QUIET
              );
    , std::invalid_argument);

    // Test invalid gender.
    EXPECT_THROW(
        (void)pkmn::calculations::generate_personality(
                  pkmn::e_species::CHARMANDER,
                  pkmn::pokemon::DEFAULT_TRAINER_ID,
                  true,
                  pkmn::e_ability::NONE,
                  pkmn::e_gender::NONE,
                  pkmn::e_nature::QUIET
              );
    , std::invalid_argument);
    EXPECT_THROW(
        (void)pkmn::calculations::generate_personality(
                  pkmn::e_species::NIDORINA,
                  pkmn::pokemon::DEFAULT_TRAINER_ID,
                  true,
                  pkmn::e_ability::POISON_POINT,
                  pkmn::e_gender::NONE,
                  pkmn::e_nature::QUIET
              );
    , std::invalid_argument);
    EXPECT_THROW(
        (void)pkmn::calculations::generate_personality(
                  pkmn::e_species::NIDORINA,
                  pkmn::pokemon::DEFAULT_TRAINER_ID,
                  true,
                  pkmn::e_ability::POISON_POINT,
                  pkmn::e_gender::GENDERLESS,
                  pkmn::e_nature::QUIET
              );
    , std::invalid_argument);
    EXPECT_THROW(
        (void)pkmn::calculations::generate_personality(
                  pkmn::e_species::NIDORINA,
                  pkmn::pokemon::DEFAULT_TRAINER_ID,
                  true,
                  pkmn::e_ability::POISON_POINT,
                  pkmn::e_gender::MALE,
                  pkmn::e_nature::QUIET
              );
    , std::invalid_argument);
    EXPECT_THROW(
        (void)pkmn::calculations::generate_personality(
                  pkmn::e_species::NIDORINO,
                  pkmn::pokemon::DEFAULT_TRAINER_ID,
                  true,
                  pkmn::e_ability::POISON_POINT,
                  pkmn::e_gender::NONE,
                  pkmn::e_nature::QUIET
              );
    , std::invalid_argument);
    EXPECT_THROW(
        (void)pkmn::calculations::generate_personality(
                  pkmn::e_species::NIDORINO,
                  pkmn::pokemon::DEFAULT_TRAINER_ID,
                  true,
                  pkmn::e_ability::POISON_POINT,
                  pkmn::e_gender::GENDERLESS,
                  pkmn::e_nature::QUIET
              );
    , std::invalid_argument);
    EXPECT_THROW(
        (void)pkmn::calculations::generate_personality(
                  pkmn::e_species::NIDORINO,
                  pkmn::pokemon::DEFAULT_TRAINER_ID,
                  true,
                  pkmn::e_ability::POISON_POINT,
                  pkmn::e_gender::FEMALE,
                  pkmn::e_nature::QUIET
              );
    , std::invalid_argument);
    EXPECT_THROW(
        (void)pkmn::calculations::generate_personality(
                  pkmn::e_species::MAGNEMITE,
                  pkmn::pokemon::DEFAULT_TRAINER_ID,
                  true,
                  pkmn::e_ability::MAGNET_PULL,
                  pkmn::e_gender::NONE,
                  pkmn::e_nature::QUIET
              );
    , std::invalid_argument);
    EXPECT_THROW(
        pkmn::calculations::generate_personality(
            pkmn::e_species::MAGNEMITE,
            pkmn::pokemon::DEFAULT_TRAINER_ID,
            true,
            pkmn::e_ability::MAGNET_PULL,
            pkmn::e_gender::FEMALE,
            pkmn::e_nature::QUIET
        );
    , std::invalid_argument);
    EXPECT_THROW(
        (void)pkmn::calculations::generate_personality(
                  pkmn::e_species::MAGNEMITE,
                  pkmn::pokemon::DEFAULT_TRAINER_ID,
                  true,
                  pkmn::e_ability::MAGNET_PULL,
                  pkmn::e_gender::MALE,
                  pkmn::e_nature::QUIET
              );
    , std::invalid_argument);

    // Test invalid nature.
    EXPECT_THROW(
        (void)pkmn::calculations::generate_personality(
                  pkmn::e_species::MAGNEMITE,
                  pkmn::pokemon::DEFAULT_TRAINER_ID,
                  true,
                  pkmn::e_ability::MAGNET_PULL,
                  pkmn::e_gender::GENDERLESS,
                  pkmn::e_nature::NONE
              );
    , std::invalid_argument);

    // Test every valid combination for single-gender Pokémon.
    static const std::vector<personality_test_data> test_values =
    {
        // Single-gender Pokémon
        {
            pkmn::e_species::MAGNEMITE,
            {pkmn::e_gender::GENDERLESS},
            {
                pkmn::e_ability::MAGNET_PULL,
                pkmn::e_ability::STURDY,
                pkmn::e_ability::ANALYTIC
            }
        },
        {
            pkmn::e_species::NIDORINA,
            {pkmn::e_gender::FEMALE},
            {
                pkmn::e_ability::POISON_POINT,
                pkmn::e_ability::RIVALRY,
                pkmn::e_ability::HUSTLE
            }
        },
        {
            pkmn::e_species::NIDORINO,
            {pkmn::e_gender::MALE},
            {
                pkmn::e_ability::POISON_POINT,
                pkmn::e_ability::RIVALRY,
                pkmn::e_ability::HUSTLE
            }
        },

        // Mixed-gender Pokémon
        {
            pkmn::e_species::CHARMANDER,
            genders,
            {
                pkmn::e_ability::BLAZE,
                pkmn::e_ability::NONE,
                pkmn::e_ability::SOLAR_POWER}
            },
        {
            pkmn::e_species::GROWLITHE,
            genders,
            {
                pkmn::e_ability::INTIMIDATE,
                pkmn::e_ability::FLASH_FIRE,
                pkmn::e_ability::JUSTIFIED
            }
        },
        {
            pkmn::e_species::PIDGEY,
            genders,
            {
                pkmn::e_ability::KEEN_EYE,
                pkmn::e_ability::TANGLED_FEET,
                pkmn::e_ability::BIG_PECKS
            }
        },
        {
            pkmn::e_species::VULPIX,
            genders,
            {
                pkmn::e_ability::FLASH_FIRE,
                pkmn::e_ability::NONE,
                pkmn::e_ability::DROUGHT
            }
        },
    };
    personality_test(test_values);
}

TEST(cpp_calculations_test, gen2_shiny_test) {
    /*
     * Make sure expected exceptions are thrown
     */
    EXPECT_THROW(
        (void)pkmn::calculations::gen2_shiny(
                  -1, 0, 0, 0
              );
    , std::out_of_range);
    EXPECT_THROW(
        (void)pkmn::calculations::gen2_shiny(
                  16, 0, 0, 0
              );
    , std::out_of_range);
    EXPECT_THROW(
        (void)pkmn::calculations::gen2_shiny(
                  0, -1, 0, 0
              );
    , std::out_of_range);
    EXPECT_THROW(
        (void)pkmn::calculations::gen2_shiny(
                  0, 16, 0, 0
              );
    , std::out_of_range);
    EXPECT_THROW(
        (void)pkmn::calculations::gen2_shiny(
                  0, 0, -1, 0
              );
    , std::out_of_range);
    EXPECT_THROW(
        (void)pkmn::calculations::gen2_shiny(
                  0, 0, 16, 0
              );
    , std::out_of_range);
    EXPECT_THROW(
        (void)pkmn::calculations::gen2_shiny(
                  0, 0, 0, -1
              );
    , std::out_of_range);
    EXPECT_THROW(
        (void)pkmn::calculations::gen2_shiny(
                  0, 0, 0, 16
              );
    , std::out_of_range);

    /*
     * Make sure known good inputs result in expected results.
     *
     * Source: http://bulbapedia.bulbagarden.net/wiki/Individual_values#Shininess
     */
    bool shiny1 = pkmn::calculations::gen2_shiny(
                      7, 10, 10, 10
                  );
    bool shiny2 = pkmn::calculations::gen2_shiny(
                      6, 15, 7, 5
                  );
    EXPECT_TRUE(shiny1);
    EXPECT_FALSE(shiny2);
}

TEST(cpp_calculations_test, modern_shiny_test) {
    /*
     * Make sure known good inputs result in expected results.
     *
     * Source: http://bulbapedia.bulbagarden.net/wiki/Personality_value#Shininess
     *         http://www.smogon.com/ingame/rng/pid_iv_creation#how_shiny
     */
    bool shiny1 = pkmn::calculations::modern_shiny(
                      2814471828,
                      2545049318
                  );
    bool shiny2 = pkmn::calculations::modern_shiny(
                      0xB58F0B2A,
                      398174488
                  );
    EXPECT_TRUE(shiny1);
    EXPECT_TRUE(shiny2);
}

TEST(cpp_calculations_test, pokemon_size_test) {
    /*
     * There are no known good calculations, so just check for reasonable values
     * for each relevant Pokémon.
     */
    static const std::vector<pkmn::database::pokemon_entry> pokemon_with_size_checks = boost::assign::list_of
        (pkmn::database::pokemon_entry(pkmn::e_species::BARBOACH,  pkmn::e_game::RUBY, ""))
        (pkmn::database::pokemon_entry(pkmn::e_species::SHROOMISH, pkmn::e_game::RUBY, ""))
        (pkmn::database::pokemon_entry(pkmn::e_species::SEEDOT,    pkmn::e_game::EMERALD, ""))
        (pkmn::database::pokemon_entry(pkmn::e_species::LOTAD,     pkmn::e_game::EMERALD, ""))
        (pkmn::database::pokemon_entry(pkmn::e_species::MAGIKARP,  pkmn::e_game::FIRERED, ""))
        (pkmn::database::pokemon_entry(pkmn::e_species::HERACROSS, pkmn::e_game::LEAFGREEN, ""))
    ;

    // Test input validation.
    EXPECT_THROW(
        (void)pkmn::calculations::pokemon_size(
                  pkmn::e_species::BARBOACH, 0, -1, 0, 0, 0, 0, 0
              );
    , std::out_of_range);
    EXPECT_THROW(
        (void)pkmn::calculations::pokemon_size(
                  pkmn::e_species::BARBOACH, 0, 32, 0, 0, 0, 0, 0
              );
    , std::out_of_range);
    EXPECT_THROW(
        (void)pkmn::calculations::pokemon_size(
                  pkmn::e_species::BARBOACH, 0, 0, -1, 0, 0, 0, 0
              );
    , std::out_of_range);
    EXPECT_THROW(
        (void)pkmn::calculations::pokemon_size(
                  pkmn::e_species::BARBOACH, 0, 0, 32, 0, 0, 0, 0
              );
    , std::out_of_range);
    EXPECT_THROW(
        (void)pkmn::calculations::pokemon_size(
                  pkmn::e_species::BARBOACH, 0, 0, 0, -1, 0, 0, 0
              );
    , std::out_of_range);
    EXPECT_THROW(
        (void)pkmn::calculations::pokemon_size(
                  pkmn::e_species::BARBOACH, 0, 0, 0, 32, 0, 0, 0
              );
    , std::out_of_range);
    EXPECT_THROW(
        (void)pkmn::calculations::pokemon_size(
                  pkmn::e_species::BARBOACH, 0, 0, 0, 0, -1, 0, 0
              );
    , std::out_of_range);
    EXPECT_THROW(
        (void)pkmn::calculations::pokemon_size(
                  pkmn::e_species::BARBOACH, 0, 0, 0, 0, 32, 0, 0
              );
    , std::out_of_range);
    EXPECT_THROW(
        (void)pkmn::calculations::pokemon_size(
                  pkmn::e_species::BARBOACH, 0, 0, 0, 0, 0, -1, 0
              );
    , std::out_of_range);
    EXPECT_THROW(
        (void)pkmn::calculations::pokemon_size(
                  pkmn::e_species::BARBOACH, 0, 0, 0, 0, 0, 32, 0
              );
    , std::out_of_range);
    EXPECT_THROW(
        (void)pkmn::calculations::pokemon_size(
                  pkmn::e_species::BARBOACH, 0, 0, 0, 0, 0, 0, -1
              );
    , std::out_of_range);
    EXPECT_THROW(
        (void)pkmn::calculations::pokemon_size(
                  pkmn::e_species::BARBOACH, 0, 0, 0, 0, 0, 0, 32
              );
    , std::out_of_range);

    for(const pkmn::database::pokemon_entry& pokemon: pokemon_with_size_checks)
    {
        float height = pokemon.get_height();
        pkmn::e_species species = pokemon.get_species();

        for(int i = 0; i < 10; ++i) {
            float size = pkmn::calculations::pokemon_size(
                             species,
                             uint32_t(std::rand()),
                             (std::rand() % 32),
                             (std::rand() % 32),
                             (std::rand() % 32),
                             (std::rand() % 32),
                             (std::rand() % 32),
                             (std::rand() % 32)
                         );
            EXPECT_LE(std::fabs(size-height), height);
        }
    }
}

TEST(cpp_calculations_test, spinda_coords_test)
{
    /*
     * Check (in)equality operators.
     */
    PKMN_CONSTEXPR_OR_CONST pkmn::calculations::spinda_coords COORDS1(123,456);
    PKMN_CONSTEXPR_OR_CONST pkmn::calculations::spinda_coords COORDS2(123,456);
    PKMN_CONSTEXPR_OR_CONST pkmn::calculations::spinda_coords COORDS3(456,123);

    EXPECT_EQ(COORDS1, COORDS2);
    EXPECT_NE(COORDS1, COORDS3);

    /*
     * Test adding coordinates.
     */
    pkmn::calculations::spinda_coords added_coords = COORDS1 + COORDS2;
    EXPECT_EQ(246, added_coords.x);
    EXPECT_EQ(912, added_coords.y);

    added_coords += COORDS3;
    EXPECT_EQ(702, added_coords.x);
    EXPECT_EQ(1035, added_coords.y);
}

TEST(cpp_calculations_test, spinda_spot_test)
{
    /*
     * Check (in)equality operators.
     */
    PKMN_CONSTEXPR_OR_CONST pkmn::calculations::spinda_spots SPOTS1(
        pkmn::calculations::spinda_coords(7,5),
        pkmn::calculations::spinda_coords(10,0),
        pkmn::calculations::spinda_coords(1,4),
        pkmn::calculations::spinda_coords(2,15)
    );
    PKMN_CONSTEXPR_OR_CONST pkmn::calculations::spinda_spots SPOTS2(
        pkmn::calculations::spinda_coords(7,5),
        pkmn::calculations::spinda_coords(10,0),
        pkmn::calculations::spinda_coords(1,4),
        pkmn::calculations::spinda_coords(2,15)
    );
    PKMN_CONSTEXPR_OR_CONST pkmn::calculations::spinda_spots SPOTS3(
        pkmn::calculations::spinda_coords(7,5),
        pkmn::calculations::spinda_coords(10,0),
        pkmn::calculations::spinda_coords(2,15),
        pkmn::calculations::spinda_coords(1,4)
    );
    EXPECT_EQ(SPOTS1, SPOTS2);
    EXPECT_NE(SPOTS1, SPOTS3);

    /*
     * Test adding spots.
     */
    pkmn::calculations::spinda_spots added_spots = SPOTS1 + SPOTS2;
    EXPECT_EQ(14, added_spots.left_ear.x);
    EXPECT_EQ(10, added_spots.left_ear.y);
    EXPECT_EQ(20, added_spots.right_ear.x);
    EXPECT_EQ(0, added_spots.right_ear.y);
    EXPECT_EQ(2, added_spots.left_face.x);
    EXPECT_EQ(8, added_spots.left_face.y);
    EXPECT_EQ(4, added_spots.right_face.x);
    EXPECT_EQ(30, added_spots.right_face.y);

    added_spots += SPOTS3;
    EXPECT_EQ(21, added_spots.left_ear.x);
    EXPECT_EQ(15, added_spots.left_ear.y);
    EXPECT_EQ(30, added_spots.right_ear.x);
    EXPECT_EQ(0, added_spots.right_ear.y);
    EXPECT_EQ(4, added_spots.left_face.x);
    EXPECT_EQ(23, added_spots.left_face.y);
    EXPECT_EQ(5, added_spots.right_face.x);
    EXPECT_EQ(34, added_spots.right_face.y);

    added_spots += pkmn::calculations::spinda_coords(20, 50);
    EXPECT_EQ(41, added_spots.left_ear.x);
    EXPECT_EQ(65, added_spots.left_ear.y);
    EXPECT_EQ(50, added_spots.right_ear.x);
    EXPECT_EQ(50, added_spots.right_ear.y);
    EXPECT_EQ(24, added_spots.left_face.x);
    EXPECT_EQ(73, added_spots.left_face.y);
    EXPECT_EQ(25, added_spots.right_face.x);
    EXPECT_EQ(84, added_spots.right_face.y);

    added_spots = added_spots + pkmn::calculations::spinda_coords(1, 5);
    EXPECT_EQ(42, added_spots.left_ear.x);
    EXPECT_EQ(70, added_spots.left_ear.y);
    EXPECT_EQ(51, added_spots.right_ear.x);
    EXPECT_EQ(55, added_spots.right_ear.y);
    EXPECT_EQ(25, added_spots.left_face.x);
    EXPECT_EQ(78, added_spots.left_face.y);
    EXPECT_EQ(26, added_spots.right_face.x);
    EXPECT_EQ(89, added_spots.right_face.y);

    /*
     * Make sure known good inputs result in expected results.
     *
     * Source: https://github.com/magical/spinda
     */

    PKMN_CONSTEXPR_OR_CONST pkmn::calculations::spinda_spots spots1 =
        pkmn::calculations::spinda_spot_offset(
            4064348759
        );
    EXPECT_EQ(spots1, SPOTS1);
}

inline void PKMN_EXPECT_STAT_CLOSE(
    int actual, int expected
) {
    EXPECT_LE(int(std::abs(actual-expected)), 1);
}

TEST(cpp_calculations_test, gb_stat_test) {
    /*
     * Make sure expected exceptions are thrown
     */

    // Invalid stat
    EXPECT_THROW(
        pkmn::calculations::get_gb_stat(
            pkmn::e_stat::NONE, 1, 1, 1, 1
        );
    , std::invalid_argument);

    // Invalid EV
    EXPECT_THROW(
        pkmn::calculations::get_gb_stat(
            pkmn::e_stat::ATTACK, 1, 1, 123456, 1
        );
    , std::out_of_range);

    // Invalid IV
    EXPECT_THROW(
        pkmn::calculations::get_gb_stat(
            pkmn::e_stat::ATTACK, 1, 1, 1, 12345
        );
    , std::out_of_range);

    /*
     * Test with known good inputs.
     *
     * Source: http://bulbapedia.bulbagarden.net/wiki/Statistic#In_Generations_I_and_II
     */
    PKMN_EXPECT_STAT_CLOSE(
        pkmn::calculations::get_gb_stat(
            pkmn::e_stat::HP, 81, 35, 22850, 7
        ), 189
    );
    PKMN_EXPECT_STAT_CLOSE(
        pkmn::calculations::get_gb_stat(
            pkmn::e_stat::ATTACK, 81, 55, 23140, 8
        ), 137
    );
    PKMN_EXPECT_STAT_CLOSE(
        pkmn::calculations::get_gb_stat(
            pkmn::e_stat::DEFENSE, 81, 30, 17280, 13
        ), 101
    );
    PKMN_EXPECT_STAT_CLOSE(
        pkmn::calculations::get_gb_stat(
            pkmn::e_stat::SPECIAL, 81, 50, 19625, 9
        ), 128
    );
    PKMN_EXPECT_STAT_CLOSE(
        pkmn::calculations::get_gb_stat(
            pkmn::e_stat::SPECIAL_ATTACK, 81, 50, 19625, 9
        ), 128
    );
    PKMN_EXPECT_STAT_CLOSE(
        pkmn::calculations::get_gb_stat(
            pkmn::e_stat::SPECIAL_DEFENSE, 81, 40, 19625, 9
        ), 112
    );
    PKMN_EXPECT_STAT_CLOSE(
        pkmn::calculations::get_gb_stat(
            pkmn::e_stat::SPEED, 81, 90, 24795, 5
        ), 190
    );
}

TEST(cpp_calculations_test, modern_stat_test) {
    /*
     * Make sure expected exceptions are thrown
     */

    // Invalid stat
    EXPECT_THROW(
        pkmn::calculations::get_modern_stat(
            pkmn::e_stat::NONE, 1, 1.0f, 1, 1, 1
        );
    , std::invalid_argument);

    // No Special past Generation I
    EXPECT_THROW(
        pkmn::calculations::get_modern_stat(
            pkmn::e_stat::SPECIAL, 1, 1.0f, 1, 1, 1
        );
    , std::invalid_argument);

    // Invalid nature modifier
    EXPECT_THROW(
        pkmn::calculations::get_modern_stat(
            pkmn::e_stat::ATTACK, 1, 0.666f, 1, 1, 1
        );
    , std::domain_error);

    // Invalid EV
    EXPECT_THROW(
        pkmn::calculations::get_modern_stat(
            pkmn::e_stat::ATTACK, 1, 1.0f, 1, 12345, 1
        );
    , std::out_of_range);

    // Invalid IV
    EXPECT_THROW(
        pkmn::calculations::get_modern_stat(
            pkmn::e_stat::ATTACK, 1, 1.0f, 1, 1, 12345
        );
    , std::out_of_range);

    /*
     * Test with known good inputs.
     *
     * Source: http://bulbapedia.bulbagarden.net/wiki/Statistic#In_Generation_III_onward
     */
    PKMN_EXPECT_STAT_CLOSE(
        pkmn::calculations::get_modern_stat(
            pkmn::e_stat::HP, 78, 1.0f, 108, 74, 24
        ), 289
    );
    PKMN_EXPECT_STAT_CLOSE(
        pkmn::calculations::get_modern_stat(
            pkmn::e_stat::ATTACK, 78, 1.1f, 130, 195, 12
        ), 280
    );
    PKMN_EXPECT_STAT_CLOSE(
        pkmn::calculations::get_modern_stat(
            pkmn::e_stat::DEFENSE, 78, 1.0f, 95, 86, 30
        ), 193
    );
    PKMN_EXPECT_STAT_CLOSE(
        pkmn::calculations::get_modern_stat(
            pkmn::e_stat::SPECIAL_ATTACK, 78, 0.9f, 80, 48, 16
        ), 136
    );
    PKMN_EXPECT_STAT_CLOSE(
        pkmn::calculations::get_modern_stat(
            pkmn::e_stat::SPECIAL_DEFENSE, 78, 1.0f, 85, 84, 23
        ), 171
    );
    PKMN_EXPECT_STAT_CLOSE(
        pkmn::calculations::get_modern_stat(
            pkmn::e_stat::SPEED, 78, 1.0f, 102, 23, 5
        ), 172
    );
}
