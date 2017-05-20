--
-- Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
--
-- Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
-- or copy at http://opensource.org/licenses/MIT)
--

local pkmn = require("pkmn")
local luaunit = require("luaunit")
local items_tests = require("items_tests")

local gcn_items_tests = {}

gcn_items_tests.colosseum_all_pocket_items =
{
    "Potion", "Ein File S", "Great Ball", "TM01",
    "TM02", "Aspear Berry", "Joy Scent", "Excite Scent"
}
gcn_items_tests.xd_all_pocket_items =
{
    "Potion", "Gonzap's Key", "Great Ball", "TM01",
    "TM02", "Aspear Berry", "Joy Scent", "Battle CD 01"
}
gcn_items_tests.colosseum_wrong_game_all_pocket_items =
{
    "Pink Bow", "Black Sludge",
    "GS Ball", "Gonzap's Key", "Poffin Items",
    "TM51", "HM01",
    "Berry", "Occa Berry"
}
gcn_items_tests.xd_wrong_game_all_pocket_items =
{
    "Pink Bow", "Black Sludge",
    "GS Ball", "Ein File S", "Poffin Items",
    "TM51", "HM01",
    "Berry", "Occa Berry"
}

function gcn_items_tests.test_item_pocket(item_pocket, game)
    local expected_capacity = 0
    if game == "Colosseum"
    then
        expected_capacity = 20
    else
        expected_capacity = 30
    end

    -- Check unchanging and initial values.
    luaunit.assertEquals(#item_pocket, expected_capacity)
    luaunit.assertEquals(item_pocket:get_name(), "Items")
    luaunit.assertEquals(item_pocket:get_game(), game)
    luaunit.assertEquals(item_pocket:get_capacity(), expected_capacity)
    luaunit.assertEquals(item_pocket:get_num_items(), 0)

    -- Make sure item slots start as correctly empty.
    items_tests.item_list_test_empty_slot(item_pocket)

    -- Confirm errors are thrown when expected.
    items_tests.item_list_test_out_of_range_error(item_pocket, "Potion")

    -- Make sure we can't add items from other pockets.
    local wrong_pocket_items = {}
    if game == "Colosseum"
    then
        wrong_pocket_items = {"Ein File S", "Great Ball", "TM01", "Oran Berry", "Joy Scent"}
    else
        wrong_pocket_items = {"Miror Radar", "Great Ball", "TM01", "Oran Berry", "Joy Scent", "Battle CD 01"}
    end
    items_tests.item_list_test_invalid_items(
        item_pocket, wrong_pocket_items
    )

    -- Make sure we can't add items from other generations.
    items_tests.item_list_test_invalid_items(
        item_pocket,
        {"Pink Bow", "Black Sludge", "Binding Band", "Beedrillite"}
    )

    -- Start adding and removing stuff, and make sure the numbers are accurate.
    items_tests.item_list_test_add_remove(
        item_pocket,
        {"Potion", "Orange Mail", "Lava Cookie", "Stardust",
         "Shadow Mail", "Pink Scarf", "Antidote", "Green Shard"}
    )

    local valid_items = item_pocket:get_valid_items()
    luaunit.assertTrue(#valid_items > 0)
end

function gcn_items_tests.test_key_item_pocket(key_item_pocket, game)
    local expected_capacity = 43
    local item_name = ""
    if game == "Colosseum"
    then
        item_name = "Ein File S"
    else
        item_name = "Miror Radar"
    end

    -- Check unchanging and initial values.
    luaunit.assertEquals(#key_item_pocket, expected_capacity)
    luaunit.assertEquals(key_item_pocket:get_name(), "Key Items")
    luaunit.assertEquals(key_item_pocket:get_game(), game)
    luaunit.assertEquals(key_item_pocket:get_capacity(), expected_capacity)
    luaunit.assertEquals(key_item_pocket:get_num_items(), 0)

    -- Make sure item slots start as correctly empty.
    items_tests.item_list_test_empty_slot(key_item_pocket)

    -- Confirm errors are thrown when expected.
    items_tests.item_list_test_out_of_range_error(key_item_pocket, item_name)

    -- Make sure we can't add items from other pockets.
    local wrong_pocket_items = {}
    if game == "Colosseum"
    then
        wrong_pocket_items = {"Potion", "Great Ball", "TM01", "Oran Berry", "Joy Scent"}
    else
        wrong_pocket_items = {"Potion", "Great Ball", "TM01", "Oran Berry", "Joy Scent", "Battle CD 01"}
    end
    items_tests.item_list_test_invalid_items(
        key_item_pocket, wrong_pocket_items
    )

    -- Make sure we can't add items from other generations.
    items_tests.item_list_test_invalid_items(
        key_item_pocket,
        {"GS Ball", "Poffin Items", "DNA Splicers", "Aqua Suit"}
    )

    -- Start adding and removing stuff, and make sure the numbers are accurate.
    local items = {}
    if game == "Colosseum"
    then
        items = {"Jail Key", "Elevator Key", "Small Tablet", "F-Disk",
                 "R-Disk", "L-Disk", "D-Disk", "U-Disk"}
    else
        items = {"Krane Memo 1", "Krane Memo 2", "Krane Memo 3", "Krane Memo 4",
                 "Krane Memo 5", "Voice Case 1", "Voice Case 2", "Voice Case 3"}
    end
    items_tests.item_list_test_add_remove(
        key_item_pocket, items
    )

    local valid_items = key_item_pocket:get_valid_items()
    luaunit.assertTrue(#valid_items > 0)
end

function gcn_items_tests.test_ball_pocket(ball_pocket, game)
    local expected_capacity = 16

    -- Check unchanging and initial values.
    luaunit.assertEquals(#ball_pocket, expected_capacity)
    luaunit.assertEquals(ball_pocket:get_name(), "Poké Balls")
    luaunit.assertEquals(ball_pocket:get_game(), game)
    luaunit.assertEquals(ball_pocket:get_capacity(), expected_capacity)
    luaunit.assertEquals(ball_pocket:get_num_items(), 0)

    -- Make sure item slots start as correctly empty.
    items_tests.item_list_test_empty_slot(ball_pocket)

    -- Confirm errors are thrown when expected.
    items_tests.item_list_test_out_of_range_error(ball_pocket, "Great Ball")

    -- Make sure we can't add items from other pockets.
    local wrong_pocket_items = {}
    if game == "Colosseum"
    then
        wrong_pocket_items = {"Ein File S", "Potion", "TM01", "Oran Berry", "Joy Scent"}
    else
        wrong_pocket_items = {"Miror Radar", "Potion", "TM01", "Oran Berry", "Joy Scent", "Battle CD 01"}
    end
    items_tests.item_list_test_invalid_items(
        ball_pocket, wrong_pocket_items
    )

    -- Make sure we can't add items from other generations.
    items_tests.item_list_test_invalid_items(
        ball_pocket,
        {"Moon Ball", "Heal Ball", "Dream Ball"}
    )

    -- Start adding and removing stuff, and make sure the numbers are accurate.
    items_tests.item_list_test_add_remove(
        ball_pocket,
        {"Master Ball", "Ultra Ball", "Great Ball", "Poké Ball",
         "Safari Ball", "Net Ball", "Dive Ball", "Nest Ball"}
    )

    local valid_items = ball_pocket:get_valid_items()
    luaunit.assertTrue(#valid_items > 0)
end

function gcn_items_tests.test_tm_pocket(tm_pocket, game)
    local expected_capacity = 64

    -- Check unchanging and initial values.
    luaunit.assertEquals(#tm_pocket, expected_capacity)
    luaunit.assertEquals(tm_pocket:get_name(), "TMs")
    luaunit.assertEquals(tm_pocket:get_game(), game)
    luaunit.assertEquals(tm_pocket:get_capacity(), expected_capacity)
    luaunit.assertEquals(tm_pocket:get_num_items(), 0)

    -- Make sure item slots start as correctly empty.
    items_tests.item_list_test_empty_slot(tm_pocket)

    -- Confirm errors are thrown when expected.
    items_tests.item_list_test_out_of_range_error(tm_pocket, "TM01")

    -- Make sure we can't add items from other pockets.
    local wrong_pocket_items = {}
    if game == "Colosseum"
    then
        wrong_pocket_items = {"Ein File S", "Potion", "Great Ball", "Oran Berry", "Joy Scent"}
    else
        wrong_pocket_items = {"Miror Radar", "Potion", "Great Ball", "Oran Berry", "Joy Scent", "Battle CD 01"}
    end
    items_tests.item_list_test_invalid_items(
        tm_pocket, wrong_pocket_items
    )

    -- Make sure we can't add items from other generations.
    items_tests.item_list_test_invalid_items(
        tm_pocket,
        {"TM51", "HM01"}
    )

    -- Start adding and removing stuff, and make sure the numbers are accurate.
    items_tests.item_list_test_add_remove(
        tm_pocket,
        {"TM01", "TM02", "TM03", "TM04",
         "TM05", "TM06", "TM07", "TM08"}
    )

    local valid_items = tm_pocket:get_valid_items()
    luaunit.assertTrue(#valid_items > 0)
end

function gcn_items_tests.test_berry_pocket(berry_pocket, game)
    local expected_capacity = 46

    -- Check unchanging and initial values.
    luaunit.assertEquals(#berry_pocket, expected_capacity)
    luaunit.assertEquals(berry_pocket:get_name(), "Berries")
    luaunit.assertEquals(berry_pocket:get_game(), game)
    luaunit.assertEquals(berry_pocket:get_capacity(), expected_capacity)
    luaunit.assertEquals(berry_pocket:get_num_items(), 0)

    -- Make sure item slots start as correctly empty.
    items_tests.item_list_test_empty_slot(berry_pocket)

    -- Confirm errors are thrown when expected.
    items_tests.item_list_test_out_of_range_error(berry_pocket, "Oran Berry")

    -- Make sure we can't add items from other pockets.
    local wrong_pocket_items = {}
    if game == "Colosseum"
    then
        wrong_pocket_items = {"Ein File S", "Potion", "Great Ball", "TM01", "Joy Scent"}
    else
        wrong_pocket_items = {"Miror Radar", "Potion", "Great Ball", "TM01", "Joy Scent", "Battle CD 01"}
    end
    items_tests.item_list_test_invalid_items(
        berry_pocket, wrong_pocket_items
    )

    -- Make sure we can't add items from other generations.
    items_tests.item_list_test_invalid_items(
        berry_pocket,
        {"Berry", "Occa Berry", "Roseli Berry"}
    )

    -- Start adding and removing stuff, and make sure the numbers are accurate.
    items_tests.item_list_test_add_remove(
        berry_pocket,
        {"Cheri Berry", "Razz Berry", "Lum Berry", "Pinap Berry",
         "Aspear Berry", "Iapapa Berry", "Wiki Berry", "Apicot Berry"}
    )

    local valid_items = berry_pocket:get_valid_items()
    luaunit.assertTrue(#valid_items > 0)
end

function gcn_items_tests.test_cologne_pocket(cologne_pocket, game)
    local expected_capacity = 3

    -- Check unchanging and initial values.
    luaunit.assertEquals(#cologne_pocket, expected_capacity)
    luaunit.assertEquals(cologne_pocket:get_name(), "Colognes")
    luaunit.assertEquals(cologne_pocket:get_game(), game)
    luaunit.assertEquals(cologne_pocket:get_capacity(), expected_capacity)
    luaunit.assertEquals(cologne_pocket:get_num_items(), 0)

    -- Make sure item slots start as correctly empty.
    items_tests.item_list_test_empty_slot(cologne_pocket)

    -- Confirm errors are thrown when expected.
    items_tests.item_list_test_out_of_range_error(cologne_pocket, "Joy Scent")

    -- Make sure we can't add items from other pockets.
    local wrong_pocket_items = {}
    if game == "Colosseum"
    then
        wrong_pocket_items = {"Ein File S", "Potion", "Great Ball", "TM01", "Oran Berry"}
    else
        wrong_pocket_items = {"Miror Radar", "Potion", "Great Ball", "TM01", "Oran Berry", "Battle CD 01"}
    end
    items_tests.item_list_test_invalid_items(
        cologne_pocket, wrong_pocket_items
    )

    -- Since this pocket can only have 3 items, we can't use our typical function, which requires 8.
    cologne_pocket:add("Joy Scent", 3)
    cologne_pocket:add("Excite Scent", 3)
    cologne_pocket:add("Vivid Scent", 3)
    cologne_pocket:remove("Excite Scent", 3)
    cologne_pocket:remove("Vivid Scent", 1)

    luaunit.assertEquals(cologne_pocket[1].item:get_name(), "Joy Scent")
    luaunit.assertEquals(cologne_pocket[1].amount, 3)
    luaunit.assertEquals(cologne_pocket[2].item:get_name(), "Vivid Scent")
    luaunit.assertEquals(cologne_pocket[2].amount, 2)
    luaunit.assertEquals(cologne_pocket[3].item:get_name(), "None")
    luaunit.assertEquals(cologne_pocket[3].amount, 0)

    cologne_pocket:remove("Joy Scent", 3)
    cologne_pocket:remove("Vivid Scent", 2)
    luaunit.assertEquals(cologne_pocket[1].item:get_name(), "None")
    luaunit.assertEquals(cologne_pocket[1].amount, 0)
    luaunit.assertEquals(cologne_pocket[2].item:get_name(), "None")
    luaunit.assertEquals(cologne_pocket[2].amount, 0)
    luaunit.assertEquals(cologne_pocket[3].item:get_name(), "None")
    luaunit.assertEquals(cologne_pocket[3].amount, 0)

    local valid_items = cologne_pocket:get_valid_items()
    luaunit.assertTrue(#valid_items > 0)
end

function gcn_items_tests.test_battle_cd_pocket(battle_cd_pocket, game)
    local expected_capacity = 60

    -- Check unchanging and initial values.
    luaunit.assertEquals(#battle_cd_pocket, expected_capacity)
    luaunit.assertEquals(battle_cd_pocket:get_name(), "Battle CDs")
    luaunit.assertEquals(battle_cd_pocket:get_game(), game)
    luaunit.assertEquals(battle_cd_pocket:get_capacity(), expected_capacity)
    luaunit.assertEquals(battle_cd_pocket:get_num_items(), 0)

    -- Make sure item slots start as correctly empty.
    items_tests.item_list_test_empty_slot(battle_cd_pocket)

    -- Confirm errors are thrown when expected.
    items_tests.item_list_test_out_of_range_error(battle_cd_pocket, "TM01")

    -- Make sure we can't add items from other pockets.
    items_tests.item_list_test_invalid_items(
        battle_cd_pocket,
        {"Miror Radar", "Potion", "Great Ball", "Oran Berry", "Joy Scent"}
    )

    -- Start adding and removing stuff, and make sure the numbers are accurate.
    items_tests.item_list_test_add_remove(
        battle_cd_pocket,
        {"Battle CD 01", "Battle CD 02", "Battle CD 03", "Battle CD 04",
         "Battle CD 05", "Battle CD 06", "Battle CD 07", "Battle CD 08"}
    )

    local valid_items = battle_cd_pocket:get_valid_items()
    luaunit.assertEquals(#valid_items, 60)
end

function gcn_items_tests.test_pc(pc, game)
    -- Check unchanging and initial values.
    luaunit.assertEquals(#pc, 235)
    luaunit.assertEquals(pc:get_name(), "PC")
    luaunit.assertEquals(pc:get_game(), game)
    luaunit.assertEquals(pc:get_capacity(), 235)
    luaunit.assertEquals(pc:get_num_items(), 0)

    -- Make sure item slots start as correctly empty.
    items_tests.item_list_test_empty_slot(pc)

    -- Confirm errors are thrown when expected.
    items_tests.item_list_test_out_of_range_error(pc, "Potion")

    -- Make sure we can't add items from other generations.
    local wrong_game_all_pocket_items = {}
    if game == "Colosseum"
    then
        wrong_game_all_pocket_items = gcn_items_tests.colosseum_wrong_game_all_pocket_items
    else
        wrong_game_all_pocket_items = gcn_items_tests.xd_wrong_game_all_pocket_items
    end
    items_tests.item_list_test_invalid_items(
        pc,
        wrong_game_all_pocket_items
    )

    -- Start adding and removing stuff, and make sure the numbers are accurate.
    local all_pocket_items = {}
    if game == "Colosseum"
    then
        all_pocket_items = gcn_items_tests.colosseum_all_pocket_items
    else
        all_pocket_items = gcn_items_tests.xd_all_pocket_items
    end
    items_tests.item_list_test_add_remove(
        pc,
        all_pocket_items
    )

    local valid_items = pc:get_valid_items()
    luaunit.assertTrue(#valid_items > 0)
end

function gcn_items_tests.test_bag(bag, game)
    local num_pockets = ""
    if game == "Colosseum"
    then
        num_pockets = 6
    else
        num_pockets = 7
    end
    
    -- Check unchanging and initial values.
    luaunit.assertEquals(bag:get_game(), game)

    local pockets = bag:get_pockets()
    luaunit.assertEquals(#pockets, num_pockets)
    luaunit.assertTrue(pockets:has_key("Items"))
    luaunit.assertTrue(pockets:has_key("Key Items"))
    luaunit.assertTrue(pockets:has_key("Poké Balls"))
    luaunit.assertTrue(pockets:has_key("TMs"))
    luaunit.assertTrue(pockets:has_key("Berries"))
    luaunit.assertTrue(pockets:has_key("Colognes"))
    if game == "XD"
    then
        luaunit.assertTrue(pockets:has_key("Battle CDs"))
    end

    gcn_items_tests.test_item_pocket(bag["Items"], game)
    gcn_items_tests.test_key_item_pocket(bag["Key Items"], game)
    gcn_items_tests.test_ball_pocket(bag["Poké Balls"], game)
    gcn_items_tests.test_tm_pocket(bag["TMs"], game)
    gcn_items_tests.test_berry_pocket(bag["Berries"], game)
    gcn_items_tests.test_cologne_pocket(bag["Colognes"], game)
    if game == "XD"
    then
        gcn_items_tests.test_battle_cd_pocket(bag["Battle CDs"], game)
    end

    -- Make sure adding items through the bag adds to the proper pocket.
    luaunit.assertEquals(bag["Items"]:get_num_items(), 0)
    luaunit.assertEquals(bag["Key Items"]:get_num_items(), 0)
    luaunit.assertEquals(bag["Poké Balls"]:get_num_items(), 0)
    luaunit.assertEquals(bag["TMs"]:get_num_items(), 0)
    luaunit.assertEquals(bag["Berries"]:get_num_items(), 0)
    luaunit.assertEquals(bag["Colognes"]:get_num_items(), 0)
    if game == "XD"
    then
        luaunit.assertEquals(bag["Battle CDs"]:get_num_items(), 0)
    end

    local all_pocket_items = {}
    local wrong_game_all_pocket_items = {}
    local key_item = ""
    if game == "Colosseum"
    then
        all_pocket_items = gcn_items_tests.colosseum_all_pocket_items
        wrong_game_all_pocket_items = gcn_items_tests.colosseum_wrong_game_all_pocket_items
        key_item = "Ein File S"
    else
        all_pocket_items = gcn_items_tests.xd_all_pocket_items
        wrong_game_all_pocket_items = gcn_items_tests.xd_wrong_game_all_pocket_items
        key_item = "Gonzap's Key"
    end

    -- Make sure we can't add items from other generations.
    items_tests.item_bag_test_invalid_items(
        bag,
        wrong_game_all_pocket_items
    )

    for i = 1, #all_pocket_items
    do
        bag:add(all_pocket_items[i], 5)
    end

    luaunit.assertEquals(bag["Items"][1].item:get_name(), "Potion")
    luaunit.assertEquals(bag["Items"][1].amount, 5)
    luaunit.assertEquals(bag["Items"][2].item:get_name(), "None")
    luaunit.assertEquals(bag["Items"][2].amount, 0)

    luaunit.assertEquals(bag["Key Items"][1].item:get_name(), key_item)
    luaunit.assertEquals(bag["Key Items"][1].amount, 5)
    luaunit.assertEquals(bag["Key Items"][2].item:get_name(), "None")
    luaunit.assertEquals(bag["Key Items"][2].amount, 0)

    luaunit.assertEquals(bag["Poké Balls"][1].item:get_name(), "Great Ball")
    luaunit.assertEquals(bag["Poké Balls"][1].amount, 5)
    luaunit.assertEquals(bag["Poké Balls"][2].item:get_name(), "None")
    luaunit.assertEquals(bag["Poké Balls"][2].amount, 0)

    luaunit.assertEquals(bag["TMs"][1].item:get_name(), "TM01")
    luaunit.assertEquals(bag["TMs"][1].amount, 5)
    luaunit.assertEquals(bag["TMs"][2].item:get_name(), "TM02")
    luaunit.assertEquals(bag["TMs"][2].amount, 5)
    luaunit.assertEquals(bag["TMs"][3].item:get_name(), "None")
    luaunit.assertEquals(bag["TMs"][3].amount, 0)

    luaunit.assertEquals(bag["Berries"][1].item:get_name(), "Aspear Berry")
    luaunit.assertEquals(bag["Berries"][1].amount, 5)
    luaunit.assertEquals(bag["Berries"][2].item:get_name(), "None")
    luaunit.assertEquals(bag["Berries"][2].amount, 0)

    luaunit.assertEquals(bag["Colognes"][1].item:get_name(), "Joy Scent")
    luaunit.assertEquals(bag["Colognes"][1].amount, 5)
    if game == "Colosseum"
    then
        luaunit.assertEquals(bag["Colognes"][2].item:get_name(), "Excite Scent")
        luaunit.assertEquals(bag["Colognes"][2].amount, 5)
        luaunit.assertEquals(bag["Colognes"][3].item:get_name(), "None")
        luaunit.assertEquals(bag["Colognes"][3].amount, 0)
    else
        luaunit.assertEquals(bag["Colognes"][2].item:get_name(), "None")
        luaunit.assertEquals(bag["Colognes"][2].amount, 0)

        luaunit.assertEquals(bag["Battle CDs"][1].item:get_name(), "Battle CD 01")
        luaunit.assertEquals(bag["Battle CDs"][1].amount, 5)
        luaunit.assertEquals(bag["Battle CDs"][2].item:get_name(), "None")
        luaunit.assertEquals(bag["Battle CDs"][2].amount, 0)
    end

    -- Make sure removing items through the bag removes from the proper pocket.
    for i = 1, #all_pocket_items
    do
        bag:remove(all_pocket_items[i], 5)
    end

    luaunit.assertEquals(bag["Items"][1].item:get_name(), "None")
    luaunit.assertEquals(bag["Items"][1].amount, 0)
    luaunit.assertEquals(bag["Items"][2].item:get_name(), "None")
    luaunit.assertEquals(bag["Items"][2].amount, 0)

    luaunit.assertEquals(bag["Key Items"][1].item:get_name(), "None")
    luaunit.assertEquals(bag["Key Items"][1].amount, 0)
    luaunit.assertEquals(bag["Key Items"][2].item:get_name(), "None")
    luaunit.assertEquals(bag["Key Items"][2].amount, 0)

    luaunit.assertEquals(bag["Poké Balls"][1].item:get_name(), "None")
    luaunit.assertEquals(bag["Poké Balls"][1].amount, 0)
    luaunit.assertEquals(bag["Poké Balls"][2].item:get_name(), "None")
    luaunit.assertEquals(bag["Poké Balls"][2].amount, 0)

    luaunit.assertEquals(bag["TMs"][1].item:get_name(), "None")
    luaunit.assertEquals(bag["TMs"][1].amount, 0)
    luaunit.assertEquals(bag["TMs"][2].item:get_name(), "None")
    luaunit.assertEquals(bag["TMs"][2].amount, 0)
    luaunit.assertEquals(bag["TMs"][3].item:get_name(), "None")
    luaunit.assertEquals(bag["TMs"][3].amount, 0)

    luaunit.assertEquals(bag["Berries"][1].item:get_name(), "None")
    luaunit.assertEquals(bag["Berries"][1].amount, 0)
    luaunit.assertEquals(bag["Berries"][2].item:get_name(), "None")
    luaunit.assertEquals(bag["Berries"][2].amount, 0)

    luaunit.assertEquals(bag["Colognes"][1].item:get_name(), "None")
    luaunit.assertEquals(bag["Colognes"][1].amount, 0)
    luaunit.assertEquals(bag["Colognes"][2].item:get_name(), "None")
    luaunit.assertEquals(bag["Colognes"][2].amount, 0)
    luaunit.assertEquals(bag["Colognes"][3].item:get_name(), "None")
    luaunit.assertEquals(bag["Colognes"][3].amount, 0)
    if game == "XD"
    then
        luaunit.assertEquals(bag["Colognes"][2].item:get_name(), "None")
        luaunit.assertEquals(bag["Colognes"][2].amount, 0)

        luaunit.assertEquals(bag["Battle CDs"][1].item:get_name(), "None")
        luaunit.assertEquals(bag["Battle CDs"][1].amount, 0)
        luaunit.assertEquals(bag["Battle CDs"][2].item:get_name(), "None")
        luaunit.assertEquals(bag["Battle CDs"][2].amount, 0)
    end
end

--
-- Colosseum
--

function test_colosseum_item_pocket()
    local item_pocket = pkmn.item_list("Items", "Colosseum")
    gcn_items_tests.test_item_pocket(item_pocket, "Colosseum")
end

function test_colosseum_key_item_pocket()
    local key_item_pocket = pkmn.item_list("Key Items", "Colosseum")
    gcn_items_tests.test_key_item_pocket(key_item_pocket, "Colosseum")
end

function test_colosseum_ball_pocket()
    local ball_pocket = pkmn.item_list("Poké Balls", "Colosseum")
    gcn_items_tests.test_ball_pocket(ball_pocket, "Colosseum")
end

function test_colosseum_tm_pocket()
    local tm_pocket = pkmn.item_list("TMs", "Colosseum")
    gcn_items_tests.test_tm_pocket(tm_pocket, "Colosseum")
end

function test_colosseum_berry_pocket()
    local berry_pocket = pkmn.item_list("Berries", "Colosseum")
    gcn_items_tests.test_berry_pocket(berry_pocket, "Colosseum")
end

function test_colosseum_cologne_pocket()
    local cologne_pocket = pkmn.item_list("Colognes", "Colosseum")
    gcn_items_tests.test_cologne_pocket(cologne_pocket, "Colosseum")
end

function test_colosseum_pc()
    local pc = pkmn.item_list("PC", "Colosseum")
    gcn_items_tests.test_pc(pc, "Colosseum")
end

function test_colosseum_bag()
    local bag = pkmn.item_bag("Colosseum")
    gcn_items_tests.test_bag(bag, "Colosseum")
end

--
-- XD
--

function test_xd_item_pocket()
    local item_pocket = pkmn.item_list("Items", "XD")
    gcn_items_tests.test_item_pocket(item_pocket, "XD")
end

function test_xd_key_item_pocket()
    local key_item_pocket = pkmn.item_list("Key Items", "XD")
    gcn_items_tests.test_key_item_pocket(key_item_pocket, "XD")
end

function test_xd_ball_pocket()
    local ball_pocket = pkmn.item_list("Poké Balls", "XD")
    gcn_items_tests.test_ball_pocket(ball_pocket, "XD")
end

function test_xd_tm_pocket()
    local tm_pocket = pkmn.item_list("TMs", "XD")
    gcn_items_tests.test_tm_pocket(tm_pocket, "XD")
end

function test_xd_berry_pocket()
    local berry_pocket = pkmn.item_list("Berries", "XD")
    gcn_items_tests.test_berry_pocket(berry_pocket, "XD")
end

function test_xd_cologne_pocket()
    local cologne_pocket = pkmn.item_list("Colognes", "XD")
    gcn_items_tests.test_cologne_pocket(cologne_pocket, "XD")
end

function test_xd_battle_cd_pocket()
    local battle_cd_pocket = pkmn.item_list("Battle CDs", "XD")
    gcn_items_tests.test_battle_cd_pocket(battle_cd_pocket, "XD")
end

function test_xd_pc()
    local pc = pkmn.item_list("PC", "XD")
    gcn_items_tests.test_pc(pc, "XD")
end

function test_xd_bag()
    local bag = pkmn.item_bag("XD")
    gcn_items_tests.test_bag(bag, "XD")
end