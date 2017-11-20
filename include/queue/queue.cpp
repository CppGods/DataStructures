#include <iostream>
#include "include\forward_list\forward_list.hpp"

template <class Ty>
class Queue
{
	forward_list<Ty> _items;
public:
	Queue();
	void Enqueue(const Ty& value);
	Ty Dequeue();
	size_t count();
	void show();
	void swap(Queue& other);
	Queue& operator=(const Queue& other);
};

template <class Ty>
Queue<Ty>& Queue<Ty>:: operator=(const Queue<Ty>& other)
{
	_items = other._items;
}

template <class Ty>
Queue<Ty>::Queue() {}


template <class Ty>
void Queue<Ty>:: Enqueue(const Ty& value)
	{
		_items.emplace_front(value);
	}

template <class Ty>
Ty Queue<Ty>::Dequeue()
	{
		return _items.pop_back();
	}

template <class Ty> 
size_t Queue<Ty>::count()
{
	return _items.count();
}

template <class Ty>
void Queue<Ty>::show()
{
	_items.Show();
}

template <class Ty>
void Queue<Ty>::swap(Queue& other)
{
	_items.swap(other._items);
}
