/*
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

using System;
using NUnit.Framework;

[TestFixture]
public class CSharpGameSaveTest {
    /*
     * Red
     */
    [Test]
    public void RedGameSaveTest() {
        PKMNTest.GameSaveTest.TestGameSave(
            "Red/Blue/Yellow",
            "Red",
            "red_blue/pokemon_red.sav"
        );
    }

    /*
     * Yellow
     */
    [Test]
    public void YellowGameSaveTest() {
        PKMNTest.GameSaveTest.TestGameSave(
            "Red/Blue/Yellow",
            "Yellow",
            "yellow/pokemon_yellow.sav"
        );
    }

    /*
     * Gold
     */
    [Test]
    public void GoldGameSaveTest() {
        PKMNTest.GameSaveTest.TestGameSave(
            "Gold/Silver",
            "Gold",
            "gold_silver/pokemon_gold.sav"
        );
    }

    /*
     * Crystal
     */
    [Test]
    public void CrystalGameSaveTest() {
        PKMNTest.GameSaveTest.TestGameSave(
            "Crystal",
            "Crystal",
            "crystal/pokemon_crystal.sav"
        );
    }

    /*
     * Ruby
     */
    [Test]
    public void RubyGameSaveTest() {
        PKMNTest.GameSaveTest.TestGameSave(
            "Ruby/Sapphire",
            "Ruby",
            "ruby_sapphire/pokemon_ruby.sav"
        );
    }

    /*
     * Emerald
     */
    [Test]
    public void EmeraldGameSaveTest() {
        PKMNTest.GameSaveTest.TestGameSave(
            "Emerald",
            "Emerald",
            "emerald/pokemon_emerald.sav"
        );
    }

    /*
     * FireRed
     */
    [Test]
    public void FireRedGameSaveTest() {
        PKMNTest.GameSaveTest.TestGameSave(
            "FireRed/LeafGreen",
            "FireRed",
            "firered_leafgreen/pokemon_firered.sav"
        );
    }

    /*
     * Colosseum
     */
    [Test]
    public void ColosseumGameSaveTest() {
        PKMNTest.GameSaveTest.TestGameSave(
            "Colosseum/XD",
            "Colosseum",
            "gamecube_saves/pokemon_colosseum.gci"
        );
    }

    /*
     * XD
     */
    [Test]
    public void XDGameSaveTest() {
        PKMNTest.GameSaveTest.TestGameSave(
            "Colosseum/XD",
            "XD",
            "gamecube_saves/pokemon_xd.gci"
        );
    }
}