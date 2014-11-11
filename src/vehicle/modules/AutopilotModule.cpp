/**
 * AutopilotModule.cpp
 *	
 *  Created on: Nov 2, 2014
 *      Author: trevor
 */

#include "AutopilotModule.h"

AutopilotModule::AutopilotModule() :
	_mediator(nullptr),
	_last_update_time(boost::posix_time::microsec_clock::local_time()),
	_self_update_timer(_self_update_io, boost::posix_time::milliseconds(100)),
	_self_update_thread(nullptr) {
}

AutopilotModule::~AutopilotModule() {
	delete _self_update_thread;
}

void AutopilotModule::start() {
	// Start timer to update own position along route..
	_self_update_timer.async_wait(boost::bind(&AutopilotModule::update_self, this));
	_self_update_thread = new boost::thread(boost::bind(
			static_cast<size_t (boost::asio::io_service::*)()> (&boost::asio::io_service::run),
			boost::ref(_self_update_io)));
}

void AutopilotModule::stop() {
	_self_update_thread->join();
}

void AutopilotModule::set_mediator(ModuleMediator *mediator) {
	_mediator = mediator;
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
void AutopilotModule::update_self() {
//	std::cout << "Updating self: " << get_id_as_string() << std::endl;
	_self_update_timer.expires_at(_self_update_timer.expires_at() + boost::posix_time::milliseconds(100));
	_self_update_timer.async_wait(boost::bind(&AutopilotModule::update_self, this));

	//Get time diff, calc new position from current
	boost::posix_time::ptime cur_time = boost::posix_time::microsec_clock::local_time();
	boost::posix_time::time_duration diff = cur_time - _last_update_time;
	long diff_millis = diff.total_milliseconds();
	calculate_progress(diff_millis);

	_last_update_time = cur_time;

//	std::cout << _mm->sensor_to_string() << std::endl;
}

/**
 * Given elapsed time since last update calculates progress
 *
 * @param millis the time in milliseconds since the last update
 */
void AutopilotModule::calculate_progress(long millis) {
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

