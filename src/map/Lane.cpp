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
	for (unsigned int i = 0; i < way_pts.size(); ++i) {
		delete way_pts[i];
	}
}

void Lane::add_waypoint(Position *p) {
	way_pts.push_back(p);
}
