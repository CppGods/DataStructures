template <class T, typename P>
struct Node
{
	Node()
	{
		next = nullptr;
		priority = 0;
	}
	Node(const T& t) : data(t), next(nullptr), priority(0) {};
	Node(const T& t, P prior) : data(t), next(nullptr) ,priority(prior) {};
	Node *prev, *next;
	T data;
	P priority;
};
template <class Type, typename Pr>
class priority_queue
{
	Node<Type, Pr> *head;
	size_t count_;
public:
	priority_queue();
	~priority_queue();
	priority_queue(const priority_queue& other);
	size_t size();
	void swap(priority_queue<Type, Pr>& other);
	void swapcp(size_t child, size_t parent);
	priority_queue<Type, Pr>& operator=(const priority_queue<Type, Pr>& other);
	Node<Type, Pr>* operator[](size_t Index);
	Node<Type, Pr>* at (size_t Index);
	Type& top() const;
	bool empty() const;
	void clear();
	void push(const Type &val, Pr prior);
	void pop();
	Node<Type, Pr>* begin();
	Node<Type, Pr>* end();
};

template<class Type,typename Pr>
priority_queue<Type, Pr>::priority_queue()
{
	count_ = 0;
	head = nullptr;
}

template<class Type, typename Pr>
size_t priority_queue<Type, Pr>::size()
{
	return (count_);
}


template<class Type, typename Pr>
priority_queue<Type, Pr>& priority_queue<Type, Pr>:: operator=(const priority_queue<Type, Pr>& other)
{
	if (this != &other)
	{
		priority_queue{ other }.swap(*this);
	}
	return *this;
}

template<class Type, typename Pr>
Node<Type, Pr> * priority_queue<Type, Pr>::operator[](size_t Index)
{
	if (Index == 0)
	{
		return begin();
	}
	if (Index > size())
	{
		return end();
	}
	Node<Type, Pr> *before = begin();
	while (Index-- > 0)
		before = before->next;
	return before;
}


template<class Type, typename Pr>
Node<Type, Pr>* priority_queue<Type, Pr>::at(size_t Index)
{
	if (Index == 0)
	{
		return begin();
	}
	if (Index > size())
	{
		return end();
	}
	Node<Type, Pr> *before = begin();
	while (Index-- > 0)
		before = before->next;
	return before;
}

template<class Type, typename Pr>
Type & priority_queue<Type, Pr>::top() const
{
	return head->data;
}

template<class Type, typename Pr>
bool priority_queue<Type, Pr>::empty() const
{
	return (!count_);
}

template<class Type, typename Pr>
void priority_queue<Type, Pr>::clear()
{
	Node<Type, Pr> *cur_ = head;
	Node<Type, Pr> *deleted_ = head;
	while (deleted_ != nullptr)
	{
		cur_ = cur_->next;
		delete deleted_;
		deleted_ = cur_;
	}
	count_ = 0;
	head = nullptr;
}

template<class Type, typename Pr>
void priority_queue<Type, Pr>::push(const Type & val, Pr prior)
{
	Node<Type, Pr> *tmp = end();
	if (tmp != nullptr)
	{
		tmp->next = new Node<Type, Pr>(val, prior);
	}
	else
	{
		head = new Node<Type, Pr>(val, prior);
	}
	int index = count_;
	int pIndex = ((index + 1) / 2) - 1;
	while (!(pIndex < 0 || (at(index)->priority) < (at(pIndex)->priority)))
	{
		swapcp(index, pIndex);
		index = pIndex;
		pIndex = ((index + 1) / 2) - 1;
	}
	count_++;
}

template<class Type, typename Pr>
void priority_queue<Type, Pr>::pop()
{
	swapcp(count_-1, 0);
	if (count_ > 1)
	{
		Node<Type, Pr> *tmp = at(count_ - 2);
		Node<Type, Pr> *tail = end();
		delete[] tail;
		tmp->next = nullptr;
		--count_;
		size_t parent = 0;
		bool f = 1;
		while (f)
		{
			size_t left = (2 * parent + 1);
			size_t right = (2 * parent + 2);
			size_t length = count_;
			size_t largest = parent;

			if (left < length && (at(left)->priority > at(largest)->priority))
				largest = left;

			if (right < length && (at(right)->priority > at(largest)->priority))
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
		else clear();

}


template<class Type, typename Pr>
Node<Type, Pr>* priority_queue<Type, Pr>::begin()
{
	return head;
}

template<class Type, typename Pr>
Node<Type, Pr>* priority_queue<Type, Pr>::end()
{
	Node<Type, Pr> *before = head;
	if (before != nullptr)
	while (before->next != nullptr)
		before = before->next;
	return before;
}

template<class Type, typename Pr>
void priority_queue<Type, Pr>::swap(priority_queue<Type, Pr> & other)
{
	std::swap(count_, other.count_);
	std::swap(head, other.head);
}

template<class Type, typename Pr>
void priority_queue<Type, Pr>::swapcp(size_t child, size_t parent)
{
	Type tempv;
	tempv = at(child)->data;
	at(child)->data = at(parent)->data;
	at(parent)->data = tempv;
	Pr tempp;
	tempp = at(child)->priority;
	at(child)->priority = at(parent)->priority;
	at(parent)->priority = tempp;
}

template<class Type, typename Pr>
priority_queue<Type, Pr>::~priority_queue()
{
	clear();
}

template<class Type, typename Pr>
priority_queue<Type, Pr>::priority_queue(const priority_queue& other)
{
	head = nullptr;
	count_ = 0;
	Node<Type, Pr> *temp = other.head;
	while (temp != nullptr)
	{
		this->push(temp->data, temp->priority);
		temp = temp->next;
	}
	count_ = other.count_;
}
