/*
 * Scenario.cpp
 *
 *  Created on: Sep 8, 2014
 *      Author: trevor
 */

#include "Scenario.h"

#include <boost/foreach.hpp>


namespace Scenario {

boost::posix_time::ptime start_time;

boost::asio::io_service io_;
boost::asio::strand strand_(io_);
Map map;
std::vector<Intersection*> intersections;
std::vector<Road*> roads;

void init() {
	DBConn::init();
}

void cleanup() {
	std::cout << "Cleaning up scenario" << std::endl;
	for (unsigned int j = 0; j < intersections.size(); ++j) {
		delete intersections[j];
	}
	for (unsigned int k = 0; k < roads.size(); ++k) {
		delete roads[k];
	}
}


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

		//Empty data
		DBConn::clear_db();

		std::string name = tree.get<std::string>(SCENARIO_NAME);
		std::string desc = tree.get<std::string>(SCENARIO_DESC);

		std::cout << "Loading scenario into db: " << desc << std::endl;

		mongo::BSONObjBuilder b;
		b.append(DBConn::SCENARIO_NAME, name);
		b.append(DBConn::SCENARIO_DESC, desc);

		mongo::BSONObj scenario_obj = b.obj();
		DBConn::insert_scenario(scenario_obj);

		//vehicles
		boost::property_tree::ptree::value_type v;
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, tree.get_child(SCENARIO_VEHICLES)) {
			std::string vname = v.second.get<std::string>(SCENARIO_VEHICLES_NAME);
			std::string vfilename = v.second.get<std::string>(SCENARIO_VEHICLES_DATA);
			std::string vpath = Utils::get_scenario_vehicle_file_path(scenario, vfilename);
			std::cout << vname << ": " << vpath << std::endl;
			load_vehicle(vname, vpath);
		}

		boost::property_tree::ptree map_tree = tree.get_child(SCENARIO_MAP);
		load_scenario_map(scenario, map_tree);
	} else {
		std::cerr << "Unable to open scenario file" << std::endl;
	}
}


void load_vehicle(std::string name, std::string file) {
	std::ifstream vehicle_file(file.c_str());
	if (vehicle_file.is_open()) {
		Vehicle *v = new Vehicle(name, &io_, &strand_);
		VehicleManager::register_vehicle(v);
		std::cout << "Inserting vehicle into db" << std::endl;
		insert_vehicle_data(vehicle_file, v->get_id_as_string());
	} else {
		std::cerr << "Unable to open vehicle file" << std::endl;
	}
}

void load_scenario_map(std::string scenario, boost::property_tree::ptree &map_tree) {
	int map_width = map_tree.get<int>(SCENARIO_MAP_WIDTH);
	int map_height = map_tree.get<int>(SCENARIO_MAP_HEIGHT);

	map.set_height(map_height);
	map.set_width(map_width);

	std::string intersections_file = map_tree.get<std::string>(SCENARIO_MAP_INTERSECTIONS);
	std::string roads_file = map_tree.get<std::string>(SCENARIO_MAP_ROADS);

	load_scenario_intersections(scenario, intersections_file);
	load_scenario_roads(scenario, roads_file);

//	populate_map();
}

/*
 * TODO: insert into db not just memory
 */
void load_scenario_intersections(std::string scenario, std::string file) {
	std::string path = Utils::get_scenario_intersection_file_path(scenario, file);
	std::cout << "Intersections: " << path << std::endl;
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

			Intersection *i = new Intersection();
			i->set_id(id);
			i->set_position(pos_x, pos_y);
			i->set_width(width);
			i->set_height(height);

			intersections.push_back(i);
		}
	} else {
		std::cerr << "Could not open intersections file" << std::endl;
	}
}

void load_scenario_roads(std::string scenario, std::string file) {
	std::string path = Utils::get_scenario_road_file_path(scenario, file);
	std::cout << "Roads: " << path << std::endl;
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

			Road *r = new Road();
			r->set_start_intersection(get_intersection_from_id(start_int_id));
			r->set_end_intersection(get_intersection_from_id(end_int_id));
			r->set_speed_limit(speed_limit);
			r->set_distance(dist);

			std::cout << "Loading lanes" << std::endl;
			BOOST_FOREACH(boost::property_tree::ptree::value_type &forward_lanes,
					road.second.get_child(ROAD_LANES+"."+ROAD_FORWARD_LANES)) {
				std::cout << forward_lanes.second.data() << std::endl;
				r->add_lane_forward(load_road_lane(scenario, forward_lanes.second.data()));
			}

			BOOST_FOREACH(boost::property_tree::ptree::value_type &backward_lanes,
					road.second.get_child(ROAD_LANES+"."+ROAD_BACKWARD_LANES)) {
				std::cout << backward_lanes.second.data() << std::endl;
				r->add_lane_backward(load_road_lane(scenario, backward_lanes.second.data()));
			}

			roads.push_back(r);
		}
	} else {
		std::cerr << "Could not open road file" << std::endl;
	}
}

Lane* load_road_lane(std::string scenario, std::string file) {
	std::string path = Utils::get_scenario_lane_file_path(scenario, file);
	std::cout << "Lane: " << path << std::endl;
	Lane *l = new Lane();
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
			Position *p = new Position();
			p->set_position(ptx, pty);
			l->add_waypoint(p);
		}
	} else {
		std::cerr << "Could not open road file" << std::endl;
	}
	return l;
}

Intersection* get_intersection_from_id(int id) {
	Intersection *intersect = nullptr;
	for (unsigned int i = 0; i < intersections.size(); ++i) {
		if (intersections[i]->get_id() == id) {
			return intersections[i];
		}
	}
	return intersect;
}

