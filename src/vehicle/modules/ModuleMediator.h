/**
 * ModuleMediator.h
 *	
 *  Created on: Nov 10, 2014
 *      Author: trevor
 */

#ifndef MODULEMEDIATOR_H_
#define MODULEMEDIATOR_H_

#include "data_types/sensor_types/Speed.h"


class Map;
class AutopilotModule;
class HazardWarningModule;
class RoutingModule;
class VehicleSensorModule;

#include "map/Map.h"
#include "AutopilotModule.h"
#include "HazardWarningModule.h"
#include "RoutingModule.h"
#include "VehicleSensorModule.h"


/**
 *
 */
class ModuleMediator {

public:

	ModuleMediator();
	virtual ~ModuleMediator();

	void set_map(Map *map);
	void set_autopilot_module(AutopilotModule *autopilot);
	void set_hazard_warning_module(HazardWarningModule *hazard_module);
	void set_routing_module(RoutingModule *routing_module);
	void set_vehicle_sensor_module(VehicleSensorModule *vehicle_sensor_module);

	Speed get_speed_from_route();
	void set_sensor_speed(Speed &s);

	Position get_new_position_from_route(Distance &dist);
	void set_sensor_position(Position &p);

	Heading get_heading_from_route();
	void set_sensor_heading(Heading &h);

	std::string sensor_to_string();

private:

	Map *_map;
	AutopilotModule *_autopilot;
	HazardWarningModule *_hazard_module;
	RoutingModule *_routing_module;
	VehicleSensorModule *_vehicle_sensor_module;

};

#endif /* MODULEMEDIATOR_H_ */
