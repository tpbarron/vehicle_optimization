/**
 * RoutingModule.cpp
 *	
 *  Created on: Oct 20, 2014
 *      Author: trevor
 */

#include "RoutingModule.h"

RoutingModule::RoutingModule() {
	// TODO Auto-generated constructor stub

}

RoutingModule::~RoutingModule() {
	// TODO Auto-generated destructor stub
}

void RoutingModule::generate_route(Map& map, Position& start, Position& goal) {
	std::pair<Intersection, Map::vertex_t> start_vertex = map.get_intersection_closest_to(start);
	std::pair<Intersection, Map::vertex_t> goal_vertex = map.get_intersection_closest_to(goal);

	Intersection start_int = start_vertex.first;
	Intersection goal_int = goal_vertex.first;

	_route.generate_route(map, start_int, goal_int);
	_route.print_route(map);
}

Speed RoutingModule::get_current_speed_limit(Map& map) {
	return _route.get_current_speed_limit(map);
}

Position RoutingModule::get_new_position(Map& map, Distance& d) {
	return _route.get_new_position(map, d);
}

Heading RoutingModule::get_current_heading() {
	return _route.get_current_heading();
}

bool RoutingModule::imminent_hazard(Map& map) {
	return _route.imminent_hazard(map);
}

const Hazard& RoutingModule::get_imminent_hazard(Map& map) {
	return _route.get_imminent_hazard(map);
}
