/**
 * MathUtils.cpp
 *	
 *  Created on: Nov 15, 2014
 *      Author: trevor
 */

#include <utils/MathUtils.h>

namespace MathUtils {

/**
 * returns the euclidean distance between points p1 and p2
 */
Distance get_distance(Position &p1, Position &p2) {
	double dx = p1.get_x() - p2.get_x();
	double dy = p1.get_y() - p2.get_y();
	double dist = std::sqrt(dx*dx + dy*dy);
	Distance d(dist);
	return d;
}

}
