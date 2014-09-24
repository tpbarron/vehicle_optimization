/*
 * Utils.h
 *
 *  Created on: Sep 3, 2014
 *      Author: trevor
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <string>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

class Utils {

public:

	Utils();
	~Utils();

	const static std::string SCENARIO_DATA_DIR;
	const static std::string SCENARIO_VEHICLE_DATA_DIR;
	const static std::string SCENARIO_LANE_DATA_DIR;

	static boost::uuids::random_generator gen_uuid;

	static std::string get_scenario_file_path(std::string);
	static std::string get_scenario_vehicle_file_path(std::string scenario, std::string file);
	static std::string get_scenario_lane_file_path(std::string scenario, std::string file);
	static std::string get_scenario_intersection_file_path(std::string scenario, std::string file);
	static std::string get_scenario_road_file_path(std::string scenario, std::string file);

};

#endif /* UTILS_H_ */

