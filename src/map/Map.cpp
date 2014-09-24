/*
 * Map.cpp
 *
 *  Created on: Sep 19, 2014
 *      Author: trevor
 */

#include "Map.h"

Map::Map() : network(0) {
	height = -1;
	width = -1;
}

Map::~Map() {
	// TODO Auto-generated destructor stub
}

void Map::set_width(int w) {
	width = w;
}

void Map::set_height(int h) {
	height = h;
}

/*
 * TODO
 */
void Map::add_edge(Intersection *i1, Intersection *i2, Road *r) {
	vertex_t u = boost::add_vertex(i1, network);
	vertex_t v = boost::add_vertex(i2, network);

	edge_t e;
	bool b;
	boost::tie(e, b) = boost::add_edge(u, v, network);

	//copy to vertex u and v
//	network[u] = i1;
//	network[v] = i2;

	//copy to edge e
	network[e] = r;
}

void Map::print_map_data() {
	//Tried to make this section more clear, instead of using tie, keeping all
	//the original types so it's more clear what is going on
	std::pair<edge_iterator, edge_iterator> ei = boost::edges(network);
	for(edge_iterator edge_iter = ei.first; edge_iter != ei.second; ++edge_iter) {
		std::cout << "(" << boost::source(*edge_iter, network) << ", " << boost::target(*edge_iter, network) << ")\n";
	}
}
