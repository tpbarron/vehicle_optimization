/*
 * Map.h
 *
 *  Created on: Sep 19, 2014
 *      Author: trevor
 */

#ifndef MAP_H_
#define MAP_H_

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>

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

	void add_edge(Intersection *i1, Intersection *i2, Road *r);

	int get_width();
	int get_height();

	void set_width(int width);
	void set_height(int height);

	void print_map_data();

private:

	int _width;
	int _height;

	typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
			Intersection*, Road*> Graph;
	typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;
	typedef boost::graph_traits<Graph>::edge_descriptor edge_t;
	typedef boost::graph_traits<Graph>::edge_iterator edge_iterator;


	Graph _network;
};

#endif /* MAP_H_ */
