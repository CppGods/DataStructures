#include <catch.hpp>
#include <list.hpp>

SCENARIO("list init") 
{
    list<int> l;
    REQUIRE(l.size() == 0);
    REQUIRE(l.empty());
    list<int> l1{1,2,3,4};
    REQUIRE(l1.front()==1);
    REQUIRE(l1.begin()->next->data == 2);
    REQUIRE(l1.end()->prev->data == 3);
    REQUIRE(l1.back() == 4);
}

SCENARIO("list push, pop") 
{
    list<int> b;
	REQUIRE(b.size() == 0);
	b.push_front(4);
	REQUIRE(b.front() == 4);
	REQUIRE(b.size() == 1);
	b.push_back(5);
	REQUIRE(b.size() == 2);
	REQUIRE(b.back() == 5);
	b.push_back(6);
	REQUIRE(b.size() == 3);
	REQUIRE(b.back() == 6);
	b.push_front(7);
	std::cout << (b.size() == 4);
	std::cout << (b.front() == 7);
	list<int> a{ 3,6,7,4,8 };
	REQUIRE(a.size() == 5);
	REQUIRE(a.back() == 8);
	a.pop_back();
	REQUIRE(a.size() == 4);
	REQUIRE(a.back() == 4);
	a.pop_front();
	REQUIRE(a.size() == 3);
	REQUIRE(a.front() == 6);
	a.pop_back();
	REQUIRE(a.size() == 2);
	REQUIRE(a.back() == 7);
}


SCENARIO("list operator=, operator==") 
{
	list<int> a{ 3,6,7,4,8 };
	list<int> b;
	b = a;
	REQUIRE(b == a);
	a.pop_back();
	REQUIRE(!(b == a));
	REQUIRE(b.size() == 5);
	REQUIRE(b.back() == 8);
	b.pop_back();
	REQUIRE(b.back() == 4);
	b.pop_back();
	REQUIRE(b.back() == 7);
	b.pop_back();
	REQUIRE(b.back() == 6);
	b.pop_back();
	REQUIRE(b.back() == 3);
}
