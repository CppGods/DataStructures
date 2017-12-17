#include <catch.hpp>
#include <unordered_map.hpp>

SCENARIO("Unordered_Map standart init") {

	Unordered_Map<char, int> ht1;
	REQUIRE(ht1.find('a') == false);
	REQUIRE(ht1.size() == 0);
	REQUIRE(ht1.empty() == true);
}

SCENARIO("Unordered_Map insert") {

	Unordered_Map<char, int> ht1;
	REQUIRE(ht1.find('b') == false);
	ht1.insert('b', 1);
	REQUIRE(1 == ht1.size());
	REQUIRE(ht1.find('b') == true);

	ht1.insert('b',2);
	REQUIRE(1 == ht1.size());
	REQUIRE(ht1.find('b') == true);

	REQUIRE(ht1.find('a') == false);
	ht1.insert('a', 10);
	REQUIRE(ht1.find('a') == true);
	REQUIRE(2 == ht1.size());
}

SCENARIO("Unordered_Map erase") {

	Unordered_Map<char,int> ht1;
	ht1.insert('a', 1);

	ht1.erase('a');
	REQUIRE(ht1.find('a') == false);
	REQUIRE(ht1.size() == 0);

	ht1.insert('a', 1);
	ht1.insert('a', 1);
	ht1.insert('a', 2);
	ht1.insert('a', 3);
	REQUIRE(ht1.find('a') == true);
	REQUIRE(1 == ht1.size());

	ht1.insert('b', 2);
	ht1.insert('c', 3);
	ht1.insert('d', 4);
	REQUIRE(4 == ht1.size());

	ht1.erase('a');
	REQUIRE(3 == ht1.size());

	ht1.erase('a');
	REQUIRE(3 == ht1.size());
	REQUIRE(ht1.find('a') == false);
	REQUIRE(ht1.find('b') == true);
	REQUIRE(ht1.find('c') == true);
	REQUIRE(ht1.find('d') == true);
}

SCENARIO("Unordered_Map clear") {

	Unordered_Map<char, int> ht1;
	ht1.clear();
	REQUIRE(ht1.size() == 0);
	REQUIRE(ht1.find('a') == false);
	REQUIRE(ht1.find('b') == false);
	REQUIRE(ht1.find('c') == false);
	REQUIRE(ht1.empty() == true);

	ht1.insert('b', 1);
	ht1.insert('c', 2);
	ht1.insert('d', 3);
	REQUIRE(ht1.size() == 3);
	REQUIRE(ht1.find('b') == true);
	REQUIRE(ht1.find('c') == true);
	REQUIRE(ht1.find('d') == true);
	REQUIRE(ht1.empty() == false);

	ht1.clear();
	REQUIRE(ht1.size() == 0);
	REQUIRE(ht1.find('b') == false);
	REQUIRE(ht1.find('c') == false);
	REQUIRE(ht1.find('d') == false);
	REQUIRE(ht1.empty() == true);
}

SCENARIO("Unordered_Map operator= and init with other") {

	Unordered_Map<char, int> ht1;
	ht1.insert('a', 2);
	ht1.insert('b', 3);
	ht1.insert('c', 4);

	Unordered_Map<char, int> ht2(ht1);
	REQUIRE(ht2.find('b') == true);
	REQUIRE(ht2.find('a') == true);
	REQUIRE(ht2.find('c') == true);
	REQUIRE(3 == ht2.size());

	ht1.clear();
	REQUIRE(ht2.find('a') == true);
	REQUIRE(ht2.find('b') == true);
	REQUIRE(ht2.find('c') == true);
	REQUIRE(3 == ht2.size());

	Unordered_Map<char, int> ht3;
	ht3 = ht2;
	REQUIRE(ht3.find('a') == true);
	REQUIRE(ht3.find('b') == true);
	REQUIRE(ht3.find('c') == true);
	REQUIRE(3 == ht3.size());

	ht2.erase('a');
	REQUIRE(ht3.find('a') == true);
	REQUIRE(ht3.find('b') == true);
	REQUIRE(ht3.find('c') == true);
	REQUIRE(3 == ht3.size());

	ht3.erase('b');
	REQUIRE(ht2.find('a') == false);
	REQUIRE(ht2.find('b') == true);
	REQUIRE(ht2.find('c') == true);
	REQUIRE(2 == ht2.size());
	REQUIRE(ht3.find('a') == true);
	REQUIRE(ht3.find('b') == false);
	REQUIRE(ht3.find('c') == true);
	REQUIRE(2 == ht3.size());
}

SCENARIO("Unordered_Map operators [] and iterators") {

	Unordered_Map<char, int> ht1;
	ht1.insert('a', 2);
	ht1.insert('b', 3);
	ht1.insert('c', 4);

	REQUIRE(ht1['a'] == 2);
	REQUIRE(ht1['b'] == 3);
	REQUIRE(ht1['c'] == 4);
	ht1['a'] = 4;
	ht1['c'] = 2;
	REQUIRE(ht1['a'] == 4);
	REQUIRE(ht1['b'] == 3);
	REQUIRE(ht1['c'] == 2);

	REQUIRE(ht1['d'] == int());
	ht1['d'] = 5;
	REQUIRE(ht1['d'] == 5);

	ht1.erase('a');
	ht1.erase('b');
	int a_count = ht1['a'];
	int b_count = ht1['b'];
	REQUIRE(int() == a_count );
	REQUIRE(int() == b_count );
	REQUIRE(ht1.size() == 4);

	

	ht1.erase('a');
	ht1.erase('b');
	auto it = ht1.cbegin();
	auto it_e = ht1.cend();
	REQUIRE(ht1.size() == 2);

	if (it.key() == 'd') {
		REQUIRE(it.value() == 5);
		++it;
		REQUIRE(it.key() == 'c');
		REQUIRE(it.value() == 2);
	} else{
		REQUIRE(it.key() == 'c');
		REQUIRE(it.value() == 2);
		++it;
		REQUIRE(it.key() == 'd');
		REQUIRE(it.value() == 5);
	}
	++it;
	REQUIRE(it == it_e);
}