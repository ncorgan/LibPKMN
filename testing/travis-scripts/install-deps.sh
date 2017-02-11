#!/bin/bash
#
# Copyright (c) 2016-2017 Nicholas Corgan (n.corgan@gmail.com)
#
# Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
# or copy at http://opensource.org/licenses/MIT)
#

REPO_TOPLEVEL=$PWD

sudo apt-get -y update
[ $? -ne 0 ] && exit 1
sudo apt-get -y install build-essential cmake clang cppcheck valgrind \
		    doxygen libpython-dev python-ply libboost1.55-all-dev \
		    swig python-pip libqt4-dev qtbase5-dev mono-complete \
		    swig3.0 python-pip libqt4-dev qtbase5-dev liblua5.1-dev \
		    luarocks mono-complete monodevelop-nunit nunit-console
[ $? -ne 0 ] && exit 1
sudo pip install CppHeaderParser
[ $? -ne 0 ] && exit 1
sudo luarocks install luaunit
[ $? -ne 0 ] && exit 1

echo # So we can check the last error code
