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

#include "utils/Utils.h"

class ModuleMediator;

/**
 *
 */
class VehicleSensorModule {
public:

	VehicleSensorModule();
	virtual ~VehicleSensorModule();

	void set_mediator(ModuleMediator *mediator);

	void start();
	void stop();

	void init(const Position &p);
	void set_vehicle_uuid(std::string uuid);

	void set_speed(const Speed &s);
	void set_position(const Position &p);
	void set_heading(const Heading &h);

	const Position& get_position() const;

	std::string to_string();

private:

	ModuleMediator *_mediator;

	VehicleSensor _sensor;
	VehicleSensorData _data;

	//Data broadcast timer
	boost::asio::deadline_timer _broadcast_timer;
	boost::thread *_broadcast_thread;
	int _count;

	void update();
	void broadcast();

};

#endif /* VEHICLESENSORMODULE_H_ */
