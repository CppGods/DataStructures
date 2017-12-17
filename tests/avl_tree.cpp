#include <tree.hpp>
#include <catch.hpp>


SCENARIO("AVL null")
{
	avl_tree<int, int> a;
	REQUIRE(a.isEmpty());
}
SCENARIO("AVL add")
{
	avl_tree <int, int> a;
	a.insert(5, 6);
	REQUIRE(!a.isEmpty());
}
SCENARIO("AVL delete non inserted element", "[delete]")
{
	avl_tree<int, int> tree = { {8, 7} };
	tree.remove(4);
	REQUIRE(!tree.isEmpty());
}
SCENARIO("AVL delete root with one element", "[delete]")
{
	avl_tree<int, int> tree = { {8,8} };
	tree.remove(8);
	REQUIRE(tree.isEmpty());
}
SCENARIO("AVL delete non  root without child", "[delete]")
{
	avl_tree<int, int> tree = { {2,8}, {5, 4}, {5, 3} };
	tree.remove(8);
	avl_tree<int, int> tr ={ {5, 4}, {5, 3}};
	REQUIRE(tree ==tr);
}
SCENARIO("AVL delete root with two children", "[delete]")
{
	avl_tree<int, int> tree = { {1, 8}, {18, 4}, {22, 3}, {2,10}, {3, 9}, {12,13}, {7,11}, {1,12} };
	tree.remove(4);
	avl_tree<int, int>tr={ {3, 9}, {1, 8},  {7,11}, {22, 3},{2,10}, {12,13}, {1,12} };
	REQUIRE(tree ==tr );
}

SCENARIO("AVL delete non root without children", "[delete]")
{
	avl_tree<int, int> tree = { {1, 8}, {18, 4}, {22, 3}, {2,10}, {3, 9}, {12,13}, {7,11}, {1,12} };
	tree.remove(3);
	avl_tree<int, int>tr = { { 3, 9 },{ 18, 4 },{7, 11 } ,{ 1, 8 },{ 12,13 }, { 2,10 },{ 1,12 }};
	REQUIRE(tree == tr);
}
SCENARIO("AVL delete non root with one child", "[delete]")
{
	avl_tree<int, int> tree = { {1, 8}, {18, 4}, {22, 3}, {2,10}, {3, 9}, {12,13}, {7,11}, {1,12} };
	tree.remove(12);
	avl_tree<int, int> tr ={{3, 9}, {18, 4}, {7,11}, {2,10}, {18, 4}, {12,13}, {1, 8}, {22, 3}};
	REQUIRE(tree == tr);
}
