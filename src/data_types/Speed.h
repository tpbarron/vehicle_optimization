/*
 * Speed.h
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#ifndef SPEED_H_
#define SPEED_H_

class Speed {
public:
	Speed();
	Speed(double s);
	virtual ~Speed();

	void set_speed(double s);
	double get_speed();

	double time_to_travel(double meters);

private:
	double spd;

};

#endif /* SPEED_H_ */
