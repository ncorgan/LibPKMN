/*
 * Copyright (c) 2017-2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "item_test_common.hpp"

#include <pkmntest/util.hpp>

#include <pkmn/exception.hpp>
#include <pkmn/database/item_entry.hpp>
#include "pksav/pksav_call.hpp"

#include "libpkmgc_includes.hpp"

#include <boost/assign.hpp>
#include <boost/algorithm/string.hpp>

static const std::vector<std::string> colosseum_all_pocket_items = boost::assign::list_of
    ("Potion")("Ein File S")("Great Ball")("TM01")
    ("TM02")("Aspear Berry")("Joy Scent")("Excite Scent")
;

static const std::vector<std::string> xd_all_pocket_items = boost::assign::list_of
    ("Potion")("Gonzap's Key")("Great Ball")("TM01")
    ("TM02")("Aspear Berry")("Joy Scent")("Battle CD 01")
;

static const std::vector<std::string> colosseum_wrong_game_all_pocket_items = boost::assign::list_of
    ("Pink Bow")("Black Sludge")
    ("GS Ball")("Gonzap's Key")("Poffin Items")
    ("TM51")("HM01")
    ("Berry")("Occa Berry")
;

static const std::vector<std::string> xd_wrong_game_all_pocket_items = boost::assign::list_of
    ("Pink Bow")("Black Sludge")
    ("GS Ball")("Ein File S")("Poffin Items")
    ("TM51")("HM01")
    ("Berry")("Occa Berry")
;

class gcn_item_list_test: public item_list_test {};

/*
 * On the C++ level, make sure the LibPKMN abstraction matches the underlying
 * LibPkmGC class.
 */
static void check_libpkmgc_class(
    const pkmn::item_slots_t& item_slots,
    pkmn::e_game game,
    const LibPkmGC::Item* p_native_items,
    int expected_num_items
)
{
    for(int item_index = 0; item_index < expected_num_items; ++item_index)
    {
        EXPECT_EQ(
            pkmn::database::item_entry(
                item_slots.at(item_index).item,
                game
            ).get_item_index(),
            int(p_native_items[item_index].index)
        );
        EXPECT_EQ(
            item_slots.at(item_index).amount,
            int(p_native_items[item_index].quantity)
        );
    }

    if(expected_num_items < int(item_slots.size()))
    {
        EXPECT_EQ(LibPkmGC::NoItem, p_native_items[expected_num_items].index);
        EXPECT_EQ(0, p_native_items[expected_num_items].quantity);
    }
}

void gcn_item_pocket_test(
    const pkmn::item_list::sptr& item_pocket
)
{
    ASSERT_EQ("Items", item_pocket->get_name());

    bool colosseum = (item_pocket->get_game() == pkmn::e_game::COLOSSEUM);

    int capacity = colosseum ? 20 : 30;
    ASSERT_EQ(capacity, item_pocket->get_capacity());
    ASSERT_EQ(size_t(capacity), item_pocket->as_vector().size());

    // Make sure item slots start as correctly empty.
    test_item_list_empty_slots(item_pocket);

    // Confirm exceptions are thrown when expected.
    test_item_list_out_of_range_error(
        item_pocket,
        "Potion"
    );

    // Make sure we can't add items from other pockets.
    static const std::vector<std::string> colosseum_wrong_pocket_items = boost::assign::list_of
        ("Ein File S")("Great Ball")("TM01")("Oran Berry")("Joy Scent")
    ;
    static const std::vector<std::string> xd_wrong_pocket_items = boost::assign::list_of
        ("Miror Radar")("Great Ball")("TM01")("Oran Berry")("Joy Scent")("Battle CD 01")
    ;
    test_item_list_invalid_items(
        item_pocket,
        (colosseum ? colosseum_wrong_pocket_items : xd_wrong_pocket_items)
    );

    // Make sure we can't add items from other generations.
    static const std::vector<std::string> wrong_generation_items = boost::assign::list_of
        ("Pink Bow")("Black Sludge")("Binding Band")("Beedrillite")
    ;
    test_item_list_invalid_items(
        item_pocket,
        wrong_generation_items
    );

    // Start adding and removing stuff, and make sure the numbers are accurate.
    static const std::vector<std::string> item_names = boost::assign::list_of
        ("Potion")("Orange Mail")("Lava Cookie")("Stardust")
        ("Shadow Mail")("Pink Scarf")("Antidote")("Green Shard")
    ;
    test_item_list_add_remove(
        item_pocket,
        item_names
    );

    // Also make sure the pocket can hold both GBA and GCN items.
    pkmn::e_item gcn_item = colosseum ? pkmn::e_item::TIME_FLUTE
                                      : pkmn::e_item::POKE_SNACK;
    std::string gcn_item_name = colosseum ? "Time Flute"
                                          : "Poké Snack";

    const std::vector<pkmn::e_item>& valid_items = item_pocket->get_valid_items();
    const std::vector<std::string>& valid_item_names = item_pocket->get_valid_item_names();

    ASSERT_EQ(valid_items.size(), valid_item_names.size());
    EXPECT_FALSE(valid_item_names.empty());

    EXPECT_TRUE(pkmn::does_vector_contain_value(valid_items, pkmn::e_item::POTION));
    EXPECT_TRUE(pkmn::does_vector_contain_value(valid_items, gcn_item));

    EXPECT_TRUE(pkmn::does_vector_contain_value<std::string>(valid_item_names, "Potion"));
    EXPECT_TRUE(pkmn::does_vector_contain_value(valid_item_names, gcn_item_name));

    check_libpkmgc_class(
        item_pocket->as_vector(),
        item_pocket->get_game(),
        static_cast<const LibPkmGC::Item*>(item_pocket->get_native()),
        item_pocket->get_num_items()
    );
}

