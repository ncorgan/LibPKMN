/*
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

%module "PKMN::BuildInfo"

%include <ruby/ruby_init.i>
PKMN_RUBY_INIT

%include <std_string.i>

%{
    #include <pkmn/build_info.hpp>

    static const std::string BOOST_VERSION = pkmn::build_info::get_boost_version();
    static const std::string LIBPKMGC_VERSION = pkmn::build_info::get_libpkmgc_version();
    static const std::string PKSAV_VERSION = pkmn::build_info::get_pksav_version();
    static const std::string QT_VERSION = pkmn::build_info::get_qt_version();
    static const std::string SQLITE3_VERSION = pkmn::build_info::get_sqlite3_version();
    static const std::string SQLITECPP_VERSION = pkmn::build_info::get_sqlitecpp_version();
%}

%constant std::string BOOST_VERSION;
%constant std::string LIBPKMGC_VERSION;
%constant std::string PKSAV_VERSION;
%constant std::string QT_VERSION;
%constant std::string SQLITE3_VERSION;
%constant std::string SQLITECPP_VERSION;
