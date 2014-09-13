/*
 * Acceleration.cpp
 *
 *  Created on: Sep 6, 2014
 *      Author: trevor
 */

#include "Acceleration.h"

Acceleration::Acceleration() {
	acceleration = 0;
}

Acceleration::Acceleration(double a) {
	acceleration = a;
}

Acceleration::~Acceleration() {
	// TODO Auto-generated destructor stub
}

void Acceleration::set_acceleration(double a) {
	acceleration = a;
}

double Acceleration::get_acceleration() {
	return acceleration;
}

/*
 * TODO: use integral if have available data
 */
Speed* Acceleration::get_speed_after_time(boost::posix_time::milliseconds millis) {
	Speed *s = new Speed(acceleration * millis.fractional_seconds());
	return s;
}
