/*
 * Road.cpp
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#include "Road.h"

#include <iostream>

#include <boost/lexical_cast.hpp>

const double Road::RANGE = 10.0;

Road::Road() :
	_distance(0),
	_speed_limit(0) {
}

Road::~Road() {
}

/*
 * ----- Setters -----
 */

void Road::set_start_intersection(Intersection &i) {
	_start_int = i;
}

void Road::set_end_intersection(Intersection &i) {
	_end_int = i;
}

void Road::set_speed_limit(double s) {
	_speed_limit.set_speed(s);
}

void Road::set_distance(double d) {
	_distance = d;
}

void Road::add_hazard(Hazard h) {
	_hazards.push_back(h);
}


/*
 * ----- Getters -----
 */

const Intersection& Road::get_start_intersection() const {
	return _start_int;
}

const Intersection& Road::get_end_intersection() const {
	return _end_int;
}

const Speed& Road::get_speed_limit() const {
	return _speed_limit;
}

const double Road::get_distance() const {
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
bool Road::is_hazard_at_position(Position &p, double range) const {
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
std::vector<Hazard> Road::get_hazard_at_position(Position &p, double range) const {
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


/**
 * Get all hazards on this Road
 */
std::vector<Hazard> Road::get_hazards() const {
	return _hazards;
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

std::string Road::to_string() {
	std::string s = "";
	s += "(" + boost::lexical_cast<std::string>(_start_int.get_id()) + ", " +
			boost::lexical_cast<std::string>(_end_int.get_id()) + ")";
	return s;
}

