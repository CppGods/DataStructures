#include"include\deque\deque.hpp"

template <class T>
class Heap 
{
private:
	Deque<T> list_;
	void Up();
	void Down();
	void swapcp(size_t child, size_t parent);
	size_t getLeftChild(size_t parent);
	size_t getRightChild(size_t parent);
	size_t getParent(size_t child);
public:
	Heap();
	void push(T);
	size_t getSize();
	Heap& operator=(const Heap& other);
	T top();
	void pop();
	void swap(Heap& other);
	Heap(Heap& other);
};

template <class T>
Heap<T>::Heap() 
{

}

template <class T>
size_t Heap<T> ::getSize()
{
	return list_.size();
}

template<class T>
Heap<T>& Heap<T>::operator=(const Heap<T> & other)
{
	list_ = other.list_;
}



template<class T>
void Heap<T>::swap(Heap& other)
{
	list_.swap(other.list_);
}

template <class T>
Heap<T>::Heap(Heap& other)
{
	list_ = other.list_;
}

template <class T>
void Heap<T>::swapcp(size_t child, size_t parent)
{
	T temp;
	temp = list_[child];
	list_[child] = list_[parent];
	list_[parent] = temp;
}

template <class T>
size_t Heap<T> ::getParent(size_t child)
{
	if (child % 2 == 0)
		return (child / 2) - 1;
	else
		return child / 2;

}

template <class T>
size_t Heap<T> ::getLeftChild(size_t parent)
{
	return (2 * parent + 1);
}

template <class T>
size_t Heap<T> ::getRightChild(size_t parent)
{
	return (2 * parent + 2);
}

template <class T>
void Heap<T> ::push(T value)
{
	list_.push_back(value);
	Up();
}

template <class T>
void Heap <T>::Up() 
{
	size_t child = list_.size() - 1;
	int parent;
	parent = getParent(child);
	while (list_[child] > list_[parent] && child >= 0 && parent >= 0) 
	{
		swapcp(child, parent);
		child = parent;
		parent = getParent(child);
	}

}


template <class T>
void Heap<T> ::pop() 
{
	size_t child = list_.size() - 1;
	swapcp(child, 0);
	list_.pop_back();
	Down();
	
}

template<class T>
T Heap<T>::top()
{
	T value = list_.front();
	return value;
}


template <class T>
void Heap<T> ::Down() 
{
	size_t parent = 0;
	bool f=1;
	while (f) 
	{
		size_t left = getLeftChild(parent);
		size_t right = getRightChild(parent);
		size_t length = list_.size();
		size_t largest = parent;

		if (left < length && list_[left] > list_[largest])
			largest = left;

		if (right < length && list_[right] > list_[largest])
			largest = right;

		if (largest != parent)
		{
			swapcp(largest, parent);
			parent = largest;
		}
		else
			f=0;
	}

}
