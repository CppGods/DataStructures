#ifndef UN_SET_HPP
#define UN_SET_HPP

#include <utility>
#include <functional>
#include "include\hash_table\hash_table_o_a.hpp"

//hash_table_using_o_a

//TODO :: &&, operators, tests, iterators

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
> class Unordered_Set {

public:

	Unordered_Set();
	Unordered_Set(Unordered_Set const & other);
	Unordered_Set(Unordered_Set && other);
	Unordered_Set & operator=(Unordered_Set const & other);
	Unordered_Set & operator=(Unordered_Set && other);
	~Unordered_Set();
	void swap(Unordered_Set & other);

	void insert(Val const & val);
	bool find(Val const & val) const;
	void erase(Val const & val);
	//Val get_value(Val const & val) const;
	//std::vector<Val> get_vals() const;
	void clear();
	bool empty() const;
	std::size_t size() const;

	Unordered_set & operator=(Unordered_set const & other);
	Unordered_set & operator=(Unordered_set && other);
	bool operator>(Unordered_set const & other) const;
	bool operator<(Unordered_set const & other) const;
	bool operator==(Unordered_set const & other) const;
	bool operator>=(Unordered_set const & other) const;
	bool operator<=(Unordered_set const & other) const;

private:

	Hash_Table_O_A<Val, Hash, ValEqual> * hash_table_;

};


////////////////////////////////REALISE/////////////////////////

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
Unordered_Set<Val, Hash, ValEqual>::
Unordered_Set() {

	hash_table_ = new Hash_Table_O_A<Value_Type, Hash, ValEqual>();
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
Unordered_Set<Val, Hash, ValEqual>::
Unordered_Set(Unordered_Set<Val, Hash, ValEqual> const & other) {
	
	hash_table = new Hash_Table_O_A<Value_Type, Hash, ValEqual>(*other.hash_table_);
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
Unordered_Set<Val, Hash, ValEqual>::
Unordered_Set(Unordered_Set<Val, Hash, ValEqual> && other)
	: Unordered_Set() {

	swap(other);
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
Unordered_Set<Val, Hash, ValEqual> &
Unordered_Set<Val, Hash, ValEqual>::
operator=(Unordered_Set<Val, Hash, ValEqual> const & other) {

	if (this != &other) {
		Unordered_Set tmp(other);
		tmp.swap(*this);
	}
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
Unordered_Set<Val, Hash, ValEqual> &
Unordered_Set<Val, Hash, ValEqual>::
operator=(Unordered_Set && other) {

	swap(other);
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
Unordered_Set<Val, Hash, ValEqual>::
~Unordered_Set() {

	delete hash_table_;
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
void
Unordered_Set<Val, Hash, ValEqual>::
swap(Unordered_Set<Val, Hash, ValEqual> &other) {

	std::swap(hash_table_, other.hash_table_);
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
void
Unordered_Set<Val, Hash, ValEqual>::
insert(Val const & val) {
	
	if (!find(val)) {
		hash_table_->insert(val);
	}
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
bool
Unordered_Set<Val, Hash, ValEqual>::
find(Val const & val) const {

	return hash_table_->find(val);
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
void
Unordered_Set<Val, Hash, ValEqual>::
erase(Val const & val) {

	hash_table_->erase(val);
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
void
Unordered_Set<Val, Hash, ValEqual>::
clear() {

	hash_table_->clear();
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
bool
Unordered_Set<Val, Hash, ValEqual>::
empty() const {

	return hash_table_->empty();
}

template<
	class Val,
	class Hash = std::hash<Val>,
	class ValEqual = std::equal_to<Val>
>
std::size_t
Unordered_Set<Val, Hash, ValEqual>::
size() const {

	return hash_table_->size();
}


#endif // !UN_SET_HPP