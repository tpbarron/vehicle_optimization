/**
 * EuclideanDistanceHeuristic.h
 *	
 *  Created on: Sep 29, 2014
 *      Author: trevor
 */

#ifndef EUCLIDEANDISTANCEHEURISTIC_H_
#define EUCLIDEANDISTANCEHEURISTIC_H_

#include <cmath>

#include <boost/graph/astar_search.hpp>
#include <boost/graph/adjacency_list.hpp>

#include "data_types/sensor_types/Position.h"
#include "map/Intersection.h"
#include "map/Map.h"

/**
 *
 */
template <class Graph, class CostType>
class EuclideanDistanceHeuristic :
		public boost::astar_heuristic<Graph, CostType> {

public:

	EuclideanDistanceHeuristic(Map::Graph g, Map::vertex_t goal)
			: _g(g), _goal(goal) {
	}
//	virtual ~EuclideanDistanceHeuristic();

	CostType operator()(Map::vertex_t u) {
		//TODO: implement. If have access to graph can easily get positions from
		// intersection properties in vertices.
		Intersection i1 = _g[u];
		Intersection i2 = _g[_goal];
		Position p1 = i1.get_position();
		Position p2 = i2.get_position();

		CostType d = p1.get_distance_to(p2).get_distance();
	//  	CostType dx = _location[m_goal].x - m_location[u].x;
	//	CostType dy = _location[m_goal].y - m_location[u].y;
	//	return std::sqrt(dx * dx + dy * dy);
		return d;
	}

private:

	Map::Graph _g;
	Map::vertex_t _goal;

};

#endif /* EUCLIDEANDISTANCEHEURISTIC_H_ */
