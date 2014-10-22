/**
 * HazardWarning.cpp
 *	
 *  Created on: Oct 15, 2014
 *      Author: trevor
 */

#include "Hazard.h"

Hazard::Hazard() : _position(0,0), _max_safe_speed(0) {
	// TODO Auto-generated constructor stub

}

Hazard::~Hazard() {
	// TODO Auto-generated destructor stub
}

bool Hazard::operator==(const Hazard& other) const {
	return _position == other.get_position();
}


void Hazard::set_position(Position &p) {
	_position.set_position(p);
}

void Hazard::set_max_safe_speed(double s) {
	_max_safe_speed.set_speed(s);
}

const Position Hazard::get_position() const {
	return _position;
}

const Speed Hazard::get_max_safe_speed() const {
	return _max_safe_speed;
}
