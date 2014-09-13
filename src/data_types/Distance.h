/*
 * Distance.h
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#ifndef DISTANCE_H_
#define DISTANCE_H_

class Distance {
public:
	Distance();
	Distance(double d);
	virtual ~Distance();

	double get_distance();
	void set_distance(double d);

private:
	double distance;

};

#endif /* DISTANCE_H_ */
