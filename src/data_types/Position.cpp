/*
 * Position.cpp
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#include "Position.h"

#include <math.h>

Position::Position() {
	x = 0;
	y = 0;
}

Position::Position(double x, double y) {
	Position::x = x;
	Position::y = y;
}

Position::~Position() {
}

void Position::set_x(double new_x) {
	Position::x = new_x;
}

void Position::set_y(double new_y) {
	Position::y = new_y;
}

void Position::set_position(double new_x, double new_y) {
	Position::x = new_x;
	Position::y = new_y;
}

const double Position::get_x() const {
	return x;
}

const double Position::get_y() const {
	return y;
}

//TODO ensure this is deallocated
/*
 * Simple euclidean dist, does not follow roads....
 */
const Distance* Position::get_distance_to(const Position *other) const {
	Distance *d = new Distance();
	double dist = sqrt(pow(other->get_x() - x, 2) + pow(other->get_y() - y, 2));
	d->set_distance(dist);
	return d;
}
