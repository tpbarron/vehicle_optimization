/**
 * VehicleSensorModule.cpp
 *	
 *  Created on: Nov 1, 2014
 *      Author: trevor
 */

#include "VehicleSensorModule.h"

VehicleSensorModule::VehicleSensorModule(boost::asio::io_service::strand &strand) :
	_mediator(nullptr),
	_strand(strand),
	_broadcast_timer(strand.get_io_service(), boost::posix_time::milliseconds(500)),
	_broadcast_thread(nullptr),
	_count(0) {
}

VehicleSensorModule::~VehicleSensorModule() {
	delete _broadcast_thread;
}

void VehicleSensorModule::set_mediator(ModuleMediator *mediator) {
	_mediator = mediator;
}


void VehicleSensorModule::start() {
	std::cout << "Starting vehicle sensor module" << std::endl;
	// Start timer to send out updates
	_broadcast_timer.async_wait(_strand.wrap(boost::bind(&VehicleSensorModule::update, this)));
	_broadcast_thread = new boost::thread(boost::bind(
			static_cast<size_t (boost::asio::io_service::*)()> (&boost::asio::io_service::run),
			boost::ref(_strand.get_io_service())));
}

void VehicleSensorModule::stop() {
	_broadcast_thread->join();
}

/**
 * Initialize memory and populate necessary data such as data struct
 */
void VehicleSensorModule::init(Position &p) {
	//just set initial position
	_sensor.set_acceleration(0);
	_sensor.set_brake_pressure(0);
	_sensor.set_heading(0);
	_sensor.set_position(p);
	_sensor.set_speed(0);
	_sensor.set_vehicle_turn_rate(0);
	_sensor.set_wheel_turn_rate(0);
}

void VehicleSensorModule::set_vehicle_uuid(std::string uuid) {
	_data.VEHICLE_UUID = uuid;
}

void VehicleSensorModule::set_speed(const Speed &s) {
	_sensor.set_speed(s);
}

void VehicleSensorModule::set_position(const Position &p) {
	_sensor.set_position(p);
}

void VehicleSensorModule::set_heading(const Heading &h) {
	_sensor.set_heading(h);
}

std::string VehicleSensorModule::to_string() {
	return _sensor.to_string();
}


void VehicleSensorModule::update() {
	if (_count < 10) {
		broadcast();
		_broadcast_timer.expires_at(_broadcast_timer.expires_at() + boost::posix_time::milliseconds(500));
		_broadcast_timer.async_wait(boost::bind(&VehicleSensorModule::update, this));
		_count++;
	}
}

/**
 * Broadcasts a message to all listeners
 */
void VehicleSensorModule::broadcast() {
	std::cout << "VehicleSensorModule broadcasting" << std::endl;

}