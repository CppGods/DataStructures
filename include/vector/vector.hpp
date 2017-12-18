#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <utility>
#include <limits>
#include <algorithm>

template <class Ty>
class vector {

public:

  vector();
  vector(vector const & other);
  vector(vector && other);
  ~vector();
  void assign( std::size_t count, Ty const & value );
  Ty & at(std::size_t index);
  Ty const & at(std::size_t index) const;
  Ty const & back() const;
  std::size_t capacity() const;
  void clear();
  Ty const * data() const;
  bool empty() const;
  Ty const & front() const;
  std::size_t max_size() const;
  void push_back(Ty const & value);
  void pop_back();
  void reserve(std::size_t size);
  void resize(std::size_t count);
  std::size_t size() const;
  void shrink_to_fit();
  vector & operator=(vector const & other);
  vector & operator=(vector && other);
  Ty & operator[](std::size_t index);
  Ty const & operator[](std::size_t index) const;

  template <class Args>
  void emplace_back(Args && args);

private:

  Ty* array_;
  std::size_t size_array_;
  std::size_t count_;

  void swap(vector & other);
};



/////////////////////////////////REALISE///////////////////////////////////////


template<class Ty>
vector<Ty>::vector() 
	: array_{ nullptr }
	, size_array_{ 0 }
	, count_{ 0 } {

}

template<class Ty>
vector<Ty>::vector(vector<Ty> const & other) 
	: size_array_{ other.size_array_ }
	, count_{ other.count_ } {

	array_ = new Ty[size_array_];
	std::copy(other.array_, other.array_ + count_, array_);
}

template<class Ty>
vector<Ty>::vector(vector<Ty> && other)
	: vector() {

	swap(other);
}

template<class Ty>
vector<Ty>::~vector() {

	delete[] array_;
}

template<class Ty>
vector<Ty> & vector<Ty>::operator=(vector<Ty> const & other) {

	if (this != &other) {
		vector<Ty> tmp(other);
		tmp.swap(*this);
	}
	return *this;
}

template<class Ty>
vector<Ty> & vector<Ty>::operator=(vector<Ty> && other) {

	swap(other);
	return *this;
}

template<class Ty>
void vector<Ty>::swap(vector<Ty> & other) {

	std::swap(array_, other.array_);
	std::swap(size_array_, other.size_array_);
	std::swap(count_, other.count_);
}

template<class Ty>
Ty & vector<Ty>::at(std::size_t index) {

	if (index < count_) {
		return array_[index];
	}
	throw "IndexOutOfRange!!!";
}

template<class Ty>
Ty const & vector<Ty>::at(std::size_t index) const {

	if (index < count_) {
		return array_[index];
	} 
	throw "IndexOutOfRange!!!";
}

template<class Ty>
Ty const & vector<Ty>::back() const {
	
	if(count_ > 0) {
		return array_[count_ - 1];
	}
	throw "Logical_error!!!";
}

template<class Ty>
Ty const & vector<Ty>::front() const {
	
	if(count_ > 0) {
		return array_[0];
	}
	throw "Logical_error!!!";
}

template<class Ty>
Ty const * vector<Ty>::data() const{

	return array_;
}

template<class Ty>
void vector<Ty>::clear() {

	if (size_array_ > 0) {
		delete[] array_;
		array_ = nullptr;
		count_ = 0;
		size_array_ = 0;
	}
}

template<class Ty>
bool vector<Ty>::empty() const {

	return count_ == 0;
}

template<class Ty>
void vector<Ty>::push_back(Ty const & value) {

	if (size_array_ == 0) {
		array_ = new Ty[1];
		size_array_ = 1;
	}
	if (count_ == size_array_) {
		std::size_t newsize = size_array_;
		newsize *= 2;
		if (newsize > max_size()) {
			if (newsize / 2 < max_size()) {
				newsize = max_size();
			} else {
				throw "Length_error!!!";
			}
		}
		Ty* tmp = array_;
		array_ = new Ty[newsize];
		std::copy(tmp, tmp + count_, array_);
		size_array_ = newsize;
		delete[] tmp;
	}
	array_[count_] = value;
	++count_;
}

