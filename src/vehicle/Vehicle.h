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
#include "map/routing/Route.h"
#include "sensor/VehicleSensor.h"
#include "sensor/VehicleSensorData.h"
#include "sim/Scenario.h"
#include "utils/Utils.h"


class Vehicle : public IVehicleDataListener {

public:
	Vehicle(std::string name, boost::asio::io_service *io, boost::asio::strand *strand);
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
	virtual void recv(struct VehicleSensorData &data);

	/*
	 * Setters
	 */
	void set_stopping_dist(Distance &dist);
	void set_start_position(double x, double y);
	void set_goal_position(double x, double y);
	void set_map(Map *m);

	/*
	 * Getters
	 */
	const boost::uuids::uuid get_id() const;
	const std::string get_id_as_string() const;
	const std::string get_readable_name() const;
	Distance* get_stopping_dist();
	VehicleSensor& get_sensor();


private:

	struct vehicle_hash {
	    size_t operator()(IVehicleDataListener *v) const
	    {
	        return std::hash<std::string>()(v->to_string());
	    }
	};


	boost::uuids::uuid _id;
	std::string _readable_name;
	VehicleSensor _sensor;
	Distance _stopping_dist;

	// Timer
	boost::asio::deadline_timer *_timer;
	boost::asio::io_service *_io;
	boost::asio::strand *_strand;
	int _count;
	boost::thread *_t;

	// Self update
	boost::posix_time::ptime _last_update_time;
	boost::asio::io_service _self_update_io;
	boost::asio::deadline_timer _self_update_timer;
	boost::thread *_self_update_thread;


	// Routing
	Map *_map;
	Route _route;
	Position _start_position;
	Position _goal_position;

	// Data struct
	struct VehicleSensorData* _data;

	std::unordered_set<IVehicleDataListener*, vehicle_hash> _listeners;

	void populate_data_struct();

	/*
	 * Called to update the own vehicle position...
	 * TODO: is it possible to only have one timer?
	 */
	void update_self();
	void calculate_progress(long millis);

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

	virtual std::string to_string();

};

#endif /* VEHICLE_H_ */
