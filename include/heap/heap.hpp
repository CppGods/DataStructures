#include"include\deque\deque.hpp"

template <class T>
class Heap 
{
private:
	Deque<T> list_;
	void swapcp(size_t child, size_t parent);

public:
	Heap();
	Heap(const Heap& other);
	~Heap(); 
	void push(T);
	size_t getSize() const;
	bool empty() const;
	Heap& operator=(const Heap& other);
	T top() const;
	void pop();
	void swap(Heap& other);
};

template <class T>
Heap<T>::Heap() 
{

}

template <class T>
size_t Heap<T> ::getSize() const
{
	return list_.size();
}

template<class T>
bool Heap<T>::empty() const
{
	return list_.empty();
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
Heap<T>::Heap(const Heap& other)
{
	list_ = other.list_;
}

template<class T>
Heap<T>::~Heap()
{
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
void Heap<T> ::push(T value)
{
	list_.push_back(value);
	size_t child = list_.size() - 1;
	int parent;
	parent = ((child % 2 == 0)?((child / 2) - 1): (child / 2));
	while (list_[child] > list_[parent] && child >= 0 && parent >= 0)
	{
		swapcp(child, parent);
		child = parent;
		parent = ((child % 2 == 0) ? ((child / 2) - 1) : (child / 2));
	}
	
}

template <class T>
void Heap<T> ::pop() 
{
	size_t child = list_.size() - 1;
	swapcp(child, 0);
	list_.pop_back();
	size_t parent = 0;
	bool f = 1;
	while (f)
	{
		size_t left = (2 * parent + 1);
		size_t right =(2 * parent + 2);
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
			f = 0;
	}
	
}
template<class T>
T Heap<T>::top() const
{
	T value = list_.front();
	return value;
}
