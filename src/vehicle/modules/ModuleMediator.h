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
class MesgHandlerModule;
class RoutingModule;
class VehicleSensorModule;

#include "map/Map.h"
#include "AutopilotModule.h"
#include "HazardWarningModule.h"
#include "MesgHandlerModule.h"
#include "RoutingModule.h"
#include "VehicleSensorModule.h"


/**
 * This class handles communication between modules
 */
class ModuleMediator {

public:

	ModuleMediator();

	virtual ~ModuleMediator();


	/*
	 * ----- Module setters -----
	 */

	void set_autopilot_module(AutopilotModule *autopilot);

	void set_hazard_warning_module(HazardWarningModule *hazard_module);

	void set_mesg_handler_module(MesgHandlerModule *mesg_handler);

	void set_routing_module(RoutingModule *routing_module);

	void set_vehicle_sensor_module(VehicleSensorModule *vehicle_sensor_module);


	/*
	 * ----- vehicle sensor interface -----
	 */

	const Speed get_speed_from_route() const;

	void set_sensor_speed(Speed &s);

	Position get_new_position_from_route(Distance &dist);

	const Position& get_sensor_position() const;

	void set_sensor_position(Position &p);

	const Heading get_heading_from_route() const;

	void set_sensor_heading(Heading &h);

	const std::string sensor_to_string() const;


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

	std::vector<Hazard> get_imminent_hazards();

	std::vector<Hazard> get_new_imminent_hazards();

	/*
	 * ----- Mesg Handler interface
	 */

	void send_messages(std::vector<Message> messages);

private:

	/*
	 * Module pointers
	 */
	AutopilotModule *_autopilot;
	HazardWarningModule *_hazard_module;
	MesgHandlerModule *_mesg_handler;
	RoutingModule *_routing_module;
	VehicleSensorModule *_vehicle_sensor_module;

};

#endif /* MODULEMEDIATOR_H_ */
