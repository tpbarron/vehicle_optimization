/**
 * AstarGoalVisitor.h
 *	
 *  Created on: Sep 30, 2014
 *      Author: trevor
 */

#ifndef ASTARGOALVISITOR_H_
#define ASTARGOALVISITOR_H_

#include <boost/graph/astar_search.hpp>

#include "map/Map.h"

/**
 *
 */
class AstarGoalVisitor : public boost::default_astar_visitor {

public:

	struct found_goal {}; //exception for termination

	AstarGoalVisitor(Map::vertex_t goal);
	virtual ~AstarGoalVisitor();

	void examine_vertex(Map::vertex_t v, const Map::Graph& g);

private:

	Map::vertex_t _goal;

};

#endif /* ASTARGOALVISITOR_H_ */
