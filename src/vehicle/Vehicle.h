/*
 * Vehicle.h
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "IVehicleDataListener.h"
#include "data_manager/VehicleManager.h"
#include "data_types/sensor_types/Distance.h"
#include "data_types/message_types/Message.h"
#include "data_types/module_types/Hazard.h"

#include "vehicle/modules/routing/Route.h"
#include "vehicle/modules/ModuleManager.h"
#include "vehicle/modules/HazardWarningModule.h"

#include "sensor/VehicleSensor.h"
#include "sensor/VehicleSensorData.h"
#include "sim/Scenario.h"
#include "utils/Utils.h"

class Vehicle : public IVehicleDataListener {

public:
	Vehicle(std::string name);
	virtual ~Vehicle();

	void init();
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
	virtual void add_listener(IVehicleDataListener &l);
	virtual void recv(Message &msg);

	/*
	 * Setters
	 */
	void set_stopping_dist(Distance &dist);
	void set_start_position(double x, double y);
	void set_goal_position(double x, double y);
	void set_map(Map &m);

	/*
	 * Getters
	 */
	const boost::uuids::uuid get_id() const;
	const std::string get_id_as_string() const;
	const std::string get_readable_name() const;
	const ModuleManager& get_module_manager() const;

private:


	boost::uuids::uuid _id;
	std::string _readable_name;

	// Self update
	boost::posix_time::ptime _last_update_time;
	boost::asio::io_service _self_update_io;
	boost::asio::deadline_timer _self_update_timer;
	boost::thread *_self_update_thread;

	// Modules
	ModuleManager _module_manager;

	/*
	 * Called to update the own vehicle position...
	 */
	void update_self();
	void calculate_progress(long millis);


	virtual std::string to_string();

};

#endif /* VEHICLE_H_ */
