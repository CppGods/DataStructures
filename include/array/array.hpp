#include <algorithm>
#include <stdexcept>

template<typename T, std::size_t N>
class array
{
public:
	std::size_t size() const noexcept;
	bool empty() const  noexcept;
	T& operator [](std::size_t idx);
	T& at(std::size_t idx);
	T& front();
	T& back();
	T* data();
	void swap(array& other);
	void fill(T * val);
	array<T, N> & operator=(const array<T, N> & arr);
	std::size_t max_size() const noexcept;
private:
	T array_[N];
};

template<typename T, std::size_t N>
std::size_t array<T, N>::size() const noexcept
{
	return N;
}

template<typename T, std::size_t N>
bool array<T, N>::empty() const  noexcept
{
	return !N;
}

template<typename T, std::size_t N>
T& array<T, N>::operator [](std::size_t idx)
{
	if (idx >= size())
		throw std::out_of_range("out_of_range");
	return array_[idx];
}

template<typename T, std::size_t N>
T& array<T, N>::at(std::size_t idx)
{
	if (idx >= size())
		throw std::out_of_range("out_of_range");
	return array_[idx];
}

template<typename T, std::size_t N>
T& array<T, N>::front()
{
	return array_[0];
}

template<typename T, std::size_t N>
T& array<T, N>::back()
{
	return array_[N - 1];
}

template<typename T, std::size_t N>
T* array<T, N>::data()
{
	return &array_[0];
}

template<typename T, std::size_t N>
void array<T, N>::swap(array& other)
{
	std::swap_ranges(data(), data() + N, other.data());
}

template<typename T, std::size_t N>
void array<T, N>::fill(T * val)
{
	for (int i = 0; i < N; i++)
	{
		*val = array_[i];
		val++;
	}
}

template<typename T, std::size_t N>
array<T, N> & array<T, N>::operator=(const array<T, N> & arr)
{
	if (this != &arr)
	{
		array<T, N> temp(arr);
		temp.swap(*this);

	}
	return *this;
}
 
template<typename T, std::size_t N>
std::size_t array<T, N>::max_size() const noexcept
{
	return N;
}
