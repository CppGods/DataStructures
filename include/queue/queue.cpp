#include <iostream>
#include "include\forward_list\forward_list.hpp"


template <class Ty>
class queue
{
	forward_list<Ty> _items;
public:
	queue();
	~queue() {};
	void enqueue(const Ty& value);
	Ty dequeue();
	size_t count();
	void show()
	{
		_items.show();
	};
	void swap(queue& other);
	queue& operator=(const queue& other);
	queue& operator=(queue&& other) = default;
	queue (const queue& other) = default;
	queue(queue&& other);
	queue(std::initializer_list<Ty> list);
	
};


template <class Ty>
queue<Ty>::queue(queue&& other)
{
	queue other_ = other;
	while (!other_._items.empty())
	{
		
		Ty _i = other_._items.pop_back();
		_items.emplace_back(_i);
	}
	
}

template <class Ty>
queue<Ty>& queue<Ty>:: operator=(const queue<Ty>& other)
{
	_items = other._items;
	return *this;
}

template <class Ty>
queue<Ty>::queue() {}

template <class Ty>
queue<Ty>::queue(std::initializer_list<Ty> list)
{
	for (auto& item : list)
	{
		enqueue(item);
	}
}


template <class Ty>
void queue<Ty>::enqueue(const Ty& value)
{
	_items.push_front(value);
}

template <class Ty>
Ty queue<Ty>::dequeue()
{
	return _items.pop_back();
}

template <class Ty>
size_t queue<Ty>::count()
{
	return _items.count();
}

template <class Ty>
void queue<Ty>::swap(queue& other)
{
	_items.swap(other._items);
}
