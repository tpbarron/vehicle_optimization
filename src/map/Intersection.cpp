/*
 * Intersection.cpp
 *
 *  Created on: Sep 18, 2014
 *      Author: trevor
 */

#include "Intersection.h"

Intersection::Intersection() {
	_pos = nullptr;
	_id = -1;
	_width = -1;
	_height = -1;
}

Intersection::~Intersection() {
	delete _pos;
}


void Intersection::set_id(int i) {
	_id = i;
}

void Intersection::set_width(double w) {
	_width = w;
}

void Intersection::set_height(double h) {
	_height = h;
}


void Intersection::set_pos_x(double x) {
	if (_pos == nullptr) {
		_pos = new Position();
	}
	_pos->set_x(x);
}

void Intersection::set_pox_y(double y) {
	if (_pos == nullptr) {
		_pos = new Position();
	}
	_pos->set_y(y);
}

void Intersection::set_position(double x, double y) {
	if (_pos == nullptr) {
		_pos = new Position();
	}
	_pos->set_position(x, y);
}


Position* Intersection::get_position() {
	return _pos;
}

int Intersection::get_id() {
	return _id;
}
