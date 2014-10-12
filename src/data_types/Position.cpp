/*
 * Position.cpp
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#include "Position.h"

#include <math.h>

#include <boost/lexical_cast.hpp>

Position::Position() {
	_x = 0;
	_y = 0;
}

Position::Position(double x, double y) {
	Position::_x = x;
	Position::_y = y;
}

Position::~Position() {
}

void Position::set_x(double new_x) {
	Position::_x = new_x;
}

void Position::set_y(double new_y) {
	Position::_y = new_y;
}

void Position::set_position(double new_x, double new_y) {
	Position::_x = new_x;
	Position::_y = new_y;
}

void Position::set_position(Position p) {
	Position::_x = p.get_x();
	Position::_y = p.get_y();
}

const double Position::get_x() const {
	return _x;
}

const double Position::get_y() const {
	return _y;
}

/*
 * Simple euclidean dist, does not follow roads....
 */
Distance Position::get_distance_to(const Position &other) const {
	Distance d;
	d.set_distance(sqrt(pow(other.get_x() - _x, 2) + pow(other.get_y() - _y, 2)));
	return d;
}

std::string Position::to_string() {
	return "(" + boost::lexical_cast<std::string>(_x) + ", " +
			boost::lexical_cast<std::string>(_y) + ")";
}
