/*
 * Speed.cpp
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#include "Speed.h"

//const double Speed::MPH_25 = 11.176;
//const double Speed::MPH_30 = 13.4112;

Speed::Speed() {
	_speed = -1;
}

Speed::Speed(double s) {
	_speed = s;
}

Speed::~Speed() {
	// TODO Auto-generated destructor stub
}

void Speed::set_speed(const Speed &s) {
	_speed = s.get_speed();
}

void Speed::set_speed(double s) {
	_speed = s;
}

const double Speed::get_speed() const {
	return _speed;
}

/**
 * Calculate time in millis to travel given meters at this speed;
 *
 * @param meters distance in meters
 */
double Speed::time_to_travel(double meters) {
	return meters / _speed * 1000.0;
}

/**
 * Get distance in meters traveled at this speed in given millis
 *
 * @param millis the time to compute the distance for
 */
Distance Speed::get_distance_for_time(double millis) {
	Distance d(_speed * millis / 1000.0);
	return d;
}
