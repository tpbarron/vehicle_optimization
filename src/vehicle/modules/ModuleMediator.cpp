/**
 * ModuleMediator.cpp
 *	
 *  Created on: Nov 10, 2014
 *      Author: trevor
 */

#include <vehicle/modules/ModuleMediator.h>

ModuleMediator::ModuleMediator() :
	_autopilot(nullptr),
	_hazard_module(nullptr),
	_routing_module(nullptr),
	_vehicle_sensor_module(nullptr) {
}

ModuleMediator::~ModuleMediator() {
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

