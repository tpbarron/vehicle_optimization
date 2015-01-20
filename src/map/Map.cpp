/*
 * Map.cpp
 *
 *  Created on: Sep 19, 2014
 *      Author: trevor
 */

#include "Map.h"

#include <boost/lexical_cast.hpp>

#include "utils/Logger.h"


Map::Map() : _width(-1),
			 _height(-1),
			 _network(0) {
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
 *
 */
void Map::add_edge(Intersection &i1, Intersection &i2, Road &r) {
	std::pair<Map::vertex_t, bool> u_exists = get_vertex_for_intersection(i1);
	std::pair<Map::vertex_t, bool> v_exists = get_vertex_for_intersection(i2);

	Map::vertex_t u, v;
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

	Map::edge_t e;
	bool b;
	boost::tie(e, b) = boost::add_edge(u, v, _network);

	//copy to edge e
	_network[e] = r;
}


const Map::Graph& Map::get_network() {
	return _network;
}

int Map::get_num_intersections() {
	return boost::num_vertices(_network);
}


/**
 * Finds the Intersection closest to the given Position. Used to find the
 * start and end Intersections for a route.
 *
 * Note: this will fail if there are no intersections.
 *
 * @param p the position to find the nearest intersection from
 *
 * @return a std::pair<Intersection, vertex_t> designating the closest
 * intersection to Position p
 */
std::pair<Intersection, Map::vertex_t> Map::get_intersection_closest_to(Position &p) {
	//Iterate the vertices and determine the nearest
	std::pair<Intersection, Map::vertex_t> closest;
	double dist = -1;

	Map::vertex_t v;
	std::pair<vertex_iterator, vertex_iterator> vi = boost::vertices(_network);
	for (vertex_iterator vertex_iter = vi.first; vertex_iter != vi.second; ++vertex_iter) {
		v = *vertex_iter;
		Intersection val = _network[*vertex_iter];
		double intersect_dist = val.get_position().get_distance_to(p).get_distance();
		if (dist < 0 || intersect_dist < dist) {
			closest = std::make_pair(val, v);
			dist = intersect_dist;
		}
	}
	return closest;
}

/**
 * Provides the boost vertex type for a given intersection
 *
 * @param i the intersection to find the vertex_t for
 *
 * @return a std::pair<vertex_t, bool> where bool determines if the
 * desired element was found
 */
std::pair<Map::vertex_t, bool> Map::get_vertex_for_intersection(Intersection &i) {
	vertex_t v = 0;
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


		Logger::info("(" + boost::lexical_cast<std::string>(i1.get_id()) + " pos=" + i1.get_position().to_string() + "), "
						 + "road = " + boost::lexical_cast<std::string>(r.get_distance()) + ", ("
						 + boost::lexical_cast<std::string>(i2.get_id()) + " pos=" + i2.get_position().to_string() + ")");

		for (auto itr = r.get_hazards().begin(); itr != r.get_hazards().end(); ++itr) {
			Logger::info("  Hazard: " + (*itr).get_position().to_string());
		}
	}
}
