/*
 * Vehicle.h
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <iostream>
#include <unordered_set>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "data_manager/VehicleManager.h"
#include "data_types/Distance.h"
#include "IVehicleDataListener.h"
#include "sensor/VehicleSensor.h"
#include "sensor/VehicleSensorData.h"
#include "sim/Scenario.h"
#include "utils/Utils.h"


class Vehicle : public IVehicleDataListener {

public:
	Vehicle(std::string name, boost::asio::io_service *io, boost::asio::strand *strand);
	virtual ~Vehicle();

	/*
	 * Start the timer update loop in a thread
	 */
	void start();

	/*
	 * Stop thread / timers
	 */
	void stop();
	/*
	 * Send out the data to all the listeners
	 */
	void broadcast_data();

	/*
	 * Add a new listener to broadcast data to
	 */
	void add_listener(Vehicle &l);
	virtual void recv(struct VehicleSensorData &data);

	void set_stopping_dist(Distance &dist);

	const boost::uuids::uuid get_id() const;
	const std::string get_id_as_string() const;
	const std::string get_readable_name() const;

	Distance* get_stopping_dist();

	VehicleSensor& get_sensor();



private:

	struct vehicle_hash {
	    size_t operator()(const Vehicle *v ) const
	    {
	        return std::hash<std::string>()((*v).get_id_as_string());
	    }
	};


	boost::uuids::uuid id;
	std::string readable_name;
	VehicleSensor sensor;
	Distance stopping_dist;

	//Timer
	boost::asio::deadline_timer *timer;
	boost::asio::io_service *_io;
	boost::asio::strand *_strand;
	int count_;

	boost::thread *t;


	//Data struct
	struct VehicleSensorData* data;

	std::unordered_set<Vehicle*, vehicle_hash> listeners;

	void populate_data_struct();


	/*
	 * Called regularly to update both check for new nearby vehicles
	 * and send out any necessary data
	 */
	void update();


	void compute();

	bool should_warn();
	/*
	 * Calculates stopping distance based on weight, current speed, and road conditions
	 */
	void calc_stopping_dist();

};

#endif /* VEHICLE_H_ */
