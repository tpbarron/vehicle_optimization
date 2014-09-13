/*
 * Distance.cpp
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#include "Distance.h"


Distance::Distance() {
	distance = -1;
}

Distance::Distance(double d) {
	distance = d;
}

Distance::~Distance() {
	// TODO Auto-generated destructor stub
}

double Distance::get_distance() {
	return distance;
}

void Distance::set_distance(double d) {
	distance = d;
}
