#include <tree.hpp>
#include <catch.hpp>


SCENARIO("null")
{
	RBtree<int, int> a;
	REQUIRE(a.isEmpty());
}
SCENARIO("add")
{
	RBtree <int, int> a;
	a.Insert(5, 6);
	REQUIRE(!a.isEmpty());
}
SCENARIO("BST delete non inserted element", "[delete]")
{
	RBtree<int, int> tree = { {8, 7} };
	tree.Remove(4);
	REQUIRE(!tree.isEmpty());
}
SCENARIO("BST delete root with one element", "[delete]")
{
	RBtree<int, int> tree = { {8,8} };
	tree.Remove(8);
	REQUIRE(tree.isEmpty());
}
SCENARIO("BST delete root without child", "[delete]")
{
	RBtree<int, int> tree = { {2,8}, {5, 4}, {5, 3} };
	tree.Remove(8);
	RBtree<int, int> tr ={ {5, 4}, {5, 3}};
	REQUIRE(tree ==tr);
}
SCENARIO("BST delete root with two children", "[delete]")
{
	RBtree<int, int> tree = { {1, 8}, {18, 4}, {22, 3}, {2,10}, {3, 9}, {12,13}, {7,11}, {1,12} };
	tree.Remove(4);
	RBtree<int, int>tr={ {3, 9}, {1, 8},  {7,11}, {22, 3},{2,10}, {12,13}, {1,12} };
	REQUIRE(tree ==tr );
}
SCENARIO("BST delete non root without children", "[delete]")
{
	RBtree<int, int> tree = { {1, 8}, {18, 4}, {22, 3}, {2,10}, {3, 9}, {12,13}, {7,11}, {1,12} };
	tree.Remove(3);
	RBtree<int, int>tr={{3, 9}, {18, 4}, {7,11}, {2,10}, {1,12}, {12,13}, {1, 8}} ;
	REQUIRE(tree == tr);
}
SCENARIO("BST delete non root with one child", "[delete]")
{
	RBtree<int, int> tree = { {1, 8}, {18, 4}, {22, 3}, {2,10}, {3, 9}, {12,13}, {7,11}, {1,12} };
	tree.Remove(12);
	RBtree<int, int> tr ={{3, 9}, {18, 4}, {7,11}, {2,10}, {18, 4}, {12,13}, {1, 8}, {22, 3}};
	REQUIRE(tree == tr);
}
