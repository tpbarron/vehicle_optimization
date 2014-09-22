/*
 * TestMain.cpp
 *
 *  Created on: Sep 19, 2014
 *      Author: trevor
 */

#define BOOST_TEST_DYN_LINK

#include "TestMain.h"

#include <boost/bind.hpp>
#include <boost/test/included/unit_test.hpp>

namespace TestMain {

int run_tests(int argc, char* argv[]) {
	return boost::unit_test::unit_test_main( &TestMain::init_function, argc, argv );
}

void free_test_function( int i, int j )
{
    BOOST_CHECK( true /* test assertion */ );
}


bool
init_function()
{
    boost::unit_test::framework::master_test_suite().
        add( BOOST_TEST_CASE( boost::bind( &free_test_function, 1, 1 ) ) );
    boost::unit_test::framework::master_test_suite().
        add( BOOST_TEST_CASE( boost::bind( &free_test_function, 1, 2 ) ) );
    boost::unit_test::framework::master_test_suite().
        add( BOOST_TEST_CASE( boost::bind( &free_test_function, 2, 1 ) ) );

    return true;
}

}
