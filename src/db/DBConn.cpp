/*
 * DBConn.cpp
 *
 *  Created on: Sep 16, 2014
 *      Author: trevor
 */

#include "DBConn.h"


namespace DBConn {

	mongo::DBClientConnection c;

	bool connect_to_db() {
		try {
			c.connect("localhost");
			return true;
		} catch (const mongo::DBException &e ) {
			std::cout << e.what() << std::endl;
			return false;
		}
	}

	void init() {
		if (!connect_to_db()) {
			std::cerr << "Unable to connect to mongo db.\nIs the mongod service running?" << std::endl;
			exit(1);
		}
	}

	void insert_vehicle(mongo::BSONObj &obj) {
		c.insert(VEHICLE_PATH, obj);
	}

	std::unique_ptr<mongo::DBClientCursor> evaluate_query(std::string query, const std::string vid, const double millis) {
		std::cout << "Evaluating query: " << query << ", at millis: " << millis << std::endl;
		/*
		 * Query will look like the following,
		 * perhaps better parameters would be
		 * id, start time, end time
		 * db.vehicles.data.find(
		 * 		{
		 * 			id: "d4120077-6703-4cf1-bf18-c5b56b4c8138"
		 * 			$and: [
		 * 				{time: { $lt: 1.123 }},
		 * 				{time: { $gt: 0.5 }}
		 * 			]
		 * 		}
		 * )
		 */
		std::unique_ptr<mongo::DBClientCursor> cursor = c.query(query,
				BSON(DBConn::ID << vid << DBConn::TIME << static_cast<int>(millis/1000+.5))
		);
		return cursor;
	}

}


