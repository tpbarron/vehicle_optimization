/**
 * ModuleManager.h
 *	
 *  Created on: Oct 20, 2014
 *      Author: trevor
 */

#ifndef MODULEMANAGER_H_
#define MODULEMANAGER_H_

#include <unordered_set>

#include "data_types/message_types/Message.h"
#include "data_types/message_types/MessageTypes.h"

#include "data_types/sensor_types/Distance.h"
#include "data_types/sensor_types/Heading.h"
#include "data_types/sensor_types/Position.h"

#include "map/Map.h"
#include "ModuleMediator.h"
#include "AutopilotModule.h"
#include "HazardWarningModule.h"
#include "MesgHandlerModule.h"
#include "RoutingModule.h"
#include "VehicleSensorModule.h"
#include "vehicle/IVehicleDataListener.h"

#include "utils/Utils.h"


/**
 * The ModuleManager encapsulates all of the Vehicle modules. It contains
 * a Mediator which manages communication between modules and handles incoming
 * messages and sends out messages.
 */
class ModuleManager {

public:
	ModuleManager();
	virtual ~ModuleManager();

	void start();
	void stop();

	void init(std::string uuid);
	void init_mediator();
	void init_sensor(std::string uuid);
	void generate_route();

	void add_listener(IVehicleDataListener &l);
	void remove_listener(IVehicleDataListener &l);

	void recv(Message &msg);

	void set_start_position(const Position& start_position);
	void set_goal_position(const Position& goal_position);
	void set_map(const Map& map);

	Position get_current_position() const;

private:

	ModuleMediator _mediator;

	AutopilotModule _autopilot;
	HazardWarningModule _hazard_module;
	MesgHandlerModule _mesg_handler;
	RoutingModule _routing_module;
	VehicleSensorModule _vehicle_sensor_module;

};

#endif /* MODULEMANAGER_H_ */
