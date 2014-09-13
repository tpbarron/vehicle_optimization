/*
 * VehicleTurnRate.cpp
 *
 *  Created on: Sep 6, 2014
 *      Author: trevor
 */

#include "TurnRate.h"

TurnRate::TurnRate(double tr) {
	turn_rate = tr;
}

TurnRate::TurnRate() {
	turn_rate = 0;
}

TurnRate::~TurnRate() {
	// TODO Auto-generated destructor stub
}

double TurnRate::get_turn_rate() {
	return turn_rate;
}

void TurnRate::set_turn_rate(double tr) {
	turn_rate = tr;
}

