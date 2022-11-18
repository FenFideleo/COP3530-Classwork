/*
	To compile:
		g++ -std=c++14 -o test test-unit/test.cpp 
	To run:
		./test
*/

#include "dijkstra.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Function: Test 1", "[given]") 
{
	std::vector<std::string> graph = {
		"s3153",
		"1.424",
		"22.3t"
	};
	REQUIRE(dijkstra(graph) == 13);
}