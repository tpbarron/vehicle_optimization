/*
 * Speed.h
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#ifndef SPEED_H_
#define SPEED_H_

#include "Distance.h"

class Speed {
public:

	constexpr static double MPH_25 = 11.176;
	constexpr static double MPH_30 = 13.4112;

	Speed();
	Speed(double s);
	virtual ~Speed();

	void set_speed(double s);
	void set_speed(const Speed &s);
	const double get_speed() const;

	double time_to_travel(double meters);
	Distance get_distance_for_time(double millis);

private:

	double _speed;

};

#endif /* SPEED_H_ */
