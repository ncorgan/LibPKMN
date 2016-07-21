/*
 * Copyright (c) 2016 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <pkmn/calculations/shininess.hpp>

#include <boost/config.hpp>

#include <algorithm>

namespace pkmn { namespace calculations {

    bool gen2_shiny(
        int IV_attack,
        int IV_defense,
        int IV_speed,
        int IV_special
    ) {
        BOOST_STATIC_CONSTEXPR int valid_IV_attack[] = {2,3,6,7,10,11,14,15};

        if((IV_defense != 10) or (IV_speed != 10) or (IV_special) != 10) {
            return false;
        } else if(std::find(valid_IV_attack, valid_IV_attack+8, IV_attack) == (valid_IV_attack+8)) {
            return false;
        }

        return true;
    }

    bool modern_shiny(
        uint32_t personality,
        uint32_t trainer_id
    ) {
        const uint16_t* p = reinterpret_cast<const uint16_t*>(&personality);
        const uint16_t* t = reinterpret_cast<const uint16_t*>(&trainer_id);

        for(size_t i = 3; i < 16; i++) {
            size_t num_ones = 0;
            if(p[0] & (1 << i)) num_ones++;
            if(p[1] & (1 << i)) num_ones++;
            if(t[0] & (1 << i)) num_ones++;
            if(t[1] & (1 << i)) num_ones++;
            if((num_ones == 1) or (num_ones == 3)) {
                return false;
            }
        }

        return true;
    }

}}
