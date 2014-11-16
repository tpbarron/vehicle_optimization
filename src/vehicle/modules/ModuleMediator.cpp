/**
 * ModuleMediator.cpp
 *	
 *  Created on: Nov 10, 2014
 *      Author: trevor
 */

#include "ModuleMediator.h"

ModuleMediator::ModuleMediator() :
	_map(nullptr),
	_autopilot(nullptr),
	_hazard_module(nullptr),
	_routing_module(nullptr),
	_vehicle_sensor_module(nullptr) {
}

ModuleMediator::~ModuleMediator() {
}

void ModuleMediator::set_map(Map *map) {
	_map = map;
}

void ModuleMediator::set_autopilot_module(AutopilotModule *autopilot) {
	_autopilot = autopilot;
}

void ModuleMediator::set_hazard_warning_module(HazardWarningModule *hazard_module) {
	_hazard_module = hazard_module;
}

void ModuleMediator::set_routing_module(RoutingModule *routing_module) {
	_routing_module = routing_module;
}

void ModuleMediator::set_vehicle_sensor_module(VehicleSensorModule *vehicle_sensor_module) {
	_vehicle_sensor_module = vehicle_sensor_module;
}


Speed ModuleMediator::get_speed_from_route() {
	return _routing_module->get_current_speed_limit(*_map);
}

void ModuleMediator::set_sensor_speed(Speed &s) {
	_vehicle_sensor_module->set_speed(s);
}

Position ModuleMediator::get_new_position_from_route(Distance &dist) {
	return _routing_module->get_new_position(*_map, dist);
}

void ModuleMediator::set_sensor_position(Position &p) {
	_vehicle_sensor_module->set_position(p);
}

Heading ModuleMediator::get_heading_from_route() {
	return _routing_module->get_current_heading();
}

void ModuleMediator::set_sensor_heading(Heading &h) {
	_vehicle_sensor_module->set_heading(h);
}

std::string ModuleMediator::sensor_to_string() {
	return _vehicle_sensor_module->to_string();
}
