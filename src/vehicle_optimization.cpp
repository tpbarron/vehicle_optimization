/*
 * vehicle_optimization.cpp
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
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
	Scenario::load_scenario("basic_grid");
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
