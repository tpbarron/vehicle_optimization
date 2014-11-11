/**
 * AutopilotModule.h
 *	
 *  Created on: Nov 2, 2014
 *      Author: trevor
 */

#ifndef AUTOPILOTMODULE_H_
#define AUTOPILOTMODULE_H_

#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>


class ModuleMediator;

/**
 *
 */
class AutopilotModule {

public:

	AutopilotModule();
	virtual ~AutopilotModule();

	void start();
	void stop();

	void set_mediator(ModuleMediator *mediator);

private:

	ModuleMediator *_mediator;

	// Self update
	boost::posix_time::ptime _last_update_time;
	boost::asio::io_service _self_update_io;
	boost::asio::deadline_timer _self_update_timer;
	boost::thread *_self_update_thread;

	/*
	 * Called to update the own vehicle position...
	 */
	void update_self();
	void calculate_progress(long millis);

};

#endif /* AUTOPILOTMODULE_H_ */
