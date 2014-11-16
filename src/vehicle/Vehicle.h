/*
 * Vehicle.h
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <iostream>

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

	enum VehicleType {
		TYPE_DEFAULT_VEHICLE,
		TYPE_EMERGENCY_VEHICLE,
		TYPE_UNKNOWN_VEHICLE
	};

	Vehicle(std::string name);
	virtual ~Vehicle();

	void init();
	/*
	 * Start the timer update loop in a thread
	 */
	void start();
	void thread_start();

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
	void set_start_position(double x, double y);
	void set_goal_position(double x, double y);
	void set_map(Map &m);
	void set_type_from_string(std::string type);
	void set_type(VehicleType t);

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
	VehicleType _type;

	// Modules
	ModuleManager _module_manager;

	// Vehicle thread
	boost::thread *_vehicle_thread;


	virtual std::string to_string();

};

#endif /* VEHICLE_H_ */
