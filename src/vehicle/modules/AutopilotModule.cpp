/**
 * AutopilotModule.cpp
 *	
 *  Created on: Nov 2, 2014
 *      Author: trevor
 */

#include "AutopilotModule.h"

AutopilotModule::AutopilotModule(boost::asio::io_service::strand &strand) :
	_mediator(nullptr),
	_strand(strand),
	_last_update_time(boost::posix_time::microsec_clock::local_time()),
	_self_update_timer(strand.get_io_service(), boost::posix_time::milliseconds(100)),
	_self_update_thread(nullptr) {

}

AutopilotModule::~AutopilotModule() {
	delete _self_update_thread;
}

void AutopilotModule::start() {
	std::cout << "Starting Autopilot Module" << std::endl;

	// Start timer to update own position along route..
	_self_update_timer.async_wait(_strand.wrap(boost::bind(&AutopilotModule::update_self, this)));
	_self_update_thread = new boost::thread(boost::bind(
			static_cast<size_t (boost::asio::io_service::*)()> (&boost::asio::io_service::run),
			boost::ref(_strand.get_io_service())));
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
	std::cout << "Updating self" << std::endl;
	_self_update_timer.expires_at(_self_update_timer.expires_at() + boost::posix_time::milliseconds(100));
	_self_update_timer.async_wait(boost::bind(&AutopilotModule::update_self, this));

	//Get time diff, calc new position from current
	boost::posix_time::ptime cur_time = boost::posix_time::microsec_clock::local_time();
	boost::posix_time::time_duration diff = cur_time - _last_update_time;
	long diff_millis = diff.total_milliseconds();
	calculate_progress(diff_millis);

	_last_update_time = cur_time;

	std::cout << _mediator->sensor_to_string() << std::endl;
}

/**
 * Given elapsed time since last update calculates progress
 *
 * @param millis the time in milliseconds since the last update
 */
void AutopilotModule::calculate_progress(long millis) {
	// Get the allowed speed at the current position
	Speed speed = _mediator->get_speed_from_route();
	_mediator->set_sensor_speed(speed);

	// Get the distance in meters that would be covered in the allotted time
	Distance dist = speed.get_distance_for_time(millis);
	// Get a new position from the route after moving dist towards destination
	// TODO: there could have been a road change here and thus a speed change
	// Perhaps the update is frequent enough that it isn't important to
	// refresh immediately.
	Position pos = _mediator->get_new_position_from_route(dist);
	_mediator->set_sensor_position(pos);

	// Get the heading from the route using the last two positions
	Heading hdng = _mediator->get_heading_from_route();
	_mediator->set_sensor_heading(hdng);

	// TODO: for now assume the following are constant
//	_sensor.set_acceleration(0);
//	_sensor.set_brake_pressure(0);
//	_sensor.set_vehicle_turn_rate(0);
//	_sensor.set_wheel_turn_rate(0);

	check_hazards(pos, hdng);
}

/**
 * Given current position and heading check for hazards and
 * respond to them.
 */
void AutopilotModule::check_hazards(Position &pos, Heading &hdng) {
//	if (_mediator->is_known_relevant_hazards(pos, hdng)) {
//		//if we already know about something, respond to it
//		Speed hazard_speed = _mediator->get_safe_hazard_speed(pos, hdng);
//		if (hazard_speed.get_speed() < _mediator->get_sensor_speed().get_speed()) {
//			// set lower speed, wouldn't want to accidentally set a higher speed
//			_mediator->set_sensor_speed(hazard_speed);
//		}
//	}

	std::vector<Hazard> imminents = _mediator->get_new_imminent_hazards();
	std::vector<Message> hazard_messages;

	for (std::vector<Hazard>::iterator itr = imminents.begin(); itr != imminents.end(); ++itr) {
		//save all new hazards
		_mediator->save_hazard(*itr);

		//create some hazard messages
		HazardMessage mesg = _mediator->create_hazard_message(*itr);
		hazard_messages.push_back(mesg);
	}

	//send out all messages
	if (hazard_messages.size() > 0)
		_mediator->send_messages(hazard_messages);

	// Now we have logged all hazards, check if we need to change the speed
	// and respond immediately if necessary
	//TODO: use mediator.get_safe_hazard_speed to check response
}

