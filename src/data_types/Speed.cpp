/*
 * Speed.cpp
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#include "Speed.h"

Speed::Speed() {
	_speed = -1;
}

Speed::Speed(double s) {
	_speed = s;
}

Speed::~Speed() {
	// TODO Auto-generated destructor stub
}

void Speed::set_speed(double s) {
	_speed = s;
}

const double Speed::get_speed() const {
	return _speed;
}

/*
 * Calculate time to travel given meters at this speed;
 */
double Speed::time_to_travel(double meters) {
	return meters / _speed;
}
