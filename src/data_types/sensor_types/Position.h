/*
 * Position.h
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#ifndef POSITION_H_
#define POSITION_H_

#include <string>

#include "data_types/sensor_types/Distance.h"

class Position {
public:
	Position();
	Position(double x, double y);
	virtual ~Position();

	bool operator==(const Position& other) const;

	void set_x(double x);
	void set_y(double y);
	void set_position(double x, double y);
	void set_position(Position p);

	const double get_x() const;
	const double get_y() const;

	Distance get_distance_to(const Position &other) const;

	std::string to_string();

private:

	double _x;
	double _y;

};

#endif /* POSITION_H_ */
