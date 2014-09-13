/*
 * DBConn.h
 *
 *  Created on: Sep 8, 2014
 *      Author: trevor
 */

#ifndef DBCONN_H_
#define DBCONN_H_

#include "mongo/client/dbclient.h"

//TODO: make this a singleton, only want one DB Connection
class DBConn {
public:
	DBConn();
	virtual ~DBConn();

	bool connect();

	void insert_vehicle(mongo::BSONObj &obj);

private:

	mongo::DBClientConnection c;


};

#endif /* DBCONN_H_ */
