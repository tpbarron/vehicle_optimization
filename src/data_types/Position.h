/*
 * Position.h
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#ifndef POSITION_H_
#define POSITION_H_

#include "../data_types/Distance.h"

/**
 * I don't know if this is accurage enough.
 * May need other data representation than GPS coords.
 */

class Position {
public:
	Position();
	Position(double lat, double lng);
	virtual ~Position();

	void set_lat(double lat);
	void set_lng(double lng);

	double get_lat();
	double get_lng();

	Distance* get_distance_to(Position &other);

private:

	double lat;
	double lng;

};

#endif /* POSITION_H_ */
