/*
 * GUI.h
 *
 *  Created on: Sep 19, 2014
 *      Author: trevor
 */

#ifndef GUI_H_
#define GUI_H_

#include <gtkmm/button.h>
#include <gtkmm/builder.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/window.h>
#include <gtkmm/main.h>

#include "graphics/gui/MapDrawingArea.h"
#include "sim/Scenario.h"
#include "utils/Utils.h"

namespace GUI {

void init(int argc, char* argv[]);

void init_scenario_combobox();
void start_button_clicked();
void test_cairo();

extern Glib::RefPtr<Gtk::Builder> builder;
extern Gtk::Button* start_button;
extern Gtk::Button* restart_button;
extern Gtk::ComboBoxText* scenario_combobox;
extern MapDrawingArea* map_area;

extern bool running;

};

#endif /* GUI_H_ */
