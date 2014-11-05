/*
 * Vehicle.cpp
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#include "Vehicle.h"

/**
 * Create a Vehicle object
 *
 * @param name the readable name
 */
Vehicle::Vehicle(std::string name) :
		_last_update_time(boost::posix_time::microsec_clock::local_time()),
		_self_update_timer(_self_update_io, boost::posix_time::milliseconds(100)) {

	_id = Utils::gen_uuid();
	_readable_name = name;
	_type = VehicleType::TYPE_UNKNOWN_VEHICLE;

	_self_update_thread = nullptr;
}

/**
 * Free the Vehicle memory
 */
Vehicle::~Vehicle() {
	delete _self_update_thread;
}


/**
 * Start the Vehicle internal simulation
 */
void Vehicle::start() {
	_module_manager.init_sensor(get_id_as_string());
	_module_manager.generate_route();
	_module_manager.start();


	// Start timer to update own position along route..
	_self_update_timer.async_wait(boost::bind(&Vehicle::update_self, this));
	_self_update_thread = new boost::thread(boost::bind(
			static_cast<size_t (boost::asio::io_service::*)()> (&boost::asio::io_service::run),
			boost::ref(_self_update_io)));
}


/**
 * Joins the Vehicle's update threads
 */
void Vehicle::stop() {
	_module_manager.stop();
	_self_update_thread->join();
}

/*
 *
 * -------------------
 * - Communication   -
 * -------------------
 *
 */


/**
 * Add a new object that will listen to updates from this Vehicle
 *
 * @param l the object to add to the listeners list
 */
void Vehicle::add_listener(IVehicleDataListener &l) {
	std::cout << "Adding listener to vehicle " << get_id_as_string() << std::endl;
	_module_manager.add_listener(l);
}


/**
 * Entry point for data coming in from other Vehicle.
 * Compute as necessary using received data
 *
 * @param data the data struct sent out by a nearby Vehicle
 */
void Vehicle::recv(Message &msg) {
	std::cout << get_id_as_string() << ": received data, sending to module manager" << std::endl;
	_module_manager.recv(msg);
}



/*
 *
 * -------------------
 * - Update self     -
 * -------------------
 *
 */

/**
 * Called regularly to move this Vehicle along route
 */
void Vehicle::update_self() {
	std::cout << "Updating self: " << get_id_as_string() << std::endl;
	_self_update_timer.expires_at(_self_update_timer.expires_at() + boost::posix_time::milliseconds(100));
	_self_update_timer.async_wait(boost::bind(&Vehicle::update_self, this));

	//Get time diff, calc new position from current
	boost::posix_time::ptime cur_time = boost::posix_time::microsec_clock::local_time();
	boost::posix_time::time_duration diff = cur_time - _last_update_time;
	long diff_millis = diff.total_milliseconds();
	calculate_progress(diff_millis);

	_last_update_time = cur_time;

	std::cout << _module_manager.sensor_to_string() << std::endl;
}


/**
 * Given elapsed time since last update calculates progress
 *
 * @param millis the time in milliseconds since the last update
 */
void Vehicle::calculate_progress(long millis) {
//	// Get the allowed speed at the current position
//	Speed speed = _module_manager.get_current_speed();
//	_sensor.set_speed(speed.get_speed());
//
//	// Get the distance in meters that would be covered in the allotted time
//	Distance dist = speed.get_distance_for_time(millis);
//	// Get a new position from the route after moving dist towards destination
//	// TODO: there could have been a road change here and thus a speed change
//	// Perhaps the update is frequent enough that it isn't important to
//	// refresh immediately.
//	Position pos = _module_manager.get_new_position(dist);
//	_sensor.set_position(pos);
//
//	// Get the heading from the route using the last two positions
//	Heading hdng = _module_manager.get_current_heading();
//	_sensor.set_heading(hdng.get_heading());
//
//	// TODO: for now assume the following are constant
//	_sensor.set_acceleration(0);
//	_sensor.set_brake_pressure(0);
//	_sensor.set_vehicle_turn_rate(0);
//	_sensor.set_wheel_turn_rate(0);

}

/*
 *
 * -------------------
 * - Setters	     -
 * -------------------
 *
 */


/*
 *
 */
void Vehicle::set_stopping_dist(Distance &dist) {

}

void Vehicle::set_start_position(double x, double y) {
	Position p(x, y);
	_module_manager.set_start_position(p);
}

void Vehicle::set_goal_position(double x, double y) {
	Position p(x, y);
	_module_manager.set_goal_position(p);
}

/*
 * TODO: do both the vehicle and the route need a map reference?
 */
void Vehicle::set_map(Map &m) {
	_module_manager.set_map(m);
}

void Vehicle::set_type_from_string(std::string type) {
	if (type == "default") {
		_type = VehicleType::TYPE_DEFAULT_VEHICLE;
	} else if (type == "emergency") {
		_type = VehicleType::TYPE_EMERGENCY_VEHICLE;
	} else if (type == "unknown") {
		_type = VehicleType::TYPE_UNKNOWN_VEHICLE;
	}
}

void Vehicle::set_type(VehicleType t) {
	_type = t;
}

/*
 *
 * -------------------
 * - Getters	     -
 * -------------------
 *
 */

const boost::uuids::uuid Vehicle::get_id() const {
	return _id;
}

const std::string Vehicle::get_id_as_string() const {
	return boost::uuids::to_string(_id);
}

const std::string Vehicle::get_readable_name() const {
	return _readable_name;
}

const ModuleManager& Vehicle::get_module_manager() const {
	return _module_manager;
}


/**
 *
 * Return a unique name for this Vehicle as
 *
 * Readable name: UUID
 */
std::string Vehicle::to_string() {
	return _readable_name + ": " + get_id_as_string();
}
