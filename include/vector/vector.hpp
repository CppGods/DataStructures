template <class Ty>
class vector {

public:

  vector();
  
  vector(const vector& other);
  
  ~vector();
  
  void assign( std::size_t count, const Ty& value );
  
  Ty& at(std::size_t index);

  const Ty& at(std::size_t index) const;
  
  const Ty& back() const;

  std::size_t capacity() const;
  
  void clear();
  
  const Ty* data() const;
  
  bool empty() const;
  
  const Ty& front() const;
  
  std::size_t max_size() const;

  void push_back(const Ty& value);

  void pop_back();

  void reserve(std::size_t size);
  
  void resize(std::size_t count);

  std::size_t size() const;

  void shrink_to_fit();
 
  vector& operator=(const vector& other);
  
  Ty& opearator[](std::size_t index);
  
  const Ty& operator[](std::size_t index) const;

private:
  
  void swap(vector& other);

  Ty* array_;
  size_t size_array_;
  size_t count_;
};



/////////////////////////////////REALISE///////////////////////////////////////

template<class Ty>
vector<Ty>::vector() 
	:
	array_{ nullptr_ },
	size_array_{ 0 },
	count_{ 0 } {

}

template<class Ty>
vector<Ty>::vector(const vector& other) 
	:
	size_array_{ other.size_array_ },
	count_{ other.count_ } {

	std::copy(other.array_, other.array_ + count_, array_);
}

template<class Ty>
vector<Ty>::~vector() {

	delete[] array_;
}

template<class Ty>
vector<Ty>& vector<Ty>::operator=(const vector<Ty>& other) {

	if (this != &other) {
		vector<T> tmp(other);
		tmp.swap(*this);
	}
	return *this;
}

template<class Ty>
void vector<T>::swap(vector<T>& other) {

	std::swap(array_, other.array_);
	std::swap(array_size_, other.array_size_);
	std::swap(count_, other.count_);
}

template<class Ty>
Ty& vector<Ty>::at(std::size_t index) {

	if (index < count_) {
		return array_[index];
	}
	throw "IndexOutOfRange!!!";
}

template<class Ty>
const Ty& vector<Ty>::at(std::size_t index) const {

	if (index < count_) {
		return array_[index];
	} 
	throw "IndexOutOfRange!!!";
}

template<class Ty>
const Ty& vector<Ty>::back() const {
	
	if(count_ > 0) {
		return array_[count_ - 1];
	}
	throw "Logical_error!!!"
}

template<class Ty>
const Ty& vector<Ty>::front() const {
	
	if(count_ > 0) {
		return array_[0];
	}
	throw "Logical_error!!!"
}

template<class Ty>
const Ty* vector<T>::data() const{

	return array_;
}

template<class Ty>
void vector<T>::clear() {

	if (count_ > 0) {
		for (size_t i = 0; i < count_; ++i) {
			array_[i].~Ty();
		}
		count_ = 0;
	}
}

template<class Ty>
bool vector<Ty>::empty() const {

	return count_ == 0;
}

template<class Ty>
void vector<Ty>::push_back(const Ty& value) {

	if (count_ == 0) {
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
				throw "Length_error!!!"
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
size_t vector<Ty>::size() const {

	return count_;
}

template<class Ty>
size_t vector<Ty>::capacity() const {

	return size_array_;
}

template<class Ty>
std::size_t vector<Ty>::max_size() const {

	return std::numeric_limits<std::size_t>::max();
}

template<class Ty>
void vector<Ty>::reserve(std::size_t size) {

	if (size > size_array_) {
		if (size_ > max_size()) {
			throw "Length_error!!!";
		} else {
			
			if(size_array_ == 0) {
				array_ = new Ty[1];
				size_array_ = 1;
			}
			std::size_t newsize = size_array_;
			while (newsize < size_) {
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
	
	if (count >= count_) {
		reserve(count);
	} else {
		std::size_t newsize = size_array_;
		while (!(newsize / 2 < count)) {
			newsize /= 2;
		}
		if (newsize < count_) { // atention, relation with each other
			Ty* tmp = array_;
			array_ = new Ty[newsize];
			std::copy(tmp, tmp + count_, array_);
			size_array_ = newsize;
			delete[] tmp;
		}
	}
}

template<class Ty>
void vector<Ty>::shrink_to_fit() {

	std::size_t start_size = size_array_;
	std::size_t newsize = size_array_;
	while (newsize / 2 > count_) {
		newsize /= 2;
	}
	if (newsize != start_size) {
		Ty* tmp = array_;
		array_ = new Ty[newsize];
		std::copy(tmp, tmp + count_, array_);
		size_array_ = newsize;
		delete[] tmp;
	}
}

template<class Ty>
void vector<Ty>::assign( std::size_t count, const Ty& value ) {
	
	if(count > max_size()) {
		throw "Length_error!!!";
	}
	reserve(count);
	for(std::size_t i = 0; i < count; ++i) {
		array_[i] = val;
	}
	count_ = count;
}

template<class Ty>
Ty& vector<Ty>::opearator[](std::size_t index) {

	return array_[index];
}  

template<class Ty>
const Ty& vector<Ty>::operator[](std::size_t index) const {  
	
	return array_[index];
}

template<class Ty>
void vector<Ty>::pop_back() {

	if (count_ > 0) {
		array_[count_ - 1].~Ty();
		--count_;
	}
	throw "vector is EMPTY!";
}

