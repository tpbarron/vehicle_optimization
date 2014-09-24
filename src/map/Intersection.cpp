/*
 * Intersection.cpp
 *
 *  Created on: Sep 18, 2014
 *      Author: trevor
 */

#include "Intersection.h"

Intersection::Intersection() {
	pos = nullptr;
	id = -1;
	width = -1;
	height = -1;
}

Intersection::~Intersection() {
	delete pos;
}


void Intersection::set_id(int i) {
	id = i;
}

void Intersection::set_width(double w) {
	width = w;
}

void Intersection::set_height(double h) {
	height = h;
}


void Intersection::set_pos_x(double x) {
	if (pos == nullptr) {
		pos = new Position();
	}
	pos->set_x(x);
}

void Intersection::set_pox_y(double y) {
	if (pos == nullptr) {
		pos = new Position();
	}
	pos->set_y(y);
}

void Intersection::set_position(double x, double y) {
	if (pos == nullptr) {
		pos = new Position();
	}
	pos->set_position(x, y);
}


Position* Intersection::get_position() {
	return pos;
}

int Intersection::get_id() {
	return id;
}
