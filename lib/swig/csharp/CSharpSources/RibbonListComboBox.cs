/*
 * Copyright (c) 2016-2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
namespace PKMN.WinForms {

    public class RibbonListComboBox: System.Windows.Forms.ComboBox {
        public RibbonListComboBox(int generation) {
            StringList ribbons = Database.Lists.RibbonList(generation);
            foreach(string ribbon in ribbons) {
                this.Items.Add(ribbon);
            }
        }
    }

}
