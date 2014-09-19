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
#include "../sensor/VehicleSensor.h"
#include "../utils/Utils.h"
#include "../data_manager/VehicleManager.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/asio.hpp>

class Scenario {
public:

	Scenario();
	~Scenario();

	void load_scenario(std::string file);
	void load_vehicle(std::string vehicle_name, std::string vehicle_file);
	void insert_vehicle_data(std::ifstream &vehicle_file, std::string vid);

	void start();
	void stop();

	static void update_vehicle_sensor(const std::string &vid, VehicleSensor &sensor);

	void test_get_closest_vehicles();

private:

	boost::asio::io_service io_;
	boost::asio::strand strand_;

	/*
	 * TODO: should this whole class have static members?
	 * Should it just be a namespace?
	 */
	static boost::posix_time::ptime start_time;

};

#endif /* SCENARIO_H_ */
