/*
 * Utils.cpp
 *
 *  Created on: Sep 3, 2014
 *      Author: trevor
 */

#include "Utils.h"

const std::string Utils::SCENARIO_DATA_DIR = "data/scenarios/";

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
	return scenario.substr(0, scenario.rfind("/")) + "/vehicles/" + file;
}
