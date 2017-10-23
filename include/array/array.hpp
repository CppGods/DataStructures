#include <algorithm>
#include <stdexcept>


template<typename T, size_t N>
class array
{
public:
	
	
	typedef typename std::add_pointer<T>::type iterator;
	
	size_t size() const
	{ 
		return N;
	}

	bool empty() const 
	{
		return !N;
	}

	T& operator [](size_t idx) 
	{ 
		if (idx >= size())
			throw std::out_of_range("out_of_range");
		return array_[idx];
	}

	T& at(size_t idx)
	{
		if (idx >= size())
			throw std::out_of_range("out_of_range");
		return array_[idx];
	}

	T& front()
	{
		return *begin();
	}
	
	T& back()
	{
		return N ? *(end() - 1) : *end();
	}

	iterator begin() 
	{
		return iterator(array_); 
	}

	iterator end() 
	{
		return iterator(array_ + N);
	}


	void swap(array& other)
	{
		std::swap_ranges(begin(), end(), other.begin());
	}

	void fill(T * val)
	{
		for (int i = 0; i < 3; i++)
		{
			*val = array_[i];
			val++;
		}
	}
	array<T, N> & operator=(const array<T, N> & arr)
	{
		if (this != arr) 
		{
			array<T, N> temp(arr);
			temp.swap(*this);
		}
		return *this;
	}
	
private:
	T array_[N ? N : 1];

};
