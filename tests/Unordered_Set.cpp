#include <catch.hpp>
#include <unordered_set.hpp>

SCENARIO("Unordered_Set standart init") {

	Unordered_Set<int> s1;
	REQUIRE(s1.find(1) == false);
	REQUIRE(s1.size() == 0);
	REQUIRE(s1.empty() == true);
}

SCENARIO("Unordered_Set insert") {

	Unordered_Set<int> s1;
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

SCENARIO("Unordered_Set erase") {

	Unordered_Set<int> s1;
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

SCENARIO("Unordered_Set clear") {

	Unordered_Set<int> s1;
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

SCENARIO("Unordered_Set iterators") {

	Unordered_Set<int> s;
	REQUIRE(s.cbegin() == s.cend());
	s.insert(-1);
	s.insert(0);
	s.insert(1);

	auto it = s.cbegin();
	REQUIRE(it != s.cend());
	auto tmp1 = *it;
	REQUIRE(((tmp1 == 0) || (tmp1 == -1) || tmp1 == 1));
	++it;
	REQUIRE(*it != tmp1);
	auto tmp2 = *it;
	REQUIRE(((tmp2 == 0) || (tmp2 == -1) || tmp2 == 1));
	it++;
	REQUIRE(*it != tmp2);
	REQUIRE(*it != tmp1);
	auto tmp3 = *it;
	REQUIRE(((tmp3 == 0) || (tmp3 == -1) || tmp3 == 1));
	--it;
	REQUIRE(*it == tmp2);
	it--;
	REQUIRE(*it == tmp1);
	++it;
	++it;
	REQUIRE(*it == tmp3);
	++it;
	REQUIRE(it == s.cend());
}

SCENARIO("Unordered_Set operator= and init with other") {

	Unordered_Set<int> s1;
	s1.insert(2);
	s1.insert(3);
	s1.insert(6);

	Unordered_Set<int> s2(s1);
	REQUIRE(s2.find(2) == true);
	REQUIRE(s2.find(3) == true);
	REQUIRE(s2.find(6) == true);
	REQUIRE(3 == s2.size());

	s1.clear();
	REQUIRE(s2.find(2) == true);
	REQUIRE(s2.find(3) == true);
	REQUIRE(s2.find(6) == true);
	REQUIRE(3 == s2.size());

	Unordered_Set<int> s3;
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

SCENARIO("Unordered_Set other operators") {

	Unordered_Set<int> s1;
	Unordered_Set<int> s2;
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

	Unordered_Set<int> s1_big;
	Unordered_Set<int> s2_big;

	for (unsigned i = 0; i < 1000; ++i) {
		s1_big.insert(i);
	}
	for (unsigned i = 1000; i > 0; --i) {
		s2_big.insert(i);
	}
	REQUIRE((s1_big == s2_big) == false);
	REQUIRE((s1_big >= s2_big) == false);
	REQUIRE((s1_big <= s2_big) == false);
	REQUIRE((s1_big < s2_big) == false);
	REQUIRE((s1_big > s2_big) == false);

	s1_big.erase(0);
	s2_big.erase(1000);
	REQUIRE((s1_big == s2_big) == true);


}

