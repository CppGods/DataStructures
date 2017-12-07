#include <catch.hpp>
#include <hash_table_o_a.hpp>

SCENARIO("Hash_Table_O_A standart init") {

	Hash_Table_O_A<int> ht1;
	REQUIRE(ht1.find(1) == false);
	REQUIRE(ht1.size() == 0);
	REQUIRE(ht1.empty() == true);
}

SCENARIO("Hash_Table_O_A insert") {

	Hash_Table_O_A<int> ht1;
	REQUIRE(ht1.find(1) == false);
	ht1.insert(1);
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