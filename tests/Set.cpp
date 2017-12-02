#include <catch.hpp>
#include <set.hpp>

///////////////////////////////////////////////set//////////////////////////////////////////////////////////

SCENARIO("set standart init") {

	set<int> s1;
	REQUIRE(s1.find(1) == false);
	REQUIRE(s1.size() == 0);
	REQUIRE(s1.empty() == true);
}

SCENARIO("set insert") {

	set<int> s1;
	REQUIRE(s1.find(1) == false);
	s1.insert(1);
	REQUIRE(1 == s1.size());
	REQUIRE(s1.find(1) == true);

	s1.insert(1);
	REQUIRE(1 == s1.size());
	REQUIRE(s1.find(1) == true);

	REQUIRE(s1.find(5) == false);
	s1.insert(5);
	REQUIRE(s1.find(5) == true);
	REQUIRE(2 == s1.size());
}

SCENARIO("set erase") {

	set<int> s1;
	s1.insert(1);

	s1.erase(1);
	REQUIRE(s1.find(1) == false);
	REQUIRE(s1.size() == 0);

	s1.insert(1);
	s1.insert(1);
	s1.insert(1);
	s1.insert(1);
	REQUIRE(s1.find(1) == true);
	REQUIRE(1 == s1.size());

	s1.insert(2);
	s1.insert(3);
	s1.insert(6);
	REQUIRE(4 == s1.size());

	s1.erase(1);
	REQUIRE(3 == s1.size());

	s1.erase(1);
	REQUIRE(3 == s1.size());
	REQUIRE(s1.find(1) == false);
	REQUIRE(s1.find(2) == true);
	REQUIRE(s1.find(3) == true);
	REQUIRE(s1.find(6) == true);
}

SCENARIO("set clear") {

	set<int> s1;
	s1.clear();
	REQUIRE(s1.size() == 0);
	REQUIRE(s1.find(2) == false);
	REQUIRE(s1.find(3) == false);
	REQUIRE(s1.find(6) == false);
	REQUIRE(s1.empty() == true);

	s1.insert(2);
	s1.insert(3);
	s1.insert(6);
	REQUIRE(s1.size() == 3);
	REQUIRE(s1.find(2) == true);
	REQUIRE(s1.find(3) == true);
	REQUIRE(s1.find(6) == true);
	REQUIRE(s1.empty() == false);

	s1.clear();
	REQUIRE(s1.size() == 0);
	REQUIRE(s1.find(2) == false);
	REQUIRE(s1.find(3) == false);
	REQUIRE(s1.find(6) == false);
	REQUIRE(s1.empty() == true);
}

SCENARIO("set iterators") {

	set<int> s;
	REQUIRE(s.cbegin() == s.cend());
	s.insert(-1);
	s.insert(0);
	s.insert(1);

	auto it = s.cbegin();
	REQUIRE(it != s.cend());
	REQUIRE(*it == -1);
	++it;
	REQUIRE(*it == 0);
	it++;
	REQUIRE(*it == 1);
	--it;
	REQUIRE(*it == 0);
	it--;
	REQUIRE(*it == -1);
	++it;
	++it;
	REQUIRE(*it == 1);
	++it;
	REQUIRE(it == s.cend());
}

SCENARIO("set operator= and init with other") {

	set<int> s1;
	s1.insert(2);
	s1.insert(3);
	s1.insert(6);

	set<int> s2(s1);
	REQUIRE(s2.find(2) == true);
	REQUIRE(s2.find(3) == true);
	REQUIRE(s2.find(6) == true);
	REQUIRE(3 == s2.size());

	s1.clear();
	REQUIRE(s2.find(2) == true);
	REQUIRE(s2.find(3) == true);
	REQUIRE(s2.find(6) == true);
	REQUIRE(3 == s2.size());

	set<int> s3;
	s3 = s2;
	REQUIRE(s3.find(2) == true);
	REQUIRE(s3.find(3) == true);
	REQUIRE(s3.find(6) == true);
	REQUIRE(3 == s3.size());

	s2.erase(2);
	REQUIRE(s3.find(2) == true);
	REQUIRE(s3.find(3) == true);
	REQUIRE(s3.find(6) == true);
	REQUIRE(3 == s3.size());

	s3.erase(3);
	REQUIRE(s2.find(2) == false);
	REQUIRE(s2.find(3) == true);
	REQUIRE(s2.find(6) == true);
	REQUIRE(2 == s2.size());
	REQUIRE(s3.find(2) == true);
	REQUIRE(s3.find(3) == false);
	REQUIRE(s3.find(6) == true);
	REQUIRE(2 == s3.size());
}

SCENARIO("set other operators") {

	set<int> s1;
	set<int> s2;
	REQUIRE((s1 <= s2) == true);
	REQUIRE((s2 <= s1) == true);
	REQUIRE((s2 >= s1) == true);
	REQUIRE((s1 < s1) == false);
	REQUIRE((s1 < s2) == false);
	REQUIRE((s1 == s2) == true);
	s1.insert(1);
	REQUIRE((s1 <= s2) == false);
	REQUIRE((s2 <= s1) == true);
	REQUIRE((s2 >= s1) == false);
	REQUIRE((s1 < s1) == false);
	REQUIRE((s1 < s2) == false);
	REQUIRE((s1 > s2) == true);
	REQUIRE((s1 == s2) == false);
	s1.insert(2);
	REQUIRE((s1 <= s2) == false);
	REQUIRE((s2 <= s1) == true);
	REQUIRE((s2 >= s1) == false);
	REQUIRE((s1 < s1) == false);
	REQUIRE((s1 < s2) == false);
	REQUIRE((s1 > s2) == true);
	REQUIRE((s1 == s2) == false);
	s2.insert(1);
	REQUIRE((s1 <= s2) == false);
	REQUIRE((s2 <= s1) == true);
	REQUIRE((s2 >= s1) == false);
	REQUIRE((s1 < s1) == false);
	REQUIRE((s1 < s2) == false);
	REQUIRE((s1 > s2) == true);
	REQUIRE((s1 == s2) == false);
	s2.insert(2);
	REQUIRE((s1 <= s2) == true);
	REQUIRE((s2 <= s1) == true);
	REQUIRE((s2 >= s1) == true);
	REQUIRE((s1 < s1) == false);
	REQUIRE((s1 < s2) == false);
	REQUIRE((s1 == s2) == true);
	s1.insert(3);
	s2.insert(5);
	REQUIRE((s1 <= s2) == false);
	REQUIRE((s2 <= s1) == false);
	REQUIRE((s2 >= s1) == false);
	REQUIRE((s1 < s1) == false);
	REQUIRE((s1 < s2) == false);
	REQUIRE((s1 == s2) == false);
}



//////////////////////////////////////////////set///////////////////////////////////////////////////////////