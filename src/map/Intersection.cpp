/*
 * Intersection.cpp
 *
 *  Created on: Sep 18, 2014
 *      Author: trevor
 */

#include "Intersection.h"

Intersection::Intersection() :
	_id(-1),
	_pos(0, 0),
	_width(-1),
	_height(-1) {
}

Intersection::~Intersection() {
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
	_pos.set_x(x);
}

void Intersection::set_pox_y(double y) {
	_pos.set_y(y);
}

void Intersection::set_position(double x, double y) {
	_pos.set_position(x, y);
}


const Position& Intersection::get_position() const {
	return _pos;
}

const int Intersection::get_id() const {
	return _id;
}
