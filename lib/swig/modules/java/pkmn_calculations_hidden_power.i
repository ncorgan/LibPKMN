/*
 * Copyright (c) 2016 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

%{
    #include <pkmn/calculations/hidden_power.hpp>
%}

%include <std_string.i>

/*
 * Doxygen documentation
 */

%javamethodmodifiers pkmn::calculations::hidden_power::getType "
/**
 * Get what type Hidden Power has when this Pokémon uses it.
 */
public";

%javamethodmodifiers pkmn::calculations::hidden_power::getBasePower "
/**
 * Get the base power.
 */
public";

%javamethodmodifiers pkmn::calculations::hidden_power::setType "
/**
 * Set the type.
 *
 * @param newType new type
 */
public";

%javamethodmodifiers pkmn::calculations::hidden_power::setBasePower "
/**
 * Set the base power.
 *
 * @param newBasePower new base power
 */
public";

/*
 * Manually write the get/set functions so we can individually
 * document them.
 */
namespace pkmn { namespace calculations {

class hidden_power {
    public:
        %extend {
            const std::string& getType() {
                return self->type;
            }
            int getBasePower() {
                return self->base_power;
            }

            void setType(const std::string &newType) {
                self->type = newType;
            }
            void setBasePower(const int newBasePower) {
                self->base_power = newBasePower;
            }
        }
};

typedef std::vector<pkmn::calculations::hidden_power> calculations::hidden_powers_t;

}}

%include <java/stl_macros.i>
PKMN_JAVA_VECTOR(pkmn::calculations::hidden_power, HiddenPower, HiddenPowerVector)

%ignore hidden_power;
%include <pkmn/calculations/hidden_power.hpp>
