/*
 * Copyright (c) 2016 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#ifndef INCLUDED_PKMN_ENV_HPP
#define INCLUDED_PKMN_ENV_HPP

#include <pkmn/config.hpp>
#include <cstdlib>
#include <string>

/*
 * Thin OS-agnostic wrapper for working with environment variables
 */

PKMN_INLINE std::string pkmn_getenv(
    const std::string &key
) {
    char* val = getenv(key.c_str());
    return (val) ? val : "";
}

PKMN_INLINE void pkmn_setenv(
    const std::string &key,
    const std::string &val
) {
    #if defined(PKMN_PLATFORM_MINGW) || defined(PKMN_PLATFORM_WIN32)
        _putenv_s(key.c_str(), val.c_str());
    #else
        setenv(key.c_str(), val.c_str(), 1);
    #endif
}

PKMN_INLINE void pkmn_unsetenv(
    const std::string &key
) {
    #if defined(PKMN_PLATFORM_MINGW) || defined(PKMN_PLATFORM_WIN32)
        _putenv_s(key.c_str(), "");
    #else
        unsetenv(key.c_str());
    #endif
}

#endif /* INCLUDED_PKMN_ENV_HPP */
