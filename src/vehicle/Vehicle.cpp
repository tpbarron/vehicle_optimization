/*
 * Vehicle.cpp
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#include "Vehicle.h"

#include "utils/Logger.h"

/**
 * Create a Vehicle object
 *
 * @param name the readable name
 */
Vehicle::Vehicle(std::string name) :
	_readable_name(name),
	_type(VehicleType::TYPE_UNKNOWN_VEHICLE) {

	_id = Utils::gen_uuid();
}

/**
 * Free the Vehicle memory
 */
Vehicle::~Vehicle() {
}


/**
 * Start the Vehicle internal simulation
 */
void Vehicle::start() {
	Logger::info("Starting vehicle");
	_module_manager.init(get_id());
	_module_manager.generate_route();
	_module_manager.start();
}


/**
 * Joins the Vehicle's update threads
 */
void Vehicle::stop() {
	_module_manager.stop();
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
	Logger::info("Adding listener to vehicle " + get_id());
	_module_manager.add_listener(l);
}


/**
 * Entry point for data coming in from other Vehicle.
 * Compute as necessary using received data
 *
 * @param msg the incoming Message
 */
void Vehicle::recv(Message *mesg) {
	Logger::info(get_id() + ": received data, sending to ModuleManager");
	_module_manager.recv(mesg);
}



/*
 *
 * -------------------
 * - Setters	     -
 * -------------------
 *
 */


void Vehicle::set_start_position(double x, double y) {
	Position p(x, y);
	_module_manager.set_start_position(p);
}

void Vehicle::set_goal_position(double x, double y) {
	Position p(x, y);
	_module_manager.set_goal_position(p);
}

/**
 * Give the manager a copy of the initial map. It is stored in the RoutingModule
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

const Position& Vehicle::get_position() const {
	return _module_manager.get_current_position();
}

const boost::uuids::uuid Vehicle::get_id_as_uuid() const {
	return _id;
}

const std::string Vehicle::get_id() const {
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
const std::string Vehicle::to_string() const {
	return _readable_name + ": " + get_id();
}
