/*
 * Utils.cpp
 *
 *  Created on: Sep 3, 2014
 *      Author: trevor
 */

#include "Utils.h"

const std::string Utils::SCENARIO_DATA_DIR = "data/scenarios/";
const std::string Utils::SCENARIO_VEHICLE_DATA_DIR = "vehicles/";
const std::string Utils::SCENARIO_LANE_DATA_DIR = "lanes/";

boost::uuids::random_generator Utils::gen_uuid;

Utils::Utils() {
}

Utils::~Utils() {
	// TODO Auto-generated destructor stub
}

std::string Utils::get_scenario_file_path(std::string file) {
	return SCENARIO_DATA_DIR + file + "/" + file + ".json";
}

std::string Utils::get_scenario_vehicle_file_path(std::string scenario, std::string file) {
	return SCENARIO_DATA_DIR + scenario + "/" + SCENARIO_VEHICLE_DATA_DIR + file;
}


std::string Utils::get_scenario_lane_file_path(std::string scenario, std::string file) {
	return SCENARIO_DATA_DIR + scenario + "/" + SCENARIO_LANE_DATA_DIR + file;
}

std::string Utils::get_scenario_intersection_file_path(std::string scenario, std::string file) {
	return SCENARIO_DATA_DIR + scenario + "/" + file;
}

std::string Utils::get_scenario_road_file_path(std::string scenario, std::string file) {
	return SCENARIO_DATA_DIR + scenario + "/" + file;
}

