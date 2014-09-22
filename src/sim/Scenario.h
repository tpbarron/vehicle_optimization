/*
 * Scenario.h
 *
 *  Created on: Sep 8, 2014
 *      Author: trevor
 */

#ifndef SCENARIO_H_
#define SCENARIO_H_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/asio.hpp>

#include "data_manager/VehicleManager.h"
#include "db/DBConn.h"
#include "sensor/VehicleSensor.h"
#include "utils/Utils.h"
#include "vehicle/Vehicle.h"

namespace Scenario {

void init();
void cleanup();

void load_scenario(std::string file);
void load_vehicle(std::string vehicle_name, std::string vehicle_file);
void insert_vehicle_data(std::ifstream &vehicle_file, std::string vid);

void start();
void stop();

void update_vehicle_sensor(const std::string &vid, VehicleSensor &sensor);

void test_get_closest_vehicles();

extern boost::asio::io_service io_;
extern boost::asio::strand strand_;
extern boost::posix_time::ptime start_time;

};

#endif /* SCENARIO_H_ */
