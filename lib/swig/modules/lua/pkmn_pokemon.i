/*
 * Copyright (c) 2016 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

%{
    #include "exception_internal.hpp"

    #include <pkmn/exception.hpp>
    #include <pkmn/pokemon.hpp>
%}

// SWIG doesn't deal well with read-only static variables
%ignore pkmn::pokemon::DEFAULT_TRAINER_ID;
%ignore pkmn::pokemon::DEFAULT_TRAINER_NAME;
%ignore pkmn::pokemon::set_move;

%include <pkmn/pokemon.hpp>

%extend std::shared_ptr<pkmn::pokemon> {

    void set_move(
        const std::string &move_name,
        int index
    )
    {
        pkmn::enforce_bounds("Move index", index, 1, 4);

        self->get()->set_move(move_name, index-1);
    }

    bool __eq__(
        const pkmn::pokemon::sptr &rhs
    ) {
        return (self->get() == rhs.get());
    }

}
%template(pokemon_sptr) std::shared_ptr<pkmn::pokemon>;

%import <lua/stl_macros.i>
PKMN_LUA_VECTOR(pkmn::pokemon::sptr, pokemon_list)
