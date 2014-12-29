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

#include <boost/asio/io_service.hpp>
#include <boost/asio/strand.hpp>

namespace Utils {

extern boost::uuids::random_generator gen_uuid;

extern boost::asio::io_service _global_io;
extern boost::asio::io_service::work _global_work;


const std::string SCENARIO_DATA_DIR = "data/scenarios/";
const std::string SCENARIO_VEHICLE_DATA_DIR = "vehicles/";
const std::string SCENARIO_LANE_DATA_DIR = "lanes/";
const std::string SCENARIO_HAZARD_DATA_DIR = "hazards/";

std::string get_scenario_file_path(std::string);
std::string get_scenario_vehicle_file_path(std::string scenario, std::string file);
std::string get_scenario_lane_file_path(std::string scenario, std::string file);
std::string get_scenario_hazard_file_path(std::string scenario, std::string file);
std::string get_scenario_intersection_file_path(std::string scenario, std::string file);
std::string get_scenario_road_file_path(std::string scenario, std::string file);

boost::asio::io_service& get_global_io_service();
void start_io();
void stop_io();

};

#endif /* UTILS_H_ */

