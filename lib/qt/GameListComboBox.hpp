/*
 * Copyright (c) 2016 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef PKMN_QT_GAMELISTCOMBOBOX_HPP
#define PKMN_QT_GAMELISTCOMBOBOX_HPP

#include <pkmn/config.hpp>

#ifdef PKMN_QT4
#include <QtGui/QComboBox>
#else
#include <QComboBox>
#endif

namespace pkmn { namespace qt {

    /*!
     * @brief A ComboBox populated with a list, sorted by version group, of games
     *        in (or up to) the given generation.
     */
    class PKMN_API GameListComboBox: public QComboBox {
        Q_OBJECT

        public:
            /*!
             * @brief Constructor.
             *
             * \param generation which generation
             * \param includePrevious include games from earlier generations
             * \param parent parent widget
             * \throws pkmn::range_error if generation is not [1-6]
             */
            GameListComboBox(
                int generation,
                bool includePrevious,
                QWidget* parent
            );

        signals:

        public slots:
    };

}}

#endif /* PKMN_QT_GAMELISTCOMBOBOX_HPP */