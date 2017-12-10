#include"include\list\list.hpp"


template <class Type>
class Deque
{
	list<Type> _data;
public:
	Deque();
	~Deque();
	Deque(std::initializer_list<Type> list);
	Deque(Deque&& other);
	size_t size() const;
	void swap(Deque& other);
	Deque& operator=(const Deque& other);
	Type& operator[](size_t Index);
	Type&	at(size_t Index);
	Type& back() const;
	Type& front() const;
	bool empty() const;
	void insert(size_t Index, const Type &val);
	void clear();
	void push_back(const Type &val);
	void push_front(const Type &val);
	void pop_back();
	void pop_front();
	void erase(size_t Index);
};

template<class Type>
Deque<Type>::Deque()
{

}

template<class Type>
Deque<Type>::~Deque()
{
	_data.clear();
}

template<class Type>
size_t Deque<Type>::size() const
{
	return _data.size();
}

template <class Type>
Deque<Type>& Deque<Type>:: operator=(const Deque<Type>& other)
{
	_data = other._data;
}
template<class Type>
Type & Deque<Type>::operator[](size_t Index)
{
	if (Index == 0)
	{
		return _data.front();
	}
	if (Index > _data.size())
	{
		return _data.back();
	}
	Node<Type> *before = _data.begin();
	while (Index-- > 0)
		before = before->next;
	return before->data;
}
template<class Type>
Type & Deque<Type>::at(size_t Index)
{
	if (Index == 0)
	{
		return _data.front();
	}
	if (Index > _data.size())
	{
		return _data.back();
	}
	Node<Type> *before = _data.begin();
	while (Index-- > 0)
		before = before->next;
	return before->data;
}
template<class Type>
Type & Deque<Type>::back() const
{
	return _data.back();
}
template<class Type>
Type & Deque<Type>::front() const
{
	return _data.front();
}
template<class Type>
bool Deque<Type>::empty() const
{
	return _data.empty();
}
template<class Type>
void Deque<Type>::insert(size_t Index, const Type & val)
{
	_data.insert();
}
template<class Type>
void Deque<Type>::clear()
{
	_data.clear();
}
template<class Type>
void Deque<Type>::push_back(const Type & val)
{
	_data.push_back(val);
}
template<class Type>
void Deque<Type>::push_front(const Type & val)
{
	_data.push_front(val);
}
template<class Type>
void Deque<Type>::pop_back()
{
	_data.pop_back();
}
template<class Type>
void Deque<Type>::pop_front()
{
	_data.pop_front();
}
template<class Type>
void Deque<Type>::erase(size_t Index)
{
	_data.erase(Index);
}

template<class Type>
void Deque<Type>::swap(Deque & other)
{
	_data.swap(other._data);
}
template<class Type>
Deque<Type>::Deque(Deque && other)
{
	Deque<Type> other_ = other;
	while (!other_._data.empty())
	{
		Type elem = other_._data.pop_back();
		_data.push_front(elem);
	}
}
template<class Type>
Deque<Type>::Deque(std::initializer_list<Type> init_list)
{
	for (auto& val : init_list)
	{
		_data.push_back(val);
	}
}
