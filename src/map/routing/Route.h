/**
 * Route.h
 *	
 *  Created on: Sep 29, 2014
 *      Author: trevor
 */

#ifndef ROUTE_H_
#define ROUTE_H_

#include <list>
#include <utility>

#include <boost/graph/astar_search.hpp>

#include "data_types/Position.h"
#include "map/Intersection.h"
#include "map/Map.h"

#include "map/routing/astar/EuclideanDistanceHeuristic.h"
#include "map/routing/astar/AstarGoalVisitor.h"

/**
 *
 */
class Route {

public:
	Route(Map &m);
	virtual ~Route();

	void set_map(Map &m);
	void generate_route(Intersection &i1, Intersection &i2);

private:

	Map _map;

};

#endif /* ROUTE_H_ */
