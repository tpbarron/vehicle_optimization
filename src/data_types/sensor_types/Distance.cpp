/*
 * Distance.cpp
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#include "Distance.h"


Distance::Distance() {
	_distance = -1;
}

Distance::Distance(double d) {
	_distance = d;
}

Distance::~Distance() {
	// TODO Auto-generated destructor stub
}

const double Distance::get_distance() const {
	return _distance;
}

void Distance::set_distance(double d) {
	_distance = d;
}
