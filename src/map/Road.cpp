/*
 * Road.cpp
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#include "Road.h"

Road::Road() {
	speed_limit = 0;
	start_int = nullptr;
	end_int = nullptr;
}

Road::~Road() {
	// TODO Do the intersections need to be deleted here? 
	// need shared pointer because multiple roads can point to the same 
	// intersections.
}


void Road::set_start_intersection(Intersection *i) {
	if (start_int ==  nullptr) {
		start_int = new Intersection();
	}
	start_int = i;
}

void Road::set_end_intersection(Intersection *i) {
	if (end_int == nullptr) {
		end_int = new Intersection();
	}
	end_int = i;
}

void Road::set_speed_limit(double s) {
	speed_limit = s;
}

void Road::set_distance(double d) {
	distance = d;
}


Intersection* Road::get_start_intersection() {
	return start_int;
}

Intersection* Road::get_end_intersection() {
	return end_int;
}

double Road::get_speed_limit() {
	return speed_limit;
}

double Road::get_distance() {
	return distance;
}

/*
 * From start to end
 */

void Road::add_lane_forward(Lane *l) {
	lanes_forward.push_back(l);
}

int Road::get_num_lanes_forward() {
	return lanes_forward.size();
}

/*
 * From end to start
 */
void Road::add_lane_backward(Lane *l) {
	lanes_backward.push_back(l);
}

int Road::get_num_lanes_backward() {
	return lanes_backward.size();
}

bool Road::is_one_way() {
	if (lanes_forward.size() > 0 && lanes_backward.size() > 0) {
		return false;
	}
	return true;
}

Road::RoadType Road::get_road_type() {
	if (is_one_way()) {
		if (lanes_forward.size() == 0) {
			return RoadType::ONE_WAY_BACKWARD;
		} else if (lanes_backward.size() == 0) {
			return RoadType::ONE_WAY_FORWARD;
		}
	}
	return RoadType::TWO_WAY;
}
