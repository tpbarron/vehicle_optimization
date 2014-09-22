/*
 * GUI.cpp
 *
 *  Created on: Sep 19, 2014
 *      Author: trevor
 */

#include "GUI.h"

#include <iostream>

namespace GUI {

Glib::RefPtr<Gtk::Builder> builder;
Gtk::Button* start_button;
Gtk::Button* restart_button;
Gtk::ComboBoxText* scenario_combobox;

bool running = false;

void init(int argc, char* argv[]) {
	Gtk::Main kit(argc, argv);

	builder = Gtk::Builder::create_from_file("resources/gui/gui-basic.glade");

	Gtk::Window* window;
	builder->get_widget("window1", window);
    builder->get_widget("button2", start_button);
    builder->get_widget("button1", restart_button);
    builder->get_widget("comboboxtext1", scenario_combobox);

    restart_button->set_sensitive(false);
    init_scenario_combobox();

    start_button->signal_clicked().connect(sigc::ptr_fun(&GUI::start_button_clicked));
    running = false;

	Gtk::Main::run(*window);
}

void init_scenario_combobox() {
	scenario_combobox->append("simple1");
	scenario_combobox->append("Scenario 1");
	scenario_combobox->append("Scenario 2");
	scenario_combobox->append("Scenario 3");
	scenario_combobox->set_active(0);
}

void start_button_clicked() {
	if (!running) {
		start_button->set_label("Stop");
		std::string scenario = scenario_combobox->get_active_text();
		std::string path = Utils::get_scenario_file_path(scenario);
		//TODO: do this in background thread so GUI doesn't lag
		Scenario::init();
		Scenario::load_scenario(path);
		Scenario::start();
		running = true;
	} else {
		//stop here, interrupt
		Scenario::stop();
		Scenario::cleanup();
		start_button->set_sensitive(false);
		restart_button->set_sensitive(true);
	}

}

//void restart_button_clicked() {
//	std::cout << "toggled" << std::endl;
//	Scenario s;
//	s.load_scenario("data/simple1.json");
//	s.start();
//	s.stop();
//}

}
