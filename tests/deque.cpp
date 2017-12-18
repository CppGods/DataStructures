#include "catch.hpp"
#include <deque.hpp>

SCENARIO("deque init")
{
  Deque<int> m;
	std::cout << (m.size() == 0);
}
SCENARIO("deque pop_back, push_back")	
{
	Deque<int> m = { 3, 4, 5, 6, 7 };
	REQUIRE (m.size() == 5);
	int s = m.back();
	REQUIRE(s == 7);
	m.pop_back();
	s = m.back();
	REQUIRE(s == 6);
	REQUIRE(m.size() == 4);
  m.push_back(9);
	m.pop_back();
	s = m.back();
	REQUIRE(s == 9);
	REQUIRE(m.size() == 5); 
}
SCENARIO("deque init list") 
{
    Deque<int> m={3, 4};
    REQUIRE(m.size()==2);
    int s = m.back();
	  REQUIRE(s == 4);
	  m.pop_back();
    REQUIRE(m.size() == 1);
    s = m.back();
    REQUIRE(s == 3);
    m.pop_back();
    REQUIRE(m.size() == 0);
}

	
