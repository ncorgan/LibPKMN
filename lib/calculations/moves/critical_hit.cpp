/*
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <pkmn/exception.hpp>

#include <pkmn/calculations/moves/critical_hit.hpp>

namespace pkmn { namespace calculations {

    static inline float _gen1_critical_hit_chance(
        float speed,
        bool rate_increased,
        bool high_rate_move
    )
    {
        return (speed / 512.0f) /
               (rate_increased ? 4.0f : 1.0f) *
               (high_rate_move ? 8.0f : 1.0f);
    }

    static inline float _stadium_critical_hit_chance(
        float speed,
        bool rate_increased,
        bool high_rate_move
    )
    {
        return (speed + (rate_increased ? 236.0f : 76.0f)) /
               (1024.0f / (rate_increased ? 2.0f : 1.0f)
                        / (high_rate_move ? 8.0f : 1.0f));
    }

    static inline float _gen1_critical_hit_modifier(
        float attacker_level
    )
    {
        return ((2.0f * attacker_level) + 5.0f) / (attacker_level + 5.0f);
    }

    // Exported functions

    float gen1_critical_hit_chance(
        int speed,
        bool rate_increased,
        bool high_rate_move
    )
    {
        // Validate input parameters.
        if(speed < 0)
        {
            throw std::out_of_range("speed must be > 0.");
        }

        return _gen1_critical_hit_chance(
                   float(speed),
                   rate_increased,
                   high_rate_move
               );
    }

    float stadium_critical_hit_chance(
        int speed,
        bool rate_increased,
        bool high_rate_move
    )
    {
        // Validate input parameters.
        if(speed < 0)
        {
            throw std::out_of_range("speed must be > 0.");
        }

        return _stadium_critical_hit_chance(
                   float(speed),
                   rate_increased,
                   high_rate_move
               );
    }

    float gen1_critical_hit_modifier(
        int attacker_level
    )
    {
        pkmn::enforce_bounds(
            "Attacker level",
            attacker_level,
            1,
            255
        );

        return _gen1_critical_hit_modifier(float(attacker_level));
    }

}}