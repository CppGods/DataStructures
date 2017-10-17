template<class Ty, size_t N> 
class array {

public:
	
	//methods

	array();

	array(const array& other);

	~array();

	const Ty& at(size_t index) const;

	const Ty& back() const;

	Ty* begin();

	Ty* end();

	bool empty() const;

	void fill(const Type& val);

	const Ty& front() const;

	size_t size() const;

	void swap(array& right);

	//...

	//operators

	Ty& operator[](size_t index);

	const Ty& operator[](size_t index) const;

	//...

private:

	//members

	Ty arr_[N];

};