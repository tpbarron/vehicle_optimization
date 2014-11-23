/**
 * ModuleMediator.cpp
 *	
 *  Created on: Nov 10, 2014
 *      Author: trevor
 */

#include "ModuleMediator.h"

ModuleMediator::ModuleMediator() :
	_autopilot(nullptr),
	_hazard_module(nullptr),
	_mesg_handler(nullptr),
	_routing_module(nullptr),
	_vehicle_sensor_module(nullptr) {
}

ModuleMediator::~ModuleMediator() {
}


/*
 *
 * ----- Module setters -----
 *
 */
void ModuleMediator::set_autopilot_module(AutopilotModule *autopilot) {
	_autopilot = autopilot;
}

void ModuleMediator::set_hazard_warning_module(HazardWarningModule *hazard_module) {
	_hazard_module = hazard_module;
}

void ModuleMediator::set_mesg_handler_module(MesgHandlerModule *mesg_handler) {
	_mesg_handler = mesg_handler;
}

void ModuleMediator::set_routing_module(RoutingModule *routing_module) {
	_routing_module = routing_module;
}

void ModuleMediator::set_vehicle_sensor_module(VehicleSensorModule *vehicle_sensor_module) {
	_vehicle_sensor_module = vehicle_sensor_module;
}


/*
 *
 * ----- vehicle sensor interface -----
 *
 */

const Speed ModuleMediator::get_speed_from_route() const {
	return _routing_module->get_current_speed_limit();
}

void ModuleMediator::set_sensor_speed(Speed &s) {
	_vehicle_sensor_module->set_speed(s);
}

Position ModuleMediator::get_new_position_from_route(Distance &dist) {
	return _routing_module->get_new_position(dist);
}

const Position& ModuleMediator::get_sensor_position() const {
	return _vehicle_sensor_module->get_position();
}

void ModuleMediator::set_sensor_position(Position &p) {
	_vehicle_sensor_module->set_position(p);
}

const Heading ModuleMediator::get_heading_from_route() const {
	return _routing_module->get_current_heading();
}

void ModuleMediator::set_sensor_heading(Heading &h) {
	_vehicle_sensor_module->set_heading(h);
}

const std::string ModuleMediator::sensor_to_string() const {
	return _vehicle_sensor_module->to_string();
}


/*
 *
 * ----- Hazard interface -----
 *
 */

/**
 * @return true if the HazardModule knows about relevant Hazards near the given
 * position going in the given heading.
 *
 * TODO: like the imminent hazard method, just convert this to return a vector
 * of known hazards that could be of size 0
 */
bool ModuleMediator::is_known_relevant_hazards(Position &pos, Heading &hdng) {
	return _hazard_module->is_known_relevant_hazards(pos, hdng);
}

Speed ModuleMediator::get_safe_hazard_speed(Position &pos, Heading &hdng) {
//	return _hazard_module->get_safe_speed(pos, hdng);
}

/**
 * Saves an imminent hazard on the road to the HazardModule
 */
void ModuleMediator::save_hazard(Hazard &h) {
	_hazard_module->add_hazard(h);
}

/**
 * Asks the HazardModule to build a HazardMessage given a Hazard
 */
HazardMessage ModuleMediator::create_hazard_message(Hazard &h) {
	return _hazard_module->create_message(h);
}


/*
 * ----- Routing interface -----
 */

/**
 * Returns true if there is an imminent hazard that is not already known about
 *
 * NOTE: Do NOT use this unless all you need to know if whether there is something
 * new. If you need to get them just call get_imminent_hazards to avoid repeat
 * calculations.
 */
bool ModuleMediator::is_new_imminent_hazard() {
	if (_routing_module->imminent_hazard()) {
		std::vector<Hazard> imminents = _routing_module->get_imminent_hazards();
		for (std::vector<Hazard>::iterator itr = imminents.begin(); itr != imminents.end(); ++itr) {
			if (!_hazard_module->is_known_hazard(*itr)) {
				return true;
			}
		}
	}
	return false;
}

/**
 * Returns all imminent hazards
 */
std::vector<Hazard> ModuleMediator::get_imminent_hazards() {
	return _routing_module->get_imminent_hazards();
}

/**
 * Returns all imminent hazards that the hazard module does not already know
 * about.
 */
std::vector<Hazard> ModuleMediator::get_new_imminent_hazards() {
	std::vector<Hazard> new_imminents;

	std::vector<Hazard> imminents = _routing_module->get_imminent_hazards();
	for (std::vector<Hazard>::iterator itr = imminents.begin(); itr != imminents.end(); ++itr) {
		if (!_hazard_module->is_known_hazard(*itr)) {
			new_imminents.push_back(*itr);
		}
	}

	return new_imminents;
}
