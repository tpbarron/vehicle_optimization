/*
 * Map.cpp
 *
 *  Created on: Sep 19, 2014
 *      Author: trevor
 */

#include "Map.h"

Map::Map() : _network(0) {
	_height = -1;
	_width = -1;
}

Map::~Map() {
	// TODO Auto-generated destructor stub
}

int Map::get_width() {
	return _width;
}

int Map::get_height() {
	return _height;
}

void Map::set_width(int w) {
	_width = w;
}

void Map::set_height(int h) {
	_height = h;
}

/*
 * TODO
 */
void Map::add_edge(Intersection *i1, Intersection *i2, Road *r) {
	vertex_t u = boost::add_vertex(i1, _network);
	vertex_t v = boost::add_vertex(i2, _network);

	edge_t e;
	bool b;
	boost::tie(e, b) = boost::add_edge(u, v, _network);

	//copy to vertex u and v
//	network[u] = i1;
//	network[v] = i2;

	//copy to edge e
	_network[e] = r;
}

void Map::print_map_data() {
	//Tried to make this section more clear, instead of using tie, keeping all
	//the original types so it's more clear what is going on
	std::pair<edge_iterator, edge_iterator> ei = boost::edges(_network);
	for(edge_iterator edge_iter = ei.first; edge_iter != ei.second; ++edge_iter) {

		vertex_t u = boost::source(*edge_iter, _network);
		vertex_t v = boost::target(*edge_iter, _network);

		Intersection *i1 = _network[u];
		Intersection *i2 = _network[v];
		std::cout << "(" << i1->get_id() << " pos=" << i1->get_position()->to_string() << "), ("
						 << i2->get_id() << " pos=" << i2->get_position()->to_string() << ")" << std::endl;
	}
}
