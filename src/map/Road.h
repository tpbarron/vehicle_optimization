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

	void set_start_intersection(Intersection &i);
	void set_end_intersection(Intersection &i);
	void set_speed_limit(double s);
	void set_distance(double d);

	Intersection get_start_intersection();
	Intersection get_end_intersection();
	double get_speed_limit();
	double get_distance();

	/*
	 * From start to end
	 */
	void add_lane_forward(Lane l);
	int get_num_lanes_forward();

	/*
	 * From end to start
	 */
	void add_lane_backward(Lane l);
	int get_num_lanes_backward();

	bool is_one_way();
	RoadType get_road_type();

	/*
	 * TODO: make this private and use function for cost..
	 * Distance between intersections in meters
	 */
	double _distance;

private:

	/*
	 * Speed limit in meters/sec
	 */
	double _speed_limit;

	Intersection _start_int;
	Intersection _end_int;

	std::vector<Lane> _lanes_forward;
	std::vector<Lane> _lanes_backward;

};

#endif /* ROAD_H_ */
