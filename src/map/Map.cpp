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

void Map::build_weight_map() {

}

/*
 * TODO
 */
void Map::add_edge(Intersection &i1, Intersection &i2, Road &r) {
	std::pair<vertex_t, bool> u_exists = get_vertex_for_intersection(i1);
	std::pair<vertex_t, bool> v_exists = get_vertex_for_intersection(i2);

	vertex_t u, v;
	if (!u_exists.second) {
		u = boost::add_vertex(i1, _network);
	} else {
		u = u_exists.first;
	}

	if (!v_exists.second) {
		v = boost::add_vertex(i2, _network);
	} else {
		v = v_exists.first;
	}

	edge_t e;
	bool b;
	boost::tie(e, b) = boost::add_edge(u, v, _network);

	//weight_map weights = boost::get(boost::edge_weight, _network);
	//weights[e] = r->get_distance();

	//copy to vertex u and v
//	_network[u] = i1;
//	_network[v] = i2;

	//copy to edge e
	_network[e] = r;
}


Map::Graph Map::get_network() {
	return _network;
}

int Map::get_num_intersections() {
	return boost::num_vertices(_network);
}

/*
 * Provides the boost vertex type for a given intersection
 *
 * @param the intersection to find the vertex_t for
 *
 * @return a std::pair<vertex_t, bool> where bool determines if the
 * desired element was found
 */
std::pair<Map::vertex_t, bool> Map::get_vertex_for_intersection(Intersection &i) {
	vertex_t v;
	std::pair<vertex_iterator, vertex_iterator> vi = boost::vertices(_network);
	for (vertex_iterator vertex_iter = vi.first; vertex_iter != vi.second; ++vertex_iter) {
		v = *vertex_iter;
		Intersection val = _network[*vertex_iter];
		if (val.get_id() == i.get_id()) {
			//found vertex
			return std::make_pair(v, true);
		}
	}
	return std::make_pair(v, false);
}

void Map::print_map_data() {
	std::pair<edge_iterator, edge_iterator> ei = boost::edges(_network);
	for(edge_iterator edge_iter = ei.first; edge_iter != ei.second; ++edge_iter) {

		vertex_t u = boost::source(*edge_iter, _network);
		vertex_t v = boost::target(*edge_iter, _network);

		Intersection i1 = _network[u];
		Intersection i2 = _network[v];
		Road r = _network[*edge_iter];

		std::cout << "(" << i1.get_id() << " pos=" << i1.get_position().to_string() << "), "
						 << "road = " << r.get_distance() << ", ("
						 << i2.get_id() << " pos=" << i2.get_position().to_string() << ")" << std::endl;
	}
}
