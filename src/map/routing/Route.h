/**
 * Route.h
 *	
 *  Created on: Sep 29, 2014
 *      Author: trevor
 */

#ifndef ROUTE_H_
#define ROUTE_H_

#include <list>
#include <cmath>
#include <utility>

#include <boost/graph/astar_search.hpp>

#include "data_types/Distance.h"
#include "data_types/Heading.h"
#include "data_types/Position.h"
#include "data_types/Speed.h"

#include "map/Intersection.h"
#include "map/Map.h"
#include "map/routing/astar/AstarGoalVisitor.h"
#include "map/routing/astar/EuclideanDistanceHeuristic.h"


/**
 *
 */
class Route {

public:
	Route();
	virtual ~Route();

	void set_map(Map *m);
	void print_route();
	void generate_route(Intersection &i1, Intersection &i2);

	Speed get_current_speed_limit();
	Position get_new_position(const Distance &d);
	Heading get_current_heading();

	bool does_path_exist();

private:

	void calculate_angle_to_intersection();

	Map *_map;
	std::list<Map::vertex_t> _vertices;

	//position along route
	Position _current_position;
	Position _last_position;

	Map::edge_t _current_edge;
	Map::vertex_t _current_start_vertex;
	Map::vertex_t _current_end_vertex;

	bool _currently_in_intersection;
	bool _path_exists;
	double _angle_to_intersection; // radians
};

#endif /* ROUTE_H_ */
