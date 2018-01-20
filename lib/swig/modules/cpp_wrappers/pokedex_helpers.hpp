/*
 * Copyright (c) 2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#ifndef CPP_WRAPPERS_POKEDEX_HELPERS_HPP
#define CPP_WRAPPERS_POKEDEX_HELPERS_HPP

#include "exception_internal.hpp"
#include "misc_common.hpp"

#include <pkmn/config.hpp>
#include <pkmn/exception.hpp>
#include <pkmn/pokedex.hpp>

namespace pkmn { namespace swig {

    class pokedex_has_seen_helper
    {
        public:
            pokedex_has_seen_helper():
                _pokedex(nullptr),
                _is_gamecube_game(false)
            {}

            pokedex_has_seen_helper(
                const pkmn::pokedex::sptr& pokedex,
                bool is_gamecube_game = false
            ): _pokedex(pokedex),
               _is_gamecube_game(is_gamecube_game)
            {}

            inline bool get_has_seen(
                const std::string& species
            )
            {
                if(_is_gamecube_game)
                {
                    throw pkmn::feature_not_in_game_error(
                              "Pokédex",
                              "Gamecube games"
                          );
                }
                else if(!_pokedex)
                {
                    throw std::runtime_error("This class should only be used as a member of another class, rather than standalone.");
                }

                return _pokedex->has_seen(species);
            }

            inline void set_has_seen(
                const std::string& species,
                bool value
            )
            {
                if(_is_gamecube_game)
                {
                    throw pkmn::feature_not_in_game_error(
                              "Pokédex",
                              "Gamecube games"
                          );
                }
                else if(!_pokedex)
                {
                    throw std::runtime_error("This class should only be used as a member of another class, rather than standalone.");
                }

                _pokedex->set_has_seen(species, value);
            }

#ifdef SWIGCSHARP
            // For equality and hash codes
            uintmax_t cptr()
            {
                return uintmax_t(_pokedex.get());
            }
#else
            bool operator==(const pokedex_has_seen_helper& rhs) const
            {
                return (_pokedex == rhs._pokedex);
            }

            bool operator!=(const pokedex_has_seen_helper& rhs) const
            {
                return !operator==(rhs);
            }
#endif

        private:
            pkmn::pokedex::sptr _pokedex;
            bool _is_gamecube_game;
    };

    class pokedex_has_caught_helper
    {
        public:
            pokedex_has_caught_helper():
                _pokedex(nullptr),
                _is_gamecube_game(false)
            {}

            pokedex_has_caught_helper(
                const pkmn::pokedex::sptr& pokedex,
                bool is_gamecube_game = false
            ): _pokedex(pokedex),
               _is_gamecube_game(is_gamecube_game)
            {}

            inline bool get_has_caught(
                const std::string& species
            )
            {
                if(_is_gamecube_game)
                {
                    throw pkmn::feature_not_in_game_error(
                              "Pokédex",
                              "Gamecube games"
                          );
                }
                else if(!_pokedex)
                {
                    throw std::runtime_error("This class should only be used as a member of another class, rather than standalone.");
                }

                return _pokedex->has_caught(species);
            }

            inline void set_has_caught(
                const std::string& species,
                bool value
            )
            {
                if(_is_gamecube_game)
                {
                    throw pkmn::feature_not_in_game_error(
                              "Pokédex",
                              "Gamecube games"
                          );
                }
                else if(!_pokedex)
                {
                    throw std::runtime_error("This class should only be used as a member of another class, rather than standalone.");
                }

                _pokedex->set_has_caught(species, value);
            }

#ifdef SWIGCSHARP
            // For equality and hash codes
            uintmax_t cptr()
            {
                return uintmax_t(_pokedex.get());
            }
#else
            bool operator==(const pokedex_has_caught_helper& rhs) const
            {
                return (_pokedex == rhs._pokedex);
            }

            bool operator!=(const pokedex_has_caught_helper& rhs) const
            {
                return !operator==(rhs);
            }
#endif

        private:
            pkmn::pokedex::sptr _pokedex;
            bool _is_gamecube_game;
    };

}}

#endif /* CPP_WRAPPERS_POKEDEX_HELPERS_HPP */
