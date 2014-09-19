/*
 * DBConn.h
 *
 *  Created on: Sep 8, 2014
 *      Author: trevor
 */

#ifndef DBCONN_H_
#define DBCONN_H_

#include "mongo/client/dbclient.h"

#include <string>

namespace DBConn {

	//scenario
	const std::string SCENARIO_PATH = "scenario.vehicles";
	const std::string SCENARIO_NAME = "name";

	//Vehicle entries
	const std::string VEHICLE_PATH = "scenario.vehicles.data";
	const std::string ID = "id";
	const std::string TIME = "time";
	const std::string POSITION_X = "pos_x";
	const std::string POSITION_Y = "pos_y";
	const std::string ACCELERATION = "accel";
	const std::string SPEED = "speed";
	const std::string BRAKE_PRESSURE = "brake";
	const std::string HEADING = "heading";
	const std::string VEHICLE_TURN_RATE = "vturn";
	const std::string WHEEL_TURN_RATE = "wturn";

	extern mongo::DBClientConnection c;

	bool connect_to_db();
	void init();

	void clear_db();

	void insert_scenario(mongo::BSONObj &obj);

	void insert_vehicle(mongo::BSONObj &obj);
	std::unique_ptr<mongo::DBClientCursor> evaluate_query(const std::string query, const std::string vid, const double millis);

}

#endif /* DBCONN_H_ */
