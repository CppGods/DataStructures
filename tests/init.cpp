#include<catch.hpp>
#include<vector.hpp>
#include<bst_tree.hpp>

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
}

SCENARIO("vector clear") {

	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.clear();
	REQUIRE(v1.capacity() == 2);
	REQUIRE(v1.size() == 0);
	v1.push_back(2);
	v1.push_back(1);
	REQUIRE(v1.capacity() == 2);
	REQUIRE(v1.size() == 2);
	v1.push_back(3);
	REQUIRE(v1.capacity() == 4);
	REQUIRE(v1.size() == 3);
	v1.clear();
	REQUIRE(v1.capacity() == 4);
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

////////////////////////////////////////////////bst_tree////////////////////////////////////////////////////

SCENARIO("bst_tree standart init") {
	bst_tree<int> tr1;
	REQUIRE(tr1.is_node(0) == nullptr);
	bst_tree<int> tr2;
	REQUIRE(tr2.is_node(1) == nullptr);
}

SCENARIO("bst_tree add") {

	bst_tree<int> tr1;
	unsigned count1 = tr1.size();
	REQUIRE(tr1.is_node(1) == nullptr);
	tr1.insert(1);
	REQUIRE(count1 + 1 == tr1.size());
	REQUIRE(tr1.is_node(1) != nullptr);
	REQUIRE(tr1.is_node(5) == nullptr);
	tr1.insert(5);
	REQUIRE(tr1.is_node(5) != nullptr);
	REQUIRE(tr1.size() == 2);
}

SCENARIO("bst_tree del") {

	bst_tree<int> tr1;
	unsigned count1 = tr1.size();
	REQUIRE(tr1.is_node(1) == nullptr);
	tr1.insert(1);
	REQUIRE(count1 + 1 == tr1.size());
	REQUIRE(tr1.is_node(1) != nullptr);
	tr1.pop_all_with(1);
	REQUIRE(tr1.is_node(1) == nullptr);
	REQUIRE(tr1.size() == 0);

	tr1.insert(1);
	tr1.insert(1);
	tr1.insert(1);
	tr1.insert(1);
	REQUIRE(tr1.is_node(1) != nullptr);
	REQUIRE(tr1.size() == 4);

	tr1.insert(2);
	tr1.insert(3);
	tr1.insert(6);
	REQUIRE(tr1.size() == 7);

	tr1.pop_all_with(1);
	REQUIRE(tr1.size() == 3);
	REQUIRE(tr1.is_node(1) == nullptr);
	REQUIRE(tr1.is_node(2) != nullptr);
	REQUIRE(tr1.is_node(3) != nullptr);
	REQUIRE(tr1.is_node(6) != nullptr);

	tr1.clear();
	REQUIRE(tr1.size() == 0);
	REQUIRE(tr1.is_node(2) == nullptr);
	REQUIRE(tr1.is_node(3) == nullptr);
	REQUIRE(tr1.is_node(6) == nullptr);
}

SCENARIO("bst_tree operator= and init with other") {

	bst_tree<int> tr1;
	tr1.insert(2);
	tr1.insert(3);
	tr1.insert(6);

	bst_tree<int> tr2(tr1);
	REQUIRE(tr2.is_node(2) != nullptr);
	REQUIRE(tr2.is_node(3) != nullptr);
	REQUIRE(tr2.is_node(6) != nullptr);
	REQUIRE(tr2.size() == 3);

	bst_tree<int> tr3;
	tr3 = tr2;
	REQUIRE(tr3.is_node(2) != nullptr);
	REQUIRE(tr3.is_node(3) != nullptr);
	REQUIRE(tr3.is_node(6) != nullptr);
	REQUIRE(tr3.size() == 3);
}

////////////////////////////////////////////////bst_tree////////////////////////////////////////////////////

///////////////////////////////////////////////set//////////////////////////////////////////////////////////

SCENARIO("set standart init") {
	set<int> s1;
	REQUIRE(s1.find(1) == false);
	REQUIRE(s1.size() == 0);
	REQUIRE(s1.empty() == true);
}

SCENARIO("set add") {

	set<int> s1;
	REQUIRE(s1.find(1) == false);
	s1.insert(1);
	REQUIRE(1 == s1.size());
	REQUIRE(s1.find(1) != false);
	REQUIRE(s1.find(5) == false);
	s1.insert(5);
	REQUIRE(s1.find(5) != false);
	REQUIRE(s1.size() == 2);
}

SCENARIO("set del") {

	set<int> s1;
	REQUIRE(s1.find(1) == false);
	s1.insert(1);
	REQUIRE(1 == s1.size());
	REQUIRE(s1.find(1) != false);
	s1.erase(1);
	REQUIRE(s1.find(1) == false);
	REQUIRE(s1.size() == 0);

	s1.insert(1);
	s1.insert(1);
	s1.insert(1);
	s1.insert(1);
	REQUIRE(s1.find(1) != false);
	REQUIRE(s1.size() == 1);

	s1.insert(2);
	s1.insert(3);
	s1.insert(6);
	REQUIRE(s1.size() == 4);

	s1.erase(1);
	REQUIRE(s1.size() == 3);
	s1.erase(1);
	REQUIRE(s1.size() == 3);
	REQUIRE(s1.find(1) == false);
	REQUIRE(s1.find(2) != false);
	REQUIRE(s1.find(3) != false);
	REQUIRE(s1.find(6) != false);

	s1.clear();
	REQUIRE(s1.size() == 0);
	REQUIRE(s1.find(2) == false);
	REQUIRE(s1.find(3) == false);
	REQUIRE(s1.find(6) == false);
}

SCENARIO("set operator= and init with other") {

	set<int> s1;
	s1.insert(2);
	s1.insert(3);
	s1.insert(6);

	set<int> s2(s1);
	REQUIRE(s2.find(2) != false);
	REQUIRE(s2.find(3) != false);
	REQUIRE(s2.find(6) != false);
	REQUIRE(s2.size() == 3);

	set<int> s3;
	s3 = s2;
	REQUIRE(s3.find(2) != false);
	REQUIRE(s3.find(3) != false);
	REQUIRE(s3.find(6) != false);
	REQUIRE(s3.size() == 3);
}

SCENARIO("other operators") {

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