void gcn_key_item_pocket_test(
    const pkmn::item_list::sptr& key_item_pocket
)
{
    ASSERT_EQ("Key Items", key_item_pocket->get_name());

    bool colosseum = (key_item_pocket->get_game() == pkmn::e_game::COLOSSEUM);

    pkmn::e_item gcn_item = colosseum ? pkmn::e_item::EIN_FILE_S
                                      : pkmn::e_item::MIROR_RADAR;
    std::string gcn_item_name = colosseum ? "Ein File S"
                                          : "Miror Radar";

    int capacity = 43;
    ASSERT_EQ(capacity, key_item_pocket->get_capacity());
    ASSERT_EQ(size_t(capacity), key_item_pocket->as_vector().size());

    // Make sure item slots start as correctly empty.
    test_item_list_empty_slots(key_item_pocket);

    // Confirm exceptions are thrown when expected.
    test_item_list_out_of_range_error(
        key_item_pocket,
        gcn_item_name
    );

    // Make sure we can't add items from other pockets.
    static const std::vector<std::string> colosseum_wrong_pocket_items = boost::assign::list_of
        ("Potion")("Great Ball")("TM01")("Oran Berry")("Joy Scent")
    ;
    static const std::vector<std::string> xd_wrong_pocket_items = boost::assign::list_of
        ("Potion")("Great Ball")("TM01")("Oran Berry")("Joy Scent")("Battle CD 01")
    ;
    test_item_list_invalid_items(
        key_item_pocket,
        (colosseum ? colosseum_wrong_pocket_items : xd_wrong_pocket_items)
    );

    // Make sure we can't add items from other generations.
    static const std::vector<std::string> wrong_generation_items = boost::assign::list_of
        ("GS Ball")("Poffin Items")("DNA Splicers")("Aqua Suit")
    ;
    test_item_list_invalid_items(
        key_item_pocket,
        wrong_generation_items
    );

    // Make sure we can't add items from incompatible Generation III games.
    static const std::vector<std::string> frlg_items = boost::assign::list_of
        ("Helix Fossil")("Tea")("Ruby")
    ;
    static const std::vector<std::string> emerald_items = boost::assign::list_of
        ("Magma Emblem")("Old Sea Map")
    ;
    test_item_list_invalid_items(
        key_item_pocket,
        frlg_items
    );
    test_item_list_invalid_items(
        key_item_pocket,
        emerald_items
    );

    // Start adding and removing stuff, and make sure the numbers are accurate.
    static const std::vector<std::string> colosseum_item_names = boost::assign::list_of
        ("Jail Key")("Elevator Key")("Small Tablet")("F-Disk")
        ("R-Disk")("L-Disk")("D-Disk")("U-Disk")
    ;
    static const std::vector<std::string> xd_item_names = boost::assign::list_of
        ("Krane Memo 1")("Krane Memo 2")("Krane Memo 3")("Krane Memo 4")
        ("Krane Memo 5")("Voice Case 1")("Voice Case 2")("Voice Case 3")
    ;
    test_item_list_add_remove(
        key_item_pocket,
        (colosseum ? colosseum_item_names : xd_item_names)
    );

    const std::vector<pkmn::e_item>& valid_items = key_item_pocket->get_valid_items();
    const std::vector<std::string>& valid_item_names = key_item_pocket->get_valid_item_names();

    ASSERT_EQ(valid_items.size(), valid_item_names.size());
    EXPECT_FALSE(valid_item_names.empty());

    EXPECT_TRUE(pkmn::does_vector_contain_value(valid_items, gcn_item));
    EXPECT_TRUE(pkmn::does_vector_contain_value(valid_item_names, gcn_item_name));

    check_libpkmgc_class(
        key_item_pocket->as_vector(),
        key_item_pocket->get_game(),
        static_cast<const LibPkmGC::Item*>(key_item_pocket->get_native()),
        key_item_pocket->get_num_items()
    );
}

