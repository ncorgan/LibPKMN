/*
 * Copyright (c) 2015-2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

%include <python/python_init.i>
PKMN_PYTHON_INIT

%include <stdint.i>
%include <std_string.i>

%{
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
    #include <pkmn/calculations/moves/power.hpp>
    #include <pkmn/calculations/moves/natural_gift.hpp>
%}

%import <enums_python.i>

// Convert Doxygen docs to Python docstrings
%include <pkmn_python_docstrings.i>

%include <pkmn/calculations/form.hpp>
%include <pkmn/calculations/gender.hpp>
%include <pkmn/calculations/nature.hpp>
%include <pkmn/calculations/personality.hpp>
%include <pkmn/calculations/shininess.hpp>
%include <pkmn/calculations/size.hpp>
%include <pkmn/calculations/spinda_spots.hpp>
%include <pkmn/calculations/stats.hpp>

%include <pkmn/calculations/moves/critical_hit.hpp>
%include <pkmn/calculations/moves/damage.hpp>
%include <pkmn/calculations/moves/hidden_power.hpp>
%include <pkmn/calculations/moves/modifiers.hpp>
%include <pkmn/calculations/moves/power.hpp>
%include <pkmn/calculations/moves/natural_gift.hpp>
