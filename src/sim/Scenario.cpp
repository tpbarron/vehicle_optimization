/*
 * Scenario.cpp
 *
 *  Created on: Sep 8, 2014
 *      Author: trevor
 */

#include "Scenario.h"

#include <boost/foreach.hpp>

#include "utils/Logger.h"

/**
 * Maintains data for a running scenario.
 *
 */
namespace Scenario {

boost::posix_time::ptime _start_time;

Map _map;
std::vector<Intersection> _intersections;
std::vector<Road> _roads;

/**
 * initializing scenario
 */
void init() {

}

/**
 * Cleanup resources used in the Scenario namespace
 */
void cleanup() {
	Logger::info("Cleaning up scenario");
}

/**
 * Load a scenario by name
 * @param scenario - a string designating the name of the scenario.
 */
void load_scenario(std::string scenario) {
	std::string file = Utils::get_scenario_file_path(scenario);
	//read json file and insert into db
	std::ifstream in(file.c_str());
	if (in.is_open()) {
		std::stringstream buf;
		buf << in.rdbuf();
		in.close();
		boost::property_tree::ptree tree;
		boost::property_tree::read_json(buf, tree);

		std::string name = tree.get<std::string>(SCENARIO_NAME);
		std::string desc = tree.get<std::string>(SCENARIO_DESC);

		//Load map first so can pass copy of map to vehicles
		boost::property_tree::ptree map_tree = tree.get_child(SCENARIO_MAP);
		load_scenario_map(scenario, map_tree);

		//Load vehicles
		boost::property_tree::ptree::value_type v;
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, tree.get_child(SCENARIO_VEHICLES)) {
			std::string vname = v.second.get<std::string>(SCENARIO_VEHICLES_NAME);
			std::string vfilename = v.second.get<std::string>(SCENARIO_VEHICLES_DATA);
			std::string vpath = Utils::get_scenario_vehicle_file_path(scenario, vfilename);
			Logger::info(vname + ": " + vpath);
			load_vehicle(vname, vpath);
		}
	} else {
		std::cerr << "Unable to open scenario file" << std::endl;
	}
}

/**
 * Load a vehicle from file for use in this scenario
 *
 * @param name - the name of the scenario being loaded
 * @param file - the file to load the vehicle from
 */
void load_vehicle(std::string name, std::string file) {
	std::ifstream vehicle_file(file.c_str());
	if (vehicle_file.is_open()) {
		Vehicle *v = new Vehicle(name);
		VehicleManager::register_vehicle(v);

		std::stringstream vbuf;
		vbuf << vehicle_file.rdbuf();
		boost::property_tree::ptree vehicle_data;
		boost::property_tree::read_json(vbuf, vehicle_data);

		std::string type = vehicle_data.get<std::string>(VEHICLE_TYPE);

		boost::property_tree::ptree start_data = vehicle_data.get_child(VEHICLE_START);
		double start_x = start_data.get<double>(VEHICLE_POSITION_X);
		double start_y = start_data.get<double>(VEHICLE_POSITION_Y);

		boost::property_tree::ptree goal_data = vehicle_data.get_child(VEHICLE_GOAL);
		double goal_x = goal_data.get<double>(VEHICLE_POSITION_X);
		double goal_y = goal_data.get<double>(VEHICLE_POSITION_Y);

		std::string i = "Loaded vehicle data : " +
				boost::lexical_cast<std::string>(start_x) +
				boost::lexical_cast<std::string>(start_y) + ", " +
				boost::lexical_cast<std::string>(goal_x) + ", " +
				boost::lexical_cast<std::string>(goal_y);
		Logger::info(i);
		v->set_start_position(start_x, start_y);
		v->set_goal_position(goal_x, goal_y);
		v->set_map(_map);
		v->set_type_from_string(type);

	} else {
		Logger::error("Unable to open vehicle file");
	}
}

/**
 * Load the map for this scenario from a file
 *
 * @param scenario - the name of the scenario
 * @param map_tree - a boost::property_tree with map data
 */
