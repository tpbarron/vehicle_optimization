/*
 * VehicleTurnRate.h
 *
 *  Created on: Sep 6, 2014
 *      Author: trevor
 */

#ifndef TURNRATE_H_
#define TURNRATE_H_

/*
 * represents deg/sec turned for both vehicle and steering wheel
 */

class TurnRate {

public:
	TurnRate();
	TurnRate(double tr);
	virtual ~TurnRate();

	const double get_turn_rate() const;
	void set_turn_rate(double tr);

private:

	double _turn_rate;

};

#endif /* TURNRATE_H_ */
