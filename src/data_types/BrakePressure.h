/*
 * Pressure.h
 *
 *  Created on: Sep 6, 2014
 *      Author: trevor
 */

#ifndef BRAKEPRESSURE_H_
#define BRAKEPRESSURE_H_

#include "Distance.h"

class BrakePressure {
public:

	BrakePressure();
	BrakePressure(double p);
	virtual ~BrakePressure();

	double get_pressure();
	void set_pressure(double p);

	Distance* dist_to_stop();

private:

	/*
	 * As a percent?
	 */
	double pressure;
};

#endif /* BRAKEPRESSURE_H_ */
