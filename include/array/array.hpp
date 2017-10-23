#include <algorithm>
#include <stdexcept>


template<typename T, int N>
class array
{
public:
	array()
	{
		array_ = new T[N ? N : 1];
		for (int i = 0; i < N; i++)
			array_[i] = 0;
	}
	array(const array& other)
	{
		array_ = new T[N ? N : 1];
		std::copy(other.array_, other.array_ + N, array_);
	}
	~array()
	{
		delete[] array_;
	}
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

	iterator begin() { return iterator(array_); }

	iterator end() 
	{ return iterator(array_ + N); }


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
		delete[] array_;
	}
	
private:
	T* array_;

};
