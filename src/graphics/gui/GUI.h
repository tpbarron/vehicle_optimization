/*
 * GUI.h
 *
 *  Created on: Sep 19, 2014
 *      Author: trevor
 */

#ifndef GUI_H_
#define GUI_H_

#include <gtkmm.h>

#include "sim/Scenario.h"
#include "utils/Utils.h"

namespace GUI {

void init(int argc, char* argv[]);

void init_scenario_combobox();
void start_button_clicked();

extern Glib::RefPtr<Gtk::Builder> builder;
extern Gtk::Button* start_button;
extern Gtk::Button* restart_button;
extern Gtk::ComboBoxText* scenario_combobox;

extern bool running;

};

#endif /* GUI_H_ */
