/*
 * Copyright (c) 2016 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#import "CppToObjC.h"

@implementation PKItemDatabaseEntryFromCpp

- (PKItemDatabaseEntryFromCpp*)initFromCpp: (const pkmn::database::item_entry&)cppInstance {
    PKMN_CPP_TO_OBJC(
        _internal = reinterpret_cast<void*>(
                        new pkmn::database::item_entry(cppInstance)
                    );
        return self;
    )
}

- (void)dealloc {
    [super dealloc];
}

@end

@implementation PKItemSlotArrayFromCpp: PKItemSlotArray

- (PKItemSlotArrayFromCpp*)initFromCpp: (pkmn::item_slots_t&)cppInstance {
    PKMN_CPP_TO_OBJC(
        _internal = reinterpret_cast<void*>(
                        new pkmn::item_slots_t(
                                (pkmn::item_slots_t&&)cppInstance
                            )
                    );
    )
}

- (void)dealloc {
    [super dealloc];
}

@end

@implementation PKLevelupMoveArrayFromCpp: PKLevelupMoveArray

- (PKLevelupMoveArrayFromCpp*)initFromCpp: (pkmn::database::levelup_moves_t&)cppInstance {
    PKMN_CPP_TO_OBJC(
        _internal = reinterpret_cast<void*>(
                        new pkmn::database::levelup_moves_t(
                                (pkmn::database::levelup_moves_t&&)cppInstance
                            )
                    );
        return self;
    )
}

- (void)dealloc {
    [super dealloc];
}

@end

@implementation PKMoveDatabaseEntryFromCpp

- (PKMoveDatabaseEntryFromCpp*)initFromCpp: (const pkmn::database::move_entry&)cppInstance {
    PKMN_CPP_TO_OBJC(
        _internal = reinterpret_cast<void*>(
                        new pkmn::database::move_entry(cppInstance)
                    );
        return self;
    )
}

- (void)dealloc {
    [super dealloc];
}

@end

@implementation PKMoveDatabaseEntryArrayFromCpp

- (PKMoveDatabaseEntryArrayFromCpp*)initFromCpp: (pkmn::database::move_list_t&)cppInstance {
    PKMN_CPP_TO_OBJC(
        _internal = reinterpret_cast<void*>(
                        new pkmn::database::move_list_t(
                                (pkmn::database::move_list_t&&)cppInstance
                            )
                    );
        return self;
    )
}

- (void)dealloc {
    [super dealloc];
}

@end

@implementation PKPokemonDatabaseEntryFromCpp

- (PKPokemonDatabaseEntryFromCpp*)initFromCpp: (const pkmn::database::pokemon_entry&)cppInstance {
    PKMN_CPP_TO_OBJC(
        _internal = reinterpret_cast<void*>(
                        new pkmn::database::pokemon_entry(cppInstance)
                    );
        return self;
    )
}

- (void)dealloc {
    [super dealloc];
}

@end

@implementation PKPokemonDatabaseEntryArrayFromCpp

- (PKPokemonDatabaseEntryArrayFromCpp*)initFromCpp: (pkmn::database::pokemon_entries_t&)cppInstance {
    PKMN_CPP_TO_OBJC(
        _internal = reinterpret_cast<void*>(
                        new pkmn::database::pokemon_entries_t(
                                (pkmn::database::pokemon_entries_t&&)cppInstance
                            )
                    );
        return self;
    )
}

- (void)dealloc {
    [super dealloc];
}

@end

@implementation PKStringArrayFromCpp

- (PKStringArrayFromCpp*)initFromCpp: (std::vector<std::string>&)cppInstance {
    PKMN_CPP_TO_OBJC(
        _internal = reinterpret_cast<void*>(
                        new std::vector<std::string>(
                                (std::vector<std::string>&&)cppInstance
                            )
                    );
        return self;
    )
}

- (void)dealloc {
    [super dealloc];
}

@end

@implementation PKStringNumberDictionaryFromCpp

- (PKStringNumberDictionaryFromCpp*)initFromCpp: (std::map<std::string, int>&)cppInstance {
    PKMN_CPP_TO_OBJC(
        _internal = reinterpret_cast<void*>(
                        new std::map<std::string, int>(
                                (std::map<std::string, int>&&)cppInstance
                            )
                    );
        return self;
    )
}

- (void)dealloc {
    [super dealloc];
}

@end

@implementation CppToObjC

+ (PKItemDatabaseEntry*)createItemDatabaseEntryFromCpp: (const pkmn::database::item_entry&)cppInstance {
    PKMN_CPP_TO_OBJC(
        return (PKItemDatabaseEntry*)[[PKItemDatabaseEntryFromCpp alloc] initFromCpp:cppInstance];
    )
}

+ (PKItemSlot*)createItemSlotFromCpp: (const pkmn::item_slot&)cppInstance {
    PKMN_CPP_TO_OBJC(
        PKItemSlot* ret = [[PKItemSlot alloc] init];
        ret->item = [CppToObjC createItemDatabaseEntryFromCpp:cppInstance.item];
        ret->amount = @(cppInstance.amount);

        return ret;
    )
}

+ (PKItemSlotArray*)createItemSlotArrayFromCpp: (pkmn::item_slots_t&)cppInstance {
    PKMN_CPP_TO_OBJC(
        return (PKItemSlotArray*)[[PKItemSlotArrayFromCpp alloc] initFromCpp:cppInstance];
    )
}

+ (PKLevelupMove*)createLevelupMoveFromCpp: (const pkmn::database::levelup_move&)cppInstance {
    PKMN_CPP_TO_OBJC(
        PKLevelupMove* ret = [[PKLevelupMove alloc] init];
        ret->move = [CppToObjC createMoveDatabaseEntryFromCpp:cppInstance.move];
        ret->level = @(cppInstance.level);

        return ret;
    )
}

+ (PKLevelupMoveArray*)createLevelupMoveArrayFromCpp: (pkmn::database::levelup_moves_t&)cppInstance {
    PKMN_CPP_TO_OBJC(
        return (PKLevelupMoveArray*)[[PKLevelupMoveArrayFromCpp alloc] initFromCpp:cppInstance];
    )
}

+ (PKMoveDatabaseEntry*)createMoveDatabaseEntryFromCpp: (const pkmn::database::move_entry&)cppInstance {
    PKMN_CPP_TO_OBJC(
        return (PKMoveDatabaseEntry*)[[PKMoveDatabaseEntryFromCpp alloc] initFromCpp:cppInstance];
    )
}

+ (PKMoveDatabaseEntryArray*)createMoveDatabaseEntryArrayFromCpp: (pkmn::database::move_list_t&)cppInstance {
    PKMN_CPP_TO_OBJC(
        return (PKMoveDatabaseEntryArray*)[[PKMoveDatabaseEntryArrayFromCpp alloc] initFromCpp:cppInstance];
    )
}

+ (PKPokemonDatabaseEntry*)createPokemonDatabaseEntryFromCpp: (const pkmn::database::pokemon_entry&)cppInstance {
    PKMN_CPP_TO_OBJC(
        return (PKPokemonDatabaseEntry*)[[PKPokemonDatabaseEntryFromCpp alloc] initFromCpp:cppInstance];
    )
}

+ (PKPokemonDatabaseEntryArray*)createPokemonDatabaseEntryArrayFromCpp: (pkmn::database::pokemon_entries_t&)cppInstance {
    PKMN_CPP_TO_OBJC(
        return (PKPokemonDatabaseEntryArray*)[[PKPokemonDatabaseEntryArrayFromCpp alloc] initFromCpp:cppInstance];
    )
}

+ (PKStringArray*)createStringArrayFromCpp: (std::vector<std::string>&)cppInstance {
    PKMN_CPP_TO_OBJC(
        return (PKStringArray*)[[PKStringArrayFromCpp alloc] initFromCpp:cppInstance];
    )
}

+ (PKStringNumberDictionary*)createStringNumberDictionaryFromCpp: (std::map<std::string, int>&)cppInstance {
    PKMN_CPP_TO_OBJC(
        return (PKStringNumberDictionary*)[[PKStringNumberDictionaryFromCpp alloc] initFromCpp:cppInstance];
    )
}

+ (PKStringPair*)createStringPairFromCpp: (const std::pair<std::string, std::string>&)cppInstance {
    return [[PKStringPair alloc] initWithFirst:[NSString stringWithUTF8String:cppInstance.first.c_str()]
                                 andSecond:[NSString stringWithUTF8String:cppInstance.second.c_str()]];
}

@end
