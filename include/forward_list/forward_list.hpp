template <class Ty>
class forward_list {
private:
	struct node
	{
		Ty data;
		node* next;
		node() : next(nullptr) {};
		node(const Ty& t) : data{ t }, next{ nullptr } {};
	};
	node *head;
	size_t count_;
	
public:
	forward_list() : count_{ 0 }, head{ nullptr } {};
	forward_list(const forward_list& other);
	forward_list& operator=(const forward_list& other);
	~forward_list();
	void clear();
	void emplace_back(const Ty& val);
	void emplace_front(const Ty &val);
	void emplace_back(const Ty&& val);
	void emplace_front(const Ty &&val);
	bool empty() const;
	void pop_back();
	void pop_front();
	size_t count() const;
private:
	void swap(forward_list& other);
};
template <class Ty>
forward_list<Ty>::forward_list(const forward_list& other)
{
	head = nullptr; count_ = 0;
	node *pTemp = other.head;
	while (pTemp != nullptr)
	{
		this->emplace_back(pTemp->data);
		pTemp = pTemp->next;
	}
}

template <class Ty>
void forward_list<Ty>::swap(forward_list& other)
{
	std::swap(count_, other.count_);
	std::swap(head, other.head);
}
template <class Ty>
forward_list<Ty>& forward_list<Ty>:: operator=(const forward_list& other)
{
	if (this != &other)
	{
    forward_list {other}.swap(*this);
	}
	return *this;
}

template <class Ty>
bool forward_list<Ty>::empty() const
{
	return (count_ == 0);
}
template <class Ty>
 forward_list<Ty>::~forward_list()
{
	clear();
}

template <class Ty>
void forward_list<Ty>::clear()
{
	node *cur_ = head;
	node *deleted_ = head;
	while (deleted_ != nullptr)
	{
		cur_ = cur_->next;
		delete deleted_;
		deleted_ = cur_;
	}
	count_ = 0;
	head = nullptr;
}

template <class Ty>
void forward_list<Ty>::emplace_front (const Ty &val)
{
	node *tmp = new node; 
	tmp->data = val; 
	tmp->next = head; 
	head = tmp; 
	count_++;
}

template <class Ty>
void forward_list<Ty>::emplace_front(const Ty &&val)
{
	node *tmp = new node;
	tmp->data = val;
	tmp->next = head;
	head = tmp;
	count_++;
}

template <class Ty>
void forward_list<Ty>::emplace_back(const Ty &val)
{
	node* front = head;
	if (front != nullptr)
	{
		while (front->next != nullptr)
		{
			front = front->next;
		}
		front->next = new node(val);
	}
	else
	{
		front = new node(val);
		head = front;
	}
	count_++;
}

template <class Ty>
void forward_list<Ty>::emplace_back(const Ty &&val)
{
	node* front = head;
	if (front != nullptr)
	{
		while (front->next != nullptr)
		{
			front = front->next;
		}
		front->next = new node(val);
	}
	else
	{
		front = new node(val);
		head = front;
	}
	count_++;
}

template <class Ty>
size_t forward_list<Ty>::count() const
{
	return count_;
}

template <class Ty>
void forward_list<Ty>::pop_front()
{
	node *tmp;
	tmp = head->next;
	delete head; 
	head=tmp; 
	--count_;
}

template <class Ty>
void forward_list<Ty>::pop_back()
{
	node* front = head;
	while (front->next->next != nullptr)
	{
		front = front->next;
	}
	delete front->next;
	front->next=nullptr;
	--count_;
}
