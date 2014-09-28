/*
 * Heading.cpp
 *
 *  Created on: Sep 4, 2014
 *      Author: trevor
 */

#include "Heading.h"

Heading::Heading() {
	_heading = 0;
}

Heading::Heading(double h) {
	_heading = h;
}

Heading::~Heading() {
	// TODO Auto-generated destructor stub
}

const double Heading::get_heading() const {
	return _heading;
}

void Heading::set_heading(double h) {
	_heading = h;
}
