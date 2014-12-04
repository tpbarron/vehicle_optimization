/**
 * Route.h
 *	
 *  Created on: Sep 29, 2014
 *      Author: trevor
 */

#ifndef ROUTE_H_
#define ROUTE_H_

#include <vector>
#include <list>
#include <cmath>
#include <utility>

#include <boost/graph/astar_search.hpp>

#include "data_types/sensor_types/Distance.h"
#include "data_types/sensor_types/Heading.h"
#include "data_types/sensor_types/Position.h"
#include "data_types/sensor_types/Speed.h"

#include "data_types/module_types/Hazard.h"

#include "map/Intersection.h"
#include "map/Map.h"
#include "vehicle/modules/routing/astar/AstarGoalVisitor.h"
#include "vehicle/modules/routing/astar/EuclideanDistanceHeuristic.h"


/**
 *
 */
class Route {

public:
	Route();
	virtual ~Route();

	void print_route(Map& map);

	void generate_route(Map &map, Map::vertex_t &start, Map::vertex_t &goal);

	Speed get_current_speed_limit(Map& map);
	Position get_current_position() const;
	Position get_new_position(Map& map, const Distance &d);
	Heading get_current_heading();

	bool imminent_hazard(Map& map);
	std::vector<Hazard> get_imminent_hazards(Map& map);

	bool does_path_exist();

	std::vector<Intersection> get_path_as_intersections(Map& map) const;

private:

	void calculate_angle_to_intersection(Map& map);

	Map _map;
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
