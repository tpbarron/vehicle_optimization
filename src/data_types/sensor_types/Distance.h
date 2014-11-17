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

	bool operator>(const Distance& d);
	bool operator<(const Distance& d);

	const double get_distance() const;
	void set_distance(double d);

private:

	double _distance;

};

#endif /* DISTANCE_H_ */
