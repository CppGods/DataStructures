template <class Ty>
class stack {

public:
	bool empty() const noexcept;
	stack(const stack<T>&);
	stack();
	Ty* top ();
	size_t size() const noexcept;
	void push(const Type& val);
	void pop ();
	~stack()  noexcept;
private:

	Ty* array_;
	size_t size_array_;
	size_t count_;
};
template <class Ty>
Ty* top()
{
	return array_;
}

template <class Ty>
bool stack<Ty>:: empty() const noexcept
{
	return count_==0;
}

template <class Ty>
stack<Ty>::stack(): count_{0}, array_size_{0}, array_{nullptr}
{
}

template <class Ty>
stack<Ty>:: stack(const stack<T>&)
{
	array_size_ = object.array_size_;
	count_ = object.count_;
	array_=new T[count_];
	std::copy(object.array_,object.array_+count_, array_);
}

template <class Ty>
stack<Ty>::~stack() noexcept
{
	delete[] array_;
}

template <class Ty>
void stack<Ty>:: pop()
{
	assert(count_ > 0);
   	array_[--count_];
}

template <class Ty>
size_t stack<Ty>::size() const noexcept
{
	return count_;
}
