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
#include "RoutingModule.h"
#include "VehicleSensorModule.h"
#include "vehicle/IVehicleDataListener.h"

/**
 *
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
	void recv(Message &msg);

	const Position& get_goal_position() const;
	void set_goal_position(const Position& goal_position);

	const Map& get_map() const;
	void set_map(const Map& map);

	const Position& get_start_position() const;
	void set_start_position(const Position& start_position);

	Speed get_current_speed();
	Position get_current_position() const;
	Position get_new_position(Distance& d);
	Heading get_current_heading();

	void update_modules();

	std::string sensor_to_string();

private:

	Map _map;
	Position _start_position;
	Position _goal_position;

	ModuleMediator _mediator;

	AutopilotModule _autopilot;
	HazardWarningModule _hazard_module;
	RoutingModule _routing_module;
	VehicleSensorModule _vehicle_sensor_module;

	struct VehicleHash {
	    size_t operator()(IVehicleDataListener *v) const
	    {
	        return std::hash<std::string>()(v->to_string());
	    }
	};

	std::unordered_set<IVehicleDataListener*, VehicleHash> _listeners;

};

#endif /* MODULEMANAGER_H_ */
