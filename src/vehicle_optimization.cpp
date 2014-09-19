/**
 * Copyright 1993-2012 NVIDIA Corporation.  All rights reserved.
 *
 * Please refer to the NVIDIA end user license agreement (EULA) associated
 * with this source code for terms and conditions that govern your use of
 * this software. Any use, reproduction, disclosure, or distribution of
 * this software and related documentation outside the terms of the EULA
 * is strictly prohibited.
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>

#include <boost/asio.hpp>

#include "sim/Scenario.h"
#include "utils/Utils.h"
#include "vehicle/Vehicle.h"



int main(void) {

	Scenario s;
	s.load_scenario("data/simple1.json");

	s.start();
	s.stop();
//	boost::asio::io_service io;
//	boost::asio::strand strand(io);
//
//	Vehicle v1("v1", &io, &strand);
//	Vehicle v2("v2", &io, &strand);
//	Vehicle v3("v3", &io, &strand);
//	v1.add_listener(v2);
//	v1.add_listener(v3);
//	v2.add_listener(v1);
//
//	io.run();

	return 0;
}