template<class Ty>
std::size_t vector<Ty>::size() const {

	return count_;
}

template<class Ty>
std::size_t vector<Ty>::capacity() const {

	return size_array_;
}

template<class Ty>
std::size_t vector<Ty>::max_size() const {

	return std::numeric_limits<std::size_t>::max();
}

template<class Ty>
void vector<Ty>::reserve(std::size_t size) {

	if (size > size_array_) {
		if (size > max_size()) {
			throw "Length_error!!!";
		} else {
			if(size_array_ == 0) {
				array_ = new Ty[1];
				size_array_ = 1;
			}
			std::size_t newsize = size_array_;
			while (newsize < size) {
				newsize *= 2;
			}
			if (newsize > max_size()) {
				newsize = max_size();
			}
			if(count_ > 0) {
				Ty* tmp = array_;
				array_ = new Ty[newsize];
				std::copy(tmp, tmp + count_, array_);
				delete[] tmp;
			} else {
				delete[] array_;
				array_ = new Ty[newsize];
			}
			size_array_ = newsize;
		}
	}
}

template<class Ty>
void vector<Ty>::resize(std::size_t count) {
	
	if (count > count_) {
		reserve(count);
	} else {
		std::size_t newsize = size_array_;
		while (!(newsize / 2 < count)) {
			newsize /= 2;
		}
		if (newsize < count_) {
			Ty* tmp = array_;
			array_ = new Ty[newsize];
			std::copy(tmp, tmp + newsize, array_);
			count_ = newsize;
			size_array_ = newsize;
			delete[] tmp;
		}
	}
}

template<class Ty>
void vector<Ty>::shrink_to_fit() {

	std::size_t start_size = size_array_;
	std::size_t newsize = size_array_;
	if (count_ != 0) {
		while (newsize / 2 >= count_) {
			newsize /= 2;
		}
		if (newsize != start_size) {
			Ty* tmp = array_;
			array_ = new Ty[newsize];
			std::copy(tmp, tmp + count_, array_);
			size_array_ = newsize;
			delete[] tmp;
		}
	} else {
		if (start_size != 0) {
			delete[] array_;
			size_array_ = 0;
		}
	}
	
}

template<class Ty>
void vector<Ty>::assign( std::size_t count, Ty const & value ) {
	
	if(count > max_size()) {
		throw "Length_error!!!";
	}
	reserve(count);
	for(std::size_t i = 0; i < count; ++i) {
		array_[i] = value;
	}
	count_ = count;
}

template<class Ty>
Ty & vector<Ty>::operator[](std::size_t index) {

	return array_[index];
}  

template<class Ty>
Ty const & vector<Ty>::operator[](std::size_t index) const {  
	
	return array_[index];
}

template<class Ty>
void vector<Ty>::pop_back() {

	if (count_ > 0) {
		array_[count_ - 1].~Ty();
		--count_;
	} else {
		throw "Vector is EMPTY!";
	}
}

template <class Ty>
template <class Args>
void
vector<Ty>::emplace_back(Args && args) {

	if (size_array_ == 0) {
		array_ = new Ty[1];
		size_array_ = 1;
	}
	if (count_ == size_array_) {
		std::size_t newsize = size_array_;
		newsize *= 2;
		if (newsize > max_size()) {
			if (newsize / 2 < max_size()) {
				newsize = max_size();
			} else {
				throw "Length_error!!!";
			}
		}
		Ty* tmp = array_;
		array_ = new Ty[newsize];
		std::copy(tmp, tmp + count_, array_);
		size_array_ = newsize;
		delete[] tmp;
	}
	array_[count_] = std::move(Ty(args));
	++count_;
}

#endif // !VECTOR_HPP
