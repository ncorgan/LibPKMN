/*
 * Copyright (c) 2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

%include <python/python_init.i>
PKMN_PYTHON_INIT

// Why don't we need to import stl_python? How does this get vectors?
%import <enums_python.i>

%{
    #include <pkmn/database/lists.hpp>
%}

// Convert Doxygen docs to Python docstrings
%include <pkmn_python_docstrings.i>

%include <pkmn/database/lists.hpp>
