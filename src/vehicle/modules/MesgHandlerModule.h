/**
 * MesgHandlerModule.h
 *	
 *  Created on: Nov 16, 2014
 *      Author: trevor
 */

#ifndef MESGHANDLERMODULE_H_
#define MESGHANDLERMODULE_H_

#include <set>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>

#include "vehicle/IVehicleDataListener.h"

#include "data_types/message_types/Message.h"

#include "utils/Utils.h"

class ModuleMediator;
#include "ModuleMediator.h"

/**
 * This module sends out messages to nearby vehicles.
 */
class MesgHandlerModule {
public:

	MesgHandlerModule();
	virtual ~MesgHandlerModule();

	void set_mediator(ModuleMediator *mediator);

	void start();
	void stop();

	void update_nearest_vehicles();

	void send_message(Message &mesg);
	void send_messages(std::vector<Message> &messages);

	void add_listener(IVehicleDataListener &l);
	void remove_listener(IVehicleDataListener &l);

private:

	ModuleMediator *_mediator;

	// Self update
	boost::asio::deadline_timer _nearby_vehicle_timer;
	boost::thread *_nearby_vehicle_thread;


	// Nearby vehicles
	std::set<IVehicleDataListener*, IVehicleDataListener::IVehicleDataListenerComp> _listeners;
};

#endif /* MESGHANDLERMODULE_H_ */
