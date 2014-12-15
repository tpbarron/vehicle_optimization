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
#include <boost/program_options.hpp>

#include "graphics/gui/GUI.h"
#include "sim/Scenario.h"
#include "utils/Utils.h"
#include "vehicle/Vehicle.h"

#include "tests/TestMain.h"

/**
 * Simulation entry point
 */
int main(int argc, char* argv[]) {

	namespace po = boost::program_options;
	po::options_description desc("Allowed options");
	desc.add_options()
	    ("help", "help message")
	    ("tests", po::value<bool>(), "Should run tests")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);


	if (vm.count("help")) {
	    std::cout << desc << std::endl;
	    return 1;
	}

	bool run_tests = false;
	if (vm.count("tests")) {
	    std::cout << "Will run tests..." << std::endl;
	    run_tests = vm["tests"].as<bool>();
	}

	Scenario::init();
	Scenario::load_scenario("basic_grid_single_vehicle");
	Scenario::test_print_map();
	//		Scenario::test_routing();
	Scenario::start();
	//		Scenario::stop();
	//		Scenario::cleanup();

	if (run_tests) {
		return TestMain::run_tests(argc, argv);
	} else {
		return 0;
	}
}
