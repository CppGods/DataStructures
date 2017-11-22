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

////////////////////////////////////////////////bst_tree////////////////////////////////////////////////////

SCENARIO("bst_tree standart init") {
	bst_tree<int> tr1;
	REQUIRE(tr1.is_node(0) == false);
	REQUIRE(tr1.size() == 0);
	bst_tree<double> tr2;
	REQUIRE(tr2.is_node(1) == false);
	REQUIRE(tr2.size() == 0);
}

SCENARIO("bst_tree insert") {

	bst_tree<int> tr1;
	REQUIRE(tr1.is_node(1) == false);
	tr1.insert(1);
	REQUIRE(1 == tr1.size());
	REQUIRE(tr1.is_node(1) == true);

	REQUIRE(tr1.is_node(5) == false);
	tr1.insert(5);
	REQUIRE(tr1.is_node(5) == true);
	REQUIRE(2 == tr1.size());

	REQUIRE(tr1.is_node(-1) == false);
	tr1.insert(-1);
	REQUIRE(tr1.is_node(-1) == true);
	REQUIRE(3 == tr1.size());

	REQUIRE(tr1.is_node(-2) == false);
	tr1.insert(-2);
	REQUIRE(tr1.is_node(-2) == true);
	REQUIRE(4 == tr1.size());

	REQUIRE(tr1.is_node(0) == false);
	tr1.insert(0);
	REQUIRE(tr1.is_node(0) == true);
	REQUIRE(5 == tr1.size());

	REQUIRE(tr1.is_node(6) == false);
	tr1.insert(6);
	REQUIRE(tr1.is_node(6) == true);
	REQUIRE(6 == tr1.size());

	REQUIRE(tr1.is_node(4) == false);
	tr1.insert(4);
	REQUIRE(tr1.is_node(4) == true);
	REQUIRE(7 == tr1.size());

	REQUIRE(tr1.is_node(8) == false);
	tr1.insert(8);
	REQUIRE(tr1.is_node(8) == true);
	REQUIRE(8 == tr1.size());

	REQUIRE(tr1.is_node(-9) == false);
	tr1.insert(-9);
	REQUIRE(tr1.is_node(-9) == true);
	REQUIRE(9 == tr1.size());

}

SCENARIO("bst_tree del") {

	bst_tree<int> tr1;
	tr1.insert(1);
	tr1.erase(1);
	REQUIRE(tr1.is_node(1) == false);
	REQUIRE(0 == tr1.size());

	tr1.insert(1);
	tr1.insert(5);
	tr1.insert(-1);
	tr1.insert(-2);
	tr1.insert(0);
	tr1.insert(6);
	tr1.insert(4);
	tr1.insert(8);
	tr1.insert(-9);

	REQUIRE(9 == tr1.size());
	tr1.erase(10);
	REQUIRE(9 == tr1.size());
	tr1.erase(1);
	REQUIRE(8 == tr1.size());
	tr1.erase(-9);
	REQUIRE(7 == tr1.size());
	tr1.erase(5);
	REQUIRE(6 == tr1.size());
	tr1.erase(4);
	REQUIRE(5 == tr1.size());
	tr1.erase(-1);
	REQUIRE(4 == tr1.size());
	tr1.erase(8);
	REQUIRE(3 == tr1.size());
	tr1.erase(0);
	REQUIRE(2 == tr1.size());
	tr1.erase(6);
	REQUIRE(1 == tr1.size());
	tr1.erase(-2);
	REQUIRE(0 == tr1.size());

	tr1.erase(-2);
	REQUIRE(0 == tr1.size());

	bst_tree<double> tr2;

	tr2.insert(16.0);
	tr2.insert(-28.0);
	tr2.insert(11.55);
	tr2.insert(19.0);
	tr2.insert(145.444);
	tr2.insert(17.88);
	tr2.insert(17.88);
	tr2.insert(6.0);
	tr2.insert(0.0);

	REQUIRE(9 == tr2.size());

	tr2.erase(16.0);
	tr2.erase(-28.0);
	tr2.erase(11.55);
	tr2.erase(19.0);
	tr2.erase(145.444);
	tr2.erase(17.88);
	tr2.erase(17.88);
	tr2.erase(6.0);
	tr2.erase(0.0);

	REQUIRE(0 == tr2.size());
}

SCENARIO("bst_tree operator= and init with other") {

	bst_tree<int> tr1;
	tr1.insert(2);
	tr1.insert(3);
	tr1.insert(6);

	bst_tree<int> tr2(tr1);
	REQUIRE(tr2.is_node(2) == true);
	REQUIRE(tr2.is_node(3) == true);
	REQUIRE(tr2.is_node(6) == true);
	REQUIRE(3 == tr2.size());

	tr1.erase(2);
	REQUIRE(tr2.is_node(2) == true);
	REQUIRE(tr2.is_node(3) == true);
	REQUIRE(tr2.is_node(6) == true);
	REQUIRE(3 == tr2.size());

	bst_tree<int> tr3;
	tr3 = tr2;
	REQUIRE(tr3.is_node(2) == true);
	REQUIRE(tr3.is_node(3) == true);
	REQUIRE(tr3.is_node(6) == true);
	REQUIRE(tr3.size() == 3);

	tr2.erase(3);
	REQUIRE(tr3.is_node(2) == true);
	REQUIRE(tr3.is_node(3) == true);
	REQUIRE(tr3.is_node(6) == true);
	REQUIRE(3 == tr3.size());

	tr3 = tr2;
	REQUIRE(tr3.is_node(2) == true);
	REQUIRE(tr3.is_node(3) == false);
	REQUIRE(tr3.is_node(6) == true);
	REQUIRE(2 == tr3.size());
}

////////////////////////////////////////////////bst_tree////////////////////////////////////////////////////

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

SCENARIO("set vector of keys") {

	set<double> s1;
	std::vector<double> v1 = s1.vector_keys(10);
	REQUIRE(v1.empty() == true);

	s1.insert(1.0);
	v1 = s1.vector_keys(1);
	REQUIRE(v1.empty() == false);
	REQUIRE(v1[0] == 1.0);
	REQUIRE(v1.size() == 1);

	s1.insert(-1.0);
	s1.insert(2);
	v1 = s1.vector_keys(3);
	std::vector<double> v2 = s1.vector_keys(2);
	REQUIRE(v1.empty() == false);
	REQUIRE(v1[0] == -1.0);
	REQUIRE(v1[1] == 1.0);
	REQUIRE(v1[2] == 2.0);
	REQUIRE(v1.size() == 3);
	REQUIRE(v2.empty() == false);
	REQUIRE(v2[0] == -1.0);
	REQUIRE(v2[1] == 1.0);
	REQUIRE(v2.size() == 2);
}

//////////////////////////////////////////////set///////////////////////////////////////////////////////////