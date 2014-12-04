/*
 * Utils.cpp
 *
 *  Created on: Sep 3, 2014
 *      Author: trevor
 */

#include "Utils.h"

namespace Utils {

boost::uuids::random_generator gen_uuid;

boost::asio::io_service _global_io;


std::string get_scenario_file_path(std::string file) {
	return SCENARIO_DATA_DIR + file + "/" + file + ".json";
}

std::string get_scenario_vehicle_file_path(std::string scenario, std::string file) {
	return SCENARIO_DATA_DIR + scenario + "/" + SCENARIO_VEHICLE_DATA_DIR + file;
}


std::string get_scenario_lane_file_path(std::string scenario, std::string file) {
	return SCENARIO_DATA_DIR + scenario + "/" + SCENARIO_LANE_DATA_DIR + file;
}

std::string get_scenario_hazard_file_path(std::string scenario, std::string file) {
	return SCENARIO_DATA_DIR + scenario + "/" + SCENARIO_HAZARD_DATA_DIR + file;
}

std::string get_scenario_intersection_file_path(std::string scenario, std::string file) {
	return SCENARIO_DATA_DIR + scenario + "/" + file;
}

std::string get_scenario_road_file_path(std::string scenario, std::string file) {
	return SCENARIO_DATA_DIR + scenario + "/" + file;
}

boost::asio::io_service& get_global_io_service() {
	return _global_io;
}


void start_io() {
	_global_io.run();
}

void stop_io() {
	_global_io.stop();
}

}

