#include <catch.hpp>
#include <hash_table_o_a.hpp>
#include <hash_table_s_c.hpp>

////HASH_TABLE_O_A////

SCENARIO("Hash_Table_O_A standart init") {

	Hash_Table_O_A<int> ht1;
	REQUIRE(ht1.find(1) == false);
	REQUIRE(ht1.size() == 0);
	REQUIRE(ht1.empty() == true);
}

SCENARIO("Hash_Table_O_A insert") {

	Hash_Table_O_A<int> ht1;
	REQUIRE(ht1.find(1) == false);
	ht1.emplace(1);
	REQUIRE(1 == ht1.size());
	REQUIRE(ht1.find(1) == true);

	ht1.insert(1);
	REQUIRE(2 == ht1.size());
	REQUIRE(ht1.find(1) == true);

	REQUIRE(ht1.find(5) == false);
	ht1.insert(5);
	REQUIRE(ht1.find(5) == true);
	REQUIRE(3 == ht1.size());
}

SCENARIO("Hash_Table_O_A erase") {

	Hash_Table_O_A<int> ht1;
	ht1.insert(1);

	ht1.erase(1);
	REQUIRE(ht1.find(1) == false);
	REQUIRE(ht1.size() == 0);

	ht1.insert(1);
	ht1.insert(1);
	ht1.insert(1);
	ht1.insert(1);
	REQUIRE(ht1.find(1) == true);
	REQUIRE(4 == ht1.size());

	ht1.insert(2);
	ht1.insert(3);
	ht1.insert(6);
	REQUIRE(7 == ht1.size());

	ht1.erase(1);
	REQUIRE(6 == ht1.size());

	ht1.erase(1);
	REQUIRE(5 == ht1.size());
	REQUIRE(ht1.find(1) == true);
	REQUIRE(ht1.find(2) == true);
	REQUIRE(ht1.find(3) == true);
	REQUIRE(ht1.find(6) == true);
}

SCENARIO("Hash_Table_O_A clear") {

	Hash_Table_O_A<int> ht1;
	ht1.clear();
	REQUIRE(ht1.size() == 0);
	REQUIRE(ht1.find(2) == false);
	REQUIRE(ht1.find(3) == false);
	REQUIRE(ht1.find(6) == false);
	REQUIRE(ht1.empty() == true);

	ht1.insert(2);
	ht1.insert(3);
	ht1.insert(6);
	REQUIRE(ht1.size() == 3);
	REQUIRE(ht1.find(2) == true);
	REQUIRE(ht1.find(3) == true);
	REQUIRE(ht1.find(6) == true);
	REQUIRE(ht1.empty() == false);

	ht1.clear();
	REQUIRE(ht1.size() == 0);
	REQUIRE(ht1.find(2) == false);
	REQUIRE(ht1.find(3) == false);
	REQUIRE(ht1.find(6) == false);
	REQUIRE(ht1.empty() == true);
}

SCENARIO("Hash_Table_O_A operator= and init with other") {

	Hash_Table_O_A<int> ht1;
	ht1.insert(2);
	ht1.insert(3);
	ht1.insert(6);

	Hash_Table_O_A<int> ht2(ht1);
	REQUIRE(ht2.find(2) == true);
	REQUIRE(ht2.find(3) == true);
	REQUIRE(ht2.find(6) == true);
	REQUIRE(3 == ht2.size());

	ht1.clear();
	REQUIRE(ht2.find(2) == true);
	REQUIRE(ht2.find(3) == true);
	REQUIRE(ht2.find(6) == true);
	REQUIRE(3 == ht2.size());

	Hash_Table_O_A<int> ht3;
	ht3 = ht2;
	REQUIRE(ht3.find(2) == true);
	REQUIRE(ht3.find(3) == true);
	REQUIRE(ht3.find(6) == true);
	REQUIRE(3 == ht3.size());

	ht2.erase(2);
	REQUIRE(ht3.find(2) == true);
	REQUIRE(ht3.find(3) == true);
	REQUIRE(ht3.find(6) == true);
	REQUIRE(3 == ht3.size());

	ht3.erase(3);
	REQUIRE(ht2.find(2) == false);
	REQUIRE(ht2.find(3) == true);
	REQUIRE(ht2.find(6) == true);
	REQUIRE(2 == ht2.size());
	REQUIRE(ht3.find(2) == true);
	REQUIRE(ht3.find(3) == false);
	REQUIRE(ht3.find(6) == true);
	REQUIRE(2 == ht3.size());
}

////HASH_TABLE_O_A////

////HASH_TABLE_S_C////

SCENARIO("Hash_Table_S_C standart init") {

	Hash_Table_S_C<char, int> ht1;
	REQUIRE(ht1.find('a') == false);
	REQUIRE(ht1.size() == 0);
	REQUIRE(ht1.empty() == true);
}

SCENARIO("Hash_Table_S_C insert") {

	Hash_Table_S_C<char, int> ht1;
	REQUIRE(ht1.find('b') == false);
	ht1.insert('b', 1);
	REQUIRE(1 == ht1.size());
	REQUIRE(ht1.find('b') == true);

	ht1.insert('b',2);
	REQUIRE(2 == ht1.size());
	REQUIRE(ht1.find('b') == true);

	REQUIRE(ht1.find('a') == false);
	ht1.insert('a', 10);
	REQUIRE(ht1.find('a') == true);
	REQUIRE(3 == ht1.size());
}

SCENARIO("Hash_Table_S_C erase") {

	Hash_Table_S_C<char,int> ht1;
	ht1.insert('a', 1);

	ht1.erase('a');
	REQUIRE(ht1.find('a') == false);
	REQUIRE(ht1.size() == 0);

	ht1.insert('a', 1);
	ht1.insert('a', 1);
	ht1.insert('a', 2);
	ht1.insert('a', 3);
	REQUIRE(ht1.find('a') == true);
	REQUIRE(4 == ht1.size());

	ht1.insert('b', 2);
	ht1.insert('c', 3);
	ht1.insert('d', 4);
	REQUIRE(7 == ht1.size());

	ht1.erase('a');
	REQUIRE(6 == ht1.size());

	ht1.erase('a');
	REQUIRE(5 == ht1.size());
	REQUIRE(ht1.find('a') == true);
	REQUIRE(ht1.find('b') == true);
	REQUIRE(ht1.find('c') == true);
	REQUIRE(ht1.find('d') == true);
}

SCENARIO("Hash_Table_S_C clear") {

	Hash_Table_S_C<char, int> ht1;
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

SCENARIO("Hash_Table_S_C operator= and init with other") {

	Hash_Table_S_C<char, int> ht1;
	ht1.insert('a', 2);
	ht1.insert('b', 3);
	ht1.insert('c', 4);

	Hash_Table_S_C<char, int> ht2(ht1);
	REQUIRE(ht2.find('b') == true);
	REQUIRE(ht2.find('a') == true);
	REQUIRE(ht2.find('c') == true);
	REQUIRE(3 == ht2.size());

	ht1.clear();
	REQUIRE(ht2.find('a') == true);
	REQUIRE(ht2.find('b') == true);
	REQUIRE(ht2.find('c') == true);
	REQUIRE(3 == ht2.size());

	Hash_Table_S_C<char, int> ht3;
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

////HASH_TABLE_S_C////