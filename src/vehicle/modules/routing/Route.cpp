/**
 * Route.cpp
 *	
 *  Created on: Sep 29, 2014
 *      Author: trevor
 */

#include "Route.h"

Route::Route() : _current_start_vertex(0),
				 _current_end_vertex(0),
				 _currently_in_intersection(false),
				 _path_exists(false),
				 _angle_to_intersection(0) {
}

Route::~Route() {
}


void Route::print_route(Map& map) {
	for (std::list<Map::vertex_t>::iterator it = _vertices.begin(); it != _vertices.end(); it++) {
		Map::vertex_t v = *it;
		std::cout << "Vertex = " << (map.get_network()[v]).get_id() << std::endl;
	}
}

void Route::generate_route(Map &map, Intersection &i1, Intersection &i2) {
	std::vector<Map::vertex_t> predecessors(map.get_num_intersections());
	std::vector<double> distances(map.get_num_intersections());

	std::pair<Map::vertex_t, bool> start_exists = map.get_vertex_for_intersection(i1);
	std::pair<Map::vertex_t, bool> goal_exists = map.get_vertex_for_intersection(i2);

	if (!start_exists.second) {
		std::cerr << "Starting intersection does not exist." << std::endl;
		exit(1);
	}

	if (!goal_exists.second) {
		std::cerr << "Goal intersection does not exist." << std::endl;
		exit(1);
	}

	// We should have both intersections... still might not be a path
	Map::vertex_t start = start_exists.first;
	Map::vertex_t goal = goal_exists.first;

	Intersection i1check = map.get_network()[start];
	Intersection i2check = map.get_network()[goal];

	std::cout << "Routing from: " << i1check.get_id() << " -> " << i2check.get_id() << std::endl;

	EuclideanDistanceHeuristic<Map::Graph, double> dist_heuristic(map.get_network(), goal);
	AstarGoalVisitor astar_visitor(goal);

	try {
		boost::astar_search_tree(
				map.get_network(), start,
				dist_heuristic,
				boost::weight_map(boost::get(&Road::_distance, map.get_network())).
					predecessor_map(boost::make_iterator_property_map(predecessors.begin(), boost::get(boost::vertex_index, map.get_network()))).
					distance_map(boost::make_iterator_property_map(distances.begin(), boost::get(boost::vertex_index, map.get_network()))).
					visitor(astar_visitor)
		);
	} catch (AstarGoalVisitor::found_goal &fg) {
		_vertices.empty(); // clear just in case...
		for (Map::vertex_t u = goal; u != start; u = predecessors[u]) {
			_vertices.push_front(u);
		}
		// Get the first non-start intersection so can easily find the first road.
		// Then add the start intersection.
		_current_end_vertex = _vertices.front();
		_current_start_vertex = start;

		//edge must exist
		std::pair<Map::edge_t, bool> edge_pair = boost::edge(_current_start_vertex,
				_current_end_vertex, map.get_network());
		_current_edge = edge_pair.first;

		//set start pos / road
		Position ipos = i1check.get_position();
		std::cout << "vehicle start intersect pos: " << ipos.to_string() << std::endl;
		_current_position.set_position(i1check.get_position());
		// Set last position so as to simulate going towards second intersection
		// This gives a reasonable but not always perfect first heading calculation
		_last_position.set_position(-i2check.get_position().get_x(), -i2check.get_position().get_y());
		calculate_angle_to_intersection(map);

		// set flag that a path exists
		_path_exists = true;
	}

	// TODO: how to handle no found route?
}


/**
 * Return the Speed at the given
 * TODO: should the road store the speed limit as a Speed object?
 */
Speed Route::get_current_speed_limit(Map& map) {
//	Speed s(Speed::MPH_25);
	Speed s(map.get_network()[_current_edge].get_speed_limit());
	return s;
}

