template<class Ty, size_t N> 
class array {

public:
	
	//methods

	array();

	array(const array& other);

	~array();

	void assign(const Ty& val);

	const Ty& at(size_t index) const;

	const Ty& back() const;

	Ty* begin();

	const Ty& front() const;

	//...

	//operators

	

	Ty& operator[](size_t index);

	const Ty& operator[](size_t index) const;

	//...

private:

	//members

	Ty arr_[N];

};