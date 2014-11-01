/*
 * Acceleration.cpp
 *
 *  Created on: Sep 6, 2014
 *      Author: trevor
 */

#include "Acceleration.h"

Acceleration::Acceleration() {
	_acceleration = 0;
}

Acceleration::Acceleration(double a) {
	_acceleration = a;
}

Acceleration::~Acceleration() {
	// TODO Auto-generated destructor stub
}

void Acceleration::set_acceleration(double a) {
	_acceleration = a;
}

const double Acceleration::get_acceleration() const {
	return _acceleration;
}

/*
 * TODO: use integral if have available data
 */
Speed* Acceleration::get_speed_after_time(boost::posix_time::milliseconds millis) {
	Speed *s = new Speed(_acceleration * millis.fractional_seconds());
	return s;
}
