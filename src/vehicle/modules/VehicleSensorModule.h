/**
 * VehicleSensorModule.h
 *	
 *  Created on: Nov 1, 2014
 *      Author: trevor
 */

#ifndef VEHICLESENSORMODULE_H_
#define VEHICLESENSORMODULE_H_

#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>

#include "data_types/sensor_types/Position.h"

#include "sensor/VehicleSensor.h"
#include "sensor/VehicleSensorData.h"


/**
 *
 */
class VehicleSensorModule {
public:

	VehicleSensorModule();
	virtual ~VehicleSensorModule();

	void start();
	void stop();

	void init(Position &p);
	void set_vehicle_uuid(std::string uuid);
	std::string to_string();

private:

	VehicleSensor _sensor;
	VehicleSensorData _data;

	//Data broadcast timer
	boost::asio::io_service _broadcast_io;
	boost::asio::deadline_timer _broadcast_timer;
	boost::thread *_broadcast_thread;
	int _count;

	void update();
	void broadcast();

};

#endif /* VEHICLESENSORMODULE_H_ */
