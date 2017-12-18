#include <catch.hpp>
#include <unordered_map.hpp>

SCENARIO("Unordered_Map standart init") {

	Unordered_Map<char, int> ump1;
	REQUIRE(ump1.find('a') == false);
	REQUIRE(ump1.size() == 0);
	REQUIRE(ump1.empty() == true);
}

SCENARIO("Unordered_Map insert") {

	Unordered_Map<char, int> ump1;
	REQUIRE(ump1.find('b') == false);
	ump1.insert('b', 1);
	REQUIRE(1 == ump1.size());
	REQUIRE(ump1.find('b') == true);

	ump1.insert('b',2);
	REQUIRE(1 == ump1.size());
	REQUIRE(ump1.find('b') == true);

	REQUIRE(ump1.find('a') == false);
	ump1.insert('a', 10);
	REQUIRE(ump1.find('a') == true);
	REQUIRE(2 == ump1.size());
}

SCENARIO("Unordered_Map erase") {

	Unordered_Map<char,int> ump1;
	ump1.insert('a', 1);

	ump1.erase('a');
	REQUIRE(ump1.find('a') == false);
	REQUIRE(ump1.size() == 0);

	ump1.insert('a', 1);
	ump1.insert('a', 1);
	ump1.insert('a', 2);
	ump1.insert('a', 3);
	REQUIRE(ump1.find('a') == true);
	REQUIRE(1 == ump1.size());

	ump1.insert('b', 2);
	ump1.insert('c', 3);
	ump1.insert('d', 4);
	REQUIRE(4 == ump1.size());

	ump1.erase('a');
	REQUIRE(3 == ump1.size());

	ump1.erase('a');
	REQUIRE(3 == ump1.size());
	REQUIRE(ump1.find('a') == false);
	REQUIRE(ump1.find('b') == true);
	REQUIRE(ump1.find('c') == true);
	REQUIRE(ump1.find('d') == true);
}

SCENARIO("Unordered_Map clear") {

	Unordered_Map<char, int> ump1;
	ump1.clear();
	REQUIRE(ump1.size() == 0);
	REQUIRE(ump1.find('a') == false);
	REQUIRE(ump1.find('b') == false);
	REQUIRE(ump1.find('c') == false);
	REQUIRE(ump1.empty() == true);

	ump1.insert('b', 1);
	ump1.insert('c', 2);
	ump1.insert('d', 3);
	REQUIRE(ump1.size() == 3);
	REQUIRE(ump1.find('b') == true);
	REQUIRE(ump1.find('c') == true);
	REQUIRE(ump1.find('d') == true);
	REQUIRE(ump1.empty() == false);

	ump1.clear();
	REQUIRE(ump1.size() == 0);
	REQUIRE(ump1.find('b') == false);
	REQUIRE(ump1.find('c') == false);
	REQUIRE(ump1.find('d') == false);
	REQUIRE(ump1.empty() == true);
}

SCENARIO("Unordered_Map operator= and init with other") {

	Unordered_Map<char, int> ump1;
	ump1.insert('a', 2);
	ump1.insert('b', 3);
	ump1.insert('c', 4);

	Unordered_Map<char, int> ump2(ump1);
	REQUIRE(ump2.find('b') == true);
	REQUIRE(ump2.find('a') == true);
	REQUIRE(ump2.find('c') == true);
	REQUIRE(3 == ump2.size());

	ump1.clear();
	REQUIRE(ump2.find('a') == true);
	REQUIRE(ump2.find('b') == true);
	REQUIRE(ump2.find('c') == true);
	REQUIRE(3 == ump2.size());

	Unordered_Map<char, int> ump3;
	ump3 = ump2;
	REQUIRE(ump3.find('a') == true);
	REQUIRE(ump3.find('b') == true);
	REQUIRE(ump3.find('c') == true);
	REQUIRE(3 == ump3.size());

	ump2.erase('a');
	REQUIRE(ump3.find('a') == true);
	REQUIRE(ump3.find('b') == true);
	REQUIRE(ump3.find('c') == true);
	REQUIRE(3 == ump3.size());

	ump3.erase('b');
	REQUIRE(ump2.find('a') == false);
	REQUIRE(ump2.find('b') == true);
	REQUIRE(ump2.find('c') == true);
	REQUIRE(2 == ump2.size());
	REQUIRE(ump3.find('a') == true);
	REQUIRE(ump3.find('b') == false);
	REQUIRE(ump3.find('c') == true);
	REQUIRE(2 == ump3.size());
}

SCENARIO("Unordered_Map operators [] and iterators") {

	Unordered_Map<char, int> ump1;
	ump1.insert('a', 2);
	ump1.insert('b', 3);
	ump1.insert('c', 4);

	REQUIRE(ump1['a'] == 2);
	REQUIRE(ump1['b'] == 3);
	REQUIRE(ump1['c'] == 4);
	ump1['a'] = 4;
	ump1['c'] = 2;
	REQUIRE(ump1['a'] == 4);
	REQUIRE(ump1['b'] == 3);
	REQUIRE(ump1['c'] == 2);

	REQUIRE(ump1['d'] == int());
	ump1['d'] = 5;
	REQUIRE(ump1['d'] == 5);

	ump1.erase('a');
	ump1.erase('b');
	int a_count = ump1['a'];
	int b_count = ump1['b'];
	REQUIRE(int() == a_count );
	REQUIRE(int() == b_count );
	REQUIRE(ump1.size() == 4);

	

	ump1.erase('a');
	ump1.erase('b');
	auto it = ump1.cbegin();
	auto it_e = ump1.cend();
	REQUIRE(ump1.size() == 2);

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