/*
 * add the roads / intersections to the graph structure in the map
 */
void populate_map() {
	//for each road
	//get the two endpoint intersections
	//add the intersections as nodes
	//copy the road to the returned object.
	for (unsigned int r = 0; r < roads.size(); ++r) {
		//TODO: if road is not one way, also add in other direction
		Road *road = roads[r];
		Intersection *i1 = road->get_start_intersection();
		Intersection *i2 = road->get_end_intersection();
		map.add_edge(i1, i2, road);
	}
}


void insert_vehicle_data(std::ifstream &vehicle_file, std::string vid) {
	std::stringstream vbuf;
	vbuf << vehicle_file.rdbuf();
	boost::property_tree::ptree vehicle_data;
	boost::property_tree::read_json(vbuf, vehicle_data);
	boost::property_tree::ptree::value_type vehicle_state;
	BOOST_FOREACH(boost::property_tree::ptree::value_type &vehicle_state, vehicle_data.get_child(VEHICLE_DATA)) {
		//Data for each vehicle
		mongo::BSONObjBuilder b;

		double pos_x = vehicle_state.second.get<double>(VEHICLE_POSITION_X);
		double pos_y = vehicle_state.second.get<double>(VEHICLE_POSITION_Y);
		float accel = vehicle_state.second.get<float>(VEHICLE_ACCELERATION);
		float speed = vehicle_state.second.get<float>(VEHICLE_SPEED);
		float brake = vehicle_state.second.get<float>(VEHICLE_BRAKE_PRESSURE);
		float heading = vehicle_state.second.get<float>(VEHICLE_HEADING);
		float vturn = vehicle_state.second.get<float>(VEHICLE_VEHICLE_TURN_RATE);
		float wturn = vehicle_state.second.get<float>(VEHICLE_WHEEL_TURN_RATE);

		b.append(DBConn::ID, vid);
		b.append(DBConn::TIME, vehicle_state.second.get<float>(VEHICLE_TIME));
		b.append(DBConn::POSITION_X, pos_x);
		b.append(DBConn::POSITION_Y, pos_y);
		b.append(DBConn::ACCELERATION, accel);
		b.append(DBConn::SPEED, speed);
		b.append(DBConn::BRAKE_PRESSURE, brake);
		b.append(DBConn::HEADING, heading);
		b.append(DBConn::VEHICLE_TURN_RATE, vturn);
		b.append(DBConn::WHEEL_TURN_RATE, wturn);

		mongo::BSONObj vehicle_obj = b.obj();
		DBConn::insert_vehicle(vehicle_obj);
	}
}

/*
 * TODO: start all timers
 */
void start() {
	std::cout << "Starting scenario" << std::endl;
	start_time = boost::posix_time::microsec_clock::local_time();
	for (unsigned int i = 0; i < VehicleManager::get_vehicles().size(); ++i) {
		Vehicle* v = VehicleManager::get_vehicles()[i];
		v->start();
	}
	io_.run();
}

void stop() {
	std::cout << "Stopping scenario" << std::endl;
	for (unsigned int i = 0; i < VehicleManager::get_vehicles().size(); ++i) {
		Vehicle* v = VehicleManager::get_vehicles()[i];
		v->stop();
	}
}

/*
 *
 *
 * get data from database or cache for vehicle with given id
 * then populate into sensor.
 *
 */
void update_vehicle_sensor(const std::string &vid, VehicleSensor &sensor) {
	boost::posix_time::ptime cur_time = boost::posix_time::microsec_clock::local_time();
	boost::posix_time::time_duration diff = cur_time - start_time;
	long millis = diff.total_milliseconds();
	std::unique_ptr<mongo::DBClientCursor> cursor = DBConn::evaluate_query(DBConn::VEHICLE_PATH, vid, millis);
	while (cursor->more()) {
		mongo::BSONObj obj = cursor->next();
		sensor.set_acceleration(obj.getField(DBConn::ACCELERATION).Double());
		sensor.set_brake_pressure(obj.getField(DBConn::BRAKE_PRESSURE).Double());
		sensor.set_heading(obj.getField(DBConn::HEADING).Double());
		sensor.set_position(obj.getField(DBConn::POSITION_X).Double(), obj.getField(DBConn::POSITION_Y).Double());
		sensor.set_speed(obj.getField(DBConn::SPEED).Double());
		sensor.set_vehicle_turn_rate(obj.getField(DBConn::VEHICLE_TURN_RATE).Double());
		sensor.set_wheel_turn_rate(obj.getField(DBConn::WHEEL_TURN_RATE).Double());
	}
	cursor.release();
}


/*
 * Tests
 */
void test_get_closest_vehicles() {
	std::cout << "Num vehicles: " << VehicleManager::get_vehicles().size() << std::endl;
	for (unsigned int i = 0; i < VehicleManager::get_vehicles().size(); ++i) {
		Vehicle* v = VehicleManager::get_vehicles()[i];
		std::cout << v->get_readable_name() << ", " << v->get_id_as_string() << std::endl;
		std::vector<VehicleManager::VehicleDistPair> nearby = VehicleManager::get_nearest(v->get_sensor().get_position(), 2, 10);
		for (std::vector<VehicleManager::VehicleDistPair>::iterator vdistitr = nearby.begin(); vdistitr != nearby.end(); ++vdistitr) {
			std::cout << "    Found vehicle: " << (*vdistitr).second->get_readable_name() << " at distance " << (*vdistitr).first->get_distance() << std::endl;
		}
	}
}

void test_print_map() {
	map.print_map_data();
}

}
