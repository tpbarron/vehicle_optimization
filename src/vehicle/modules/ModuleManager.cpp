/**
 * ModuleManager.cpp
 *	
 *  Created on: Oct 20, 2014
 *      Author: trevor
 */

#include "ModuleManager.h"

ModuleManager::ModuleManager() {
	// TODO Auto-generated constructor stub

}

ModuleManager::~ModuleManager() {
	// TODO Auto-generated destructor stub
}

void ModuleManager::generate_route() {
	_routing_module.generate_route(_map, _start_position, _goal_position);
}

const Position& ModuleManager::get_goal_position() const {
	return _goal_position;
}

void ModuleManager::set_goal_position(const Position& goal_position) {
	_goal_position = goal_position;
}

const Map& ModuleManager::get_map() const {
	return _map;
}

void ModuleManager::set_map(const Map& map) {
	_map = map;
}

const Position& ModuleManager::get_start_position() const {
	return _start_position;
}

void ModuleManager::set_start_position(const Position& start_position) {
	_start_position = start_position;
}

Speed ModuleManager::get_current_speed() {
	Speed limit = _routing_module.get_current_speed_limit(_map);

	//Check hazards
	//If there is an imminent hazard, we have run into something that
	//we didn't already know about
	if (_routing_module.imminent_hazard(_map)) {
		Hazard h = _routing_module.get_imminent_hazard(_map);
		if (!_hazard_module.is_known_hazard(h)) {
			_hazard_module.add_hazard(h);
		}
	}
	//For each known hazard ordered by closest,
	//respond as necessary, if necessary

	return limit;
}

Position ModuleManager::get_new_position(Distance& d) {
	return _routing_module.get_new_position(_map, d);
}

Heading ModuleManager::get_current_heading() {
	return _routing_module.get_current_heading();
}

/**
 * The modules are updated at every self update
 */
void ModuleManager::update_modules() {
	//Update module
	_hazard_module.update();
}
