#include <iostream>

template <class T>
struct Node {
	Node()
	{
		prev = nullptr;
		next = nullptr;
	}
	Node(Node *next_, const T &data_) : prev(next_->prev), next(next_), data(data_)
	{
		prev->next = next->prev = this;
	}
	Node(const T& t) : data(t), next( nullptr ), prev( nullptr ) {};

	Node *prev, *next;
	T data;
};
template <class Ty>
class list
{
private:
	Node<Ty> *head, *tail;
	size_t count_;
	
public:
	list();
	list(const list& other);
	~list();
	list& operator=(const list& other);
	bool empty() const;
	size_t size() const;
	Ty& back() const;
	Ty& front() const;
	void insert(size_t Index, const Ty &val);
	void push_back(const Ty &val);
	void push_front(const Ty &val);
	void pop_back();
	void pop_front();
	void swap(list& other);
	void clear();
	void erase(size_t Index);
	Node<Ty>* begin();
	Node<Ty>* end();
};



template <class Ty>
list<Ty>::list()
{
	count_ = 0;
	head = nullptr;
	tail = nullptr;
}
template <class Ty>
list<Ty>::~list()
{
	clear();
}

template <class Ty>
list<Ty>::list(const list& other)
{
	head = tail = nullptr;
	count_ = 0;
	Node<Ty> *temp = other.head;
	while (temp != nullptr)
	{
		this->push_back(temp->data);
		temp = temp->next;
	}
	count_ = other.count_;
}

template <class Ty>
list<Ty>& list<Ty>:: operator=(const list& other)
{
	if (this != &other)
	{
		list{ other }.swap(*this);
	}
	return *this;
}

template <class Ty>
void list<Ty>::swap(list& other)
{
	std::swap(count_, other.count_);
	std::swap(head, other.head);
	std::swap(tail, other.tail);
}
template <class Ty>
Ty& list<Ty>::back() const
{
	return tail->data;
}
template <class Ty>
Ty& list<Ty>::front() const
{
	return head->data;
}

template <class Ty>
void list<Ty>::clear()
{
	while (head)
	{
		tail = head->next;
		delete head;
		head = tail;
	}
	count_ = 0;
}

template <class Ty>
void list<Ty>::push_front(const Ty &val)
{
	Node<Ty> *tmp = new Node<Ty>;
	tmp->data = val;
	if (count_ != 0)
	{
		tmp->next = head;
		head->prev = tmp;
		head = tmp;
	}
	else
	{
		head = tail = tmp;
	}
	count_++;
}
template <class Ty>
void list<Ty>::push_back(const Ty &val)
{
	Node<Ty> *tmp = new Node<Ty>;
	tmp->data = val;
	if (count_ != 0)
	{
		tail->next = tmp;
		tmp->prev = tail;
		tail = tmp;
	}
	else
	{
		head = tail = tmp;
	}
	count_++;
}

template <class Ty>
void list<Ty>::insert(size_t Index, const Ty &val)
{
	if (Index == 0)
	{
	push_front(val);
	}
	else
		if (Index > count_)
		{
			push_back(val);
		}
		else
		{
			Node<Ty> *before = head;
			while (Index-- > 0)
				before = before->next;
			Node<Ty> *tmp = new Node<Ty>;
			tmp->data = val;
			tmp->prev = before->prev;
			before->prev->next = tmp;
			before->prev = tmp;
			tmp->next = before;
			count_++;
		}
}
template<class Ty>
void list<Ty>::erase(size_t Index)
{
	if (Index == 0)
	{
		pop_front();
	}
	else
		if (Index >=size())
		{
			pop_back();
		}
		else
		{
			Node<Ty> *before = head;
			while (Index-- > 0)
				before = before->next;
			before->prev->next = before->next;
			before->next->prev = before->prev;
			delete before;
		}
	count_--;
}
template <class Ty>
void list<Ty>::pop_front()
{
	Node<Ty> *tmp;
	tmp = head->next;
	delete head;
	head = tmp;
	tmp->prev = nullptr;
	--count_;
}

template <class Ty>
void list<Ty>::pop_back()
{
	Node<Ty> *tmp;
	tmp = tail->prev;
	delete tail;
	tail = tmp;
	tmp->next = nullptr;
	--count_;
}

template< typename Ty >
bool list<Ty>::empty() const
{
	return (count_ == 0);
}

template< typename Ty >
size_t list<Ty>::size() const
{
	return (count_);
}
template<class Ty>
Node<Ty>* list<Ty>::begin()
{
	return head;
}

template<class Ty>
Node<Ty>* list<Ty>::end()
{
	return tail;
}
