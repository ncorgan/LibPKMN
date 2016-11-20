/*
 * Copyright (c) 2016 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#ifndef PKMN_OBJC_CPPTOOBJC_H
#define PKMN_OBJC_CPPTOOBJC_H

#import <PKMN-ObjC/PKItemSlot.h>
#import <PKMN-ObjC/Database/PKItemDatabaseEntry.h>
#import <PKMN-ObjC/PKItemSlotArray.h>
#import <PKMN-ObjC/Database/PKLevelupMove.h>
#import <PKMN-ObjC/Database/PKLevelupMoveArray.h>
#import <PKMN-ObjC/Database/PKMoveDatabaseEntry.h>
#import <PKMN-ObjC/Database/PKMoveDatabaseEntryArray.h>
#import <PKMN-ObjC/Database/PKPokemonDatabaseEntry.h>
#import <PKMN-ObjC/Database/PKPokemonDatabaseEntryArray.h>
#import <PKMN-ObjC/Types/PKStringArray.h>
#import <PKMN-ObjC/Types/PKStringNumberDictionary.h>
#import <PKMN-ObjC/Types/PKStringPair.h>

#include <pkmn/item_slot.hpp>
#include <pkmn/database/item_entry.hpp>
#include <pkmn/database/levelup_move.hpp>
#include <pkmn/database/move_entry.hpp>
#include <pkmn/database/pokemon_entry.hpp>

#import <Foundation/Foundation.h>

#include <map>
#include <stdexcept>
#include <utility>
#include <vector>

#define PKMN_CPP_TO_OBJC(...) \
{ \
    NSString* errMsg; \
    NSString* objCErrName; \
    bool thrown = false; \
    @try { \
        try { __VA_ARGS__ } \
        catch(const std::out_of_range &e) { \
            errMsg = [NSString stringWithUTF8String:e.what()]; \
            objCErrName = @"NSRangeException"; \
            thrown = true; \
        } catch(const std::logic_error &e) { \
            errMsg = [NSString stringWithUTF8String:e.what()]; \
            objCErrName = @"NSInvalidArgumentException"; \
            thrown = true; \
        } catch(const std::runtime_error &e) { \
            errMsg = [NSString stringWithUTF8String:e.what()]; \
            objCErrName = @"NSGenericException"; \
            thrown = true; \
        } catch(const std::exception &e) { \
            errMsg = [NSString stringWithUTF8String:e.what()]; \
            objCErrName = @"NSGenericException"; \
            thrown = true; \
        } catch(...) { \
            errMsg = @"Unknown error."; \
            objCErrName = @"NSGenericException"; \
            thrown = true; \
        } \
        if(thrown) { \
            @throw [NSException \
                        exceptionWithName:objCErrName \
                        reason:errMsg \
                        userInfo:nil \
                   ]; \
        } \
    } \
    @catch(NSException* e) { \
        @throw; \
    } \
    @finally { \
    } \
}

@interface PKItemDatabaseEntryFromCpp: PKItemDatabaseEntry

- (PKItemDatabaseEntryFromCpp*)initFromCpp: (const pkmn::database::item_entry&)cppInstance;

- (void)dealloc;

@end

@interface PKItemSlotArrayFromCpp: PKItemSlotArray

- (PKItemSlotArrayFromCpp*)initFromCpp: (pkmn::item_slots_t&)cppInstance;

- (void)dealloc;

@end

@interface PKLevelupMoveArrayFromCpp: PKLevelupMoveArray

- (PKLevelupMoveArrayFromCpp*)initFromCpp: (pkmn::database::levelup_moves_t&)cppInstance;

- (void)dealloc;

@end

@interface PKMoveDatabaseEntryFromCpp: PKMoveDatabaseEntry

- (PKMoveDatabaseEntryFromCpp*)initFromCpp: (const pkmn::database::move_entry&)cppInstance;

- (void)dealloc;

@end

@interface PKMoveDatabaseEntryArrayFromCpp: PKMoveDatabaseEntryArray

- (PKMoveDatabaseEntryArrayFromCpp*)initFromCpp: (pkmn::database::move_list_t&)cppInstance;

- (void)dealloc;

@end

@interface PKPokemonDatabaseEntryFromCpp: PKPokemonDatabaseEntry

- (PKPokemonDatabaseEntryFromCpp*)initFromCpp: (const pkmn::database::pokemon_entry&)cppInstance;

- (void)dealloc;

@end

@interface PKPokemonDatabaseEntryArrayFromCpp: PKPokemonDatabaseEntryArray

- (PKPokemonDatabaseEntryArrayFromCpp*)initFromCpp: (pkmn::database::pokemon_entries_t&)cppInstance;

- (void)dealloc;

@end

@interface PKStringArrayFromCpp: PKStringArray

- (PKStringArrayFromCpp*)initFromCpp: (std::vector<std::string>&)cppInstance;

- (void)dealloc;

@end

@interface PKStringNumberDictionaryFromCpp: PKStringNumberDictionary

- (PKStringNumberDictionaryFromCpp*)initFromCpp: (std::map<std::string, int>&)cppInstance;

- (void)dealloc;

@end

@interface CppToObjC: NSObject

+ (PKItemDatabaseEntry*)createItemDatabaseEntryFromCpp: (const pkmn::database::item_entry&)cppInstance;

+ (PKItemSlot*)createItemSlotFromCpp: (const pkmn::item_slot&)cppInstance;

+ (PKItemSlotArray*)createItemSlotArrayFromCpp: (pkmn::item_slots_t&)cppInstance;

+ (PKLevelupMove*)createLevelupMoveFromCpp: (const pkmn::database::levelup_move&)cppInstance;

+ (PKLevelupMoveArray*)createLevelupMoveArrayFromCpp: (pkmn::database::levelup_moves_t&)cppInstance;

+ (PKMoveDatabaseEntry*)createMoveDatabaseEntryFromCpp: (const pkmn::database::move_entry&)cppInstance;

+ (PKMoveDatabaseEntryArray*)createMoveDatabaseEntryArrayFromCpp: (pkmn::database::move_list_t&)cppInstance;

+ (PKPokemonDatabaseEntry*)createPokemonDatabaseEntryFromCpp: (const pkmn::database::pokemon_entry&)cppInstance;

+ (PKPokemonDatabaseEntryArray*)createPokemonDatabaseEntryArrayFromCpp: (pkmn::database::pokemon_entries_t&)cppInstance;

+ (PKStringArray*)createStringArrayFromCpp: (std::vector<std::string>&)cppInstance;

+ (PKStringNumberDictionary*)createStringNumberDictionaryFromCpp: (std::map<std::string, int>&)cppInstance;

+ (PKStringPair*)createStringPairFromCpp: (const std::pair<std::string, std::string>&)cppInstance;

@end

#endif /* PKMN_OBJC_CPPTOOBJC_H */