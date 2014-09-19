/*
 * Scenario.cpp
 *
 *  Created on: Sep 8, 2014
 *      Author: trevor
 */

#include "Scenario.h"

#include <boost/foreach.hpp>

boost::posix_time::ptime Scenario::start_time;


Scenario::Scenario() : strand_(io_) {
	DBConn::init();
}


Scenario::~Scenario() {
	for (unsigned int i = 0; i < VehicleManager::get_vehicles().size(); ++i) {
		delete VehicleManager::get_vehicles()[i];
	}
}


void Scenario::load_scenario(std::string file) {
	//read json file and insert into db
	std::ifstream in(file.c_str());
	if (in.is_open()) {
		std::stringstream buf;
		buf << in.rdbuf();
		in.close();
		boost::property_tree::ptree tree;
		boost::property_tree::read_json(buf, tree);

		//Empty an data
		DBConn::clear_db();

		std::string name = tree.get<std::string>("_name");
		std::string desc = tree.get<std::string>("_desc");

		std::cout << "Loading scenario into db: " << desc << std::endl;

		mongo::BSONObjBuilder b;
		b.append("name", name);
		b.append("desc", desc);

		mongo::BSONObj scenario_obj = b.obj();
		DBConn::insert_scenario(scenario_obj);

		//vehicles
		boost::property_tree::ptree::value_type v;
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, tree.get_child("vehicles")) {
			std::string vname = v.second.get<std::string>("name");
			std::string vfile = Utils::DATA_DIR+v.second.get<std::string>("data");
			std::cout << vname << ": " << vfile << std::endl;
			load_vehicle(vname, vfile);
		}
	} else {
		std::cerr << "Unable to open scenario file" << std::endl;
	}
}

void Scenario::load_vehicle(std::string name, std::string file) {
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

void Scenario::insert_vehicle_data(std::ifstream &vehicle_file, std::string vid) {
	std::stringstream vbuf;
	vbuf << vehicle_file.rdbuf();
	boost::property_tree::ptree vehicle_data;
	boost::property_tree::read_json(vbuf, vehicle_data);
	boost::property_tree::ptree::value_type vehicle_state;
	BOOST_FOREACH(boost::property_tree::ptree::value_type &vehicle_state, vehicle_data.get_child("data")) {
		//Data for each vehicle
		mongo::BSONObjBuilder b;

		double pos_x = vehicle_state.second.get<double>("pos_x");
		double pos_y = vehicle_state.second.get<double>("pos_y");
		float accel = vehicle_state.second.get<float>("accel");
		float speed = vehicle_state.second.get<float>("speed");
		float brake = vehicle_state.second.get<float>("brake");
		float heading = vehicle_state.second.get<float>("heading");
		float vturn = vehicle_state.second.get<float>("vturn");
		float wturn = vehicle_state.second.get<float>("wturn");

		b.append("id", vid);
		b.append("time", vehicle_state.second.get<float>("time"));
		b.append("pos_x", pos_x);
		b.append("pos_y", pos_y);
		b.append("accel", accel);
		b.append("speed", speed);
		b.append("brake", brake);
		b.append("heading", heading);
		b.append("vturn", vturn);
		b.append("wturn", wturn);

		mongo::BSONObj vehicle_obj = b.obj();
		DBConn::insert_vehicle(vehicle_obj);
	}
}

/*
 * TODO: start all timers
 */
void Scenario::start() {
	std::cout << "Starting scenario" << std::endl;
	start_time = boost::posix_time::microsec_clock::local_time();
	for (unsigned int i = 0; i < VehicleManager::get_vehicles().size(); ++i) {
		Vehicle* v = VehicleManager::get_vehicles()[i];
		v->start();
	}
	io_.run();
}

void Scenario::stop() {
	std::cout << "Stopping scenario" << std::endl;
	for (unsigned int i = 0; i < VehicleManager::get_vehicles().size(); ++i) {
		Vehicle* v = VehicleManager::get_vehicles()[i];
		v->stop();
	}
}

/*
 * Static function
 *
 * get data from database or cache for vehicle with given id
 * then populate into sensor.
 *
 */
void Scenario::update_vehicle_sensor(const std::string &vid, VehicleSensor &sensor) {
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
void Scenario::test_get_closest_vehicles() {
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