/**
 * Calculate new position after moving the given distance along route
 *
 * Let,
 *
 * 	theta = the angle from the start intersection to the end intersection
 *
 * Then we want to move Distance d along the hypotenuse where the horizontal
 * leg is the change in x value between the intersections and the vertical leg
 * is the change in y value between the intersections. Then the change in the
 * current position can be evaluated:
 *
 * 	dy = d * sin(theta)
 * 	dx = d * cos(theta)
 *
 * We move the Vehicle by adding these values to the current positions x, y
 * respectively.
 *
 * If the distance moved will take us past the intersection we wish to reach
 * need to get the next intersection, update angle, compute dx & dy from new
 * angle, and set current road, start int, and end int values.
 *
 * @param d the distance to move
 */
Position Route::get_new_position(Map& map, const Distance &d) {
	//TODO: move vehicle along road from int1 to int2
	//might as well store current end points too

	//TODO: For now, assume that all roads are straight,
	//Just move dist closer to in direction of end intersection
	//If moving that far would push you past the end of the road
	//continue on to the next segment of the route

	// Remember the current position
	_last_position = _current_position;

	// Get dist from current position to intersection
	Position end_int_position = map.get_network()[_current_end_vertex].get_position();
	double gdx = end_int_position.get_x() - _current_position.get_x(); //dx to goal
	double gdy = end_int_position.get_y() - _current_position.get_y(); //dy to goal
	double max_dist_on_road = std::sqrt(gdx*gdx + gdy*gdy); //dist on this road

	double dist = d.get_distance();

	// If the dist we want to go is less than the dist left on this road
	if (dist > max_dist_on_road) {
		//Well, that sucks, we need to compute the transition
		if (_vertices.size() == 1) {
			//Then we are coming to the end of the route...
			//Just move to the intersection and stop
			//This should keep returning the same position once we have
			//reached this point.
			_current_position = map.get_network()[_current_end_vertex].get_position();
			return _current_position;
		}

		//Dist still need to go after turn
		double excess_dist = dist - max_dist_on_road;

		//Get rid of the intersection that used to be the last intersection
		_vertices.pop_front();

		//The new start is the old end
		_current_start_vertex = _current_end_vertex;

		//The new end is the next element in the list.
		_current_end_vertex = _vertices.front();

		//Get the new edge from the new intersections
		std::pair<Map::edge_t, bool> edge_pair = boost::edge(_current_start_vertex,
				_current_end_vertex, map.get_network());
		_current_edge = edge_pair.first;

		calculate_angle_to_intersection(map);

		//Set my current position to be at the intersection I'm now 'starting' from
		_current_position.set_position(map.get_network()[_current_start_vertex].get_position());

		//Now just do computation as normal with distance to go
		dist = excess_dist;

	} // else Phew, we are good, just continue on this road

	double dx = dist * std::cos(_angle_to_intersection);
	double dy = dist * std::sin(_angle_to_intersection);
	_current_position.set_x(_current_position.get_x() + dx);
	_current_position.set_y(_current_position.get_y() + dy);

	return _current_position;
}

/**
 * Return the current expected heading for a vehicle on the route
 */
Heading Route::get_current_heading() {
	Heading hdng;
	hdng.set_from_pts(_last_position, _current_position);
	return hdng;
}

/**
 * Return true if there is an imminent Hazard along this route
 */
bool Route::imminent_hazard(Map& map) {
	return map.get_network()[_current_edge].is_hazard_at_position(_current_position);
}

/*
 * Return the nearest Hazard to the current vehicle position
 */
Hazard Route::get_imminent_hazard(Map& map) {
	return map.get_network()[_current_edge].get_hazard_at_position(_current_position);
}

/**
 * True if a route was able to be generated
 */
bool Route::does_path_exist() {
	return _path_exists;
}

/**
 * Calculate angle from start vertex to end vertex so we have a reasonable
 * starting Heading
 */
void Route::calculate_angle_to_intersection(Map& map) {
	Position i1 = map.get_network()[_current_start_vertex].get_position();
	Position i2 = map.get_network()[_current_end_vertex].get_position();
	double dy = i2.get_y() - i1.get_y();
	double dx = i2.get_x() - i1.get_x();
	_angle_to_intersection = std::atan2(dy, dx);
	std::cout << "Computed angle to intersection in rad: " << _angle_to_intersection << std::endl;
}
