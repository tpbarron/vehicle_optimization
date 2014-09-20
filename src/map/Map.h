/*
 * Map.h
 *
 *  Created on: Sep 19, 2014
 *      Author: trevor
 */

#ifndef MAP_H_
#define MAP_H_

#include <boost/graph/adjacency_matrix.hpp>

#include "Intersection.h"
#include "Road.h"

/*
 * A literal map with a graph representation with edges as roads
 * and Intersections as vertices
 */
class Map {

public:
	Map();
	virtual ~Map();

	/*
	 * Will need to add all intersections first
	 * boost::add_edge returns an edge_description, i.e. Road.
	 * Then properties can be set on the road.
	 */

	Road* add_edge(Intersection &i1, Intersection &i2);

private:

	int width;
	int height;

	typedef boost::adjacency_matrix<boost::undirectedS,  Intersection, Road> Graph;
	Graph network;

};

#endif /* MAP_H_ */
