#include "quiz8.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Function: findTheDigits. Testing adding 1 new digit. x is \"1234\", y is \"12345\"", "[simple]") {
	std::string x = "1234", y = "12345";
	REQUIRE(findTheDigits(x, y) == "5");
}

TEST_CASE("Function: findTheDigits. Testing adding n more new digits. x is \"8\", y is \"56981234\"", "[simple]") {
	std::string x = "8", y = "56981234";
	REQUIRE(findTheDigits(x, y) == "1234569");
}
