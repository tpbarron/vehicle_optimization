/**
 * MesgHandlerModule.cpp
 *	
 *  Created on: Nov 16, 2014
 *      Author: trevor
 */


#include <vehicle/modules/MesgHandlerModule.h>

#include <algorithm>

#include "data_manager/VehicleManager.h"
#include "utils/Logger.h"


MesgHandlerModule::MesgHandlerModule() :
	_update_period(500),
	_mediator(nullptr),
	_nearby_vehicle_timer(Utils::get_global_io_service(), boost::posix_time::milliseconds(1000)),
	_nearby_vehicle_thread(nullptr) {
}

MesgHandlerModule::~MesgHandlerModule() {
	delete _nearby_vehicle_thread;
}

void MesgHandlerModule::set_mediator(ModuleMediator *mediator) {
	_mediator = mediator;
}

void MesgHandlerModule::start() {
	Logger::info("Starting MesgHandler Module");

	// Start timer to update own position along route..
	_nearby_vehicle_timer.async_wait(boost::bind(&MesgHandlerModule::update_nearest_vehicles, this));
	_nearby_vehicle_thread = new boost::thread(boost::bind(
			static_cast<size_t (boost::asio::io_service::*)()> (&boost::asio::io_service::run),
			boost::ref(Utils::get_global_io_service())));
}

void MesgHandlerModule::stop() {
	_nearby_vehicle_thread->join();
}

/**
 * Gets nearest vehicles from VehicleManager and merges any new ones into the
 * set of nearest Vehicles.
 */
void MesgHandlerModule::update_nearest_vehicles() {
	Logger::info("Updating nearest vehicles");

	// recalc every half second
	_nearby_vehicle_timer.expires_at(_nearby_vehicle_timer.expires_at() + boost::posix_time::milliseconds(_update_period));
	_nearby_vehicle_timer.async_wait(boost::bind(&MesgHandlerModule::update_nearest_vehicles, this));

	std::set<IVehicleDataListener*, IVehicleDataListener::IVehicleDataListenerComp> nearest =
			VehicleManager::get_nearest(_mediator->get_sensor_position(), 50, 25);

	// remove the own vehicle
	std::string uuid = _mediator->get_uuid();
	for (auto itr = nearest.begin(); itr != nearest.end(); ++itr) {
		IVehicleDataListener* v = *itr;
		if (v->get_id() == uuid) {
			nearest.erase(itr);
			break;
		}
	}

	_listeners = nearest;
}

/**
 * Send out a Message to all nearby listening vehicles
 */
void MesgHandlerModule::send_message(Message *mesg) {
	Logger::info("Sending Message to " + boost::lexical_cast<std::string>(_listeners.size()) + " vehicles");
	for (auto itr = _listeners.begin(); itr != _listeners.end(); ++itr) {
		(*itr)->recv(mesg);
	}
}

/**
 * Send out a bunch of messages
 */
void MesgHandlerModule::send_messages(std::vector<Message*> &messages) {
	for (auto itr = messages.begin(); itr != messages.end(); ++itr) {
		send_message(*itr);
	}
}

void MesgHandlerModule::add_listener(IVehicleDataListener &l) {
	_listeners.insert(&l);
}

void MesgHandlerModule::remove_listener(IVehicleDataListener &l) {
	_listeners.erase(&l);
}
