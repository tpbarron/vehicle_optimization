/*
 * Road.h
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#ifndef ROAD_H_
#define ROAD_H_

#include <vector>


#include "data_types/module_types/Hazard.h"

#include "Intersection.h"
#include "Lane.h"

class Road {

public:

	enum RoadType {
		TWO_WAY,
		ONE_WAY_FORWARD,
		ONE_WAY_BACKWARD
	};

	Road();
	virtual ~Road();

	void set_start_intersection(Intersection &i);
	void set_end_intersection(Intersection &i);
	void set_speed_limit(double s);
	void set_distance(double d);
	void add_hazard(Hazard h);

	const Intersection& get_start_intersection() const;
	const Intersection& get_end_intersection() const;
	const Speed& get_speed_limit() const;
	const double get_distance() const;

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
	 * Check if there is a hazard within the given range...
	 */
	const static double RANGE;
	bool is_hazard_at_position(Position &p, double range=RANGE);
	std::vector<Hazard> get_hazard_at_position(Position &p, double range=RANGE);

	/*
	 * TODO: make this private and use function for cost..
	 * Distance between intersections in meters
	 */
	double _distance;

private:

	/*
	 * Speed limit in meters/sec
	 */
	Speed _speed_limit;

	Intersection _start_int;
	Intersection _end_int;

	std::vector<Lane> _lanes_forward;
	std::vector<Lane> _lanes_backward;

	std::vector<Hazard> _hazards;

};

#endif /* ROAD_H_ */
