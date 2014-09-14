vehicle_optimization
====================

Vehicle simulator to test algorithms for traffic optimization.


Dependencies:

  * libboost-all-dev
  * mongodb

These can be installed using:

  apt-get install libboost-all-dev<br/>
  apt-get install mongodb

The following should already be done for you if you use eclipse and have the .cproject file. 

 * To build you need to link the following libraries (in this order):
pthread, mongoclient, crypto, ssl, boost_thread, boost_filesystem, boost_system

 * If you are using Eclipse with the C dev tools (apt-get install eclipse-cdt) you can add these libraries under Project->Properties->C/C++ Build->Settings. On the Tool Settings tab under GCC C++ Linker select libraries and in the top panel and the above libraries.


For version control in eclipse install EGit as a plugin. You might have to match the version to your version of eclipse. A good tutorial is here: http://www.vogella.com/tutorials/EclipseGit/article.html
