/*
 * Lane.h
 *
 *  Created on: Sep 19, 2014
 *      Author: trevor
 */

#ifndef LANE_H_
#define LANE_H_

#include <vector>
#include <utility>

#include "data_types/Position.h"

class Lane {

public:
	Lane();
	virtual ~Lane();

	void add_waypoint(Position &p);

private:

	std::vector<Position> _way_pts;
};

#endif /* LANE_H_ */
