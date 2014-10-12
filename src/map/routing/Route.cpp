/**
 * Route.cpp
 *	
 *  Created on: Sep 29, 2014
 *      Author: trevor
 */

#include <map/routing/Route.h>

Route::Route() : _currently_in_intersection(false), _angle_to_intersection(0) {
	_map = nullptr;
}

Route::~Route() {
}


void Route::set_map(Map *m) {
	_map = m;
}

void Route::print_route() {
	for (std::list<Map::vertex_t>::iterator it = _vertices.begin(); it != _vertices.end(); it++) {
		Map::vertex_t v = *it;
		std::cout << "Vertex = " << (_map->get_network()[v]).get_id() << std::endl;
	}
}

void Route::generate_route(Intersection &i1, Intersection &i2) {
	std::vector<Map::vertex_t> predecessors(_map->get_num_intersections());
	std::vector<double> distances(_map->get_num_intersections());

	std::pair<Map::vertex_t, bool> start_exists = _map->get_vertex_for_intersection(i1);
	std::pair<Map::vertex_t, bool> goal_exists = _map->get_vertex_for_intersection(i2);

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

	Intersection i1check = _map->get_network()[start];
	Intersection i2check = _map->get_network()[goal];

	std::cout << "Routing from: " << i1check.get_id() << " -> " << i2check.get_id() << std::endl;

	EuclideanDistanceHeuristic<Map::Graph, double> dist_heuristic(_map->get_network(), goal);
	AstarGoalVisitor astar_visitor(goal);

	try {
		boost::astar_search_tree(
				_map->get_network(), start,
				dist_heuristic,
				boost::weight_map(boost::get(&Road::_distance, _map->get_network())).
					predecessor_map(make_iterator_property_map(predecessors.begin(), boost::get(boost::vertex_index, _map->get_network()))).
					distance_map(make_iterator_property_map(distances.begin(), boost::get(boost::vertex_index, _map->get_network()))).
					visitor(astar_visitor)
		);
	} catch (AstarGoalVisitor::found_goal &fg) {
		_vertices.empty(); // clear just in case...
		for (Map::vertex_t u = goal; u != start; u = predecessors[u]) {
			_vertices.push_front(u);
		}
		// Get the first non-start intersection so can easily find the first road.
		// Then add the start intersection.
		Map::vertex_t first_int = _vertices.front();
		_current_end_intersection = _map->get_network()[first_int];
		_current_start_intersection = i1check; // i1check is the starting int

		//edge must exist
		std::pair<Map::edge_t, bool> edge_pair = boost::edge(start, first_int, _map->get_network());
		Map::edge_t e = edge_pair.first;

		//set start pos / road
		Position ipos = i1check.get_position();
		std::cout << "vehicle start intersect pos: " << ipos.to_string() << std::endl;
		_current_position.set_position(i1check.get_position());
		_current_road = _map->get_network()[e];

		calculate_angle_to_intersection();
	}

	// TODO: how to handle no found route?
}

void Route::calculate_angle_to_intersection() {
	Position i1 = _current_start_intersection.get_position();
	Position i2 = _current_end_intersection.get_position();
	double dy = i2.get_y() - i1.get_y();
	double dx = i2.get_x() - i1.get_x();
	_angle_to_intersection = std::atan2(dy, dx);
	std::cout << "Computed angle to intersection in rad: " << _angle_to_intersection << std::endl;
}

/**
 * Return the Speed at the given
 * TODO: should the road store the speed limit as a Speed object?
 */
Speed Route::get_current_speed_limit() {
//	Speed s(Speed::MPH_25);
	Speed s(_current_road.get_speed_limit());
	return s;
}

/**
 * Calculate new position after moving the given distance along route
 *
 * Let theta = the angle from the start intersection to the end intersection.
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
Position Route::get_new_position(const Distance &d) {
	//TODO: move vehicle along road from int1 to int2
	//might as well store current end points too

	//TODO: For now, assume that all roads are straight,
	//Just move dist closer to in direction of end intersection
	//If moving that far would push you past the end of the road
	//continue on to the next segment of the route

	//Get dist from current position to intersection
	Position end_int_position = _current_end_intersection.get_position();
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
			_current_position = _current_end_intersection.get_position();
			return _current_position;
		}

		//Dist still need to go after turn
		double excess_dist = dist - max_dist_on_road;

		//Get rid of the intersection that used to be the last intersection
		_vertices.pop_front();

		//The new start is the old end
		//TODO: this is relatively inefficient and get_vertex_for_int iterates
		//through the vertices until it finds the right one...
		//Maybe the vertices / edges should be stored instead of the
		//intersections and roads since it is each to go from vertex to intersection
		//but not the other way.
		Map::vertex_t start = _map->get_vertex_for_intersection(_current_end_intersection).first;
		_current_start_intersection = _current_end_intersection;

		//The new end is the next element in the list.
		Map::vertex_t end = _vertices.front();
		_current_end_intersection = _map->get_network()[end];

		//Get the new edge from the new intersections
		std::pair<Map::edge_t, bool> edge_pair = boost::edge(start, end, _map->get_network());
		Map::edge_t e = edge_pair.first;
		_current_road = _map->get_network()[e];

		calculate_angle_to_intersection();

		//Set my current position to be at the intersection I'm now 'starting' from
		_current_position.set_position(_current_start_intersection.get_position());

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
	//TODO: calculate heading based on last movement
	Heading hdng(0);
	return hdng;
}


