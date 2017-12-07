#ifndef UN_MAP_HPP
#define UN_MAP_HPP

#include <utility>
#include <functional>
#include <vector>
#include "include\hash_table\hash_table_s_c.hpp"

//hash_table_using_separate_chaining
//one key - one value
//holding std::pair<Key, Val>

// TODO :: &&functional + iterators + hash_table + operators 

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
> class Unordered_Map {

public:

	using Value_Type = std::pair<Key, Val>;

	Unordered_Map();
	Unordered_Map(Unordered_Map const & other);
	Unordered_Map(Unordered_Map && other);
	Unordered_Map & operator=(Unordered_Map const & other);
	Unordered_Map & operator=(Unordered_Map && other);
	~Unordered_Map();
	void swap(Unordered_Map & other);

	void insert(Key const & key, Val const & val);
	bool find(Key const & key) const;
	void erase(Key const & key);
	Val get_value(Key const & key) const;
	std::vector<Key> get_keys() const;
	void clear();
	bool empty() const;
	std::size_t size() const;
	
	Val operator[](Key const & key);
	Val & operator[](Key const & key);

private:

	Hash_Table_S_C<Key, Value_Type, Hash, KeyEqual> * hash_table_;

};


////////////////////////////////REALISE/////////////////////////

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
Unordered_Map<Key, Val, Hash, KeyEqual>::
Unordered_Map() {

	hash_table_ = new Hash_Table_S_C<Key, Value_Type, Hash, KeyEqual>();
}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
Unordered_Map<Key, Val, Hash, KeyEqual>::
Unordered_Map(Unordered_Map<Key, Val, Hash, KeyEqual> const & other) {
	
	hash_table = new Hash_Table_S_C<Key, Value_Type, Hash, KeyEqual>(*other.hash_table_);
}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
Unordered_Map<Key, Val, Hash, KeyEqual>::
Unordered_Map(Unordered_Map<Key, Val, Hash, KeyEqual> && other)
	: Unordered_Map() {

	swap(other);
}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
Unordered_Map<Key, Val, Hash, KeyEqual> &
Unordered_Map<Key, Val, Hash, KeyEqual>::
operator=(Unordered_Map<Key, Val, Hash, KeyEqual> const & other) {

	if (this != &other) {
		Unordered_Map tmp(other);
		tmp.swap(*this);
	}
}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
Unordered_Map<Key, Val, Hash, KeyEqual> &
Unordered_Map<Key, Val, Hash, KeyEqual>::
operator=(Unordered_Map && other) {

	swap(other);
}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
Unordered_Map<Key, Val, Hash, KeyEqual>::
~Unordered_Map() {

	delete hash_table_;
}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
void
Unordered_Map<Key, Val, Hash, KeyEqual>::
swap(Unordered_Map<Key, Val, Hash, KeyEqual> &other) {

	std::swap(hash_table_, other.hash_table_);
}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
void
Unordered_Map<Key, Val, Hash, KeyEqual>::
insert(Key const & key, Val const & val) {
	
	if (!find(key)) {
		hash_table_->insert(key, val);
	}
}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
bool
Unordered_Map<Key, Val, Hash, KeyEqual>::
find(Key const & key) const {

	return hash_table_->find(key);
}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
void
Unordered_Map<Key, Val, Hash, KeyEqual>::
erase(Key const & key) {

	hash_table_->erase(key);
}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
void
Unordered_Map<Key, Val, Hash, KeyEqual>::
clear() {

	hash_table_->clear();
}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
bool
Unordered_Map<Key, Val, Hash, KeyEqual>::
empty() const {

	return hash_table_->empty();
}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
std::size_t
Unordered_Map<Key, Val, Hash, KeyEqual>::
size() const {

	return hash_table_->size();
}


#endif // !UN_MAP_HPP