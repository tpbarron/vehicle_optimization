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
	//pass reference of every module to mediator
	_mediator.set_autopilot_module(&_autopilot);
	_mediator.set_hazard_warning_module(&_hazard_module);
	_mediator.set_mesg_handler_module(&_mesg_handler);
	_mediator.set_routing_module(&_routing_module);
	_mediator.set_vehicle_sensor_module(&_vehicle_sensor_module);

	//pass reference of mediator to each module
	_autopilot.set_mediator(&_mediator);
	_hazard_module.set_mediator(&_mediator);
	_mesg_handler.set_mediator(&_mediator);
	_routing_module.set_mediator(&_mediator);
	_vehicle_sensor_module.set_mediator(&_mediator);
}

/**
 * It is possible to get the start position from the routing module for the
 * sensor init here because the start and goal positions are set BEFORE
 * this initialization, which is called just before starting.
 */
void ModuleManager::init_sensor(std::string uuid) {
	_vehicle_sensor_module.set_vehicle_uuid(uuid);
	_vehicle_sensor_module.init(_routing_module.get_start_position());
}

void ModuleManager::generate_route() {
	_routing_module.generate_route();
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

void ModuleManager::set_goal_position(const Position& goal_position) {
	_routing_module.set_goal_position(goal_position);
}

void ModuleManager::set_map(const Map& map) {
	_routing_module.set_map(map);
}

void ModuleManager::set_start_position(const Position& start_position) {
	_routing_module.set_start_position(start_position);
}

Position ModuleManager::get_current_position() const {
	return _vehicle_sensor_module.get_position();
}


