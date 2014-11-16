/*
 * Heading.h
 *
 *  Created on: Sep 4, 2014
 *      Author: trevor
 */

#ifndef HEADING_H_
#define HEADING_H_


#include <cmath>

#include <boost/math/constants/constants.hpp>

#include "Position.h"

/*
 * http://en.wikipedia.org/wiki/Course_%28navigation%29
 */

/**
 * Represents a vehicles heading using compass coordinates where
 * 0 is north, 90 E, 180 S, 270 W
 */
class Heading {
public:
	Heading();
	Heading(double h);
	virtual ~Heading();

	const double get_heading() const;
	void set_heading(const Heading &h);
	void set_heading(double h);
	void set_from_pts(Position &p1, Position &p2);

private:

	double _heading;

};

#endif /* HEADING_H_ */