void load_scenario_map(std::string scenario, boost::property_tree::ptree &map_tree) {
	int map_width = map_tree.get<int>(SCENARIO_MAP_WIDTH);
	int map_height = map_tree.get<int>(SCENARIO_MAP_HEIGHT);

	_map.set_height(map_height);
	_map.set_width(map_width);

	std::string intersections_file = map_tree.get<std::string>(SCENARIO_MAP_INTERSECTIONS);
	std::string roads_file = map_tree.get<std::string>(SCENARIO_MAP_ROADS);

	load_scenario_intersections(scenario, intersections_file);
	load_scenario_roads(scenario, roads_file);

	populate_map();
}

/*
 * TODO: insert into db not just memory
 */
void load_scenario_intersections(std::string scenario, std::string file) {
	std::string path = Utils::get_scenario_intersection_file_path(scenario, file);
	Logger::info("Intersections: " + path);
	std::ifstream in(path.c_str());
	if (in.is_open()) {
		std::stringstream buf;
		buf << in.rdbuf();
		in.close();
		boost::property_tree::ptree intersection_data;
		boost::property_tree::read_json(buf, intersection_data);

		boost::property_tree::ptree::value_type intersection;
		BOOST_FOREACH(boost::property_tree::ptree::value_type &intersection, intersection_data.get_child(INTERSECTION_DATA)) {
			int id = intersection.second.get<int>(INTERSECTION_ID);
			double pos_x = intersection.second.get<double>(INTERSECTION_POSITION_X);
			double pos_y = intersection.second.get<double>(INTERSECTION_POSITION_Y);
			double width = intersection.second.get<double>(INTERSECTION_WIDTH);
			double height = intersection.second.get<double>(INTERSECTION_HEIGHT);

			Intersection i;
			i.set_id(id);
			i.set_position(pos_x, pos_y);
			i.set_width(width);
			i.set_height(height);

			_intersections.push_back(i);
		}
	} else {
		Logger::error("Could not open intersections file");
	}
}

void load_scenario_roads(std::string scenario, std::string file) {
	std::string path = Utils::get_scenario_road_file_path(scenario, file);
	Logger::info("Roads: " + path);
	std::ifstream in(path.c_str());

	if (in.is_open()) {

		std::stringstream buf;
		buf << in.rdbuf();
		in.close();
		boost::property_tree::ptree road_data;
		boost::property_tree::read_json(buf, road_data);

		boost::property_tree::ptree::value_type road;
		BOOST_FOREACH(boost::property_tree::ptree::value_type &road,
				road_data.get_child(ROAD_DATA)) {

			int start_int_id = road.second.get<int>(ROAD_START_INT_ID);
			int end_int_id = road.second.get<int>(ROAD_END_INT_ID);
			double speed_limit = road.second.get<double>(ROAD_SPEED_LIMIT);
			double dist = road.second.get<double>(ROAD_DISTANCE);

			Road r;
			r.set_start_intersection(get_intersection_from_id(start_int_id));
			r.set_end_intersection(get_intersection_from_id(end_int_id));
			r.set_speed_limit(speed_limit);
			r.set_distance(dist);

			// Load lanes
			BOOST_FOREACH(boost::property_tree::ptree::value_type &forward_lanes,
					road.second.get_child(ROAD_LANES+"."+ROAD_FORWARD_LANES)) {
				r.add_lane_forward(load_road_lane(scenario, forward_lanes.second.data()));
			}

			BOOST_FOREACH(boost::property_tree::ptree::value_type &backward_lanes,
					road.second.get_child(ROAD_LANES+"."+ROAD_BACKWARD_LANES)) {
				r.add_lane_backward(load_road_lane(scenario, backward_lanes.second.data()));
			}

			// Load hazards
			BOOST_FOREACH(boost::property_tree::ptree::value_type &hazards,
					road.second.get_child(ROAD_HAZARDS)) {
				r.add_hazard(load_road_hazard(scenario, hazards.second.data()));
			}

			_roads.push_back(r);
		}
	} else {
		Logger::error("Could not open road file");
	}
}

/**
 * Load a road lane from a file
 */
Lane load_road_lane(std::string scenario, std::string file) {
	std::string path = Utils::get_scenario_lane_file_path(scenario, file);
	Logger::info("Lane: " + path);
	Lane l;
	std::ifstream in(path.c_str());
	if (in.is_open()) {
		std::stringstream buf;
		buf << in.rdbuf();
		in.close();
		boost::property_tree::ptree lane_data;
		boost::property_tree::read_json(buf, lane_data);

		boost::property_tree::ptree::value_type lane;
		BOOST_FOREACH(boost::property_tree::ptree::value_type &lane, lane_data.get_child(LANE_WAYPOINTS)) {
			double ptx = lane.second.get<double>(LANE_POINT_X);
			double pty = lane.second.get<double>(LANE_POINT_Y);
			Position p(ptx, pty);
			l.add_waypoint(p);
		}
	} else {
		std::cerr << "Could not open road file" << std::endl;
	}
	return l;
}

