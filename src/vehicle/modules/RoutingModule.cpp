/**
 * RoutingModule.cpp
 *	
 *  Created on: Oct 20, 2014
 *      Author: trevor
 */

#include "RoutingModule.h"

RoutingModule::RoutingModule() :
	_mediator(nullptr) {
}

RoutingModule::~RoutingModule() {
}

void RoutingModule::set_mediator(ModuleMediator *mediator) {
	_mediator = mediator;
}

void RoutingModule::set_map(const Map& map) {
	_map = map;
}

void RoutingModule::set_start_position(const Position& start) {
	_start = start;
}

void RoutingModule::set_goal_position(const Position& goal) {
	_goal = goal;
}

const Position& RoutingModule::get_start_position() const {
	return _start;
}

void RoutingModule::generate_route() {
	std::pair<Intersection, Map::vertex_t> start_vertex = _map.get_intersection_closest_to(_start);
	std::pair<Intersection, Map::vertex_t> goal_vertex = _map.get_intersection_closest_to(_goal);

	Map::vertex_t start = start_vertex.second;
	Map::vertex_t goal = goal_vertex.second;
	_route.generate_route(_map, start, goal);
	_route.print_route(_map);
}

Speed RoutingModule::get_current_speed_limit() {
	return _route.get_current_speed_limit(_map);
}

Position RoutingModule::get_current_position() const {
	return _route.get_current_position();
}

Position RoutingModule::get_new_position(Distance& d) {
	return _route.get_new_position(_map, d);
}

Heading RoutingModule::get_current_heading() {
	return _route.get_current_heading();
}

bool RoutingModule::imminent_hazard() {
	return _route.imminent_hazard(_map);
}

Hazard RoutingModule::get_imminent_hazard() {
	return _route.get_imminent_hazard(_map);
}

