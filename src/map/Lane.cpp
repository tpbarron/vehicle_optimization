/*
 * Lane.cpp
 *
 *  Created on: Sep 19, 2014
 *      Author: trevor
 */

#include "Lane.h"

Lane::Lane() {
	// TODO Auto-generated constructor stub

}

Lane::~Lane() {
}

void Lane::add_waypoint(Position &p) {
	_way_pts.push_back(p);
}
