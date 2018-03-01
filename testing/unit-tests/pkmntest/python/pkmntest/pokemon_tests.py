#!/usr/bin/env python
#
# Copyright (c) 2017-2018 Nicholas Corgan (n.corgan@gmail.com)
#
# Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
# or copy at http://opensource.org/licenses/MIT)
#

import pkmn

import os
import random
import string
import sys
import unittest

PYTHON_MAJOR_VERSION = sys.version_info[0]

GAME_TO_GENERATION = {
    "Red": 1,
    "Blue": 1,
    "Yellow": 1,
    "Gold": 2,
    "Silver": 2,
    "Crystal": 2,
    "Ruby": 3,
    "Sapphire": 3,
    "Emerald": 3,
    "FireRed": 3,
    "LeafGreen": 3,
    "Colosseum": 3,
    "XD": 3
}

GEN1_POKEMON_WITH_XY_MEGA_FORMS = [
    "Venusaur", "Blastoise", "Alakazam", "Gengar",
    "Kangaskhan", "Pinsir", "Gyarados", "Aerodactyl"
]

GEN1_POKEMON_WITH_ORAS_MEGA_FORMS = [
    "Beedrill", "Pidgeot", "Slowbro"
]

GEN2_POKEMON_WITH_XY_MEGA_FORMS = [
    "Ampharos", "Scizor", "Heracross", "Houndoom", "Tyranitar"
]

GEN3_POKEMON_WITH_XY_MEGA_FORMS = [
    "Blaziken", "Gardevoir", "Mawile", "Aggron", "Medicham",
    "Manectric", "Banette", "Absol", "Latias", "Latios", "Garchomp"
]

GEN3_POKEMON_WITH_ORAS_MEGA_FORMS = [
    "Sceptile", "Swampert", "Sableye", "Sharpedo", "Camerupt",
    "Altaria", "Glalie", "Salamence", "Metagross", "Rayquaza"
]

class pokemon_test_params:
    def __init__(
        self,
        valid_ball, invalid_balls,
        valid_item, invalid_items,
        expected_original_location, valid_locations, invalid_locations,
        valid_moves, invalid_moves,
        valid_original_games, invalid_original_games
    ):
        self.valid_ball = valid_ball
        self.invalid_balls = invalid_balls
        self.valid_item = valid_item
        self.invalid_items = invalid_items
        self.expected_original_location = expected_original_location
        self.valid_locations = valid_locations
        self.invalid_locations = invalid_locations
        self.valid_moves = valid_moves
        self.invalid_moves = invalid_moves
        self.valid_original_games = valid_original_games
        self.invalid_original_games = invalid_original_games

