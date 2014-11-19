/**
 * RoutingModule.h
 *	
 *  Created on: Oct 20, 2014
 *      Author: trevor
 */

#ifndef ROUTINGMODULE_H_
#define ROUTINGMODULE_H_

#include "data_types/sensor_types/Distance.h"
#include "data_types/sensor_types/Heading.h"
#include "data_types/sensor_types/Position.h"
#include "data_types/sensor_types/Speed.h"
#include "map/Map.h"
#include "vehicle/modules/routing/Route.h"


class ModuleMediator;

/**
 *
 */
class RoutingModule {

public:
	RoutingModule();
	virtual ~RoutingModule();

	void set_mediator(ModuleMediator *mediator);

	void set_map(const Map& map);
	void set_start_position(const Position& start);
	void set_goal_position(const Position& goal);

	const Position& get_start_position() const;

	void generate_route();

	Speed get_current_speed_limit();
	Position get_current_position() const;
	Position get_new_position(Distance& d);
	Heading get_current_heading();

	bool imminent_hazard();
	Hazard get_imminent_hazard();

private:

	ModuleMediator *_mediator;

	Route _route;
	Map _map;
	Position _start;
	Position _goal;

};

#endif /* ROUTINGMODULE_H_ */