void gcn_ball_pocket_test(
    const pkmn::item_list::sptr& ball_pocket
)
{
    ASSERT_EQ("Poké Balls", ball_pocket->get_name());

    bool colosseum = (ball_pocket->get_game() == pkmn::e_game::COLOSSEUM);
    int capacity = 16;
    ASSERT_EQ(capacity, ball_pocket->get_capacity());
    ASSERT_EQ(size_t(capacity), ball_pocket->as_vector().size());

    // Make sure item slots start as correctly empty.
    test_item_list_empty_slots(ball_pocket);

    // Confirm exceptions are thrown when expected.
    test_item_list_out_of_range_error(
        ball_pocket,
        "Poké Ball"
    );

    // Make sure we can't add items from other pockets.
    static const std::vector<std::string> colosseum_wrong_pocket_items = boost::assign::list_of
        ("Ein File S")("Potion")("TM01")("Oran Berry")("Joy Scent")
    ;
    static const std::vector<std::string> xd_wrong_pocket_items = boost::assign::list_of
        ("Miror Radar")("Potion")("TM01")("Oran Berry")("Joy Scent")("Battle CD 01")
    ;
    test_item_list_invalid_items(
        ball_pocket,
        (colosseum ? colosseum_wrong_pocket_items : xd_wrong_pocket_items)
    );

    // Make sure we can't add items from other generations.
    static const std::vector<std::string> wrong_generation_items = boost::assign::list_of
        ("Moon Ball")("Heal Ball")("Dream Ball")
    ;
    test_item_list_invalid_items(
        ball_pocket,
        wrong_generation_items
    );

    // Start adding and removing stuff, and make sure the numbers are accurate.
    static const std::vector<std::string> item_names = boost::assign::list_of
        ("Master Ball")("Ultra Ball")("Great Ball")("Poké Ball")
        ("Safari Ball")("Net Ball")("Dive Ball")("Nest Ball")
    ;
    test_item_list_add_remove(
        ball_pocket,
        item_names
    );

    const std::vector<pkmn::e_item>& valid_items = ball_pocket->get_valid_items();
    const std::vector<std::string>& valid_item_names = ball_pocket->get_valid_item_names();

    ASSERT_EQ(valid_items.size(), valid_item_names.size());
    EXPECT_FALSE(valid_item_names.empty());

    check_libpkmgc_class(
        ball_pocket->as_vector(),
        ball_pocket->get_game(),
        static_cast<const LibPkmGC::Item*>(ball_pocket->get_native()),
        ball_pocket->get_num_items()
    );
}

void gcn_tm_pocket_test(
    const pkmn::item_list::sptr& tm_pocket
)
{
    ASSERT_EQ("TMs", tm_pocket->get_name());

    bool colosseum = (tm_pocket->get_game() == pkmn::e_game::COLOSSEUM);
    int capacity = 64;
    ASSERT_EQ(capacity, tm_pocket->get_capacity());
    ASSERT_EQ(size_t(capacity), tm_pocket->as_vector().size());

    // Make sure item slots start as correctly empty.
    test_item_list_empty_slots(tm_pocket);

    // Confirm exceptions are thrown when expected.
    test_item_list_out_of_range_error(
        tm_pocket,
        "TM01"
    );

    // Make sure we can't add items from other pockets.
    static const std::vector<std::string> colosseum_wrong_pocket_items = boost::assign::list_of
        ("Ein File S")("Potion")("Great Ball")("Oran Berry")("Joy Scent")
    ;
    static const std::vector<std::string> xd_wrong_pocket_items = boost::assign::list_of
        ("Miror Radar")("Potion")("Great Ball")("Oran Berry")("Joy Scent")("Battle CD 01")
    ;
    test_item_list_invalid_items(
        tm_pocket,
        (colosseum ? colosseum_wrong_pocket_items : xd_wrong_pocket_items)
    );

    // Make sure we can't add items from other generations.
    static const std::vector<std::string> wrong_generation_items = boost::assign::list_of
        ("TM51")("HM01")
    ;
    test_item_list_invalid_items(
        tm_pocket,
        wrong_generation_items
    );

    // Start adding and removing stuff, and make sure the numbers are accurate.
    static const std::vector<std::string> item_names = boost::assign::list_of
        ("TM01")("TM02")("TM03")("TM04")
        ("TM05")("TM06")("TM07")("TM08")
    ;
    test_item_list_add_remove(
        tm_pocket,
        item_names
    );

    // Gamecube games have no HMs.
    const std::vector<pkmn::e_item>& valid_items = tm_pocket->get_valid_items();
    const std::vector<std::string>& valid_item_names = tm_pocket->get_valid_item_names();

    ASSERT_EQ(valid_items.size(), valid_item_names.size());
    EXPECT_EQ(50, valid_item_names.size());

    EXPECT_TRUE(pkmn::does_vector_contain_value(valid_items, pkmn::e_item::TM01));
    EXPECT_FALSE(pkmn::does_vector_contain_value(valid_items, pkmn::e_item::HM01));

    EXPECT_TRUE(pkmn::does_vector_contain_value<std::string>(valid_item_names, "TM01"));
    EXPECT_FALSE(pkmn::does_vector_contain_value<std::string>(valid_item_names, "HM01"));

    check_libpkmgc_class(
        tm_pocket->as_vector(),
        tm_pocket->get_game(),
        static_cast<const LibPkmGC::Item*>(tm_pocket->get_native()),
        tm_pocket->get_num_items()
    );
}

