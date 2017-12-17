#include <iostream>

template <class Ty>
class stack {

public:
	stack();
	~stack()  noexcept;
	stack(const stack<Ty>&);
	Ty& top () const;
	size_t size() const noexcept;
	void push(const Ty& val);
	void pop ();
	bool empty() const noexcept;
	
private:

	Ty* array_;
	size_t array_size_;
	size_t count_;
};



template <typename Ty>
void stack<Ty>::push(const Ty &value)
{
	
	if (array_size_ == count_)
	{
		size_t array_size = array_size_ == 0 ? 1 : array_size_ * 2;
		Ty *ptr = new Ty [array_size_];
		try 
		{
			std::copy(array_, array_ + count_, ptr);
		}
		catch (...)
		{  
      			delete[] ptr;
			throw;
		}
		
		array_size_=array_size;
		delete[] array_;
		array_ = ptr;
	}
	
	array_[count_] = value;
	++count_;
}


template <class Ty>
Ty& stack<Ty>:: top() const
{
	return array_[count_-1];
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
stack<Ty>:: stack(const stack<Ty>& object)
{
	array_size_ = object.array_size_;
	count_ = object.count_;
	array_=new Ty[count_];
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
	if (count_ == 0)
	{
		throw "logic error";
	}
   	--count_;
}

template <class Ty>
size_t stack<Ty>::size() const noexcept
{
	return count_;
}