class pokemon_tests(unittest.TestCase):

    def assertStringEqual(self, str1, str2):
        if PYTHON_MAJOR_VERSION == 2:
            if "str" in str(type(str1)):
                str1 = str1.decode("utf-8")
            if "str" in str(type(str2)):
                str2 = str2.decode("utf-8")

        self.assertEqual(str1, str2)

    def __get_both_string_types(self, input_str):
        if PYTHON_MAJOR_VERSION == 2:
            # Which call succeeds depends on SWIG version
            try:
                return (input_str, input_str.decode("utf-8"))
            except:
                return (input_str, unicode(input_str))
        else:
            return (input_str, input_str)

    def gen1_forms_test(self, game):
        generation = GAME_TO_GENERATION[game]

        # Check that Mega forms only work in their given games.
        for species in GEN1_POKEMON_WITH_XY_MEGA_FORMS:
            if generation >= 6:
                pkmn.pokemon(species, game, "Mega", 100)
            else:
                with self.assertRaises(ValueError):
                    pkmn.pokemon(species, game, "Mega", 100)

        for species in GEN1_POKEMON_WITH_ORAS_MEGA_FORMS:
            if game in ["Omega Ruby", "Alpha Sapphire"]:
                pkmn.pokemon(species, game, "Mega", 100)
            else:
                with self.assertRaises(ValueError):
                    pkmn.pokemon(species, game, "Mega", 100)

        # Cosplay Pikachu should only work in OR/AS.
        for form in pkmn.database.pokemon_entry("Pikachu", "Omega Ruby", "").forms[1:]:
            if game in ["Omega Ruby", "Alpha Sapphire"]:
                pkmn.pokemon("Pikachu", game, form, 100)
            else:
                with self.assertRaises(ValueError):
                    pkmn.pokemon("Pikachu", game, form, 100)

        # Hardcode Mega X/Y cases.
        for species in ["Charizard", "Mewtwo"]:
            if generation >= 6:
                pkmn.pokemon(species, game, "Mega X", 100)
                pkmn.pokemon(species, game, "Mega Y", 100)
            else:
                with self.assertRaises(ValueError):
                    pkmn.pokemon(species, game, "Mega X", 100)
                with self.assertRaises(ValueError):
                    pkmn.pokemon(species, game, "Mega Y", 100)

    def gen2_forms_test(self, game):
        generation = GAME_TO_GENERATION[game]

        # Check that Mega forms only work in their given games.
        for species in GEN2_POKEMON_WITH_XY_MEGA_FORMS:
            if generation >= 6:
                pkmn.pokemon(species, game, "Mega", 100)
            else:
                with self.assertRaises(ValueError):
                    pkmn.pokemon(species, game, "Mega", 100)

        if game in ["Omega Ruby", "Alpha Sapphire"]:
            pkmn.pokemon("Steelix", game, "Mega", 100)
        else:
            with self.assertRaises(ValueError):
                pkmn.pokemon("Steelix", game, "Mega", 100)

        # Spiky-eared Pichu should only work in HG/SS.
        if game in ["HeartGold", "SoulSilver"]:
            pkmn.pokemon("Pichu", game, "Spiky-eared", 100)
        else:
            with self.assertRaises(ValueError):
                pkmn.pokemon("Pichu", game, "Spiky-eared", 100)

        # Unown's "!" and "?" forms aren't in Generation II.
        for letter in string.ascii_uppercase:
            unown = pkmn.pokemon("Unown", game, letter, 10)
            if game not in ["Colosseum", "XD"]:
                self.assertTrue(os.path.exists(unown.icon_filepath))
                self.assertTrue(os.path.exists(unown.sprite_filepath))

        if generation > 2:
            pkmn.pokemon("Unown", game, "!", 10)
            pkmn.pokemon("Unown", game, "?", 10)
        else:
            with self.assertRaises(ValueError):
                pkmn.pokemon("Unown", game, "!", 10)
            with self.assertRaises(ValueError):
                pkmn.pokemon("Unown", game, "?", 10)

    def gen3_forms_test(self, game):
        gamecube = (game in ["Colosseum", "XD"])
        generation = GAME_TO_GENERATION[game]

        # Check that Mega forms only work in their given games.
        for species in GEN3_POKEMON_WITH_XY_MEGA_FORMS:
            if generation >= 6:
                pkmn.pokemon(species, game, "Mega", 100)
            else:
                with self.assertRaises(ValueError):
                    pkmn.pokemon(species, game, "Mega", 100)

        for species in GEN3_POKEMON_WITH_ORAS_MEGA_FORMS:
            if game in ["Omega Ruby", "Alpha Sapphire"]:
                pkmn.pokemon(species, game, "Mega", 100)
            else:
                with self.assertRaises(ValueError):
                    pkmn.pokemon(species, game, "Mega", 100)

        # Castform should always work.
        for form in pkmn.database.pokemon_entry("Castform", "Omega Ruby", "").forms:
            castform = pkmn.pokemon("Castform", game, form, 30)
            if game not in ["Colosseum", "XD"]:
                self.assertTrue(os.path.exists(castform.icon_filepath))
                self.assertTrue(os.path.exists(castform.sprite_filepath))

        # Primal Reversion should only work in OR/AS.
        for species in ["Groudon", "Kyogre"]:
            pokemon = pkmn.pokemon(species, game, "", 70)
            if game not in ["Colosseum", "XD"]:
                self.assertTrue(os.path.exists(pokemon.icon_filepath))
                self.assertTrue(os.path.exists(pokemon.sprite_filepath))
            if game in ["Omega Ruby", "Alpha Sapphire"]:
                pkmn.pokemon(species, game, "Primal Reversion", 70)
            else:
                with self.assertRaises(ValueError):
                    pkmn.pokemon(species, game, "Primal Reversion", 70)

        # In Generation III, Deoxys's form is game-specific.
        if generation == 3:
            if game in ["Ruby", "Sapphire", "Colosseum", "XD"]:
                deoxys = pkmn.pokemon("Deoxys", game, "Normal", 70)
                if game not in ["Colosseum", "XD"]:
                    self.assertTrue(os.path.exists(deoxys.icon_filepath))
                    self.assertTrue(os.path.exists(deoxys.sprite_filepath))
            else:
                with self.assertRaises(ValueError):
                    deoxys = pkmn.pokemon("Deoxys", game, "Normal", 70)

            if game in ["FireRed"]:
                deoxys = pkmn.pokemon("Deoxys", game, "Attack", 70)
                self.assertTrue(os.path.exists(deoxys.icon_filepath))
                self.assertTrue(os.path.exists(deoxys.sprite_filepath))
            else:
                with self.assertRaises(ValueError):
                    deoxys = pkmn.pokemon("Deoxys", game, "Attack", 70)

            if game in ["LeafGreen"]:
                deoxys = pkmn.pokemon("Deoxys", game, "Defense", 70)
                self.assertTrue(os.path.exists(deoxys.icon_filepath))
                self.assertTrue(os.path.exists(deoxys.sprite_filepath))
            else:
                with self.assertRaises(ValueError):
                    deoxys = pkmn.pokemon("Deoxys", game, "Defense", 70)

            if game in ["Emerald"]:
                deoxys = pkmn.pokemon("Deoxys", game, "Speed", 70)
                self.assertTrue(os.path.exists(deoxys.icon_filepath))
                self.assertTrue(os.path.exists(deoxys.sprite_filepath))
            else:
                with self.assertRaises(ValueError):
                    deoxys = pkmn.pokemon("Deoxys", game, "Speed", 70)
        else:
            for form in pkmn.database.pokemon_entry("Deoxys", "Omega Ruby", "").forms:
                deoxys = pkmn.pokemon("Deoxys", game, form, 70)
                self.assertTrue(os.path.exists(deoxys.icon_filepath))
                self.assertTrue(os.path.exists(deoxys.sprite_filepath))

    def forms_test(self, game):
        generation = GAME_TO_GENERATION[game]

        if generation >= 1:
            self.gen1_forms_test(game)
        if generation >= 2:
            self.gen2_forms_test(game)
        if generation >= 3:
            self.gen3_forms_test(game)

    def gender_test(self, game):
        # Single-gender
        nidorina = pkmn.pokemon("Nidorina", game, "", 50)
        self.assertEqual(nidorina.gender, "Female")
        nidorina.gender = "Female"
        with self.assertRaises(ValueError):
            nidorina.gender = "Male"
        with self.assertRaises(ValueError):
            nidorina.gender = "Genderless"

        nidorino = pkmn.pokemon("Nidorino", game, "", 50)
        self.assertEqual(nidorino.gender, "Male")
        nidorino.gender = "Male"
        with self.assertRaises(ValueError):
            nidorino.gender = "Female"
        with self.assertRaises(ValueError):
            nidorino.gender = "Genderless"

        magnemite = pkmn.pokemon("Magnemite", game, "", 50)
        self.assertEqual(magnemite.gender, "Genderless")
        magnemite.gender = "Genderless"
        with self.assertRaises(ValueError):
            magnemite.gender = "Male"
        with self.assertRaises(ValueError):
            magnemite.gender = "Female"

        mixed_pokemon = [
            "Charmander", # 87.5% male
            "Growlithe",  # 75% male
            "Pidgey",     # 50% male
            "Vulpix"      # 25% male
        ]

        for species in mixed_pokemon:
            pokemon = pkmn.pokemon(species, game, "", 50)
            pokemon.gender = "Female"
            self.assertEqual(pokemon.gender, "Female")
            pokemon.gender = "Male"
            self.assertEqual(pokemon.gender, "Male")
            with self.assertRaises(ValueError):
                pokemon.gender = "Genderless"

    def initial_values_test(self, pokemon):
        generation = GAME_TO_GENERATION[pokemon.game]

        self.assertEqual(pokemon.condition, "None")

        if generation >= 5:
            self.assertEqual(pokemon.nickname, pokemon.species)
        else:
            self.assertEqual(pokemon.nickname, pokemon.species.upper())

        self.assertEqual(pokemon.original_trainer_name, pkmn.pokemon.DEFAULT_TRAINER_NAME)

        if generation >= 2:
            self.assertEqual(pokemon.held_item, "None")
            self.assertEqual(pokemon.original_trainer_gender, "Male")
        else:
            # Default value since a getter shouldn't throw an exception.
            self.assertEqual(pokemon.held_item, "")
            self.assertEqual(pokemon.original_trainer_gender, "")

        self.assertEqual(
            pokemon.original_trainer_public_id,
            (pkmn.pokemon.DEFAULT_TRAINER_ID & 0xFFFF)
        )

        if generation >= 3:
            self.assertEqual(
                pokemon.original_trainer_secret_id,
                ((pkmn.pokemon.DEFAULT_TRAINER_ID & 0xFFFF0000) >> 16)
            )
            self.assertEqual(
                pokemon.original_trainer_id,
                pkmn.pokemon.DEFAULT_TRAINER_ID
            )
        else:
            self.assertEqual(
                pokemon.original_trainer_id,
                (pkmn.pokemon.DEFAULT_TRAINER_ID & 0xFFFF)
            )

            # Default value since a getter shouldn't throw an exception.
            self.assertEqual(pokemon.original_trainer_secret_id, 0)

        if generation >= 2:
            self.assertEqual(
                pokemon.current_trainer_friendship,
                pokemon.database_entry.base_friendship
            )
        else:
            # Default value since a getter shouldn't throw an exception.
            self.assertEqual(pokemon.current_trainer_friendship, 0)

        if generation >= 3:
            self.assertEqual(pokemon.ball, "Premier Ball")

            # There is no distinction between Colosseum and XD in the game
            #storage.
            if pokemon.game in ["Colosseum", "XD"]:
                self.assertEqual(pokemon.original_game, "Colosseum/XD")
            else:
                self.assertEqual(pokemon.original_game, pokemon.game)
        else:
            # Default value since a getter shouldn't throw an exception.
            self.assertEqual(pokemon.ball, "")
            self.assertEqual(pokemon.original_game, "")

        self.assertEqual(
            pokemon.experience,
            pokemon.database_entry.get_experience_at_level(pokemon.level)
        )

        if generation >= 2:
            self.assertEqual(pokemon.level_met, pokemon.level)

        for move_index in range(len(pokemon.moves)):
            self.assertEqual(pokemon.moves[move_index].move, "None")
            self.assertEqual(pokemon.moves[move_index].pp, 0)

        self.assertTrue(os.path.exists(pokemon.icon_filepath))
        self.assertTrue(os.path.exists(pokemon.sprite_filepath))

        self.assertEqual(pokemon.current_hp, pokemon.stats["HP"])

    def initial_maps_test(self, pokemon):
        generation = GAME_TO_GENERATION[pokemon.game]

        # EVs

        self.assertTrue("HP" in pokemon.EVs.keys)
        self.assertTrue("Attack" in pokemon.EVs.keys)
        self.assertTrue("Defense" in pokemon.EVs.keys)
        self.assertTrue("Speed" in pokemon.EVs.keys)
        if generation >= 3:
            self.assertFalse("Special" in pokemon.EVs.keys)
            self.assertTrue("Special Attack" in pokemon.EVs.keys)
            self.assertTrue("Special Defense" in pokemon.EVs.keys)
        else:
            self.assertTrue("Special" in pokemon.EVs.keys)
            self.assertFalse("Special Attack" in pokemon.EVs.keys)
            self.assertFalse("Special Defense" in pokemon.EVs.keys)

        for EV in pokemon.EVs.keys:
            self.assertGreaterEqual(pokemon.EVs[EV], 0)
            self.assertLessEqual(
                pokemon.EVs[EV],
                (255 if generation >= 3 else 65535)
            )

        # IVs

        self.assertTrue("HP" in pokemon.IVs.keys)
        self.assertTrue("Attack" in pokemon.IVs.keys)
        self.assertTrue("Defense" in pokemon.IVs.keys)
        self.assertTrue("Speed" in pokemon.IVs.keys)
        if generation >= 3:
            self.assertFalse("Special" in pokemon.IVs.keys)
            self.assertTrue("Special Attack" in pokemon.IVs.keys)
            self.assertTrue("Special Defense" in pokemon.IVs.keys)
        else:
            self.assertTrue("Special" in pokemon.IVs.keys)
            self.assertFalse("Special Attack" in pokemon.IVs.keys)
            self.assertFalse("Special Defense" in pokemon.IVs.keys)

        for IV in pokemon.IVs.keys:
            self.assertGreaterEqual(pokemon.IVs[IV], 0)
            self.assertLessEqual(
                pokemon.IVs[IV],
                (31 if generation >= 3 else 15)
            )

        # Stats

        self.assertTrue("HP" in pokemon.stats.keys())
        self.assertTrue("Attack" in pokemon.stats.keys())
        self.assertTrue("Defense" in pokemon.stats.keys())
        self.assertTrue("Speed" in pokemon.stats.keys())
        if generation >= 2:
            self.assertFalse("Special" in pokemon.stats.keys())
            self.assertTrue("Special Attack" in pokemon.stats.keys())
            self.assertTrue("Special Defense" in pokemon.stats.keys())
        else:
            self.assertTrue("Special" in pokemon.stats.keys())
            self.assertFalse("Special Attack" in pokemon.stats.keys())
            self.assertFalse("Special Defense" in pokemon.stats.keys())

        for stat in pokemon.stats.keys():
            self.assertGreaterEqual(pokemon.stats[stat], 0)
            self.assertLessEqual(pokemon.stats[stat], 65535)

        if generation >= 3:
            # Contest stats

            self.assertTrue("Cool" in pokemon.contest_stats.keys)
            self.assertTrue("Beauty" in pokemon.contest_stats.keys)
            self.assertTrue("Cute" in pokemon.contest_stats.keys)
            self.assertTrue("Smart" in pokemon.contest_stats.keys)
            self.assertTrue("Tough" in pokemon.contest_stats.keys)
            if generation == 3:
                self.assertTrue("Feel" in pokemon.contest_stats.keys)
                self.assertFalse("Sheen" in pokemon.contest_stats.keys)
            else:
                self.assertFalse("Feel" in pokemon.contest_stats.keys)
                self.assertTrue("Sheen" in pokemon.contest_stats.keys)

            for contest_stat in pokemon.contest_stats.keys:
                self.assertEqual(pokemon.contest_stats[contest_stat], 0)

            # Markings

            self.assertTrue("Circle" in pokemon.markings.keys)
            self.assertTrue("Triangle" in pokemon.markings.keys)
            self.assertTrue("Square" in pokemon.markings.keys)
            self.assertTrue("Heart" in pokemon.markings.keys)
            if generation >= 4:
                self.assertTrue("Star" in pokemon.markings.keys)
                self.assertTrue("Diamond" in pokemon.markings.keys)
            else:
                self.assertFalse("Star" in pokemon.markings.keys)
                self.assertFalse("Diamond" in pokemon.markings.keys)

            for marking in pokemon.markings.keys:
                self.assertFalse(pokemon.markings[marking])

    def image_filepaths_test(self, pokemon):
        generation = GAME_TO_GENERATION[pokemon.game]

        self.assertTrue(os.path.exists(pokemon.icon_filepath))

        if generation >= 2:
            for gender in ["Male", "Female"]:
                for is_shiny in [True, False]:
                    pokemon.gender = gender
                    pokemon.is_shiny = is_shiny
                    self.assertTrue(os.path.exists(pokemon.sprite_filepath))
        else:
            self.assertTrue(os.path.exists(pokemon.sprite_filepath))

    def ability_test(self, pokemon):
        generation = GAME_TO_GENERATION[pokemon.game]

        if generation >= 3:
            self.assertNotEquals(
                pokemon.database_entry.abilities.first,
                "None"
            )

            pokemon.ability = pokemon.database_entry.abilities.first
            self.assertEqual(
                pokemon.ability,
                pokemon.database_entry.abilities.first
            )

            if pokemon.database_entry.abilities.second != "None":
                pokemon.ability = pokemon.database_entry.abilities.second
                self.assertEqual(
                    pokemon.ability,
                    pokemon.database_entry.abilities.second
                )

            if generation >= 5:
                if pokemon.database_entry.hidden_ability != "None":
                    pokemon.ability = pokemon.database_entry.ability
                    self.assertEqual(
                        pokemon.ability,
                        pokemon.database_entry.hidden_ability
                    )

            with self.assertRaises(ValueError):
                pokemon.ability = "Not an ability"
            with self.assertRaises(ValueError):
                pokemon.ability = "Wonder Guard"
        else:
            # The getter shouldn't throw by convention, but the setter will.
            self.assertEqual(pokemon.ability, "")

            with self.assertRaises(RuntimeError):
                pokemon.ability = "Wonder Guard"

    def ball_test(self, pokemon, valid_ball_name, invalid_ball_names):
        generation = GAME_TO_GENERATION[pokemon.game]

        if generation >= 3:
            pokemon.ball = valid_ball_name
            self.assertEqual(pokemon.ball, valid_ball_name)

            for invalid_ball_name in invalid_ball_names:
                with self.assertRaises(ValueError):
                    pokemon.ball = invalid_ball_name
        else:
            # The getter shouldn't throw by convention, but the setter will.
            self.assertEqual(pokemon.ball, "")

            with self.assertRaises(RuntimeError):
                pokemon.ball = "Great Ball"

    def condition_test(self, pokemon):
        generation = GAME_TO_GENERATION[pokemon.game]

        conditions = ["None", "Asleep", "Poison", "Burn", "Frozen", "Paralysis"]
        if generation >= 3:
            conditions += ["Bad Poison"]

        for condition in conditions:
            pokemon.condition = condition
            self.assertEqual(pokemon.condition, condition)

    def friendship_test(self, pokemon):
        generation = GAME_TO_GENERATION[pokemon.game]

        if generation >= 2:
            friendship = random.randint(0, 255)

            pokemon.current_trainer_friendship = friendship
            self.assertEqual(pokemon.current_trainer_friendship, friendship)

            with self.assertRaises(IndexError):
                pokemon.current_trainer_friendship = -1
            with self.assertRaises(IndexError):
                pokemon.current_trainer_friendship = 256
        else:
            # The getter shouldn't throw by convention, but the setter will.
            self.assertEqual(pokemon.current_trainer_friendship, 0)

            with self.assertRaises(RuntimeError):
                pokemon.current_trainer_friendship = 0

    def item_test(self, pokemon, valid_item_name, invalid_item_names):
        generation = GAME_TO_GENERATION[pokemon.game]

        if generation >= 2:
            pokemon.held_item = valid_item_name
            self.assertEqual(pokemon.held_item, valid_item_name)

            for invalid_item_name in invalid_item_names:
                with self.assertRaises(ValueError):
                    pokemon.held_item = invalid_item_name
        else:
            # The getter shouldn't throw by convention, but the setter will.
            self.assertEqual(pokemon.held_item, "")

            with self.assertRaises(RuntimeError):
                pokemon.held_item = "Potion"

    def level_test(self, pokemon):
        generation = GAME_TO_GENERATION[pokemon.game]

        with self.assertRaises(IndexError):
            pokemon.level = -1
        with self.assertRaises(IndexError):
            pokemon.level = 101

        level = 50
        pokemon.level = level
        self.assertEqual(pokemon.level, level)
        self.assertEqual(
            pokemon.database_entry.get_level_at_experience(pokemon.experience),
            level
        )

        experience = 123456
        pokemon.experience = experience
        self.assertEqual(pokemon.experience, experience)
        self.assertLess(
            pokemon.database_entry.get_experience_at_level(pokemon.level-1),
            experience
        )
        self.assertLessEqual(
            pokemon.database_entry.get_experience_at_level(pokemon.level),
            experience
        )

        if generation == 1:
            with self.assertRaises(IndexError):
                pokemon.level = 1

            # The getter shouldn't throw by convention, but the setter will.
            self.assertEqual(pokemon.level_met, 0)

            with self.assertRaises(RuntimeError):
                pokemon.level_met = 10
        elif generation == 2:
            level_met = 5
            pokemon.level_met = level_met
            self.assertEqual(pokemon.level_met, level_met)

            with self.assertRaises(IndexError):
                pokemon.level = 1
            with self.assertRaises(IndexError):
                pokemon.level_met = 101
        else:
            level_met = 5
            pokemon.level_met = level_met
            self.assertEqual(pokemon.level_met, level_met)

            with self.assertRaises(IndexError):
                pokemon.level = 0
            with self.assertRaises(IndexError):
                pokemon.level_met = 101

    def location_met_test(
        self,
        pokemon,
        expected_original_location,
        valid_locations,
        invalid_locations
    ):
        generation = GAME_TO_GENERATION(pokemon.game)

        if generation == 1:
            # The getters shouldn't throw by convention, but the setters will.
            self.assertEqual(pokemon.location_met, "")
            self.assertEqual(pokemon.location_met_as_egg, "")

            with self.assertRaises(RuntimeError):
                pokemon.location_met = valid_locations[0]
            with self.assertRaises(RuntimeError):
                pokemon.location_met_as_egg = valid_locations[0]
        elif generation in [2,3]:
            self.assertEqual(pokemon.location_met, expected_original_location)

            for valid_location in valid_locations:
                pokemon.location_met = valid_location
                self.assertEqual(pokemon.location_met, valid_location)

            for invalid_location in invalid_locations:
                with self.assertRaises(ValueError):
                    pokemon.location_met = invalid_location

            # The getter shouldn't throw by convention, but the setter will.
            self.assertEqual(pokemon.location_met, "")

            with self.assertRaises(RuntimeError):
                pokemon.location_met_as_egg = valid_locations[0]
        else:
            self.assertEqual(pokemon.location_met, expected_original_location)
            self.assertEqual(pokemon.location_met_as_egg, expected_original_location)

            for valid_location in valid_locations:
                pokemon.location_met = valid_location
                self.assertEqual(pokemon.location_met, valid_location)

                pokemon.location_met_as_egg = valid_location
                self.assertEqual(pokemon.location_met_as_egg, valid_location)

            for invalid_location in invalid_locations:
                with self.assertRaises(ValueError):
                    pokemon.location_met = invalid_location

                with self.assertRaises(ValueError):
                    pokemon.location_met_as_egg = invalid_location

    def markings_test(self, pokemon):
        generation = GAME_TO_GENERATION[pokemon.game]

        if generation >= 3:
            for marking in pokemon.markings.keys:
                self.assertFalse(pokemon.markings[marking])
                pokemon.markings[marking] = True
                self.assertTrue(pokemon.markings[marking])
        else:
            self.assertEqual(len(pokemon.markings), 0)
            with self.assertRaises(RuntimeError):
                pokemon.markings["Circle"] = True

    def move_test(self, pokemon, valid_move_names, invalid_move_names):
        self.assertEqual(len(valid_move_names), 4)

        for move_index in range(len(valid_move_names)):
            pokemon.moves[move_index].move = valid_move_names[move_index]
            self.assertEqual(
                pokemon.moves[move_index].move,
                valid_move_names[move_index]
            )

            move_entry = pkmn.database.move_entry(
                             valid_move_names[move_index],
                             pokemon.game
                         )
            pokemon.moves[move_index].pp = 0
            self.assertEqual(pokemon.moves[move_index].pp, 0)

            max_pp = move_entry.get_pp(3)
            pokemon.moves[move_index].pp = max_pp
            self.assertEqual(pokemon.moves[move_index].pp, max_pp)

            with self.assertRaises(IndexError):
                pokemon.moves[move_index].pp = -1
            with self.assertRaises(IndexError):
                pokemon.moves[move_index].pp = max_pp+1

        for invalid_move_name in invalid_move_names:
            with self.assertRaises(ValueError):
                pokemon.moves[0].move = invalid_move_name

        with self.assertRaises(IndexError):
            pokemon.moves[-1].move = valid_move_names[0]
        with self.assertRaises(IndexError):
            pokemon.moves[4].move = valid_move_names[0]

        with self.assertRaises(IndexError):
            pokemon.moves[-1].pp = valid_move_names[0]
        with self.assertRaises(IndexError):
            pokemon.moves[4].pp = valid_move_names[0]

    def original_game_test(self, pokemon, valid_games, invalid_games):
        generation = GAME_TO_GENERATION[pokemon.game]

        if generation >= 3:
            for valid_game in valid_games:
                pokemon.original_game = valid_game
                if valid_game in ["Colosseum", "XD"]:
                    self.assertEqual(
                        pokemon.original_game,
                        "Colosseum/XD"
                    )
                else:
                    self.assertEqual(
                        pokemon.original_game,
                        valid_game
                    )

            for invalid_game in invalid_games:
                with self.assertRaises(ValueError):
                    pokemon.original_game = invalid_game
        else:
            # The getter shouldn't throw by convention, but the setter will.
            self.assertEqual(pokemon.original_game, "")

            with self.assertRaises(RuntimeError):
                pokemon.original_game = valid_games[0]

    def personality_test(self, pokemon):
        generation = GAME_TO_GENERATION[pokemon.game]

        if generation >= 3:
            personality = random.randint(0, 0xFFFFFFFF)

            pokemon.personality = personality
            self.assertEqual(pokemon.personality, personality)

            # Make sure SWIG+Python catches values outside the uint32_t
            # range. What type of error is thrown depends on SWIG version.
            try:
                with self.assertRaises(OverflowError):
                    pokemon.personality = -1
            except:
                with self.assertRaises(TypeError):
                    pokemon.personality = -1

            try:
                with self.assertRaises(OverflowError):
                    pokemon.personality = 0xFFFFFFFF+1
            except:
                with self.assertRaises(TypeError):
                    pokemon.personality = 0xFFFFFFFF+1
        else:
            # The getter shouldn't throw by convention, but the setter will.
            self.assertEqual(pokemon.personality, 0)

            with self.assertRaises(RuntimeError):
                pokemon.personality = 0

    def pokerus_test(self, pokemon):
        generation = GAME_TO_GENERATION[pokemon.game]

        if generation >= 2:
            pokerus_duration = random.randint(0, 15)
            pokemon.pokerus_duration = pokerus_duration
            self.assertEqual(pokemon.pokerus_duration, pokerus_duration)

            with self.assertRaises(IndexError):
                pokemon.pokerus_duration = -1
            with self.assertRaises(IndexError):
                pokemon.pokerus_duration = 16
        else:
            # The getter shouldn't throw by convention, but the setter will.
            self.assertEquals(pokemon.pokerus_duration, 0)

            with self.assertRaises(RuntimeError):
                pokemon.pokerus_duration = 1

    def stats_test(self, pokemon):
        generation = GAME_TO_GENERATION[pokemon.game]

        # Check bounds for setting the current HP.
        with self.assertRaises(IndexError):
            pokemon.current_hp = -1
        with self.assertRaises(IndexError):
            pokemon.current_hp = pokemon.stats["HP"] + 1

        pokemon.current_hp = 0
        self.assertEqual(pokemon.current_hp, 0)

        pokemon.current_hp = pokemon.stats["HP"] - 1
        self.assertEqual(pokemon.current_hp, pokemon.stats["HP"] - 1)

        # Set the HP stat to lower than the current HP, and make sure
        # it's updated.

        current_hp = pokemon.current_hp
        pokemon.EVs["HP"] = 0
        pokemon.IVs["HP"] = 0
        self.assertLessEqual(pokemon.current_hp, current_hp)

        if generation >= 3:
            for contest_stat in pokemon.contest_stats.keys:
                stat_value = random.randint(0, 255)
                pokemon.contest_stats[contest_stat] = stat_value
                self.assertEqual(
                    pokemon.contest_stats[contest_stat],
                    stat_value
                )

    def trainer_info_test(self, pokemon):
        generation = GAME_TO_GENERATION[pokemon.game]

        with self.assertRaises(ValueError):
            pokemon.nickname = ""
        with self.assertRaises(ValueError):
            pokemon.nickname = "Too long nickname"

        pokemon.nickname = "foobarbaz"
        self.assertEqual(pokemon.nickname, "foobarbaz")

        with self.assertRaises(ValueError):
            pokemon.original_trainer_name = ""
        with self.assertRaises(ValueError):
            pokemon.original_trainer_name = "Too long trainer name"

        pokemon.original_trainer_name = "foobar"
        self.assertEqual(pokemon.original_trainer_name, "foobar")

        if generation >= 2:
            for gender in ["Male", "Female"]:
                pokemon.original_trainer_gender = gender
                self.assertEqual(
                    pokemon.original_trainer_gender,
                    gender
                )

                with self.assertRaises(ValueError):
                    pokemon.original_trainer_gender = "Genderless"
        else:
            for gender in ["Male", "Female"]:
                with self.assertRaises(RuntimeError):
                    pokemon.original_trainer_gender = gender

        if generation >= 3:
            pokemon.original_trainer_id = 0x1234ABCD
            self.assertEqual(pokemon.original_trainer_id, 0x1234ABCD)
            self.assertEqual(pokemon.original_trainer_public_id, 0xABCD)
            self.assertEqual(pokemon.original_trainer_secret_id, 0x1234)

            pokemon.original_trainer_public_id = 0x1A2B
            self.assertEqual(pokemon.original_trainer_id, 0x12341A2B)
            self.assertEqual(pokemon.original_trainer_public_id, 0x1A2B)
            self.assertEqual(pokemon.original_trainer_secret_id, 0x1234)

            pokemon.original_trainer_secret_id = 0x3C4D
            self.assertEqual(pokemon.original_trainer_id, 0x3C4D1A2B)
            self.assertEqual(pokemon.original_trainer_public_id, 0x1A2B)
            self.assertEqual(pokemon.original_trainer_secret_id, 0x3C4D)

            # Make sure SWIG+Python catches values outside the uint(16|32)_t
            # ranges. What type of error is thrown depends on SWIG version.

            try:
                with self.assertRaises(OverflowError):
                    pokemon.original_trainer_id = -1
            except:
                with self.assertRaises(TypeError):
                    pokemon.original_trainer_id = -1

            try:
                with self.assertRaises(OverflowError):
                    pokemon.original_trainer_id = 0xFFFFFFFF+1
            except:
                with self.assertRaises(TypeError):
                    pokemon.original_trainer_id = 0xFFFFFFFF+1

            try:
                with self.assertRaises(OverflowError):
                    pokemon.original_trainer_secret_id = -1
            except:
                with self.assertRaises(TypeError):
                    pokemon.original_trainer_secret_id = -1

            try:
                with self.assertRaises(OverflowError):
                    pokemon.original_trainer_secret_id = 0xFFFF+1
            except:
                with self.assertRaises(TypeError):
                    pokemon.original_trainer_secret_id = 0xFFFF+1
        else:
            pokemon.original_trainer_id = 0xABCD
            self.assertEqual(pokemon.original_trainer_id, 0xABCD)
            self.assertEqual(pokemon.original_trainer_public_id, 0xABCD)

            pokemon.original_trainer_public_id = 0x9876
            self.assertEqual(pokemon.original_trainer_id, 0x9876)
            self.assertEqual(pokemon.original_trainer_public_id, 0x9876)

            with self.assertRaises(IndexError):
                pokemon.original_trainer_id = 0xFFFF+1
            with self.assertRaises(RuntimeError):
                pokemon.original_trainer_secret_id = 0

        # Make sure SWIG+Python catches values outside the uint16_t
        # ranges. What type of error is thrown depends on SWIG version.
        try:
            with self.assertRaises(OverflowError):
                pokemon.original_trainer_public_id = -1
        except:
            with self.assertRaises(TypeError):
                pokemon.original_trainer_public_id = -1

        try:
            with self.assertRaises(OverflowError):
                pokemon.original_trainer_public_id = 0xFFFF+1
        except:
            with self.assertRaises(TypeError):
                pokemon.original_trainer_public_id = 0xFFFF+1

    def common_test(self, pokemon, test_params):
        self.initial_values_test(pokemon)
        self.initial_maps_test(pokemon)
        self.ability_test(pokemon)
        self.ball_test(
            pokemon,
            test_params.valid_ball,
            test_params.invalid_balls
        )
        self.condition_test(pokemon)
        self.image_filepaths_test(pokemon)
        self.item_test(
            pokemon,
            test_params.valid_item,
            test_params.invalid_items
        )
        self.level_test(pokemon)
        self.move_test(
            pokemon,
            test_params.valid_moves,
            test_params.invalid_moves
        )
        self.original_game_test(
            pokemon,
            test_params.valid_original_games,
            test_params.invalid_original_games
        )
        self.personality_test(pokemon)
        self.pokerus_test(pokemon)
        self.stats_test(pokemon)
        self.trainer_info_test(pokemon)
