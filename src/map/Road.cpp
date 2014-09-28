/*
 * Road.cpp
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#include "Road.h"

Road::Road() {
	_speed_limit = 0;
	_distance = 0;
	_start_int = nullptr;
	_end_int = nullptr;
}

Road::~Road() {
	for (unsigned int i = 0; i < _lanes_forward.size(); ++i) {
		delete _lanes_forward[i];
	}
	for (unsigned int j = 0; j < _lanes_backward.size(); ++j) {
		delete _lanes_backward[j];
	}
	// TODO Do the intersections need to be deleted here? 
	// need shared pointer because multiple roads can point to the same 
	// intersections.
}


void Road::set_start_intersection(Intersection *i) {
	if (_start_int ==  nullptr) {
		_start_int = new Intersection();
	}
	_start_int = i;
}

void Road::set_end_intersection(Intersection *i) {
	if (_end_int == nullptr) {
		_end_int = new Intersection();
	}
	_end_int = i;
}

void Road::set_speed_limit(double s) {
	_speed_limit = s;
}

void Road::set_distance(double d) {
	_distance = d;
}


Intersection* Road::get_start_intersection() {
	return _start_int;
}

Intersection* Road::get_end_intersection() {
	return _end_int;
}

double Road::get_speed_limit() {
	return _speed_limit;
}

double Road::get_distance() {
	return _distance;
}

/*
 * From start to end
 */

void Road::add_lane_forward(Lane *l) {
	_lanes_forward.push_back(l);
}

int Road::get_num_lanes_forward() {
	return _lanes_forward.size();
}

/*
 * From end to start
 */
void Road::add_lane_backward(Lane *l) {
	_lanes_backward.push_back(l);
}

int Road::get_num_lanes_backward() {
	return _lanes_backward.size();
}

bool Road::is_one_way() {
	if (_lanes_forward.size() > 0 && _lanes_backward.size() > 0) {
		return false;
	}
	return true;
}

Road::RoadType Road::get_road_type() {
	if (is_one_way()) {
		if (_lanes_forward.size() == 0) {
			return RoadType::ONE_WAY_BACKWARD;
		} else if (_lanes_backward.size() == 0) {
			return RoadType::ONE_WAY_FORWARD;
		}
	}
	return RoadType::TWO_WAY;
}
