#include <catch.hpp>
#include <vector.hpp>

////////////////////////////////////////////////VECTOR////////////////////////////////////////////////////

SCENARIO("vector init") {

	vector<int> v1;
	REQUIRE(v1.size() == 0);
	REQUIRE(v1.capacity() == 0);
	REQUIRE(v1.empty() == true);
}

SCENARIO("vector push_back") {

	vector<int> v1;
	v1.push_back(888);
	REQUIRE(v1.size() == 1);
	REQUIRE(v1.capacity() == 1);
	REQUIRE(v1.empty() == false);
	v1.push_back(999);
	REQUIRE(v1.size() == 2);
	REQUIRE(v1.capacity() == 2);
	REQUIRE(v1.empty() == false);
	v1.push_back(3);
	REQUIRE(v1.size() == 3);
	REQUIRE(v1.capacity() == 4);
}

SCENARIO("vector at, back, front, data, operator[]") {

	vector<int> v1;
	v1.push_back(888);
	v1.push_back(999);
	int tmp = v1.at(0);
	REQUIRE(tmp == 888);
	REQUIRE(tmp == v1.front());
	REQUIRE(tmp == *v1.data());
	REQUIRE(tmp == *v1.data());
	tmp = v1.at(1);
	REQUIRE(tmp == 999);
	REQUIRE(tmp == v1.back());
	REQUIRE(tmp == *(v1.data() + 1));
	REQUIRE(tmp == *(v1.data() + 1));
	REQUIRE(v1[0] == 888);
	REQUIRE(v1[1] == 999);
}

SCENARIO("vector pop_back") {

	vector<int> v1;
	v1.push_back(888);
	REQUIRE(v1.size() == 1);
	v1.pop_back();
	REQUIRE(v1.size() == 0);
	REQUIRE(v1.capacity() == 1);
	REQUIRE(v1.empty() == true);
	v1.push_back(2000);
	v1.push_back(2001);
	REQUIRE(v1.size() == 2);
	REQUIRE(v1.capacity() == 2);
	REQUIRE(v1.empty() == false);
}

SCENARIO("vector operator= and init with other") {

	vector<int> v2;
	v2.push_back(888);
	v2.push_back(999);
	vector<int> v1(v2);
	int tmp = v1.at(0);
	REQUIRE(tmp == 888);
	REQUIRE(tmp == v1.front());
	REQUIRE(tmp == *v1.data());
	REQUIRE(tmp == *v1.data());
	tmp = v1.at(1);
	REQUIRE(tmp == 999);
	REQUIRE(tmp == v1.back());
	REQUIRE(tmp == *(v1.data() + 1));
	REQUIRE(tmp == *(v1.data() + 1));
	REQUIRE(v1[0] == 888);
	REQUIRE(v1[1] == 999);

	v2.pop_back();
	tmp = v1.at(0);
	REQUIRE(tmp == 888);
	REQUIRE(tmp == v1.front());
	REQUIRE(tmp == *v1.data());
	REQUIRE(tmp == *v1.data());
	tmp = v1.at(1);
	REQUIRE(tmp == 999);
	REQUIRE(tmp == v1.back());
	REQUIRE(tmp == *(v1.data() + 1));
	REQUIRE(tmp == *(v1.data() + 1));
	REQUIRE(v1[0] == 888);
	REQUIRE(v1[1] == 999);

	vector<int> v3;
	v3 = v1;
	tmp = v3.at(0);
	REQUIRE(tmp == 888);
	REQUIRE(tmp == v3.front());
	REQUIRE(tmp == *v3.data());
	REQUIRE(tmp == *v3.data());
	tmp = v3.at(1);
	REQUIRE(tmp == 999);
	REQUIRE(tmp == v3.back());
	REQUIRE(tmp == *(v3.data() + 1));
	REQUIRE(tmp == *(v3.data() + 1));
	REQUIRE(v3[0] == 888);
	REQUIRE(v3[1] == 999);

	v1.pop_back();
	tmp = v3.at(0);
	REQUIRE(tmp == 888);
	REQUIRE(tmp == v3.front());
	REQUIRE(tmp == *v3.data());
	REQUIRE(tmp == *v3.data());
	tmp = v3.at(1);
	REQUIRE(tmp == 999);
	REQUIRE(tmp == v3.back());
	REQUIRE(tmp == *(v3.data() + 1));
	REQUIRE(tmp == *(v3.data() + 1));
	REQUIRE(v3[0] == 888);
	REQUIRE(v3[1] == 999);

	v3.pop_back();
	v3.pop_back();
	tmp = v1.at(0);
	REQUIRE(tmp == 888);
	REQUIRE(tmp == v1.front());
	REQUIRE(tmp == *v1.data());
	REQUIRE(tmp == *v1.data());
	REQUIRE(v1[0] == 888);
}

