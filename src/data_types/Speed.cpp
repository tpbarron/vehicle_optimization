/*
 * Speed.cpp
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#include "Speed.h"

Speed::Speed() {
	spd = -1;
}

Speed::Speed(double s) {
	spd = s;
}

Speed::~Speed() {
	// TODO Auto-generated destructor stub
}

void Speed::set_speed(double s) {
	spd = s;
}

double Speed::get_speed() {
	return spd;
}

/*
 * Calculate time to travel given meters at this speed;
 */
double Speed::time_to_travel(double meters) {
	return meters / spd;
}
