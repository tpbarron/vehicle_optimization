/*
 * Acceleration.h
 *
 *  Created on: Sep 6, 2014
 *      Author: trevor
 */

#ifndef ACCELERATION_H_
#define ACCELERATION_H_

#include <boost/date_time/posix_time/posix_time.hpp>

#include "Speed.h"

/*
 * Current acceleration in Meters/Second^2
 */
class Acceleration {
public:
	Acceleration();
	Acceleration(double a);
	virtual ~Acceleration();

	void set_acceleration(double a);
	const double get_acceleration() const;

	/*
	 * Get the expected speed after the given time if acceleration
	 * continues at this rate
	 */
	Speed* get_speed_after_time(boost::posix_time::milliseconds millis);

private:

	double _acceleration;

};

#endif /* ACCELERATION_H_ */
