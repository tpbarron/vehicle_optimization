/**
 * AstarGoalVisitor.cpp
 *	
 *  Created on: Sep 30, 2014
 *      Author: trevor
 */

#include "AstarGoalVisitor.h"

AstarGoalVisitor::AstarGoalVisitor(Map::vertex_t goal) : _goal(goal) {
	// TODO Auto-generated constructor stub

}

AstarGoalVisitor::~AstarGoalVisitor() {
	// TODO Auto-generated destructor stub
}

void AstarGoalVisitor::examine_vertex(Map::vertex_t v, const Map::Graph& g) {
	if (v == _goal) {
		throw found_goal();
	}
}
