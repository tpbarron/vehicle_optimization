/*
 * Heading.cpp
 *
 *  Created on: Sep 4, 2014
 *      Author: trevor
 */

#include "Heading.h"

Heading::Heading() {
	heading = 0;
}

Heading::Heading(double h) {
	heading = h;
}

Heading::~Heading() {
	// TODO Auto-generated destructor stub
}

double Heading::get_heading() {
	return heading;
}

void Heading::set_heading(double h) {
	heading = h;
}
