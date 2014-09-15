/*
 * Scenario.h
 *
 *  Created on: Sep 8, 2014
 *      Author: trevor
 */

#ifndef SCENARIO_H_
#define SCENARIO_H_

#include "../db/DBConn.h"

#include "../vehicle/Vehicle.h"
#include "../utils/Utils.h"
#include "../data_manager/VehicleManager.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <boost/uuid/uuid.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/asio.hpp>
#include <boost/utility.hpp>

class Scenario {
public:

	Scenario();
	~Scenario();

	void load_scenario(std::string file);
	void load_vehicle(std::string vehicle_name, std::string vehicle_file);

	void start();
	void stop();

	void update_sensor_data(boost::uuids::uuid &vid);

	void test_get_closest_vehicles();

private:

	DBConn conn;

	boost::asio::io_service io_;
	boost::asio::strand strand_;


};

#endif /* SCENARIO_H_ */
