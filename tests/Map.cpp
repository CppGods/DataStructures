#include <catch.hpp>
#include <map.hpp>


SCENARIO("map standart init") {

	map<char, int> mp1;
	REQUIRE(mp1.find('a') == false);
	REQUIRE(mp1.size() == 0);
	REQUIRE(mp1.empty() == true);
}


SCENARIO("map insert") {

	map<char, int> mp1;
	REQUIRE(mp1.find('b') == false);
	mp1.insert('b', 1);
	REQUIRE(1 == mp1.size());
	REQUIRE(mp1.find('b') == true);

	mp1.insert('b', 2);
	REQUIRE(1 == mp1.size());
	REQUIRE(mp1.find('b') == true);

	REQUIRE(mp1.find('a') == false);
	mp1.insert('a', 10);
	REQUIRE(mp1.find('a') == true);
	REQUIRE(2 == mp1.size());
}


SCENARIO("map erase") {

	map<char, int> mp1;
	mp1.insert('a', 1);

	mp1.erase('a');
	REQUIRE(mp1.find('a') == false);
	REQUIRE(mp1.size() == 0);

	mp1.insert('a', 1);
	mp1.insert('a', 1);
	mp1.insert('a', 2);
	mp1.insert('a', 3);
	REQUIRE(mp1.find('a') == true);
	REQUIRE(1 == mp1.size());

	mp1.insert('b', 2);
	mp1.insert('c', 3);
	mp1.insert('d', 4);
	REQUIRE(4 == mp1.size());

	mp1.erase('a');
	REQUIRE(3 == mp1.size());

	mp1.erase('a');
	REQUIRE(3 == mp1.size());
	REQUIRE(mp1.find('a') == false);
	REQUIRE(mp1.find('b') == true);
	REQUIRE(mp1.find('c') == true);
	REQUIRE(mp1.find('d') == true);
}


SCENARIO("map clear") {

	map<char, int> mp1;
	mp1.clear();
	REQUIRE(mp1.size() == 0);
	REQUIRE(mp1.find('a') == false);
	REQUIRE(mp1.find('b') == false);
	REQUIRE(mp1.find('c') == false);
	REQUIRE(mp1.empty() == true);

	mp1.insert('b', 1);
	mp1.insert('c', 2);
	mp1.insert('d', 3);
	REQUIRE(mp1.size() == 3);
	REQUIRE(mp1.find('b') == true);
	REQUIRE(mp1.find('c') == true);
	REQUIRE(mp1.find('d') == true);
	REQUIRE(mp1.empty() == false);

	mp1.clear();
	REQUIRE(mp1.size() == 0);
	REQUIRE(mp1.find('b') == false);
	REQUIRE(mp1.find('c') == false);
	REQUIRE(mp1.find('d') == false);
	REQUIRE(mp1.empty() == true);
}


SCENARIO("map operator= and init with other") {

	map<char, int> mp1;
	mp1.insert('a', 2);
	mp1.insert('b', 3);
	mp1.insert('c', 4);

	map<char, int> mp2(mp1);
	REQUIRE(mp2.find('b') == true);
	REQUIRE(mp2.find('a') == true);
	REQUIRE(mp2.find('c') == true);
	REQUIRE(3 == mp2.size());

	mp1.clear();
	REQUIRE(mp2.find('a') == true);
	REQUIRE(mp2.find('b') == true);
	REQUIRE(mp2.find('c') == true);
	REQUIRE(3 == mp2.size());

	map<char, int> mp3;
	mp3 = mp2;
	REQUIRE(mp3.find('a') == true);
	REQUIRE(mp3.find('b') == true);
	REQUIRE(mp3.find('c') == true);
	REQUIRE(3 == mp3.size());

	mp2.erase('a');
	REQUIRE(mp3.find('a') == true);
	REQUIRE(mp3.find('b') == true);
	REQUIRE(mp3.find('c') == true);
	REQUIRE(3 == mp3.size());

	mp3.erase('b');
	REQUIRE(mp2.find('a') == false);
	REQUIRE(mp2.find('b') == true);
	REQUIRE(mp2.find('c') == true);
	REQUIRE(2 == mp2.size());
	REQUIRE(mp3.find('a') == true);
	REQUIRE(mp3.find('b') == false);
	REQUIRE(mp3.find('c') == true);
	REQUIRE(2 == mp3.size());
}

SCENARIO("map operators [] and iterators") {

	map<char, int> mp1;
	mp1.insert('a', 2);
	mp1.insert('b', 3);
	mp1.insert('c', 4);

	REQUIRE(mp1['a'] == 2);
	REQUIRE(mp1['b'] == 3);
	REQUIRE(mp1['c'] == 4);

	mp1.insert('d', 5);
	REQUIRE(mp1['d'] == 5);

	mp1.erase('a');
	mp1.erase('b');
	REQUIRE(mp1.size() == 2);

	mp1.erase('a');
	mp1.erase('b');
	auto it = mp1.cbegin();
	auto it_e = mp1.cend();
	REQUIRE(mp1.size() == 2);

	REQUIRE(it.key() == 'c');
	REQUIRE(it.value() == 4);
	++it;
	REQUIRE(it.key() == 'd');
	REQUIRE(it.value() == 5);
	++it;
	REQUIRE(it == it_e);
	
}