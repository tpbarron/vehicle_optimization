/*
 * Road.h
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#ifndef ROAD_H_
#define ROAD_H_

#include <vector>

#include "Intersection.h"
#include "Lane.h"

class Road {

public:
	Road();
	virtual ~Road();

	enum RoadType {
		TWO_WAY,
		ONE_WAY_FORWARD,
		ONE_WAY_BACKWARD
	};

	void set_start_intersection(Intersection *i);
	void set_end_intersection(Intersection *i);
	void set_speed_limit(double s);

	Intersection* get_start_intersection();
	Intersection* get_end_intersection();

	/*
	 * From start to end
	 */
	int get_num_lanes_forward();

	/*
	 * From end to start
	 */
	int get_num_lanes_backward();

	bool is_one_way();
	RoadType get_road_type();

private:

	/*
	 * Speed limit in meters/sec
	 */
	double speed_limit;

	Intersection* start_int;
	Intersection* end_int;

	std::vector<Lane> lanes_forward;
	std::vector<Lane> lanes_backward;

};

#endif /* ROAD_H_ */
