#include <catch.hpp>
#include <queue.hpp>


SCENARIO("init1") 
{
   	queue <int> m;
    REQUIRE(m.count()==0);
}
SCENARIO("init list1") 
{
    queue <int> m={3, 4};
    REQUIRE(m.count()==2);
    int s = m.dequeue();
    REQUIRE(m.count() == 1);
    REQUIRE(s == 3);
    s = m.dequeue();
    REQUIRE(s == 4);
    REQUIRE(m.count() == 0);
}
SCENARIO("pop1") 
{
    queue <int> m={3, 4};
    REQUIRE(m.count()==2);
    int s = m.dequeue();
    REQUIRE(m.count() == 1);
    REQUIRE(s == 3);
}

SCENARIO("push1") 
{
    queue <int> m={3, 4};
    REQUIRE(m.count()==2);
    m.enqueue(5);
    REQUIRE(m.count() == 3);
    m.dequeue();
    m.dequeue();
    int s = m.dequeue();
    REQUIRE(s == 5);
}
 SCENARIO("move1") 
{
   queue <int> l={3, 4};
   queue <int> m =std:: move(l);
   REQUIRE(m.count()==2);
   int s = m.dequeue();
   REQUIRE(m.count() == 1);
   REQUIRE(s == 3);
   s = m.dequeue();
   REQUIRE(s == 4);
   REQUIRE(m.count() == 0);
 }
SCENARIO("copy1") 
{
    queue <int> l={3, 4};
   queue <int> m =l;
   REQUIRE(m.count()==2);
   int s = m.dequeue();
   REQUIRE(m.count() == 1);
   REQUIRE(s == 3);
   s = m.dequeue();
   REQUIRE(s == 4);
   REQUIRE(m.count() == 0);
   
}
