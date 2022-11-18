#include "quiz4.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Function: sum of level 1", "[given]") {
	TreeNode* root = nullptr;
	root = insert(root, 2);
	root = insert(root, 1);
	root = insert(root, 3);
	root = insert(root, 4);
	REQUIRE(2 == sumOfLevel(root, 0));
}


 TEST_CASE("Function: sum of level 2", "[output_hidden]") {
	TreeNode* root = nullptr;
	root = insert(root, 2);
	root = insert(root, 1);
	root = insert(root, 3);
	root = insert(root, 4);
	REQUIRE(4 == sumOfLevel(root, 1));
 }
