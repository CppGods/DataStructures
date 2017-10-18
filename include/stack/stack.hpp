template <class Ty>
class stack {

public:
bool empty() const noexcept;
stack();
~stack()  noexcept;
private:

	Ty* array_;
	size_t size_array_;
	size_t count_;
};
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
stack<Ty>::~stack() noexcept
{
	delete[] array_;
}