void gcn_berry_pocket_test(
    const pkmn::item_list::sptr& berry_pocket
) {
    ASSERT_EQ("Berries", berry_pocket->get_name());

    bool colosseum = (berry_pocket->get_game() == pkmn::e_game::COLOSSEUM);
    int capacity = 46;
    ASSERT_EQ(capacity, berry_pocket->get_capacity());
    ASSERT_EQ(size_t(capacity), berry_pocket->as_vector().size());

    // Make sure item slots start as correctly empty.
    test_item_list_empty_slots(berry_pocket);

    // Confirm exceptions are thrown when expected.
    test_item_list_out_of_range_error(
        berry_pocket,
        "Oran Berry"
    );

    // Make sure we can't add items from other pockets.
    static const std::vector<std::string> colosseum_wrong_pocket_items = boost::assign::list_of
        ("Ein File S")("Potion")("Great Ball")("TM01")("Joy Scent")
    ;
    static const std::vector<std::string> xd_wrong_pocket_items = boost::assign::list_of
        ("Miror Radar")("Potion")("Great Ball")("TM01")("Joy Scent")("Battle CD 01")
    ;
    test_item_list_invalid_items(
        berry_pocket,
        (colosseum ? colosseum_wrong_pocket_items : xd_wrong_pocket_items)
    );

    // Make sure we can't add items from other generations.
    static const std::vector<std::string> wrong_generation_items = boost::assign::list_of
        ("Berry")("Occa Berry")("Roseli Berry")
    ;
    test_item_list_invalid_items(
        berry_pocket,
        wrong_generation_items
    );

    // Start adding and removing stuff, and make sure the numbers are accurate.
    static const std::vector<std::string> item_names = boost::assign::list_of
        ("Cheri Berry")("Razz Berry")("Lum Berry")("Pinap Berry")
        ("Aspear Berry")("Iapapa Berry")("Wiki Berry")("Apicot Berry")
    ;
    test_item_list_add_remove(
        berry_pocket,
        item_names
    );

    const std::vector<pkmn::e_item>& valid_items = berry_pocket->get_valid_items();
    const std::vector<std::string>& valid_item_names = berry_pocket->get_valid_item_names();

    ASSERT_EQ(valid_items.size(), valid_item_names.size());
    EXPECT_FALSE(valid_item_names.empty());

    EXPECT_TRUE(pkmn::does_vector_contain_value(valid_items, pkmn::e_item::ORAN_BERRY));
    EXPECT_TRUE(pkmn::does_vector_contain_value<std::string>(valid_item_names, "Oran Berry"));

    check_libpkmgc_class(
        berry_pocket->as_vector(),
        berry_pocket->get_game(),
        static_cast<const LibPkmGC::Item*>(berry_pocket->get_native()),
        berry_pocket->get_num_items()
    );
}

