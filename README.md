vehicle_optimization
====================

Vehicle simulator to test algorithms for traffic optimization.


Dependencies:

  * libboost-all-dev
  * mongodb

These can be installed using:

  apt-get install libboost-all-dev<br/>
  apt-get install mongodb

To build you need to link the following libraries (in this order):
pthread, mongoclient, crypto, ssl, boost_thread, boost_filesystem, boost_system

If you are using Eclipse with the C dev tools (apt-get install eclipse-cdt) you can add these libraries under Project->Properties->C/C++ Build->Settings. On the Tool Settings tab under GCC C++ Linker select libraries and in the top panel and the above libraries.
