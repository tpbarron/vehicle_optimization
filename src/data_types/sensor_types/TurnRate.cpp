/*
 * VehicleTurnRate.cpp
 *
 *  Created on: Sep 6, 2014
 *      Author: trevor
 */

#include "TurnRate.h"

TurnRate::TurnRate(double tr) {
	_turn_rate = tr;
}

TurnRate::TurnRate() {
	_turn_rate = 0;
}

TurnRate::~TurnRate() {
	// TODO Auto-generated destructor stub
}

const double TurnRate::get_turn_rate() const {
	return _turn_rate;
}

void TurnRate::set_turn_rate(double tr) {
	_turn_rate = tr;
}

