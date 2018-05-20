/*
 * Copyright (c) 2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "database/database_common.hpp"
#include "utils/misc.hpp"

#include <pkmn/exception.hpp>
#include <pkmn/breeding/compatibility.hpp>
#include <pkmn/database/pokemon_entry.hpp>

#include <boost/assert.hpp>
#include <boost/config.hpp>

namespace pkmn { namespace breeding {

    static bool does_string_pair_contain_value(
        const std::pair<std::string, std::string>& string_pair,
        const std::string& value
    )
    {
        return ((string_pair.first == value) ||
                (string_pair.second == value));
    }

    static bool do_string_pairs_have_common_valid_value(
        const std::pair<std::string, std::string>& string_pair1,
        const std::pair<std::string, std::string>& string_pair2
    )
    {
        bool has_common_value = false;

        has_common_value |= (string_pair1.first == string_pair2.first);
        if(!has_common_value && (string_pair2.first != "None"))
        {
            has_common_value |= (string_pair1.first == string_pair2.second);
        }
        if(!has_common_value && (string_pair1.second != "None"))
        {
            has_common_value |= (string_pair1.second == string_pair2.first);
            if(!has_common_value && (string_pair2.second != "None"))
            {
                has_common_value |= (string_pair1.second == string_pair2.second);
            }
        }

        return has_common_value;
    }

    static bool are_species_valid_and_compatible(
        int pokemon1_id,
        int pokemon2_id
    )
    {
        bool are_compatible = true;

        // "None" and "Invalid" species are incompatible.
        are_compatible = (pokemon1_id >= 1) && (pokemon2_id >= 1);

        if(are_compatible)
        {
            BOOST_STATIC_CONSTEXPR int DITTO_SPECIES_ID = 132;

            are_compatible &= !((pokemon1_id == DITTO_SPECIES_ID) &&
                                (pokemon2_id == DITTO_SPECIES_ID));
        }
        if(are_compatible)
        {
            BOOST_STATIC_CONSTEXPR int NIDOQUEEN_SPECIES_ID = 31;
            BOOST_STATIC_CONSTEXPR int NIDOKING_SPECIES_ID  = 34;

            static const std::vector<int> NONBREEDABLE_SPECIES_IDS =
            {
                NIDOQUEEN_SPECIES_ID, NIDOKING_SPECIES_ID
            };

            are_compatible &= !(does_vector_contain_value(NONBREEDABLE_SPECIES_IDS, pokemon1_id) ||
                                does_vector_contain_value(NONBREEDABLE_SPECIES_IDS, pokemon2_id));
        }

        return are_compatible;
    }

    static bool are_egg_groups_valid_and_compatible(
        const pkmn::database::pokemon_entry& pokemon1_entry,
        const pkmn::database::pokemon_entry& pokemon2_entry
    )
    {
        bool are_compatible = true;

        std::pair<std::string, std::string> pokemon1_egg_groups = pokemon1_entry.get_egg_groups();
        std::pair<std::string, std::string> pokemon2_egg_groups = pokemon2_entry.get_egg_groups();

        bool is_pokemon1_ditto = (pokemon1_egg_groups.first == "Ditto");
        bool is_pokemon2_ditto = (pokemon2_egg_groups.first == "Ditto");

        // Pokémon in the "Undiscovered" group cannot breed.
        if(does_string_pair_contain_value(pokemon1_egg_groups, "Undiscovered") ||
           does_string_pair_contain_value(pokemon2_egg_groups, "Undiscovered"))
        {
            are_compatible = false;
        }
        else if(is_pokemon1_ditto && is_pokemon2_ditto)
        {
            // Two Ditto cannot breed.
            are_compatible = false;
        }
        else if(!is_pokemon1_ditto && !is_pokemon2_ditto)
        {
            are_compatible = do_string_pairs_have_common_valid_value(
                                 pokemon1_egg_groups,
                                 pokemon2_egg_groups
                             );
        }

        return are_compatible;
    }

    bool are_genders_compatible(
        const pkmn::database::pokemon_entry& pokemon1_entry,
        const pkmn::database::pokemon_entry& pokemon2_entry
    )
    {
        bool are_compatible = true;

        float pokemon1_chance_female = pokemon1_entry.get_chance_female();
        float pokemon2_chance_female = pokemon2_entry.get_chance_female();

        if(fp_compare_equal(pokemon1_chance_female, 1.0f) &&
           fp_compare_equal(pokemon2_chance_female, 1.0f))
        {
            are_compatible = false;
        }
        if(are_compatible)
        {
            float pokemon1_chance_male = pokemon1_entry.get_chance_male();
            float pokemon2_chance_male = pokemon2_entry.get_chance_male();

            if(fp_compare_equal(pokemon1_chance_male, 1.0f) &&
               fp_compare_equal(pokemon2_chance_male, 1.0f))
            {
                are_compatible = false;
            }
        }

        return are_compatible;
    }

    bool are_pokemon_species_compatible(
        const std::string& species1,
        const std::string& species2
    )
    {
        bool are_compatible = true;

        static const std::string ENTRY_GAME = "X";

        pkmn::database::pokemon_entry species1_entry(species1, ENTRY_GAME, "");
        pkmn::database::pokemon_entry species2_entry(species2, ENTRY_GAME, "");

        are_compatible = are_species_valid_and_compatible(
                             species1_entry.get_species_id(),
                             species2_entry.get_species_id()
                         );
        are_compatible &= are_egg_groups_valid_and_compatible(
                              species1_entry, species2_entry
                          );
        are_compatible &= are_genders_compatible(
                              species1_entry, species2_entry
                          );

        return are_compatible;
    }

}}