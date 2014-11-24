/*
 * Road.cpp
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#include "Road.h"

const double Road::RANGE = 10.0;

Road::Road() {
	_speed_limit = 0;
	_distance = 0;
}

Road::~Road() {
}


void Road::set_start_intersection(Intersection &i) {
	_start_int = i;
}

void Road::set_end_intersection(Intersection &i) {
	_end_int = i;
}

void Road::set_speed_limit(double s) {
	_speed_limit = s;
}

void Road::set_distance(double d) {
	_distance = d;
}

void Road::add_hazard(Hazard h) {
	_hazards.push_back(h);
}


Intersection Road::get_start_intersection() {
	return _start_int;
}

Intersection Road::get_end_intersection() {
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

void Road::add_lane_forward(Lane l) {
	_lanes_forward.push_back(l);
}

int Road::get_num_lanes_forward() {
	return _lanes_forward.size();
}

/*
 * From end to start
 */
void Road::add_lane_backward(Lane l) {
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


/**
 * Determine whether there exists a hazard within range meters of the
 * given position
 *
 * @param p the position near which to find hazards
 * @param range the distance to search for a hazard
 */
bool Road::is_hazard_at_position(Position &p, double range) {
	for (unsigned int i = 0; i < _hazards.size(); ++i) {
		if (_hazards[i].get_position().get_distance_to(p).get_distance() < range) {
			return true;
		}
	}
	return false;
}

/**
 * Return any Hazards on the Road within the given range.
 */
std::vector<Hazard> Road::get_hazard_at_position(Position &p, double range) {
	std::vector<Hazard> hazards;

	for (auto itr = _hazards.begin(); itr != _hazards.end(); ++itr) {
		Hazard h = *itr;
		double d = h.get_position().get_distance_to(p).get_distance();
		if (d < range) {
			hazards.push_back(h);
		}
	}

	return hazards;
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
