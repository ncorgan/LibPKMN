/*
 * Copyright (c) 2016-2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#ifndef PKMN_C_CPP_TO_C_HPP
#define PKMN_C_CPP_TO_C_HPP

#include <pkmn/config.hpp>
#include <pkmn/daycare.hpp>
#include <pkmn/game_save.hpp>
#include <pkmn/item_bag.hpp>
#include <pkmn/item_list.hpp>
#include <pkmn/item_slot.hpp>
#include <pkmn/move_slot.hpp>
#include <pkmn/pokedex.hpp>
#include <pkmn/pokemon.hpp>
#include <pkmn/pokemon_box.hpp>
#include <pkmn/pokemon_party.hpp>
#include <pkmn/pokemon_pc.hpp>

#include <pkmn/calculations/moves/hidden_power.hpp>
#include <pkmn/calculations/moves/natural_gift.hpp>

#include <pkmn/database/item_entry.hpp>
#include <pkmn/database/levelup_move.hpp>
#include <pkmn/database/move_entry.hpp>
#include <pkmn/database/pokemon_entry.hpp>

#include <pkmn/enums/ability.hpp>
#include <pkmn/enums/contest_stat.hpp>
#include <pkmn/enums/egg_group.hpp>
#include <pkmn/enums/stat.hpp>
#include <pkmn/enums/type.hpp>

#include <pkmn/types/time_duration.hpp>

#include <pkmn-c/error.h>
#include <pkmn-c/database/item_entry.h>
#include <pkmn-c/database/move_entry.h>
#include <pkmn-c/database/pokemon_entry.h>
#include <pkmn-c/enums/ability.h>
#include <pkmn-c/enums/contest_stat.h>
#include <pkmn-c/enums/egg_group.h>
#include <pkmn-c/enums/stat.h>
#include <pkmn-c/enums/type.h>
#include <pkmn-c/types/hidden_power.h>
#include <pkmn-c/types/int_pair.h>
#include <pkmn-c/types/item_slot.h>
#include <pkmn-c/types/levelup_move.h>
#include <pkmn-c/types/natural_gift.h>
#include <pkmn-c/types/string_types.h>
#include <pkmn-c/types/time_duration.h>

#include <boost/assert.hpp>
#include <boost/bimap.hpp>
#include <boost/config.hpp>
#include <boost/thread/mutex.hpp>

#include <cstdlib>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

#include "error_internal.hpp"

#include <pkmn-c/types/hidden_power.h>
#include <pkmn-c/types/int_pair.h>
#include <pkmn-c/types/item_slot.h>
#include <pkmn-c/types/levelup_move.h>
#include <pkmn-c/types/move_slot.h>
#include <pkmn-c/types/pokemon_list.h>
#include <pkmn-c/types/pokemon_box_list.h>
#include <pkmn-c/types/string_types.h>

#include <pkmn-c/daycare.h>
#include <pkmn-c/game_save.h>
#include <pkmn-c/item_bag.h>
#include <pkmn-c/item_list.h>
#include <pkmn-c/pokedex.h>
#include <pkmn-c/pokemon.h>
#include <pkmn-c/pokemon_box.h>
#include <pkmn-c/pokemon_party.h>
#include <pkmn-c/pokemon_pc.h>

// Internal representations

template <typename libpkmn_type>
struct pkmn_c_internal_class_t
{
    std::shared_ptr<libpkmn_type> cpp;
    boost::mutex error_mutex;
    std::string last_error;

    int generation;
};

typedef pkmn_c_internal_class_t<pkmn::daycare> pkmn_daycare_internal_t;
typedef pkmn_c_internal_class_t<pkmn::game_save> pkmn_game_save_internal_t;
typedef pkmn_c_internal_class_t<pkmn::item_bag> pkmn_item_bag_internal_t;
typedef pkmn_c_internal_class_t<pkmn::item_list> pkmn_item_list_internal_t;
typedef pkmn_c_internal_class_t<pkmn::pokedex> pkmn_pokedex_internal_t;
typedef pkmn_c_internal_class_t<pkmn::pokemon> pkmn_pokemon_internal_t;
typedef pkmn_c_internal_class_t<pkmn::pokemon_box> pkmn_pokemon_box_internal_t;
typedef pkmn_c_internal_class_t<pkmn::pokemon_party> pkmn_pokemon_party_internal_t;
typedef pkmn_c_internal_class_t<pkmn::pokemon_pc> pkmn_pokemon_pc_internal_t;

#define DAYCARE_INTERNAL_RCAST(ptr)       (reinterpret_cast<pkmn_daycare_internal_t*>(ptr))
#define ITEM_BAG_INTERNAL_RCAST(ptr)      (reinterpret_cast<pkmn_item_bag_internal_t*>(ptr))
#define ITEM_LIST_INTERNAL_RCAST(ptr)     (reinterpret_cast<pkmn_item_list_internal_t*>(ptr))
#define POKEDEX_INTERNAL_RCAST(ptr)       (reinterpret_cast<pkmn_pokedex_internal_t*>(ptr))
#define POKEMON_INTERNAL_RCAST(ptr)       (reinterpret_cast<pkmn_pokemon_internal_t*>(ptr))
#define POKEMON_BOX_INTERNAL_RCAST(ptr)   (reinterpret_cast<pkmn_pokemon_box_internal_t*>(ptr))
#define POKEMON_PARTY_INTERNAL_RCAST(ptr) (reinterpret_cast<pkmn_pokemon_party_internal_t*>(ptr))
#define POKEMON_PC_INTERNAL_RCAST(ptr)    (reinterpret_cast<pkmn_pokemon_pc_internal_t*>(ptr))
#define GAME_SAVE_INTERNAL_RCAST(ptr)     (reinterpret_cast<pkmn_game_save_internal_t*>(ptr))

namespace pkmn { namespace c {

    template <typename value_type>
    void set_to_value_for_invalid_enum(
        value_type* p_value
    )
    {
        BOOST_ASSERT(p_value != nullptr);

        *p_value = static_cast<value_type>(-1);
    }

    template <>
    void set_to_value_for_invalid_enum<bool>(
        bool* p_value
    );

    // Calls to initialize internal representations.
    void init_daycare(
        const pkmn::daycare::sptr& daycare_cpp,
        struct pkmn_daycare* p_daycare_c_out
    );

    void init_item_bag(
        const pkmn::item_bag::sptr& item_bag_cpp,
        struct pkmn_item_bag* p_item_bag_c_out
    );

    void init_item_list(
        const pkmn::item_list::sptr& item_list_cpp,
        struct pkmn_item_list* p_item_list_c_out
    );

    void init_pokedex(
        const pkmn::pokedex::sptr& pokedex_cpp,
        struct pkmn_pokedex* p_pokedex_c_out
    );

    void init_pokemon(
        const pkmn::pokemon::sptr& pokemon_cpp,
        struct pkmn_pokemon* p_pokemon_c_out
    );

    void init_pokemon_box(
        const pkmn::pokemon_box::sptr& pokemon_box_cpp,
        struct pkmn_pokemon_box* p_pokemon_box_c_out
    );

    void init_pokemon_party(
        const pkmn::pokemon_party::sptr& pokemon_party_cpp,
        struct pkmn_pokemon_party* p_pokemon_party_c_out
    );

    void init_pokemon_pc(
        const pkmn::pokemon_pc::sptr& pokemon_pc_cpp,
        struct pkmn_pokemon_pc* p_pokemon_pc_c_out
    );

    void init_game_save(
        const pkmn::game_save::sptr& game_save_cpp,
        struct pkmn_game_save* p_game_save_c_out
    );

    template <typename pointer_type>
    inline void delete_pointer_and_set_to_null(pointer_type** p_pointer)
    {
        BOOST_ASSERT(p_pointer != nullptr);

        delete (*p_pointer);
        *p_pointer = nullptr;
    }

    template <typename pointer_type>
    inline void free_pointer_and_set_to_null(pointer_type** p_pointer)
    {
        BOOST_ASSERT(p_pointer != nullptr);

        std::free(*p_pointer);
        *p_pointer = nullptr;
    }

    // TODO: accept null buffer input, will just output necessary size
    template <typename T>
    void list_cpp_to_c(
        const std::vector<T>& list_cpp,
        T* p_list_c_out,
        size_t buffer_len,
        size_t* p_num_values_out
    )
    {
        BOOST_ASSERT(p_list_c_out != nullptr);

        if(!list_cpp.empty())
        {
            std::memcpy(
                p_list_c_out,
                list_cpp.data(),
                buffer_len * sizeof(T)
            );
        }

        if(p_num_values_out != nullptr)
        {
            *p_num_values_out = list_cpp.size();
        }
    }

    template <typename cpp_enum_type, typename c_enum_type, typename c_struct_type>
    typename std::enable_if<std::is_enum<cpp_enum_type>::value && std::is_enum<c_enum_type>::value, void>::type
    enum_list_cpp_to_c(
        const std::vector<cpp_enum_type>& cpp_enum_vector,
        c_struct_type* p_c_struct_out
    )
    {
        BOOST_ASSERT(p_c_struct_out != nullptr);

        static_assert(
            sizeof(cpp_enum_type) == sizeof(c_enum_type),
            "Enums aren't the same size."
        );

        if(!cpp_enum_vector.empty())
        {
            p_c_struct_out->p_enums = static_cast<c_enum_type*>(
                                          std::calloc(
                                              cpp_enum_vector.size(),
                                              sizeof(c_enum_type)
                                          )
                                      );
            p_c_struct_out->length = cpp_enum_vector.size();

            std::memcpy(
                p_c_struct_out->p_enums,
                cpp_enum_vector.data(),
                cpp_enum_vector.size() * sizeof(cpp_enum_type)
            );
        }
    }

    /*
     * The compiler can't auto-deduce c_enum_type from c_struct_type, and since we
     * can't alias functions, this is the best we can do.
     */
    BOOST_STATIC_CONSTEXPR auto& ability_enum_list_cpp_to_c =
        enum_list_cpp_to_c<pkmn::e_ability, enum pkmn_ability, struct pkmn_ability_enum_list>;
    BOOST_STATIC_CONSTEXPR auto& game_enum_list_cpp_to_c =
        enum_list_cpp_to_c<pkmn::e_game, enum pkmn_game, struct pkmn_game_enum_list>;
    BOOST_STATIC_CONSTEXPR auto& item_enum_list_cpp_to_c =
        enum_list_cpp_to_c<pkmn::e_item, enum pkmn_item, struct pkmn_item_enum_list>;
    BOOST_STATIC_CONSTEXPR auto& move_enum_list_cpp_to_c =
        enum_list_cpp_to_c<pkmn::e_move, enum pkmn_move, struct pkmn_move_enum_list>;
    BOOST_STATIC_CONSTEXPR auto& nature_enum_list_cpp_to_c =
        enum_list_cpp_to_c<pkmn::e_nature, enum pkmn_nature, struct pkmn_nature_enum_list>;
    BOOST_STATIC_CONSTEXPR auto& species_enum_list_cpp_to_c =
        enum_list_cpp_to_c<pkmn::e_species, enum pkmn_species, struct pkmn_species_enum_list>;
    BOOST_STATIC_CONSTEXPR auto& type_enum_list_cpp_to_c =
        enum_list_cpp_to_c<pkmn::e_type, enum pkmn_type, struct pkmn_type_enum_list>;

    template <
        typename cpp_enum_type,
        typename c_enum_type,
        typename c_struct_type,
        typename map_value_type,
        cpp_enum_type max_enum
    >
    typename std::enable_if<std::is_enum<cpp_enum_type>::value && std::is_enum<c_enum_type>::value, void>::type
    enum_map_cpp_to_c(
        const std::map<cpp_enum_type, map_value_type>& cpp_enum_map,
        c_struct_type* p_c_struct_out
    )
    {
        BOOST_ASSERT(p_c_struct_out != nullptr);

        if(!cpp_enum_map.empty())
        {
            p_c_struct_out->length = static_cast<size_t>(max_enum) + 1;
            BOOST_ASSERT(p_c_struct_out->length >= cpp_enum_map.size());

            // We're overriding default values anyway, but there's a warning
            // from CppCheck about using malloc instead of calloc.
            p_c_struct_out->p_values = static_cast<map_value_type*>(
                                           std::calloc(
                                               p_c_struct_out->length,
                                               sizeof(map_value_type)
                                           )
                                       );
            for(size_t value_index = 0;
                value_index < p_c_struct_out->length;
                ++value_index)
            {
                set_to_value_for_invalid_enum<map_value_type>(
                    &p_c_struct_out->p_values[value_index]
                );
            }

            for(const auto& map_iter: cpp_enum_map)
            {
                c_enum_type c_enum = static_cast<c_enum_type>(map_iter.first);
                int value = map_iter.second;

                BOOST_ASSERT(static_cast<size_t>(c_enum) < p_c_struct_out->length);

                p_c_struct_out->p_values[c_enum] = value;
            }
        }
    }

    /*
     * The compiler can't auto-deduce c_enum_type from c_struct_type, and since we
     * can't alias functions, this is the best we can do.
     */
    BOOST_STATIC_CONSTEXPR auto& contest_stat_enum_map_cpp_to_c =
        enum_map_cpp_to_c<
            pkmn::e_contest_stat,
            enum pkmn_contest_stat,
            struct pkmn_contest_stat_enum_map,
            int,
            pkmn::e_contest_stat::SHEEN
        >;
    BOOST_STATIC_CONSTEXPR auto& marking_enum_map_cpp_to_c =
        enum_map_cpp_to_c<
            pkmn::e_marking,
            enum pkmn_marking,
            struct pkmn_marking_enum_map,
            bool,
            pkmn::e_marking::DIAMOND
        >;
    BOOST_STATIC_CONSTEXPR auto& stat_enum_map_cpp_to_c =
        enum_map_cpp_to_c<
            pkmn::e_stat,
            enum pkmn_stat,
            struct pkmn_stat_enum_map,
            int,
            pkmn::e_stat::SPECIAL_DEFENSE
        >;

    inline void int_pair_cpp_to_c(
        const std::pair<int, int>& int_pair_cpp,
        struct pkmn_int_pair* p_int_pair_c_out
    )
    {
        BOOST_ASSERT(p_int_pair_c_out != nullptr);

        p_int_pair_c_out->first = int_pair_cpp.first;
        p_int_pair_c_out->second = int_pair_cpp.second;
    }

    inline void ability_pair_cpp_to_c(
        const std::pair<pkmn::e_ability, pkmn::e_ability>& ability_pair_cpp,
        struct pkmn_ability_enum_pair* p_ability_pair_c_out
    )
    {
        BOOST_ASSERT(p_ability_pair_c_out != nullptr);

        p_ability_pair_c_out->first = static_cast<enum pkmn_ability>(ability_pair_cpp.first);
        p_ability_pair_c_out->second = static_cast<enum pkmn_ability>(ability_pair_cpp.second);
    }

    inline void egg_group_pair_cpp_to_c(
        const std::pair<pkmn::e_egg_group, pkmn::e_egg_group>& egg_group_pair_cpp,
        struct pkmn_egg_group_enum_pair* p_egg_group_pair_c_out
    )
    {
        BOOST_ASSERT(p_egg_group_pair_c_out != nullptr);

        p_egg_group_pair_c_out->first = static_cast<enum pkmn_egg_group>(egg_group_pair_cpp.first);
        p_egg_group_pair_c_out->second = static_cast<enum pkmn_egg_group>(egg_group_pair_cpp.second);
    }

    inline void type_pair_cpp_to_c(
        const std::pair<pkmn::e_type, pkmn::e_type>& type_pair_cpp,
        struct pkmn_type_enum_pair* p_type_pair_c_out
    )
    {
        BOOST_ASSERT(p_type_pair_c_out != nullptr);

        p_type_pair_c_out->first = static_cast<enum pkmn_type>(type_pair_cpp.first);
        p_type_pair_c_out->second = static_cast<enum pkmn_type>(type_pair_cpp.second);
    }

    void string_cpp_to_c(
        const std::string& string_cpp,
        char* p_c_str_out,
        size_t buffer_len,
        size_t* p_string_length_out
    );

    inline void string_cpp_to_c_alloc(
        const std::string& string_cpp,
        char** pp_c_str_out
    )
    {
        BOOST_ASSERT(pp_c_str_out != nullptr);

        *pp_c_str_out = (char*)std::calloc(string_cpp.size()+1, sizeof(char));
        std::strncpy(
            *pp_c_str_out,
            string_cpp.c_str(),
            string_cpp.size()
        );
    }

    inline void string_cpp_to_c_realloc(
        const std::string& string_cpp,
        char** pp_c_str_out
    )
    {
        BOOST_ASSERT(pp_c_str_out != nullptr);

        std::free(*pp_c_str_out);
        string_cpp_to_c_alloc(
            string_cpp,
            pp_c_str_out
        );
    }

    void string_list_cpp_to_c(
        const std::vector<std::string>& string_list_cpp,
        struct pkmn_string_list* p_string_list_c_out
    );

    inline void string_pair_cpp_to_c(
        const std::pair<std::string, std::string>& string_pair_cpp,
        struct pkmn_string_pair* p_string_pair_c_out
    )
    {
        BOOST_ASSERT(p_string_pair_c_out != nullptr);

        string_cpp_to_c_alloc(
            string_pair_cpp.first,
            &p_string_pair_c_out->p_first
        );
        string_cpp_to_c_alloc(
            string_pair_cpp.second,
            &p_string_pair_c_out->p_second
        );
    }

    template <typename value_type>
    void string_map_keys_to_string_list(
        const std::map<std::string, value_type>& map_cpp,
        struct pkmn_string_list* p_string_list_c_out
    )
    {
        BOOST_ASSERT(p_string_list_c_out != nullptr);

        // Make all C++ calls and operate on a second struct until we
        // know everything succeeds before changing any user output.
        // If this fails, we'll leak, but it's small enough to not be
        // a concern.
        struct pkmn_string_list temp_string_list_c =
        {
            nullptr,       // pp_strings
            map_cpp.size() // length
        };

        if(temp_string_list_c.length > 0)
        {
            temp_string_list_c.pp_strings = (char**)std::calloc(
                                                        temp_string_list_c.length,
                                                        sizeof(char*)
                                                    );
            size_t index = 0;
            for(auto map_iter = map_cpp.begin();
                (map_iter != map_cpp.end()) && (index < temp_string_list_c.length);
                ++map_iter, ++index)
            {
                string_cpp_to_c_alloc(
                    map_iter->first,
                    &temp_string_list_c.pp_strings[index]
                );
            }
        }

        // Everything succeeded, so move it into the pointer the caller
        // provided.
        *p_string_list_c_out = std::move(temp_string_list_c);
    }

    inline void hidden_power_cpp_to_c(
        const pkmn::calculations::hidden_power& hidden_power_cpp,
        struct pkmn_hidden_power* p_hidden_power_c_out
    )
    {
        BOOST_ASSERT(p_hidden_power_c_out != nullptr);

        p_hidden_power_c_out->type = static_cast<enum pkmn_type>(hidden_power_cpp.type);
        p_hidden_power_c_out->base_power = hidden_power_cpp.base_power;
    }

    inline void natural_gift_cpp_to_c(
        const pkmn::calculations::natural_gift& natural_gift_cpp,
        struct pkmn_natural_gift* p_natural_gift_c_out
    )
    {
        BOOST_ASSERT(p_natural_gift_c_out != nullptr);

        p_natural_gift_c_out->type = static_cast<enum pkmn_type>(natural_gift_cpp.type);
        p_natural_gift_c_out->base_power = natural_gift_cpp.base_power;
    }

    inline void item_slot_cpp_to_c(
        const pkmn::item_slot& item_slot_cpp,
        struct pkmn_item_slot* p_item_slot_c_out
    )
    {
        BOOST_ASSERT(p_item_slot_c_out != nullptr);

        p_item_slot_c_out->item = static_cast<enum pkmn_item>(item_slot_cpp.item);
        p_item_slot_c_out->amount = item_slot_cpp.amount;
    }

    void item_slots_cpp_to_c(
        const pkmn::item_slots_t& item_slots_cpp,
        struct pkmn_item_slots* p_item_slots_c
    );

    inline void levelup_move_cpp_to_c(
        const pkmn::database::levelup_move& levelup_move_cpp,
        struct pkmn_levelup_move* p_levelup_move_c_out
    )
    {
        BOOST_ASSERT(p_levelup_move_c_out != nullptr);

        p_levelup_move_c_out->move = static_cast<enum pkmn_move>(levelup_move_cpp.move);
        p_levelup_move_c_out->level = levelup_move_cpp.level;
    }

    void levelup_moves_cpp_to_c(
        const pkmn::database::levelup_moves_t& levelup_moves_cpp,
        struct pkmn_levelup_moves* p_levelup_moves_c_out
    );

    void move_list_to_string_list(
        const pkmn::database::move_list_t& move_list_cpp,
        struct pkmn_string_list* p_string_list_c_out
    );

    inline void move_slot_cpp_to_c(
        const pkmn::move_slot& move_slot_cpp,
        struct pkmn_move_slot* p_move_slot_c_out
    )
    {
        BOOST_ASSERT(p_move_slot_c_out != nullptr);

        p_move_slot_c_out->move = static_cast<enum pkmn_move>(move_slot_cpp.move);
        p_move_slot_c_out->pp = move_slot_cpp.pp;
    }

    void move_slots_cpp_to_c(
        const pkmn::move_slots_t& move_slots_cpp,
        struct pkmn_move_slots* p_move_slots_c_out
    );

    void item_entry_cpp_to_c(
        const pkmn::database::item_entry& item_entry_cpp,
        struct pkmn_database_item_entry* p_item_entry_c_out
    );

    void move_entry_cpp_to_c(
        const pkmn::database::move_entry& move_entry_cpp,
        struct pkmn_database_move_entry* p_move_entry_c_out
    );

    void pokemon_entry_cpp_to_c(
        const pkmn::database::pokemon_entry& pokemon_entry_cpp,
        struct pkmn_database_pokemon_entry* p_pokemon_entry_c_out
    );

    void pokemon_list_cpp_to_c(
        const pkmn::pokemon_list_t& pokemon_list_cpp,
        struct pkmn_pokemon_list* p_pokemon_list_c_out
    );

    void pokemon_box_list_cpp_to_c(
        const pkmn::pokemon_box_list_t& pokemon_box_list_cpp,
        struct pkmn_pokemon_box_list* p_pokemon_box_list_c_out
    );

    inline void time_duration_cpp_to_c(
        const pkmn::time_duration& time_duration_cpp,
        struct pkmn_time_duration* p_time_duration_c_out
    )
    {
        BOOST_ASSERT(p_time_duration_c_out != nullptr);

        p_time_duration_c_out->hours   = time_duration_cpp.hours;
        p_time_duration_c_out->minutes = time_duration_cpp.minutes;
        p_time_duration_c_out->seconds = time_duration_cpp.seconds;
        p_time_duration_c_out->frames  = time_duration_cpp.frames;
    }

    // Return struct to match C++ convention
    inline pkmn::time_duration time_duration_c_to_cpp(
        const pkmn_time_duration* p_time_duration_c
    )
    {
        BOOST_ASSERT(p_time_duration_c != nullptr);

        return {p_time_duration_c->hours,
                p_time_duration_c->minutes,
                p_time_duration_c->seconds,
                p_time_duration_c->frames};
    }

    template <typename sptr_type>
    void get_attribute_names_from_sptr(
        const std::shared_ptr<sptr_type>& libpkmn_sptr,
        struct pkmn_attribute_names* p_attribute_names_out
    )
    {
        BOOST_ASSERT(libpkmn_sptr.get() != nullptr);
        BOOST_ASSERT(p_attribute_names_out != nullptr);

        // Make all C++ calls and operate on a second struct until we
        // know everything succeeds before changing any user output.
        // If this fails, we'll leak, but it's small enough to not be
        // a concern.
        struct pkmn_attribute_names temp_attribute_names_c =
        {
            // numeric_attribute_names
            {
                nullptr, // pp_strings
                0ULL     // length
            },
            // string_attribute_names
            {
                nullptr, // pp_strings
                0ULL     // length
            },
            // boolean_attribute_names
            {
                nullptr, // pp_strings
                0ULL     // length
            }
        };

        string_list_cpp_to_c(
            libpkmn_sptr->get_numeric_attribute_names(),
            &temp_attribute_names_c.numeric_attribute_names
        );
        string_list_cpp_to_c(
            libpkmn_sptr->get_string_attribute_names(),
            &temp_attribute_names_c.string_attribute_names
        );
        string_list_cpp_to_c(
            libpkmn_sptr->get_boolean_attribute_names(),
            &temp_attribute_names_c.boolean_attribute_names
        );

        // Everything succeeded, so move it into the pointer the caller
        // provided.
        *p_attribute_names_out = std::move(temp_attribute_names_c);
    }

    template <typename map_key_type, typename bimap_key_type, typename c_enum_type, typename buffer_type>
    static void copy_map_to_buffer(
        const std::map<map_key_type, buffer_type>& value_map,
        const boost::bimap<bimap_key_type, c_enum_type>& value_enum_bimap,
        buffer_type* p_values_buffer_out,
        size_t value_buffer_size,
        size_t actual_num_values,
        size_t* p_actual_num_values_out
    )
    {
        BOOST_ASSERT(p_values_buffer_out != nullptr);

        std::memset(
            p_values_buffer_out,
            0,
            value_buffer_size * sizeof(buffer_type)
        );

        size_t internal_num_values = std::min<size_t>(value_buffer_size, actual_num_values);
        for(size_t value = 0; value < internal_num_values; ++value)
        {
            c_enum_type value_enum = c_enum_type(value);
            BOOST_ASSERT(value_enum_bimap.right.count(value_enum) > 0);

            const bimap_key_type& cpp_key = value_enum_bimap.right.at(value_enum);
            if(value_map.count(cpp_key) > 0)
            {
                p_values_buffer_out[value] = value_map.at(value_enum_bimap.right.at(value_enum));
            }
            else
            {
                set_to_value_for_invalid_enum<buffer_type>(
                    &p_values_buffer_out[value]
                );
            }
        }

        // Optional parameter
        if(p_actual_num_values_out != nullptr)
        {
            *p_actual_num_values_out = actual_num_values;
        }
    }
}
}

#endif /* PKMN_C_CPP_TO_C_HPP */