SCENARIO("vector clear") {

	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.clear();
	REQUIRE(v1.capacity() == 0);
	REQUIRE(v1.size() == 0);
	v1.push_back(2);
	v1.push_back(1);
	REQUIRE(v1.capacity() == 2);
	REQUIRE(v1.size() == 2);
	v1.push_back(3);
	REQUIRE(v1.capacity() == 4);
	REQUIRE(v1.size() == 3);
	v1.clear();
	REQUIRE(v1.capacity() == 0);
	REQUIRE(v1.size() == 0);
}

SCENARIO("vector reserve") {

	vector<int> v1;
	v1.reserve(4);
	REQUIRE(v1.size() == 0);
	REQUIRE(v1.capacity() == 4);
	v1.push_back(1);
	v1.push_back(1);
	v1.push_back(1);
	v1.push_back(1);
	REQUIRE(v1.size() == 4);
	REQUIRE(v1.capacity() == 4);
	v1.push_back(1);
	REQUIRE(v1.size() == 5);
	REQUIRE(v1.capacity() == 8);
	v1.reserve(3);
	REQUIRE(v1.size() == 5);
	REQUIRE(v1.capacity() == 8);
}

SCENARIO("vector assign") {

	vector<int> v1;
	v1.assign(3, 5);
	REQUIRE(v1.size() == 3);
	REQUIRE(v1.capacity() == 4);
	REQUIRE(v1[0] == 5);
	REQUIRE(v1[1] == 5);
	REQUIRE(v1[2] == 5);
	v1.push_back(1);
	REQUIRE(v1.size() == 4);
	REQUIRE(v1.capacity() == 4);
	REQUIRE(v1[3] == 1);
	v1.assign(17, 0);
	REQUIRE(v1.size() == 17);
	REQUIRE(v1.capacity() == 32);
	REQUIRE(v1.at(0) == 0);
	REQUIRE(v1.at(8) == 0);
	REQUIRE(v1.at(16) == 0);
}

SCENARIO("vector resize") {

	vector<int> v1;
	v1.resize(9);
	REQUIRE(v1.size() == 0);
	REQUIRE(v1.capacity() == 16);
	v1.assign(15, 1);
	REQUIRE(v1.size() == 15);
	REQUIRE(v1.capacity() == 16);
	REQUIRE(v1[6] == 1);
	v1.resize(9);
	REQUIRE(v1.size() == 15);
	REQUIRE(v1.capacity() == 16);
	REQUIRE(v1[6] == 1);
	v1.resize(5);
	REQUIRE(v1.size() == 8);
	REQUIRE(v1.capacity() == 8);
	REQUIRE(v1[4] == 1);
}

SCENARIO("vector shrink_to_fit") {

	vector<int> v1;
	v1.resize(16);
	REQUIRE(v1.size() == 0);
	REQUIRE(v1.capacity() == 16);
	v1.shrink_to_fit();
	REQUIRE(v1.size() == 0);
	REQUIRE(v1.size() == 0);
	v1.assign(10, 8);
	REQUIRE(v1.size() == 10);
	REQUIRE(v1.capacity() == 16);
	v1.pop_back();
	v1.pop_back();
	v1.shrink_to_fit();
	REQUIRE(v1.size() == 8);
	REQUIRE(v1.capacity() == 8);


}

////////////////////////////////////////////////VECTOR////////////////////////////////////////////////////
