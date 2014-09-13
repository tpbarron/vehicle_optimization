/*
 * Scenario.cpp
 *
 *  Created on: Sep 8, 2014
 *      Author: trevor
 */

#include "Scenario.h"

#include <boost/foreach.hpp>

Scenario::Scenario() : strand_(io_) {

}


Scenario::~Scenario() {
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
		std::string desc = tree.get<std::string>("_desc");
		std::cout << "Loading scenario into db: " << desc << std::endl;

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
		Vehicle v(name, &io_, &strand_);
		vehicles.push_back(v);
		std::stringstream vbuf;
		vbuf << vehicle_file.rdbuf();
		boost::property_tree::ptree vehicle_data;
		boost::property_tree::read_json(vbuf, vehicle_data);
		boost::property_tree::ptree::value_type vehicle_state;
		BOOST_FOREACH(boost::property_tree::ptree::value_type &vehicle_state, vehicle_data.get_child("data")) {
			//Data for each vehicle
			mongo::BSONObjBuilder b;
			b.append("id", v.get_id_as_string());
			b.append("time", vehicle_state.second.get<float>("time"));
			b.append("pos_lat", vehicle_state.second.get<float>("pos_lat"));
			b.append("pos_lng", vehicle_state.second.get<float>("pos_lng"));
			b.append("accel", vehicle_state.second.get<float>("accel"));
			b.append("speed", vehicle_state.second.get<float>("speed"));
			b.append("brake", vehicle_state.second.get<float>("brake"));
			b.append("heading", vehicle_state.second.get<float>("heading"));
			b.append("vturn", vehicle_state.second.get<float>("vturn"));
			b.append("wturn", vehicle_state.second.get<float>("wturn"));
			mongo::BSONObj vehicle_obj = b.obj();
			conn.insert_vehicle(vehicle_obj);
		}
	} else {
		std::cerr << "Unable to open vehicle file" << std::endl;
	}
}

/*
 * TODO: start all timers
 */
void Scenario::start() {
	for (std::vector<Vehicle>::iterator it = vehicles.begin(); it != vehicles.end(); ++it) {
		(*it).start();
	}
}

void Scenario::stop() {
	//
}

void Scenario::update_sensor_data(boost::uuids::uuid &vid) {

}

