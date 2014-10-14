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

void Heading::set_from_pts(Position &p1, Position &p2) {
	double dx = p2.get_x() - p1.get_x();
	double dy = p2.get_y() - p1.get_y();

	double pi = boost::math::constants::pi<double>();
	double rad = std::atan2(dy, dx) + pi / 2.0;
	if (rad >= 2*pi) {
		rad -= 2*pi;
	}
	if (rad < 0.0) {
		rad += 2*pi;
	}
	_heading = rad;
}
