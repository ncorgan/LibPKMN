/*
 * Copyright (c) 2016-2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "pokemon_gen1impl.hpp"

#include "database/database_common.hpp"
#include "database/id_to_index.hpp"
#include "database/id_to_string.hpp"

#include "io/pk1.hpp"
#include "io/read_write.hpp"

#include <pksav/gen1/pokemon.h>

#include <boost/filesystem.hpp>
#include <boost/format.hpp>

#include <stdexcept>

namespace fs = boost::filesystem;

namespace pkmn { namespace io {

    BOOST_STATIC_CONSTEXPR int RED_ID = 1;

    bool vector_is_valid_pk1(
        const std::vector<uint8_t>& buffer
    )
    {
        // Validate size
        if(buffer.size() != sizeof(struct pksav_gen1_pc_pokemon) and
           buffer.size() != sizeof(struct pksav_gen1_party_pokemon))
        {
            return false;
        }

        const struct pksav_gen1_pc_pokemon* native = reinterpret_cast<const struct pksav_gen1_pc_pokemon*>(buffer.data());

        // Validate species
        try
        {
            (void)pkmn::database::pokemon_index_to_id(
                      native->species,
                      RED_ID
                  );
        }
        catch(const std::invalid_argument&)
        {
            return false;
        }

        return true;
    }

    pkmn::pokemon::sptr load_pk1(
        const std::vector<uint8_t>& buffer
    )
    {
        if(!vector_is_valid_pk1(buffer))
        {
            throw std::runtime_error("Invalid .pk1.");
        }

        return std::make_shared<pokemon_gen1impl>(
                   reinterpret_cast<const struct pksav_gen1_pc_pokemon*>(buffer.data()),
                   RED_ID
               );
    }

    pkmn::pokemon::sptr load_pk1(
        const std::string& filepath
    )
    {
        if(!fs::exists(filepath))
        {
            throw std::invalid_argument(
                      str(boost::format("The file \"%s\" does not exist.")
                          % filepath.c_str())
                  );
        }

        return load_pk1(read_file(filepath));
    }
}}
