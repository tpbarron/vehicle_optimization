/*
 * Position.h
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#ifndef POSITION_H_
#define POSITION_H_

#include "../data_types/Distance.h"


class Position {
public:
	Position();
	Position(double x, double y);
	virtual ~Position();

	void set_x(double x);
	void set_y(double y);

	const double get_x() const;
	const double get_y() const;

	const Distance* get_distance_to(const Position *other) const;

private:

	double x;
	double y;

};

#endif /* POSITION_H_ */
