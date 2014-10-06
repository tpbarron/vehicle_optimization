/*
 * Intersection.h
 *
 *  Created on: Sep 18, 2014
 *      Author: trevor
 */

#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include "../data_types/Position.h"

class Intersection {

public:
	Intersection();
	virtual ~Intersection();

	void set_id(int i);
	void set_width(double w);
	void set_height(double h);
	void set_pos_x(double x);
	void set_pox_y(double y);
	void set_position(double x, double y);

	Position get_position();
	int get_id();

private:

	int _id;

	Position _pos;

	double _width;
	double _height;

};

#endif /* INTERSECTION_H_ */
