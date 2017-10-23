template <class Ty>
class vector {

public:

// methods

  vector();
  
  vetor(const vector& other);
  
  ~vector();
  
  T& at(size_t index);
  
  Ty& back();
  
  void clear();
  
  Ty* data();
  
  bool empty() const;
  
  Ty& front();
  
  size_t max_size() const;

  void push_back(const Ty& value); 

  void reserve(size_t size);
  
  void resize(size_t size);

  void shrink_to_fit();

//...

// operators 
 
  vector& operator=(const vector& other);
  
  Ty& opearator[](size_t index);
  
  const Ty& operator[](size_t index) const;
  
// ...

private:
  
  void swap(vector& other)

  Ty* array_;
  size_t size_array;
  size_t count_;
};


template<class Ty>
vector() :
	array_(nullptr_),
	size_array_(0),
	count_(0)
{}

template<class Ty>
vector(const vector& other) :
	size_array_(other.size_array_),
	count_(other.count_)
{
	std::copy(other.array_, other.array_ + count_, array_);
}

template<class Ty>
~vector() {
	delete[] array_;
}

template<class Ty>
vector<Ty>& operator=(const vector<Ty>& other) {
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
