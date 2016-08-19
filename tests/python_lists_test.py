#!/usr/bin/env python
#
# Copyright (c) 2015 Nicholas Corgan (n.corgan@gmail.com)
#
# Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
# or copy at http://opensource.org/licenses/MIT)
#

import pkmn
import sys
import traceback

def ability_list_test():
    try:
        # Make sure trying to create an invalid list results in a IndexError
        try:
            ability_list = pkmn.database.get_ability_list(2)
        except IndexError:
            pass
        except:
            raise RuntimeError("This should have thrown a IndexError.")

        try:
            ability_list = pkmn.database.get_ability_list(7)
        except IndexError:
            pass
        except:
            raise RuntimeError("This should have thrown a IndexError.")

        ability_list = pkmn.database.get_ability_list(6)
        if len(ability_list) != 191:
            raise RuntimeError("len(ability_list) (%d) != 191" % len(ability_list))

        return True
    except:
        print
        exc_type, exc_value, exc_traceback = sys.exc_info()
        traceback.print_exception(exc_type, exc_value, exc_traceback,
                                  limit=5, file=sys.stdout)
        return False

def game_list_test():
    try:
        # Make sure trying to create an invalid list results in a IndexError
        try:
            game_list = pkmn.database.get_game_list(0,False)
        except IndexError:
            pass
        except:
            raise RuntimeError("This should have thrown a IndexError.")

        try:
            game_list = pkmn.database.get_game_list(7,False)
        except IndexError:
            pass
        except:
            raise RuntimeError("This should have thrown a IndexError.")

        game_list = pkmn.database.get_game_list(6,False)
        if len(game_list) != 4:
            raise RuntimeError("len(game_list) (%d) != 4" % len(game_list))
        game_list = pkmn.database.get_game_list(6,True)
        if len(game_list) != 26:
            raise RuntimeError("len(game_list) (%d) != 26" % len(game_list))

        return True
    except:
        print
        exc_type, exc_value, exc_traceback = sys.exc_info()
        traceback.print_exception(exc_type, exc_value, exc_traceback,
                                  limit=5, file=sys.stdout)
        return False

# TODO when database branch is merged in
def item_list_test():
    item_list = pkmn.database.get_item_list("Red")
    return True

# TODO when database branch is merged in
def location_list_test():
    location_list = pkmn.database.get_location_list("Red",False)
    return True

# TODO when database branch is merged in
def move_list_test():
    move_list = pkmn.database.get_move_list("Red")
    return True

# TODO when database branch is merged in
def nature_list_test():
    nature_list = pkmn.database.get_nature_list()
    return True

# TODO when database branch is merged in
def pokemon_list_test():
    pokemon_list = pkmn.database.get_pokemon_list(1,True)
    return True

# TODO when database branch is merged in
def region_list_test():
    region_list = pkmn.database.get_region_list()
    return True

# TODO when database branch is merged in
def ribbon_list_test():
    ribbon_list = pkmn.database.get_ribbon_list(1)
    return True

# TODO when database branch is merged in
def super_training_medal_list_test():
    super_training_medal_list = pkmn.database.get_super_training_medal_list()
    return True

# TODO when database branch is merged in
def type_list_test():
    type_list = pkmn.database.get_type_list("Red")
    return True

if __name__ == "__main__":

    successful = True
    for test in [ability_list_test, game_list_test, item_list_test, location_list_test, \
                 move_list_test, nature_list_test, pokemon_list_test, region_list_test, \
                 ribbon_list_test, super_training_medal_list_test, type_list_test]:
        sys.stdout.write("Starting test %s..." % test.__name__)
        result = test()
        print("success.\n" if result else "failed.\n")
        successful = successful and result

    sys.exit(0 if successful else 1)
