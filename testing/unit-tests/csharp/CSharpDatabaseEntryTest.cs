/*
 * Copyright (c) 2016-2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

using System;
using NUnit.Framework;

[TestFixture]
public class CSharpDatabaseEntryTest {
    [Test]
    public void ItemEntryTest() {
        // Make sure trying to create an invalid entry results in an error.
        Assert.Throws<ArgumentOutOfRangeException>(
            delegate {
                new PKMN.Database.ItemEntry("Not an item", "SoulSilver");
            }
        );
        Assert.Throws<ArgumentOutOfRangeException>(
            delegate {
                new PKMN.Database.ItemEntry("Fast Ball", "Not a game");
            }
        );
        Assert.Throws<ArgumentOutOfRangeException>(
            delegate {
                new PKMN.Database.ItemEntry("Fast Ball", "Red");
            }
        );

        PKMN.Database.ItemEntry itemEntry = new PKMN.Database.ItemEntry("Fast Ball", "SoulSilver");

        Assert.AreEqual(itemEntry.Name, "Fast Ball");
        Assert.AreEqual(itemEntry.Game, "SoulSilver");
        Assert.AreEqual(itemEntry.Category, "Apricorn balls");
        Assert.AreEqual(itemEntry.Pocket, "Poké Balls");

        // Just make sure it works
        string description = itemEntry.Description;

        Assert.IsTrue(itemEntry.isHoldable);
        Assert.AreEqual(itemEntry.FlingPower, 0);
        Assert.AreEqual(itemEntry.FlingEffect, "None");

        PKMN.Database.ItemEntry itemEntrySame = new PKMN.Database.ItemEntry("Fast Ball", "SoulSilver");
        PKMN.Database.ItemEntry itemEntryDifferentItem = new PKMN.Database.ItemEntry("Potion", "SoulSilver");
        PKMN.Database.ItemEntry itemEntryDifferentGame = new PKMN.Database.ItemEntry("Potion", "HeartGold");

        Assert.AreEqual(itemEntry, itemEntry);
        Assert.AreEqual(itemEntry, itemEntrySame);
        Assert.AreEqual(itemEntry.GetHashCode(), itemEntrySame.GetHashCode());

        Assert.AreNotEqual(itemEntry, itemEntryDifferentItem);
        Assert.AreNotEqual(itemEntry.GetHashCode(), itemEntryDifferentItem.GetHashCode());

        Assert.AreNotEqual(itemEntry, itemEntryDifferentGame);
        Assert.AreNotEqual(itemEntry.GetHashCode(), itemEntryDifferentGame.GetHashCode());
     }

    [Test]
    public void MoveEntryTest() {
        // Make sure trying to create an invalid entry results in an error.
        Assert.Throws<ArgumentOutOfRangeException>(
            delegate {
                new PKMN.Database.MoveEntry("Not an item", "Silver");
            }
        );
        Assert.Throws<ArgumentOutOfRangeException>(
            delegate {
                new PKMN.Database.MoveEntry("Octazooka", "Not a game");
            }
        );
        Assert.Throws<ArgumentOutOfRangeException>(
            delegate {
                new PKMN.Database.MoveEntry("Octazooka", "Red");
            }
        );

        PKMN.Database.MoveEntry moveEntry = new PKMN.Database.MoveEntry("Octazooka", "Silver");

        Assert.AreEqual(moveEntry.Name, "Octazooka");
        Assert.AreEqual(moveEntry.Game, "Silver");
        Assert.AreEqual(moveEntry.MoveType, "Water");

        // Just make sure it works
        string description = moveEntry.Description;

        Assert.AreEqual(moveEntry.Target, "Selected Pokémon");
        Assert.AreEqual(moveEntry.DamageClass, "Special");
        Assert.AreEqual(moveEntry.BasePower, 65);

        int[] PPs = {10, 12, 14, 16};
        for(int i = 0; i < 4; ++i) {
            Assert.AreEqual(moveEntry.GetPP(i), PPs[i]);
        }

        Assert.That(moveEntry.Accuracy, Is.EqualTo(0.85f).Within(0.0001));
        Assert.AreEqual(moveEntry.Priority, 0);

        // Just make sure it works
        string effect = moveEntry.Effect;

        Assert.AreEqual(moveEntry.ContestType, "None");
        Assert.AreEqual(moveEntry.ContestEffect, "None");
        Assert.AreEqual(moveEntry.SuperContestEffect, "None");

        PKMN.Database.MoveEntry moveEntrySame = new PKMN.Database.MoveEntry("Octazooka", "Silver");
        PKMN.Database.MoveEntry moveEntryDifferentMove = new PKMN.Database.MoveEntry("Hydro Pump", "Silver");
        PKMN.Database.MoveEntry moveEntryDifferentGame = new PKMN.Database.MoveEntry("Octazooka", "Gold");

        Assert.AreEqual(moveEntry, moveEntry);
        Assert.AreEqual(moveEntry, moveEntrySame);
        Assert.AreEqual(moveEntry.GetHashCode(), moveEntrySame.GetHashCode());

        Assert.AreNotEqual(moveEntry, moveEntryDifferentMove);
        Assert.AreNotEqual(moveEntry.GetHashCode(), moveEntryDifferentMove.GetHashCode());

        Assert.AreNotEqual(moveEntry, moveEntryDifferentGame);
        Assert.AreNotEqual(moveEntry.GetHashCode(), moveEntryDifferentGame.GetHashCode());
    }

    [Test]
    public void PokemonEntryTest() {
        // Make sure trying to create an invalid entry results in an error.
        Assert.Throws<ArgumentOutOfRangeException>(
            delegate {
                new PKMN.Database.PokemonEntry("Invalid", "Black 2", "Sunny");
            }
        );
        Assert.Throws<ArgumentOutOfRangeException>(
            delegate {
                new PKMN.Database.PokemonEntry("Castform", "Not a game", "Sunny");
            }
        );
        Assert.Throws<ArgumentOutOfRangeException>(
            delegate {
                new PKMN.Database.PokemonEntry("Castform", "Black 2", "Not a form");
            }
        );

        PKMN.Database.PokemonEntry pokemonEntry = new PKMN.Database.PokemonEntry("Stunfisk", "Black 2", "");

        Assert.AreEqual(pokemonEntry.Name, "Stunfisk");
        Assert.AreEqual(pokemonEntry.Game, "Black 2");
        Assert.AreEqual(pokemonEntry.Species, "Trap");
        Assert.AreEqual(pokemonEntry.Form, "Standard");

        // Just make sure this works
        string pokedexEntry = pokemonEntry.PokedexEntry;

        Assert.That(pokemonEntry.Height, Is.EqualTo(0.7).Within(0.0001));
        Assert.That(pokemonEntry.Weight, Is.EqualTo(11.0).Within(0.0001));
        Assert.That(pokemonEntry.ChanceMale, Is.EqualTo(0.5).Within(0.0001));
        Assert.That(pokemonEntry.ChanceFemale, Is.EqualTo(0.5).Within(0.0001));
        Assert.IsFalse(pokemonEntry.HasGenderDifferences);
        Assert.AreEqual(pokemonEntry.BaseFriendship, 70);
        Assert.AreEqual(pokemonEntry.Types, (new PKMN.StringPair("Ground", "Electric")));
        Assert.AreEqual(pokemonEntry.Abilities, (new PKMN.StringPair("Static", "Limber")));
        Assert.AreEqual(pokemonEntry.HiddenAbility, "Sand Veil");
        Assert.AreEqual(pokemonEntry.EggGroups, (new PKMN.StringPair("Water 1", "Amorphous")));

        PKMN.StringIntDict baseStats = pokemonEntry.BaseStats;
        Assert.AreEqual(baseStats["HP"], 109);
        Assert.AreEqual(baseStats["Attack"], 66);
        Assert.AreEqual(baseStats["Defense"], 84);
        Assert.AreEqual(baseStats["Speed"], 32);
        Assert.AreEqual(baseStats["Special Attack"], 81);
        Assert.AreEqual(baseStats["Special Defense"], 99);

        PKMN.StringIntDict evYields = pokemonEntry.EVYields;
        Assert.AreEqual(evYields["HP"], 2);
        Assert.AreEqual(evYields["Attack"], 0);
        Assert.AreEqual(evYields["Defense"], 0);
        Assert.AreEqual(evYields["Speed"], 0);
        Assert.AreEqual(evYields["Special Attack"], 0);
        Assert.AreEqual(evYields["Special Defense"], 0);

        Assert.AreEqual(pokemonEntry.ExperienceYield, 165);
        Assert.AreEqual(pokemonEntry.GetExperienceAtLevel(50), 125000);
        Assert.AreEqual(pokemonEntry.GetLevelAtExperience(200000), 58);
        Assert.Greater(pokemonEntry.LevelupMoves.Count, 0);
        Assert.Greater(pokemonEntry.TMHMMoves.Count, 0);
        Assert.Greater(pokemonEntry.EggMoves.Count, 0);
        Assert.Greater(pokemonEntry.TutorMoves.Count, 0);
        Assert.AreEqual(pokemonEntry.Forms.Count, 1);
        Assert.AreEqual(pokemonEntry.Evolutions.Count, 0);

        PKMN.Database.PokemonEntry pokemonEntryFirst = new PKMN.Database.PokemonEntry("Pikachu", "Omega Ruby", "Standard");
        PKMN.Database.PokemonEntry pokemonEntrySame = new PKMN.Database.PokemonEntry("Pikachu", "Omega Ruby", "Standard");
        PKMN.Database.PokemonEntry pokemonEntryDifferentPokemon = new PKMN.Database.PokemonEntry("Pichu", "Omega Ruby", "Standard");
        PKMN.Database.PokemonEntry pokemonEntryDifferentGame = new PKMN.Database.PokemonEntry("Pikachu", "Alpha Sapphire", "Standard");
        PKMN.Database.PokemonEntry pokemonEntryDifferentForm = new PKMN.Database.PokemonEntry("Pikachu", "Omega Ruby", "Belle");

        Assert.AreEqual(pokemonEntryFirst, pokemonEntryFirst);
        Assert.AreEqual(pokemonEntryFirst, pokemonEntrySame);
        Assert.AreEqual(pokemonEntryFirst.GetHashCode(), pokemonEntrySame.GetHashCode());

        Assert.AreNotEqual(pokemonEntryFirst, pokemonEntryDifferentPokemon);
        Assert.AreNotEqual(pokemonEntryFirst.GetHashCode(), pokemonEntryDifferentPokemon.GetHashCode());

        Assert.AreNotEqual(pokemonEntryFirst, pokemonEntryDifferentGame);
        Assert.AreNotEqual(pokemonEntryFirst.GetHashCode(), pokemonEntryDifferentGame.GetHashCode());

        Assert.AreNotEqual(pokemonEntryFirst, pokemonEntryDifferentForm);
        Assert.AreNotEqual(pokemonEntryFirst.GetHashCode(), pokemonEntryDifferentForm.GetHashCode());
    }
}