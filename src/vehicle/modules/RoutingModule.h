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
#include "map/routing/Route.h"

/**
 *
 */
class RoutingModule {

public:
	RoutingModule();
	virtual ~RoutingModule();

	void generate_route(Map& map, Position& start, Position& goal);

	Speed get_current_speed_limit(Map& map);
	Position get_new_position(Map& map,Distance& d);
	Heading get_current_heading();

	bool imminent_hazard(Map& map);
	const Hazard& get_imminent_hazard(Map& map);

private:

	Route _route;

};

#endif /* ROUTINGMODULE_H_ */
