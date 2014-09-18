/*
 * Pressure.cpp
 *
 *  Created on: Sep 6, 2014
 *      Author: trevor
 */

#include "BrakePressure.h"

BrakePressure::BrakePressure() {
	pressure = 0;
}

BrakePressure::BrakePressure(double p) {
	pressure = p;
}

BrakePressure::~BrakePressure() {
	// TODO Auto-generated destructor stub
}

const double BrakePressure::get_pressure() const {
	return pressure;
}

void BrakePressure::set_pressure(double p) {
	pressure = p;
}

/*
 * TODO: need way to calc for current pressure and any given pressure
 */
Distance* BrakePressure::dist_to_stop() {
	Distance *d = new Distance();
	return d;
}
