/*
 * DBConn.cpp
 *
 *  Created on: Sep 8, 2014
 *      Author: trevor
 */

#include "DBConn.h"

const std::string VEHICLE_PATH = "scenario.vehicles.data";

DBConn::DBConn() {
	if (!connect()) {
		std::cerr << "Unable to connect to mongo db.\nIs the mongod service running?" << std::endl;
		exit(1);
	}
}

DBConn::~DBConn() {
	// TODO Auto-generated destructor stub
}

bool DBConn::connect() {
	try {
		c.connect("localhost");
		return true;
	} catch (const mongo::DBException &e ) {
		return false;
	}
}

void DBConn::insert_vehicle(mongo::BSONObj &obj) {
	c.insert(VEHICLE_PATH, obj);
}
