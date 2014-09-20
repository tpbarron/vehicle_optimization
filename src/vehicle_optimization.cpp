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

#include "sim/Scenario.h"
#include "utils/Utils.h"
#include "vehicle/Vehicle.h"

#include "tests/TestMain.h"

int main(int argc, char* argv[]) {

	namespace po = boost::program_options;
	po::options_description desc("Allowed options");
	desc.add_options()
	    ("help", "help message")
	    ("run-tests", po::value<bool>(), "Should run tests")
	    ("use-graphics", po::value<bool>(), "Should use GTK graphics")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);


	if (vm.count("help")) {
	    std::cout << desc << std::endl;
	    return 1;
	}

	bool run_tests = false;
	if (vm.count("run-tests")) {
	    std::cout << "Will run tests..." << std::endl;
	    run_tests = vm["run-tests"].as<bool>();
	}

	bool use_graphics = false;
	if (vm.count("use_graphics")) {
		std::cout << "Will use GTK graphics..." << std::endl;
		use_graphics = vm["use-graphics"].as<bool>();
	}

	Scenario s;
	s.load_scenario("data/simple1.json");

	s.start();
	s.stop();

	if (run_tests) {
		return TestMain::run_tests(argc, argv);
	} else {
		return 0;
	}
}
