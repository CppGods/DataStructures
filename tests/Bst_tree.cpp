#include <catch.hpp>
#include <bst_tree.hpp>

////////////////////////////////////////////////bst_tree////////////////////////////////////////////////////

SCENARIO("bst_tree standart init") {
	bst_tree<int> tr1;
	REQUIRE(tr1.is_node(0) == false);
	REQUIRE(tr1.size() == 0);
	bst_tree<double> tr2;
	REQUIRE(tr2.is_node(1) == false);
	REQUIRE(tr2.size() == 0);
}

SCENARIO("bst_tree insert") {

	bst_tree<int> tr1;
	REQUIRE(tr1.is_node(1) == false);
	tr1.insert(1);
	REQUIRE(1 == tr1.size());
	REQUIRE(tr1.is_node(1) == true);

	REQUIRE(tr1.is_node(5) == false);
	tr1.insert(5);
	REQUIRE(tr1.is_node(5) == true);
	REQUIRE(2 == tr1.size());

	REQUIRE(tr1.is_node(-1) == false);
	tr1.insert(-1);
	REQUIRE(tr1.is_node(-1) == true);
	REQUIRE(3 == tr1.size());

	REQUIRE(tr1.is_node(-2) == false);
	tr1.insert(-2);
	REQUIRE(tr1.is_node(-2) == true);
	REQUIRE(4 == tr1.size());

	REQUIRE(tr1.is_node(0) == false);
	tr1.insert(0);
	REQUIRE(tr1.is_node(0) == true);
	REQUIRE(5 == tr1.size());

	REQUIRE(tr1.is_node(6) == false);
	tr1.insert(6);
	REQUIRE(tr1.is_node(6) == true);
	REQUIRE(6 == tr1.size());

	REQUIRE(tr1.is_node(4) == false);
	tr1.insert(4);
	REQUIRE(tr1.is_node(4) == true);
	REQUIRE(7 == tr1.size());

	REQUIRE(tr1.is_node(8) == false);
	tr1.insert(8);
	REQUIRE(tr1.is_node(8) == true);
	REQUIRE(8 == tr1.size());

	REQUIRE(tr1.is_node(-9) == false);
	tr1.insert(-9);
	REQUIRE(tr1.is_node(-9) == true);
	REQUIRE(9 == tr1.size());

}

SCENARIO("bst_tree del") {

	bst_tree<int> tr1;
	tr1.insert(1);
	tr1.erase(1);
	REQUIRE(tr1.is_node(1) == false);
	REQUIRE(0 == tr1.size());

	tr1.insert(1);
	tr1.insert(5);
	tr1.insert(-1);
	tr1.insert(-2);
	tr1.insert(0);
	tr1.insert(6);
	tr1.insert(4);
	tr1.insert(8);
	tr1.insert(-9);

	REQUIRE(9 == tr1.size());
	tr1.erase(10);
	REQUIRE(9 == tr1.size());
	tr1.erase(1);
	REQUIRE(8 == tr1.size());
	tr1.erase(-9);
	REQUIRE(7 == tr1.size());
	tr1.erase(5);
	REQUIRE(6 == tr1.size());
	tr1.erase(4);
	REQUIRE(5 == tr1.size());
	tr1.erase(-1);
	REQUIRE(4 == tr1.size());
	tr1.erase(8);
	REQUIRE(3 == tr1.size());
	tr1.erase(0);
	REQUIRE(2 == tr1.size());
	tr1.erase(6);
	REQUIRE(1 == tr1.size());
	tr1.erase(-2);
	REQUIRE(0 == tr1.size());

	tr1.erase(-2);
	REQUIRE(0 == tr1.size());

	bst_tree<double> tr2;

	tr2.insert(16.0);
	tr2.insert(-28.0);
	tr2.insert(11.55);
	tr2.insert(19.0);
	tr2.insert(145.444);
	tr2.insert(17.88);
	tr2.insert(17.88);
	tr2.insert(6.0);
	tr2.insert(0.0);

	REQUIRE(9 == tr2.size());

	tr2.erase(16.0);
	tr2.erase(-28.0);
	tr2.erase(11.55);
	tr2.erase(19.0);
	tr2.erase(145.444);
	tr2.erase(17.88);
	tr2.erase(17.88);
	tr2.erase(6.0);
	tr2.erase(0.0);

	REQUIRE(0 == tr2.size());
}

SCENARIO("bst_tree operator= and init with other") {

	bst_tree<int> tr1;
	tr1.insert(2);
	tr1.insert(3);
	tr1.insert(6);

	bst_tree<int> tr2(tr1);
	REQUIRE(tr2.is_node(2) == true);
	REQUIRE(tr2.is_node(3) == true);
	REQUIRE(tr2.is_node(6) == true);
	REQUIRE(3 == tr2.size());

	tr1.erase(2);
	REQUIRE(tr2.is_node(2) == true);
	REQUIRE(tr2.is_node(3) == true);
	REQUIRE(tr2.is_node(6) == true);
	REQUIRE(3 == tr2.size());

	bst_tree<int> tr3;
	tr3 = tr2;
	REQUIRE(tr3.is_node(2) == true);
	REQUIRE(tr3.is_node(3) == true);
	REQUIRE(tr3.is_node(6) == true);
	REQUIRE(tr3.size() == 3);

	tr2.erase(3);
	REQUIRE(tr3.is_node(2) == true);
	REQUIRE(tr3.is_node(3) == true);
	REQUIRE(tr3.is_node(6) == true);
	REQUIRE(3 == tr3.size());

	tr3 = tr2;
	REQUIRE(tr3.is_node(2) == true);
	REQUIRE(tr3.is_node(3) == false);
	REQUIRE(tr3.is_node(6) == true);
	REQUIRE(2 == tr3.size());
}

////////////////////////////////////////////////bst_tree////////////////////////////////////////////////////