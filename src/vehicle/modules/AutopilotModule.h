/**
 * AutopilotModule.h
 *	
 *  Created on: Nov 2, 2014
 *      Author: trevor
 */

#ifndef AUTOPILOTMODULE_H_
#define AUTOPILOTMODULE_H_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>

#include "data_types/sensor_types/Heading.h"
#include "data_types/sensor_types/Speed.h"

#include "utils/Utils.h"

class ModuleMediator;
#include "ModuleMediator.h"

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

	unsigned int _update_period;

	ModuleMediator *_mediator;

	// Self update
	boost::posix_time::ptime _last_update_time;
	boost::asio::deadline_timer _self_update_timer;
	boost::thread *_self_update_thread;

	/*
	 * Called to update the own vehicle position...
	 */
	void update_self();
	void calculate_progress(long millis);
	void check_hazards(Position &pos, Heading &hdng, Speed &spd);

};

#endif /* AUTOPILOTMODULE_H_ */
