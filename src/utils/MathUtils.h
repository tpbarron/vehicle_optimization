/**
 * MathUtils.h
 *	
 *  Created on: Nov 15, 2014
 *      Author: trevor
 */

#ifndef MATHUTILS_H_
#define MATHUTILS_H_

#include <cmath>

#include "data_types/sensor_types/Distance.h"
#include "data_types/sensor_types/Position.h"

/**
 *
 */
namespace MathUtils {

Distance get_distance(Position &p1, Position &p2);


};

#endif /* MATHUTILS_H_ */
