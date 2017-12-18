#include <catch.hpp>
#include <avl_tree.hpp>

SCENARIO("avl_tree standart init") {
	avl_tree<char, int> tr1;
	REQUIRE(tr1.search('a') == nullptr);
	REQUIRE(tr1.size() == 0);
	avl_tree<char, double> tr2;
	REQUIRE(tr2.search('a') == nullptr);
	REQUIRE(tr2.size() == 0);
}

SCENARIO("avl_tree insert") {

	avl_tree<char, int> tr1;
	tr1.insert(1, 'a');
	REQUIRE(1 == tr1.size());
	REQUIRE(tr1.search('a') != nullptr);

	REQUIRE(tr1.search('b') == nullptr);
	tr1.insert(5, 'b');
	REQUIRE(tr1.search('b') != nullptr);
	REQUIRE(2 == tr1.size());

	REQUIRE(tr1.search('c') == nullptr);
	tr1.insert(-1,'c');
	REQUIRE(tr1.search('c') != nullptr);
	REQUIRE(3 == tr1.size());

	REQUIRE(tr1.search('d') == nullptr);
	tr1.insert(-2, 'd');
	REQUIRE(tr1.search('d') != nullptr);
	REQUIRE(4 == tr1.size());

	REQUIRE(tr1.search('-') == nullptr);
	tr1.insert(0, '-');
	REQUIRE(tr1.search('-') != nullptr);
	REQUIRE(5 == tr1.size());

	REQUIRE(tr1.search('6') == nullptr);
	tr1.insert(6, '6');
	REQUIRE(tr1.search('6') != nullptr);
	REQUIRE(6 == tr1.size());

	REQUIRE(tr1.search('4') == nullptr);
	tr1.insert(4, '4');
	REQUIRE(tr1.search('4') != nullptr);
	REQUIRE(7 == tr1.size());

	REQUIRE(tr1.search('z') == nullptr);
	tr1.insert(8, 'z');
	REQUIRE(tr1.search('z') != nullptr);
	REQUIRE(8 == tr1.size());

	REQUIRE(tr1.search('.') == nullptr);
	tr1.insert(-9, '.');
	REQUIRE(tr1.search('.') != nullptr);
	REQUIRE(9 == tr1.size());

}

SCENARIO("avl_tree del") {

	avl_tree<char ,int> tr1;
	tr1.insert(1, 'a');
	tr1.remove('a');
	REQUIRE(tr1.search('a') == nullptr);
	REQUIRE(0 == tr1.size());

	tr1.insert(1, 'e');
	tr1.insert(5, 'g');
	tr1.insert(-1, 'b');
	tr1.insert(-2, 'c');
	tr1.insert(0, 'd');
	tr1.insert(6, 'h');
	tr1.insert(4, 'f');
	tr1.insert(8, 'i');
	tr1.insert(-9, 'a');

	REQUIRE(9 == tr1.size());
	tr1.remove('r');
	REQUIRE(9 == tr1.size());
	tr1.remove('e');
	REQUIRE(8 == tr1.size());
	tr1.remove('a');
	REQUIRE(7 == tr1.size());
	tr1.remove('g');
	REQUIRE(6 == tr1.size());
	tr1.remove('f');
	REQUIRE(5 == tr1.size());
	tr1.remove('b');
	REQUIRE(4 == tr1.size());
	tr1.remove('i');
	REQUIRE(3 == tr1.size());
	tr1.remove('d');
	REQUIRE(2 == tr1.size());
	tr1.remove('h');
	REQUIRE(1 == tr1.size());
	tr1.remove('c');
	REQUIRE(0 == tr1.size());

	tr1.remove('c');
	REQUIRE(0 == tr1.size());

	avl_tree<char, double> tr2;
	
	tr2.insert(16.0, 'a');
	tr2.insert(-28.0, 'b');
	tr2.insert(11.55, 'c');
	tr2.insert(19.0, 'd');
	tr2.insert(145.444, 'e');
	tr2.insert(17.88, 'f');
	tr2.insert(17.88, 'g');
	tr2.insert(6.0, 'h');
	tr2.insert(0.0, 'i');

	REQUIRE(9 == tr2.size());

	tr2.remove('a');
	tr2.remove('b');
	tr2.remove('c');
	tr2.remove('d');
	tr2.remove('e');
	tr2.remove('f');
	tr2.remove('g');
	tr2.remove('h');
	tr2.remove('i');

	REQUIRE(0 == tr2.size());
}

SCENARIO("avl_tree init with other") {

	avl_tree<char, int> tr1;
	tr1.insert(2, 'a');
	tr1.insert(3, 'b');
	tr1.insert(6, 'c');

	avl_tree<char, int> tr2(tr1);
	REQUIRE(tr2.search('a') != nullptr);
	REQUIRE(tr2.search('b') != nullptr);
	REQUIRE(tr2.search('c') != nullptr);
	REQUIRE(3 == tr2.size());

	tr1.remove('a');
	REQUIRE(tr2.search('a') != nullptr);
	REQUIRE(tr2.search('b') != nullptr);
	REQUIRE(tr2.search('c') != nullptr);
	REQUIRE(3 == tr2.size());

}
