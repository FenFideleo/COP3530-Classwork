#include "quiz11.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Function: swampExplorer 1", "[simple]") {
	std::vector<std::vector<int>> input = {{5, 3, 4}, {8, 6, 9}, {1, 3, 2}};
	REQUIRE(swampExplorer(input) == 30);
}

TEST_CASE("Function: swampExplorer 2", "[simple]") {
	std::vector<std::vector<int>> input = {{0, 0}, {1, 0}};
	REQUIRE(swampExplorer(input) == 1);
}

// TEST_CASE("Function: swampExplorer 3", "[simple]") {
// 	std::vector<std::vector<int>> input = {{2, 3}, {0, 0, 0}, {0, 0, 0}};
// 	REQUIRE(swampExplorer(input) == ____ //fill this);
// }