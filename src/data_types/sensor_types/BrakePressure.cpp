/*
 * Pressure.cpp
 *
 *  Created on: Sep 6, 2014
 *      Author: trevor
 */

#include "BrakePressure.h"

BrakePressure::BrakePressure() {
	_pressure = 0;
}

BrakePressure::BrakePressure(double p) {
	_pressure = p;
}

BrakePressure::~BrakePressure() {
	// TODO Auto-generated destructor stub
}

const double BrakePressure::get_pressure() const {
	return _pressure;
}

void BrakePressure::set_pressure(double p) {
	_pressure = p;
}

/*
 * TODO: need way to calc for current pressure and any given pressure
 */
Distance* BrakePressure::dist_to_stop() {
	Distance *d = new Distance();
	return d;
}
