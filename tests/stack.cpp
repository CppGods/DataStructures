#include <stack.hpp>
#include <catch.hpp>
SCENARIO("ini")
{
	stack<int> Stack;
	REQUIRE(Stack.size() == 0);
	REQUIRE(Stack.empty());
}
	
SCENARIO("push")
{
	stack<int> Stack;
	Stack.push(5);
	Stack.push(7);
	Stack.push(12);
	int sp =Stack.top();
	Stack.pop();
	bool d=(sp==12);
	REQUIRE(Stack.size() == 2);
	REQUIRE(d);
}

SCENARIO("count and size")
{
	stack<int> Stack;
	Stack.push(5);
	Stack.push(7);
	REQUIRE(Stack.size() == 2);
}

SCENARIO("pop")
{
	stack<int> Stack;
	Stack.push(5);
	Stack.push(7);
	REQUIRE(Stack.size() == 2);
}
