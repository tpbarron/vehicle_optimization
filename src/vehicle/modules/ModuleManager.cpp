/**
 * ModuleManager.cpp
 *	
 *  Created on: Oct 20, 2014
 *      Author: trevor
 */

#include "ModuleManager.h"

#include "utils/Logger.h"

ModuleManager::ModuleManager() {
}

ModuleManager::~ModuleManager() {
}


void ModuleManager::start() {
	Logger::info("Starting ModuleManager");

	_autopilot.start();
	_mesg_handler.start();
	_vehicle_sensor_module.start();
}

void ModuleManager::stop() {
	_autopilot.stop();
	_mesg_handler.stop();
	_vehicle_sensor_module.stop();
}

void ModuleManager::init(std::string uuid) {
	Logger::info("Initializing ModuleManager");
	init_mediator(uuid);
	init_sensor(uuid);
}

/**
 * Hook up the ModuleMediator for inter module communication.
 * This needs to be updated every time a module is added.
 */
void ModuleManager::init_mediator(std::string uuid) {
	//Give mediator uuid so that modules have access
	_mediator.set_uuid(uuid);

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
	Logger::info("Generating Route");
	_routing_module.generate_route();
}


void ModuleManager::add_listener(IVehicleDataListener &l) {
	_mesg_handler.add_listener(l);
}

void ModuleManager::remove_listener(IVehicleDataListener &l) {
	_mesg_handler.remove_listener(l);
}

void ModuleManager::recv(Message *mesg) {
	Logger::info("ModuleManager received Message");
	if (mesg->get_type() == message_types::TYPE_HAZARD_WARNING) {
		Logger::info("ModuleManager received HazardMessage");
		HazardMessage* hazard_mesg = dynamic_cast<HazardMessage*>(mesg);
		_hazard_module.handle(hazard_mesg);
	} else if (mesg->get_type() == message_types::TYPE_EMERGENCY_VEHICLE) {
		Logger::info("ModuleManager received emergency vehicle message");
	}
}

void ModuleManager::set_start_position(const Position& start_position) {
	_routing_module.set_start_position(start_position);
}

void ModuleManager::set_goal_position(const Position& goal_position) {
	_routing_module.set_goal_position(goal_position);
}

void ModuleManager::set_map(const Map& map) {
	_routing_module.set_map(map);
}

const Position& ModuleManager::get_current_position() const {
	return _vehicle_sensor_module.get_position();
}


