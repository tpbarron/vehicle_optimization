/*
 * Vehicle.h
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <iostream>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "vehicle/IVehicleDataListener.h"
#include "vehicle/modules/ModuleManager.h"

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
	 * Start the vehicle simulation
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
	void set_start_position(double x, double y);
	void set_goal_position(double x, double y);
	void set_map(Map &m);
	void set_type_from_string(std::string type);
	void set_type(VehicleType t);

	/*
	 * Getters
	 */
	const Position get_position() const;
	const boost::uuids::uuid get_id_as_uuid() const;
	const std::string get_id() const;
	const std::string get_readable_name() const;
	const ModuleManager& get_module_manager() const;

private:


	boost::uuids::uuid _id;
	std::string _readable_name;
	VehicleType _type;

	// Modules
	ModuleManager _module_manager;


	const std::string to_string() const;

};

#endif /* VEHICLE_H_ */
