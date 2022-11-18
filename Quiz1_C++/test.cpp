#include "quiz1.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Function: suffixCount 1", "[given]") {
	REQUIRE(suffixCount("et tu, brute", 1) == 2);
}

TEST_CASE("Function: suffixCount 2", "[given]") {
	REQUIRE(suffixCount("aaa", 1) == 3);
}

// TEST_CASE("Function: suffixCount 4", "[given]") {
// 	REQUIRE(suffixCount("aaaaaa", 3) == ?);
// }

// TEST_CASE("Function: suffixCount 5", "[given]") {
// 	REQUIRE(suffixCount("aaabaaaa", 4) == ?);
// }
