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
 * This class handles communication between modules
 */
class ModuleMediator {

public:

	ModuleMediator();
	virtual ~ModuleMediator();

	void set_map(Map *map);

	/*
	 * ----- Module setters -----
	 */
	void set_autopilot_module(AutopilotModule *autopilot);

	void set_hazard_warning_module(HazardWarningModule *hazard_module);

	void set_routing_module(RoutingModule *routing_module);

	void set_vehicle_sensor_module(VehicleSensorModule *vehicle_sensor_module);

	/*
	 * ----- vehicle sensor interface -----
	 */
	Speed get_speed_from_route();

	void set_sensor_speed(Speed &s);

	Position get_new_position_from_route(Distance &dist);

	void set_sensor_position(Position &p);

	Heading get_heading_from_route();

	void set_sensor_heading(Heading &h);

	std::string sensor_to_string();

	/*
	 * ----- Hazard interface -----
	 */
	bool is_known_relevant_hazards(Position &pos, Heading &hdng);

	Speed get_safe_hazard_speed(Position &pos, Heading &hdng);

	void save_hazard(Hazard &h);

	HazardMessage create_hazard_message(Hazard &h);

	/*
	 * ----- Routing interface -----
	 */
	bool is_new_imminent_hazard();

	Hazard get_imminent_hazard();

private:

	Map *_map;
	AutopilotModule *_autopilot;
	HazardWarningModule *_hazard_module;
	RoutingModule *_routing_module;
	VehicleSensorModule *_vehicle_sensor_module;

};

#endif /* MODULEMEDIATOR_H_ */
