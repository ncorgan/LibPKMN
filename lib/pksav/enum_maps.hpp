/*
 * Copyright (c) 2017,2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#ifndef INCLUDED_PKMN_PKSAV_ENUM_MAPS_HPP
#define INCLUDED_PKMN_PKSAV_ENUM_MAPS_HPP

#include <pkmn/enums/condition.hpp>
#include <pkmn/enums/gender.hpp>
#include <pkmn/enums/language.hpp>
#include <pkmn/enums/nature.hpp>
#include <pkmn/enums/stat.hpp>
#include <pkmn/enums/type.hpp>

#include <pksav/gen1/options.h>
#include <pksav/gen1/pokemon.h>
#include <pksav/gen1/type.h>

#include <pksav/gen2/mom_money_policy.h>
#include <pksav/gen2/options.h>
#include <pksav/gen2/save.h>

#include <pksav/gba/box_wallpaper.h>
#include <pksav/gba/language.h>
#include <pksav/gba/options.h>
#include <pksav/gba/ribbons.h>

#include <pksav/common/condition.h>
#include <pksav/common/nature.h>
#include <pksav/common/stats.h>

#include <boost/assign.hpp>
#include <boost/bimap.hpp>

#include <string>

namespace pksav
{
    // Stats
    using gb_IV_bimap_t = boost::bimap<pkmn::e_stat, enum pksav_gb_IV>;
    using IV_bimap_t = boost::bimap<pkmn::e_stat, enum pksav_IV>;

    const gb_IV_bimap_t& get_gb_IV_bimap();
    const IV_bimap_t& get_IV_bimap();

    // Genders
    using gen2_gender_bimap_t = boost::bimap<pkmn::e_gender, enum pksav_gen2_gender>;

    const gen2_gender_bimap_t& get_gen2_gender_bimap();

    // Options
    using gen1_rb_text_speed_bimap_t = boost::bimap<std::string, enum pksav_gen1_rb_text_speed>;
    using gen1_yellow_sound_option_bimap_t = boost::bimap<std::string, enum pksav_gen1_yellow_sound_option>;
    using gen2_text_speed_bimap_t = boost::bimap<std::string, enum pksav_gen2_text_speed>;
    using gen2_gbprinter_brightness_bimap_t = boost::bimap<std::string, enum pksav_gen2_gbprinter_brightness>;
    using gba_rse_button_mode_bimap_t = boost::bimap<std::string, enum pksav_gba_rse_button_mode>;
    using gba_frlg_button_mode_bimap_t = boost::bimap<std::string, enum pksav_gba_frlg_button_mode>;
    using gba_text_speed_bimap_t = boost::bimap<std::string, enum pksav_gba_text_speed>;

    const gen1_rb_text_speed_bimap_t& get_gen1_rb_text_speed_bimap();
    const gen1_yellow_sound_option_bimap_t& get_gen1_yellow_sound_option_bimap();

    const gen2_text_speed_bimap_t& get_gen2_text_speed_bimap();
    const gen2_gbprinter_brightness_bimap_t& get_gen2_gbprinter_brightness_bimap();

    const gba_rse_button_mode_bimap_t& get_gba_rse_button_mode_bimap();
    const gba_frlg_button_mode_bimap_t& get_gba_frlg_button_mode_bimap();
    const gba_text_speed_bimap_t& get_gba_text_speed_bimap();

    // Status conditions
    using gb_condition_bimap_t = boost::bimap<pkmn::e_condition, enum pksav_gb_condition>;
    using condition_mask_bimap_t = boost::bimap<pkmn::e_condition, enum pksav_condition_mask>;

    const gb_condition_bimap_t& get_gb_condition_bimap();
    const condition_mask_bimap_t& get_condition_mask_bimap();

    // Box wallpapers
    using gba_box_wallpaper_bimap_t = boost::bimap<std::string, enum pksav_gba_box_wallpaper>;
    using gba_rse_box_wallpaper_bimap_t = boost::bimap<std::string, enum pksav_gba_rse_box_wallpaper>;
    using gba_frlg_box_wallpaper_bimap_t = boost::bimap<std::string, enum pksav_gba_frlg_box_wallpaper>;

    const gba_box_wallpaper_bimap_t& get_gba_box_wallpaper_bimap();
    const gba_rse_box_wallpaper_bimap_t& get_gba_rse_box_wallpaper_bimap();
    const gba_frlg_box_wallpaper_bimap_t& get_gba_frlg_box_wallpaper_bimap();

    // Ribbons
    using gba_ribbon_mask_bimap_t = boost::bimap<std::string, enum pksav_gba_ribbon_mask>;
    using gba_contest_ribbon_level_bimap_t = boost::bimap<std::string, enum pksav_gba_contest_ribbon_level>;
    using gba_contest_ribbon_mask_bimap_t = boost::bimap<std::string, enum pksav_gba_contest_ribbons_mask>;
    using gba_contest_ribbon_offset_bimap_t = boost::bimap<std::string, enum pksav_gba_contest_ribbons_offset>;

    const gba_ribbon_mask_bimap_t& get_gba_ribbon_mask_bimap();
    const gba_contest_ribbon_level_bimap_t& get_gba_contest_ribbon_level_bimap();
    const gba_contest_ribbon_mask_bimap_t& get_gba_contest_ribbon_mask_bimap();
    const gba_contest_ribbon_offset_bimap_t& get_gba_contest_ribbon_offset_bimap();

    // Misc
    using gen1_type_bimap_t = boost::bimap<pkmn::e_type, enum pksav_gen1_type>;
    using gen2_mom_money_policy_bimap_t = boost::bimap<std::string, enum pksav_gen2_mom_money_policy>;
    using gba_language_bimap_t = boost::bimap<pkmn::e_language, enum pksav_gba_language>;
    using nature_bimap_t = boost::bimap<pkmn::e_nature, enum pksav_nature>;

    const gen1_type_bimap_t& get_gen1_type_bimap();
    const gen2_mom_money_policy_bimap_t& get_gen2_mom_money_policy_bimap();
    const gba_language_bimap_t& get_gba_language_bimap();
    const nature_bimap_t& get_nature_bimap();
}

#endif /* INCLUDED_PKMN_PKSAV_ENUM_MAPS_HPP */
