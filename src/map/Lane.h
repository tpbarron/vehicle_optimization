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

class Lane {

public:
	Lane();
	virtual ~Lane();

private:

	typedef std::pair<double, double> Point;

	std::vector<Point> way_pts;
};

#endif /* LANE_H_ */
