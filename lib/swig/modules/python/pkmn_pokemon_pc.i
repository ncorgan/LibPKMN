/*
 * Copyright (c) 2017-2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

%{
    #include "cpp_wrappers/pokemon_pc.hpp"
%}

%include <attribute.i>

%ignore pkmn::swig::pokemon_pc::pokemon_pc();
%ignore pkmn::swig::pokemon_pc::pokemon_pc(const pkmn::pokemon_pc::sptr&);
%ignore pkmn::swig::pokemon_pc::cptr();
%ignore pkmn::swig::pokemon_pc::get_box(int);
%ignore pkmn::swig::pokemon_pc::get_num_boxes();

// Convert getter/setter functions into attributes for more idiomatic Python.

%attribute(pkmn::swig::pokemon_pc, pkmn::e_game, game, get_game);
%attributeval(pkmn::swig::pokemon_pc, %arg(std::vector<std::string>), box_names, get_box_names);

%extend pkmn::swig::pokemon_pc
{
    pkmn::swig::pokemon_box __getitem__(
        size_t position
    )
    {
        return self->get_box(int(position));
    }

    size_t __len__()
    {
        return self->get_num_boxes();
    }
}

%include "cpp_wrappers/pokemon_pc.hpp"
