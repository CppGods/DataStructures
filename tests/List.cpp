#include <catch.hpp>
#include <list.hpp>

SCENARIO("list init") 
{
    list<int> l;
    REQUIRE(l.size() == 0);
    REQUIRE(l.empty());
    list<int> l1{1,2,3,4};
    REQUIRE(l.front()==1);
    REQUIRE(l.front()->next==2);
    REQUIRE(l.back()==4);
    REQUIRE(l.back()->prev==3);
}

