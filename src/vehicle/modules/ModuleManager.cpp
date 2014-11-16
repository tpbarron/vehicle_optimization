/**
 * ModuleManager.cpp
 *	
 *  Created on: Oct 20, 2014
 *      Author: trevor
 */

#include "ModuleManager.h"

ModuleManager::ModuleManager() :
	_manager_strand(_manager_io),
	_autopilot(_manager_strand),
	_vehicle_sensor_module(_manager_strand) {
}

ModuleManager::~ModuleManager() {
}

void ModuleManager::start() {
	std::cout << "Starting ModuleManager" << std::endl;
	_vehicle_sensor_module.start();
	_autopilot.start();
	_manager_io.run();
}

void ModuleManager::stop() {
	_vehicle_sensor_module.stop();
	_autopilot.stop();
}

void ModuleManager::init(std::string uuid) {
	init_mediator();
	init_sensor(uuid);
}

/**
 * Hook up the ModuleMediator for inter module communication.
 * This needs to be updated every time a module is added.
 */
void ModuleManager::init_mediator() {
	//give mediator map reference
	_mediator.set_map(&_map);

	//pass reference of every module to mediator
	_mediator.set_autopilot_module(&_autopilot);
	_mediator.set_hazard_warning_module(&_hazard_module);
	_mediator.set_routing_module(&_routing_module);
	_mediator.set_vehicle_sensor_module(&_vehicle_sensor_module);

	//pass reference of mediator to each module
	_autopilot.set_mediator(&_mediator);
	_hazard_module.set_mediator(&_mediator);
	_routing_module.set_mediator(&_mediator);
	_vehicle_sensor_module.set_mediator(&_mediator);
}

void ModuleManager::init_sensor(std::string uuid) {
	_vehicle_sensor_module.set_vehicle_uuid(uuid);
	_vehicle_sensor_module.init(_start_position);
}

void ModuleManager::generate_route() {
	_routing_module.generate_route(_map, _start_position, _goal_position);
}


void ModuleManager::add_listener(IVehicleDataListener &l) {
	_listeners.insert(&l);
}

void ModuleManager::recv(Message &msg) {
	if (msg.get_type() == message_types::TYPE_HAZARD_WARNING) {
		std::cout << "Module Manager received hazard warning message";
		_hazard_module.handle(msg);
	} else if (msg.get_type() == message_types::TYPE_EMERGENCY_VEHICLE) {
		std::cout << "Module Manager received emergency vehicle message";
	}
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

Position ModuleManager::get_current_position() const {
	return _routing_module.get_current_position();
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