void gcn_cologne_pocket_test(
    const pkmn::item_list::sptr& cologne_pocket
)
{
    ASSERT_EQ("Colognes", cologne_pocket->get_name());

    bool colosseum = (cologne_pocket->get_game() == pkmn::e_game::COLOSSEUM);
    int capacity = 3;
    ASSERT_EQ(capacity, cologne_pocket->get_capacity());
    ASSERT_EQ(size_t(capacity), cologne_pocket->as_vector().size());

    // Make sure item slots start as correctly empty.
    test_item_list_empty_slots(cologne_pocket);

    // Confirm exceptions are thrown when expected.
    test_item_list_out_of_range_error(
        cologne_pocket,
        "Joy Scent"
    );

    // Make sure we can't add items from other pockets.
    static const std::vector<std::string> colosseum_wrong_pocket_items = boost::assign::list_of
        ("Ein File S")("Potion")("Great Ball")("TM01")("Oran Berry")
    ;
    static const std::vector<std::string> xd_wrong_pocket_items = boost::assign::list_of
        ("Miror Radar")("Potion")("Great Ball")("TM01")("Oran Berry")("Battle CD 01")
    ;
    test_item_list_invalid_items(
        cologne_pocket,
        (colosseum ? colosseum_wrong_pocket_items : xd_wrong_pocket_items)
    );

    // Since this pocket can only have 3 items, we can't use our typical function, which requires 8.
    const pkmn::item_slots_t& item_slots = cologne_pocket->as_vector();

    cologne_pocket->add("Joy Scent", 3);
    cologne_pocket->add("Excite Scent", 3);
    cologne_pocket->add("Vivid Scent", 3);

    cologne_pocket->remove("Excite Scent", 3);
    cologne_pocket->remove("Vivid Scent", 1);

    EXPECT_EQ("Joy Scent", item_slots.at(0).item);
    EXPECT_EQ(3, item_slots.at(0).amount);
    EXPECT_EQ("Vivid Scent", item_slots.at(1).item);
    EXPECT_EQ(2, item_slots.at(1).amount);
    EXPECT_EQ("None", item_slots.at(2).item);
    EXPECT_EQ(0, item_slots.at(2).amount);

    const std::vector<pkmn::e_item>& valid_items = cologne_pocket->get_valid_items();
    const std::vector<std::string>& valid_item_names = cologne_pocket->get_valid_item_names();

    ASSERT_EQ(valid_items.size(), valid_item_names.size());
    EXPECT_EQ(3, valid_item_names.size());

    EXPECT_TRUE(pkmn::does_vector_contain_value(valid_items, pkmn::e_item::JOY_SCENT));
    EXPECT_TRUE(pkmn::does_vector_contain_value<std::string>(valid_item_names, "Joy Scent"));

    check_libpkmgc_class(
        cologne_pocket->as_vector(),
        cologne_pocket->get_game(),
        static_cast<const LibPkmGC::Item*>(cologne_pocket->get_native()),
        cologne_pocket->get_num_items()
    );
}

void gcn_battle_cd_pocket_test(
    const pkmn::item_list::sptr& battle_cd_pocket
)
{
    ASSERT_EQ("Battle CDs", battle_cd_pocket->get_name());

    int capacity = 60;
    ASSERT_EQ(capacity, battle_cd_pocket->get_capacity());
    ASSERT_EQ(size_t(capacity), battle_cd_pocket->as_vector().size());

    // Make sure item slots start as correctly empty.
    test_item_list_empty_slots(battle_cd_pocket);

    // Confirm exceptions are thrown when expected.
    test_item_list_out_of_range_error(
        battle_cd_pocket,
        "Battle CDs"
    );

    // Make sure we can't add items from other pockets.
    static const std::vector<std::string> wrong_pocket_items = boost::assign::list_of
        ("Miror Radar")("Potion")("Great Ball")("TM01")("Oran Berry")("Joy Scent")
    ;
    test_item_list_invalid_items(
        battle_cd_pocket,
        wrong_pocket_items
    );

    // Start adding and removing stuff, and make sure the numbers are accurate.
    static const std::vector<std::string> item_names = boost::assign::list_of
        ("Battle CD 01")("Battle CD 02")("Battle CD 03")("Battle CD 04")
        ("Battle CD 05")("Battle CD 06")("Battle CD 07")("Battle CD 08")
    ;
    test_item_list_add_remove(
        battle_cd_pocket,
        item_names
    );

    const std::vector<pkmn::e_item>& valid_items = battle_cd_pocket->get_valid_items();
    const std::vector<std::string>& valid_item_names = battle_cd_pocket->get_valid_item_names();

    ASSERT_EQ(valid_items.size(), valid_item_names.size());
    EXPECT_EQ(60, valid_item_names.size());

    EXPECT_TRUE(pkmn::does_vector_contain_value(valid_items, pkmn::e_item::BATTLE_CD_01));
    EXPECT_TRUE(pkmn::does_vector_contain_value<std::string>(valid_item_names, "Battle CD 01"));

    check_libpkmgc_class(
        battle_cd_pocket->as_vector(),
        battle_cd_pocket->get_game(),
        static_cast<const LibPkmGC::Item*>(battle_cd_pocket->get_native()),
        battle_cd_pocket->get_num_items()
    );
}

