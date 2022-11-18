#include "quiz3.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Function: encryptImage 1", "[given]") {
	ListNode* imagehead = nullptr;
	imagehead = addEnd(imagehead, 3);
	imagehead = addEnd(imagehead, 1);
	imagehead = addEnd(imagehead, 6);
	imagehead = addEnd(imagehead, 4);
	imagehead = addEnd(imagehead, 7);
	imagehead = addEnd(imagehead, 2);
	std::vector<int> output = encryptImage(imagehead);
	std::vector<int> expected_output {6, 6, 7, 7, 0, 0};
	REQUIRE(output == expected_output);
}

TEST_CASE("Function: encryptImage 2", "[given]") {
	ListNode* imagehead = nullptr;
	imagehead = addEnd(imagehead, 2);
	imagehead = addEnd(imagehead, 1);
	imagehead = addEnd(imagehead, 2);
	std::vector<int> output = encryptImage(imagehead);
	std::vector<int> expected_output {0, 2, 0};
	REQUIRE(output == expected_output);
}

// TEST_CASE("Function: encryptImage 3", "[output_hidden]") {
// 	ListNode* imagehead = nullptr;
// 	imagehead = addEnd(imagehead, 6);
// 	imagehead = addEnd(imagehead, 5);
// 	imagehead = addEnd(imagehead, 4);
// 	imagehead = addEnd(imagehead, 3);
// 	imagehead = addEnd(imagehead, 2);
// 	imagehead = addEnd(imagehead, 1);
// 	std::vector<int> output = encryptImage(imagehead);
// 	std::vector<int> expected_output {?};
// 	REQUIRE(output == expected_output);
// }
