/*
	To compile:
		g++ -o test test-unit/test.cpp 
	To run:
		./test
*/

#include "graph.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Function: sumEdge", "[unit]") 
{
	Graph g;
	g.insertEdge(1, 2, 10);
	g.insertEdge(1, 2, 20);
	g.insertEdge(1, 4, 30);
	REQUIRE(g.sumEdge(1, 2) == 30);
	REQUIRE(g.sumEdge(1, 4) == 30);
	REQUIRE(g.sumEdge(2, 4) == 0);
}