void gcn_item_pc_test(
    const pkmn::item_list::sptr& item_pc
)
{
    ASSERT_EQ("PC", item_pc->get_name());
    ASSERT_EQ(235, item_pc->get_capacity());
    ASSERT_EQ(235, item_pc->as_vector().size());
    bool colosseum = (item_pc->get_game() == pkmn::e_game::COLOSSEUM);

    // Make sure item slots start as correctly empty
    test_item_list_empty_slots(item_pc);

    // Confirm exceptions are thrown when expected.
    test_item_list_out_of_range_error(
        item_pc,
        "Potion"
    );

    // Make sure we can't add items from other generations or incompatible Generation III games.
    test_item_list_invalid_items(
        item_pc,
        (colosseum ? colosseum_wrong_game_all_pocket_items : xd_wrong_game_all_pocket_items)
    );

    // Start adding and removing stuff, and make sure the numbers are accurate.
    test_item_list_add_remove(
        item_pc,
        (colosseum ? colosseum_all_pocket_items: xd_all_pocket_items)
    );

    check_libpkmgc_class(
        item_pc->as_vector(),
        item_pc->get_game(),
        static_cast<const LibPkmGC::Item*>(item_pc->get_native()),
        item_pc->get_num_items()
    );
}

static const item_list_test_fcns_t gcn_test_fcns = boost::assign::map_list_of
    ("Items", &gcn_item_pocket_test)
    ("Key Items", &gcn_key_item_pocket_test)
    ("Poké Balls", &gcn_ball_pocket_test)
    ("TMs", &gcn_tm_pocket_test)
    ("Berries", &gcn_berry_pocket_test)
    ("Colognes", &gcn_cologne_pocket_test)
    ("Battle CDs", &gcn_battle_cd_pocket_test)
    ("PC", &gcn_item_pc_test)
;

TEST_P(gcn_item_list_test, item_list_test)
{
    gcn_test_fcns.at(get_name())(get_item_list());
}

static const std::vector<std::pair<pkmn::e_game, std::string>> item_list_params =
{
    {pkmn::e_game::COLOSSEUM, "Items"},
    {pkmn::e_game::COLOSSEUM, "Key Items"},
    {pkmn::e_game::COLOSSEUM, "Poké Balls"},
    {pkmn::e_game::COLOSSEUM, "TMs"},
    {pkmn::e_game::COLOSSEUM, "Berries"},
    {pkmn::e_game::COLOSSEUM, "Colognes"},
    {pkmn::e_game::COLOSSEUM, "PC"},

    {pkmn::e_game::XD, "Items"},
    {pkmn::e_game::XD, "Key Items"},
    {pkmn::e_game::XD, "Poké Balls"},
    {pkmn::e_game::XD, "TMs"},
    {pkmn::e_game::XD, "Berries"},
    {pkmn::e_game::XD, "Colognes"},
    {pkmn::e_game::XD, "Battle CDs"},
    {pkmn::e_game::XD, "PC"}
};

INSTANTIATE_TEST_CASE_P(
    cpp_gcn_item_list_test,
    gcn_item_list_test,
    ::testing::ValuesIn(item_list_params)
);

class gcn_item_bag_test: public item_bag_test {};

