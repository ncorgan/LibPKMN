/*
 * Copyright (c) 2016 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "cpp_to_c.hpp"
#include "error_internal.hpp"

#include <pkmn-c/database/pokemon_entry.h>

#include <pkmn/database/pokemon_entry.hpp>

#include <cstdlib>
#include <cstring>

pkmn_error_t pkmn_database_get_pokemon_entry(
    const char* species,
    const char* game,
    const char* form,
    pkmn_database_pokemon_entry_t* pokemon_entry_out
) {
    PKMN_CPP_TO_C(
        pkmn::database::pokemon_entry pokemon_entry_cpp(
                                          species,
                                          game,
                                          form
                                      );

        pkmn::pkmn_pokemon_entry_cpp_to_c(
            pokemon_entry_cpp,
            pokemon_entry_out
        );
    )
}

pkmn_error_t pkmn_database_pokemon_entry_set_form(
    pkmn_database_pokemon_entry_t* pokemon_entry,
    const char* form
) {
    // Just to see if it exists
    PKMN_CPP_TO_C(
        pkmn::database::pokemon_entry new_entry(
                                          pokemon_entry->name,
                                          pokemon_entry->game,
                                          form
                                      );

        pkmn_database_pokemon_entry_free(pokemon_entry);
        pkmn::pkmn_pokemon_entry_cpp_to_c(
            new_entry,
            pokemon_entry
        );
    )
}

pkmn_error_t pkmn_database_pokemon_entry_experience_at_level(
    pkmn_database_pokemon_entry_t* pokemon_entry,
    int level,
    int* experience_out
) {
    PKMN_CPP_TO_C(
        *experience_out = pkmn::database::pokemon_entry(
                              pokemon_entry->name,
                              pokemon_entry->game,
                              pokemon_entry->form
                          ).get_experience_at_level(level);
    )
}

pkmn_error_t pkmn_database_pokemon_entry_level_at_experience(
    pkmn_database_pokemon_entry_t* pokemon_entry,
    int experience,
    int* level_out
) {
    PKMN_CPP_TO_C(
        *level_out = pkmn::database::pokemon_entry(
                         pokemon_entry->name,
                         pokemon_entry->game,
                         pokemon_entry->form
                     ).get_level_at_experience(experience);
    )
}

pkmn_error_t pkmn_database_pokemon_entry_free(
    pkmn_database_pokemon_entry_t* pokemon_entry
) {
    std::free(pokemon_entry->name);
    pokemon_entry->name = NULL;

    std::free(pokemon_entry->game);
    pokemon_entry->game = NULL;

    std::free(pokemon_entry->species);
    pokemon_entry->species = NULL;

    std::free(pokemon_entry->form);
    pokemon_entry->form = NULL;

    std::free(pokemon_entry->pokedex_entry);
    pokemon_entry->pokedex_entry = NULL;

    pokemon_entry->height = 0.0f;
    pokemon_entry->weight = 0.0f;
    pokemon_entry->chance_male = 0.0f;
    pokemon_entry->chance_female = 0.0f;
    pokemon_entry->has_gender_differences = false;
    pokemon_entry->base_happiness = 0;

    pkmn_string_pair_free(&pokemon_entry->types);
    pkmn_string_pair_free(&pokemon_entry->abilities);

    std::free(pokemon_entry->hidden_ability);
    pokemon_entry->hidden_ability = NULL;

    pkmn_string_pair_free(&pokemon_entry->egg_groups);

    for(int i = 0; i < 7; ++i) {
        pokemon_entry->base_stats[i] = 0;
        pokemon_entry->EV_yields[i] = 0;
    }

    pokemon_entry->experience_yield = 0;

    pkmn_levelup_moves_free(&pokemon_entry->levelup_moves);

    pkmn_string_list_free(&pokemon_entry->tm_hm_moves);
    pkmn_string_list_free(&pokemon_entry->egg_moves);
    pkmn_string_list_free(&pokemon_entry->tutor_moves);
    pkmn_string_list_free(&pokemon_entry->forms);
    pkmn_string_list_free(&pokemon_entry->evolutions);

    return PKMN_ERROR_NONE;
}
