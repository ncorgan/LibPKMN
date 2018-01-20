/*
 * Copyright (c) 2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#ifndef CPP_WRAPPERS_POKEDEX_HPP
#define CPP_WRAPPERS_POKEDEX_HPP

#include "pokedex_helpers.hpp"

#include <pkmn/config.hpp>
#include <pkmn/exception.hpp>
#include <pkmn/pokedex.hpp>

namespace pkmn { namespace swig {

    class pokedex
    {
        public:
            pokedex():
                _pokedex(nullptr),
                _game(""),
                _is_gamecube_game(false)
            {}

            pokedex(const std::string& game):
                _game(game),
                _is_gamecube_game((game == "Colosseum") or (game == "XD"))
            {
                if(not _is_gamecube_game)
                {
                    _pokedex = pkmn::pokedex::make(game);
                }
            }

            pokedex(
                const pkmn::pokedex::sptr& cpp_pokedex
            ): _pokedex(cpp_pokedex),
               _game(cpp_pokedex->get_game()),
               _is_gamecube_game(false) // There is no valid Gamecube instance
            {}

            inline std::string get_game()
            {
                return _game;
            }

            inline pokedex_has_seen_helper get_has_seen()
            {
                return pokedex_has_seen_helper(_pokedex);
            }

            // Copy, since SWIG will cast away the const in the reference.
            inline std::vector<std::string> get_all_seen()
            {
                return _is_gamecube_game ? std::vector<std::string>()
                                         : _pokedex->get_all_seen();
            }

            inline int get_num_seen()
            {
                return _is_gamecube_game ? 0 : _pokedex->get_num_seen();
            }

            inline pokedex_has_caught_helper get_has_caught()
            {
                return pokedex_has_caught_helper(_pokedex);
            }

            // Copy, since SWIG will cast away the const in the reference.
            std::vector<std::string> get_all_caught()
            {
                return _is_gamecube_game ? std::vector<std::string>()
                                         : _pokedex->get_all_caught();
            }

            inline int get_num_caught()
            {
                return _is_gamecube_game ? 0 : _pokedex->get_num_caught();
            }

#ifdef SWIGCSHARP
            inline uintmax_t cptr()
            {
                return uintmax_t(_pokedex.get());
            }
#else
            inline bool operator==(const pokedex& rhs) const
            {
                if(_is_gamecube_game or rhs._is_gamecube_game)
                {
                    return (_is_gamecube_game == rhs._is_gamecube_game);
                }
                else
                {
                    return (_pokedex == rhs._pokedex);
                }
            }

            inline bool operator!=(const pokedex& rhs) const
            {
                return !operator==(rhs);
            }
#endif

        private:
            pkmn::pokedex::sptr _pokedex;

            std::string _game;
            bool _is_gamecube_game;
    };

}}

#endif /* CPP_WRAPPERS_POKEDEX_HPP */