TEST_P(gcn_item_bag_test, item_bag_test)
{
    const pkmn::item_bag::sptr& bag = get_item_bag();
    pkmn::e_game game = get_game();
    bool colosseum = (game == pkmn::e_game::COLOSSEUM);
    int num_pockets = colosseum ? 6 : 7;

    const pkmn::item_pockets_t& pockets = bag->get_pockets();
    ASSERT_EQ(num_pockets, pockets.size());
    ASSERT_EQ("Items", pockets.at("Items")->get_name());
    ASSERT_EQ(game, pockets.at("Items")->get_game());
    ASSERT_EQ("Key Items", pockets.at("Key Items")->get_name());
    ASSERT_EQ(game, pockets.at("Key Items")->get_game());
    ASSERT_EQ("Poké Balls", pockets.at("Poké Balls")->get_name());
    ASSERT_EQ(game, pockets.at("Poké Balls")->get_game());
    ASSERT_EQ("TMs", pockets.at("TMs")->get_name());
    ASSERT_EQ(game, pockets.at("TMs")->get_game());
    ASSERT_EQ("Berries", pockets.at("Berries")->get_name());
    ASSERT_EQ(game, pockets.at("Berries")->get_game());
    ASSERT_EQ("Colognes", pockets.at("Colognes")->get_name());
    ASSERT_EQ(game, pockets.at("Colognes")->get_game());
    if(not colosseum)
    {
        ASSERT_EQ("Battle CDs", pockets.at("Battle CDs")->get_name());
        ASSERT_EQ(game, pockets.at("Battle CDs")->get_game());
    }

    const std::vector<std::string>& pocket_names = bag->get_pocket_names();
    ASSERT_EQ(num_pockets, pockets.size());
    ASSERT_NE(pocket_names.end(), std::find(pocket_names.begin(), pocket_names.end(), "Items"));
    ASSERT_NE(pocket_names.end(), std::find(pocket_names.begin(), pocket_names.end(), "Key Items"));
    ASSERT_NE(pocket_names.end(), std::find(pocket_names.begin(), pocket_names.end(), "Poké Balls"));
    ASSERT_NE(pocket_names.end(), std::find(pocket_names.begin(), pocket_names.end(), "TMs"));
    ASSERT_NE(pocket_names.end(), std::find(pocket_names.begin(), pocket_names.end(), "Berries"));
    ASSERT_NE(pocket_names.end(), std::find(pocket_names.begin(), pocket_names.end(), "Colognes"));
    if(colosseum)
    {
        ASSERT_EQ(pocket_names.end(), std::find(pocket_names.begin(), pocket_names.end(), "Battle CDs"));
    }
    else
    {
        ASSERT_NE(pocket_names.end(), std::find(pocket_names.begin(), pocket_names.end(), "Battle CDs"));
    }

    gcn_item_pocket_test(pockets.at("Items"));
    gcn_key_item_pocket_test(pockets.at("Key Items"));
    gcn_ball_pocket_test(pockets.at("Poké Balls"));
    gcn_tm_pocket_test(pockets.at("TMs"));
    gcn_berry_pocket_test(pockets.at("Berries"));
    gcn_cologne_pocket_test(pockets.at("Colognes"));
    if(not colosseum)
    {
        gcn_battle_cd_pocket_test(pockets.at("Battle CDs"));
    }
    reset();

    // Make sure adding items through the bag adds to the proper pockets.
    ASSERT_EQ(0, bag->get_pocket("Items")->get_num_items());
    ASSERT_EQ(0, bag->get_pocket("Key Items")->get_num_items());
    ASSERT_EQ(0, bag->get_pocket("Poké Balls")->get_num_items());
    ASSERT_EQ(0, bag->get_pocket("TMs")->get_num_items());
    ASSERT_EQ(0, bag->get_pocket("Berries")->get_num_items());
    ASSERT_EQ(0, bag->get_pocket("Colognes")->get_num_items());
    if(not colosseum)
    {
        ASSERT_EQ(0, bag->get_pocket("Battle CDs")->get_num_items());
    }
    for(int item_index = 0; item_index < 8; ++item_index)
    {
        bag->add(
            (colosseum ? colosseum_all_pocket_items[item_index]
                       : xd_all_pocket_items[item_index]),
            5
        );
    }

    const pkmn::item_slots_t& item_slots = bag->get_pocket("Items")->as_vector();
    const pkmn::item_slots_t& key_item_slots = bag->get_pocket("Key Items")->as_vector();
    const pkmn::item_slots_t& ball_slots = bag->get_pocket("Poké Balls")->as_vector();
    const pkmn::item_slots_t& tm_slots = bag->get_pocket("TMs")->as_vector();
    const pkmn::item_slots_t& berry_slots = bag->get_pocket("Berries")->as_vector();
    const pkmn::item_slots_t& cologne_slots = bag->get_pocket("Colognes")->as_vector();
    std::string gcn_item = colosseum ? "Ein File S" : "Gonzap's Key";

    EXPECT_EQ("Potion", item_slots.at(0).item);
    EXPECT_EQ(5, item_slots.at(0).amount);
    EXPECT_EQ("None", item_slots.at(1).item);
    EXPECT_EQ(0, item_slots.at(1).amount);

    EXPECT_EQ(gcn_item, key_item_slots.at(0).item);
    EXPECT_EQ(5, key_item_slots.at(0).amount);
    EXPECT_EQ("None", key_item_slots.at(1).item);
    EXPECT_EQ(0, key_item_slots.at(1).amount);

    EXPECT_EQ("Great Ball", ball_slots.at(0).item);
    EXPECT_EQ(5, ball_slots.at(0).amount);
    EXPECT_EQ("None", ball_slots.at(1).item);
    EXPECT_EQ(0, ball_slots.at(1).amount);

    EXPECT_EQ("TM01", tm_slots.at(0).item);
    EXPECT_EQ(5, tm_slots.at(0).amount);
    EXPECT_EQ("TM02", tm_slots.at(1).item);
    EXPECT_EQ(5, tm_slots.at(1).amount);
    EXPECT_EQ("None", tm_slots.at(2).item);
    EXPECT_EQ(0, tm_slots.at(2).amount);

    EXPECT_EQ("Aspear Berry", berry_slots.at(0).item);
    EXPECT_EQ(5, berry_slots.at(0).amount);
    EXPECT_EQ("None", berry_slots.at(1).item);
    EXPECT_EQ(0, berry_slots.at(1).amount);

    EXPECT_EQ("Joy Scent", cologne_slots.at(0).item);
    EXPECT_EQ(5, cologne_slots.at(0).amount);

    if(colosseum)
    {
        EXPECT_EQ("Excite Scent", cologne_slots.at(1).item);
        EXPECT_EQ(5, cologne_slots.at(1).amount);
    }
    else
    {
        EXPECT_EQ("None", cologne_slots.at(1).item);
        EXPECT_EQ(0, cologne_slots.at(1).amount);

        const pkmn::item_slots_t& battle_cd_slots = bag->get_pocket("Battle CDs")->as_vector();
        EXPECT_EQ("Battle CD 01", battle_cd_slots.at(0).item);
        EXPECT_EQ(5, battle_cd_slots.at(0).amount);
        EXPECT_EQ("None", battle_cd_slots.at(1).item);
        EXPECT_EQ(0, battle_cd_slots.at(1).amount);
    }

    /*
     * On the C++ level, make sure the LibPKMN abstraction matches the underlying
     * PKSav struct.
     */
    const LibPkmGC::GC::BagData* native = static_cast<const LibPkmGC::GC::BagData*>(bag->get_native());
    check_libpkmgc_class(
        item_slots,
        game,
        native->regularItems,
        1
    );
    check_libpkmgc_class(
        key_item_slots,
        game,
        native->keyItems,
        1
    );
    check_libpkmgc_class(
        ball_slots,
        game,
        native->pokeballs,
        1
    );
    check_libpkmgc_class(
        tm_slots,
        game,
        native->TMs,
        2
    );
    check_libpkmgc_class(
        berry_slots,
        game,
        native->berries,
        1
    );
    check_libpkmgc_class(
        cologne_slots,
        game,
        native->colognes,
        (colosseum ? 2 : 1)
    );
    if(not colosseum)
    {
        check_libpkmgc_class(
            bag->get_pocket("Battle CDs")->as_vector(),
            game,
            dynamic_cast<const LibPkmGC::XD::BagData*>(native)->battleCDs,
            1
        );
    }

    // Make sure removing items through the bag removes from the proper pockets.
    for(int i = 0; i < 8; ++i) {
        bag->remove(
            (colosseum ? colosseum_all_pocket_items[i] : xd_all_pocket_items[i]),
            5
        );
    }

    EXPECT_EQ("None", item_slots.at(0).item);
    EXPECT_EQ(0, item_slots.at(0).amount);
    EXPECT_EQ("None", item_slots.at(1).item);
    EXPECT_EQ(0, item_slots.at(1).amount);

    EXPECT_EQ("None", key_item_slots.at(0).item);
    EXPECT_EQ(0, key_item_slots.at(0).amount);
    EXPECT_EQ("None", key_item_slots.at(1).item);
    EXPECT_EQ(0, key_item_slots.at(1).amount);

    EXPECT_EQ("None", ball_slots.at(0).item);
    EXPECT_EQ(0, ball_slots.at(0).amount);
    EXPECT_EQ("None", ball_slots.at(1).item);
    EXPECT_EQ(0, ball_slots.at(1).amount);

    EXPECT_EQ("None", tm_slots.at(0).item);
    EXPECT_EQ(0, tm_slots.at(0).amount);
    EXPECT_EQ("None", tm_slots.at(1).item);
    EXPECT_EQ(0, tm_slots.at(1).amount);
    EXPECT_EQ("None", tm_slots.at(2).item);
    EXPECT_EQ(0, tm_slots.at(2).amount);

    EXPECT_EQ("None", berry_slots.at(0).item);
    EXPECT_EQ(0, berry_slots.at(0).amount);
    EXPECT_EQ("None", berry_slots.at(1).item);
    EXPECT_EQ(0, berry_slots.at(1).amount);

    EXPECT_EQ("None", cologne_slots.at(0).item);
    EXPECT_EQ(0, cologne_slots.at(0).amount);

    if(colosseum)
    {
        EXPECT_EQ("None", cologne_slots.at(1).item);
        EXPECT_EQ(0, cologne_slots.at(1).amount);
    }
    else
    {
        EXPECT_EQ("None", cologne_slots.at(1).item);
        EXPECT_EQ(0, cologne_slots.at(1).amount);

        const pkmn::item_slots_t& battle_cd_slots = bag->get_pocket("Battle CDs")->as_vector();
        EXPECT_EQ("None", battle_cd_slots.at(0).item);
        EXPECT_EQ(0, battle_cd_slots.at(0).amount);
        EXPECT_EQ("None", battle_cd_slots.at(1).item);
        EXPECT_EQ(0, battle_cd_slots.at(1).amount);
    }

    // Make sure we can't add items from other generations or invalid Generation III games.
    test_item_bag_invalid_items(
        bag,
        (colosseum ? colosseum_wrong_game_all_pocket_items : xd_wrong_game_all_pocket_items)
    );
}

INSTANTIATE_TEST_CASE_P(
    cpp_gcn_item_bag_test,
    gcn_item_bag_test,
    ::testing::ValuesIn(pkmntest::GCN_GAMES)
);
