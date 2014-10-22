/**
 * HazardWarning.h
 *	
 *  Created on: Oct 15, 2014
 *      Author: trevor
 */

#ifndef HAZARD_H_
#define HAZARD_H_

#include "data_types/Position.h"
#include "data_types/Speed.h"

/**
 *
 */
class Hazard {

public:

	Hazard();
	virtual ~Hazard();

	bool operator==(const Hazard& other) const;

	void set_position(Position &p);
	void set_max_safe_speed(double s);

	const Position get_position() const;
	const Speed get_max_safe_speed() const ;

private:

	Position _position;
	Speed _max_safe_speed;

};

#endif /* HAZARD_H_ */