Hazard load_road_hazard(std::string scenario, std::string file) {
	std::string path = Utils::get_scenario_hazard_file_path(scenario, file);
	Logger::info("Hazard: " + path);
	Hazard h;
	std::ifstream in(path.c_str());
	if (in.is_open()) {
		std::stringstream buf;
		buf << in.rdbuf();
		in.close();
		boost::property_tree::ptree hazard_data;
		boost::property_tree::read_json(buf, hazard_data);

		double ptx = hazard_data.get<double>(HAZARD_POSITION_X);
		double pty = hazard_data.get<double>(HAZARD_POSITION_Y);
		double max_safe_speed = hazard_data.get<double>(HAZARD_MAX_SAFE_SPEED);

		Position p(ptx, pty);
		h.set_position(p);
		h.set_max_safe_speed(max_safe_speed);
	} else {
		Logger::error("Could not open road file");
	}
	return h;
}

Intersection& get_intersection_from_id(int id) {
	for (unsigned int i = 0; i < _intersections.size(); ++i) {
		if (_intersections[i].get_id() == id) {
			return _intersections[i];
		}
	}
	Logger::error("No intersection for id = " + boost::lexical_cast<std::string>(id));
	throw std::invalid_argument("No intersection for id = " + boost::lexical_cast<std::string>(id));
}

/*
 * add the roads / intersections to the graph structure in the map
 */
void populate_map() {
	//for each road
	//get the two endpoint intersections
	//add the intersections as nodes
	//copy the road to the returned object.
	for (unsigned int r = 0; r < _roads.size(); ++r) {
		//TODO: if road is not one way, also add in other direction
		Road road = _roads[r];
		Intersection i1 = road.get_start_intersection();
		Intersection i2 = road.get_end_intersection();
		_map.add_edge(i1, i2, road);
		if (!road.is_one_way()) {
			_map.add_edge(i2, i1, road);
		}
	}
}



void start() {
	Logger::info("Starting scenario");
	_start_time = boost::posix_time::microsec_clock::local_time();

	auto vehicles = VehicleManager::get_vehicles();

	for (auto itr = vehicles.begin();
			itr != vehicles.end();
			++itr) {
		Vehicle* v = dynamic_cast<Vehicle*>(*itr);
		v->start();
	}
	Utils::start_io();
}

void stop() {
	Logger::info("Stopping scenario");

	auto vehicles = VehicleManager::get_vehicles();
	for (auto itr = vehicles.begin();
			itr != vehicles.end();
			++itr) {
		Vehicle* v = dynamic_cast<Vehicle*>(*itr);
		v->stop();
	}
	Utils::stop_io();
}


/*
 *
 *
 * ----------------------------------
 * Tests - should eventually be moved
 * ----------------------------------
 *
 *
 *
 */
//void test_get_closest_vehicles() {
//	std::cout << "Num vehicles: " << VehicleManager::get_vehicles().size() << std::endl;
//	for (unsigned int i = 0; i < VehicleManager::get_vehicles().size(); ++i) {
//		Vehicle* v = VehicleManager::get_vehicles()[i];
//		std::cout << v->get_readable_name() << ", " << v->get_id_as_string() << std::endl;
//		std::vector<VehicleManager::VehicleDistPair> nearby = VehicleManager::get_nearest(v->get_module_manager().get_current_position(), 2, 10);
//		for (std::vector<VehicleManager::VehicleDistPair>::iterator vdistitr = nearby.begin(); vdistitr != nearby.end(); ++vdistitr) {
//			std::cout << "    Found vehicle: " << (*vdistitr).second->get_readable_name() << " at distance " << (*vdistitr).first.get_distance() << std::endl;
//		}
//	}
//}

void test_print_map() {
	_map.print_map_data();
}
//
//void test_routing() {
//	Route r;
//	r.set_map(_map);
//	r.generate_route(_intersections[0], _intersections[5]);
//}

}
