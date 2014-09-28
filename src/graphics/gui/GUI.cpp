/*
 * GUI.cpp
 *
 *  Created on: Sep 19, 2014
 *      Author: trevor
 */

#include "GUI.h"

#include <iostream>

namespace GUI {

Glib::RefPtr<Gtk::Builder> _builder;
Gtk::Button* _start_button;
Gtk::Button* _restart_button;
Gtk::ComboBoxText* _scenario_combobox;
MapDrawingArea* _map_area;
bool _running = false;

void init(int argc, char* argv[]) {
	Gtk::Main kit(argc, argv);

	_builder = Gtk::Builder::create_from_file("resources/gui/gui-basic.glade");

	Gtk::Window* window;
	_builder->get_widget("window1", window);
    _builder->get_widget("button2", _start_button);
    _builder->get_widget("button1", _restart_button);
    _builder->get_widget("comboboxtext1", _scenario_combobox);
    _builder->get_widget_derived("drawingarea1", _map_area);

    _restart_button->set_sensitive(false);
    init_scenario_combobox();

    _start_button->signal_clicked().connect(sigc::ptr_fun(&GUI::start_button_clicked));
    _running = false;

	Gtk::Main::run(*window);
}

void cleanup() {
	delete _start_button;
	delete _restart_button;
	delete _scenario_combobox;
	delete _map_area;
}

void init_scenario_combobox() {
	_scenario_combobox->append("simple1");
	_scenario_combobox->append("Scenario1");
	_scenario_combobox->append("Scenario2");
	_scenario_combobox->append("Scenario3");
	_scenario_combobox->set_active(0);
}

void start_button_clicked() {
	if (!_running) {
		_start_button->set_label("Stop");
		std::string scenario = _scenario_combobox->get_active_text();
		//TODO: do this in background thread so GUI doesn't lag
		Scenario::init();
		Scenario::load_scenario(scenario);
		Scenario::start();
		_running = true;
	} else {
		//stop here, interrupt
		Scenario::stop();
		Scenario::cleanup();
		_start_button->set_sensitive(false);
		_restart_button->set_sensitive(true);
	}

}

void test_cairo() {
}
//void restart_button_clicked() {
//	std::cout << "toggled" << std::endl;
//	Scenario s;
//	s.load_scenario("data/simple1.json");
//	s.start();
//	s.stop();
//}

}
