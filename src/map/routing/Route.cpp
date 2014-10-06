/**
 * Route.cpp
 *	
 *  Created on: Sep 29, 2014
 *      Author: trevor
 */

#include <map/routing/Route.h>

Route::Route(Map &m) : _map(m) {
}

Route::~Route() {
}

void Route::set_map(Map &m) {
	_map = m;
}

void Route::generate_route(Intersection &i1, Intersection &i2) {
	std::vector<Map::vertex_t> predecessors(_map.get_num_intersections());
	std::vector<double> distances(_map.get_num_intersections());

	std::pair<Map::vertex_t, bool> start_exists = _map.get_vertex_for_intersection(i1);
	std::pair<Map::vertex_t, bool> goal_exists = _map.get_vertex_for_intersection(i2);

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

	Intersection i1check = _map.get_network()[start];
	Intersection i2check = _map.get_network()[goal];

	std::cout << "Routing from: " << i1check.get_id() << " -> " << i2check.get_id() << std::endl;

	EuclideanDistanceHeuristic<Map::Graph, double> dist_heuristic(_map.get_network(), goal);
	AstarGoalVisitor astar_visitor(goal);

	try {
		boost::astar_search_tree(
				_map.get_network(), start,
				dist_heuristic,
				boost::weight_map(boost::get(&Road::_distance, _map.get_network())).
					predecessor_map(make_iterator_property_map(predecessors.begin(), boost::get(boost::vertex_index, _map.get_network()))).
					distance_map(make_iterator_property_map(distances.begin(), boost::get(boost::vertex_index, _map.get_network()))).
					visitor(astar_visitor)
		);
	} catch (AstarGoalVisitor::found_goal &fg) {
		std::list<Map::vertex_t> solution;
		for (Map::vertex_t u = goal; u != start; u = predecessors[u])
			solution.push_front(u);

		for (std::list<Map::vertex_t>::iterator it = solution.begin(); it != solution.end(); it++) {
			Map::vertex_t v = *it;
			std::cout << "Vertex = " << (_map.get_network()[v]).get_id() << std::endl;
		}
	}
}
