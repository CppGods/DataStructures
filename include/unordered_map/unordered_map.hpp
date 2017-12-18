#ifndef UN_MAP_HPP
#define UN_MAP_HPP

#include <utility>
#include <functional>
#include <vector>
#include <hash_table\hash_table_s_c.hpp>

//hash_table_using_separate_chaining
//one key - one value
//holding std::pair<Key, Val>

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
> class Unordered_Map {

public:

	class TUnordered_Map_Bidiretional_Iterator
		: public std::iterator<std::bidirectional_iterator_tag, std::pair<Key, Val> > {

		friend class Unordered_Map;

	private:

		TUnordered_Map_Bidiretional_Iterator()
			: pos_{ 0 } {

		}

	public:

		TUnordered_Map_Bidiretional_Iterator(TUnordered_Map_Bidiretional_Iterator const & other)
			: pos_{ other.pos_ } {

			pairs_ = other.pairs_;
		}

		bool operator!=(TUnordered_Map_Bidiretional_Iterator const & other) const {

			return pos_ != other.pos_;
		}

		bool operator==(TUnordered_Map_Bidiretional_Iterator const & other) const {
	
			return pos_ == other.pos_;
		}

		std::pair<Key, Val> const & operator*() const {

			return *pairs_[pos_];
		}

		Key const & key() const {

			return (*pairs_[pos_]).first;
		}

		Val const & value() const {

			return (*pairs_[pos_]).second;
		}

		TUnordered_Map_Bidiretional_Iterator & operator++() {

			++pos_;
			return *this;
		}

		TUnordered_Map_Bidiretional_Iterator & operator--() {

			--pos_;
			return *this;
		}

		TUnordered_Map_Bidiretional_Iterator & operator++(int) {

			TUnordered_Map_Bidiretional_Iterator tmp(*this);
			++pos_;
			return tmp;
		}

		TUnordered_Map_Bidiretional_Iterator & operator--(int) {

			TUnordered_Map_Bidiretional_Iterator tmp(*this);
			--pos_;
			return tmp;
		}

		~TUnordered_Map_Bidiretional_Iterator() {
		
		}

	private:

		std::vector<std::pair<Key, Val> const *> pairs_;
		std::size_t pos_;
	};

	TUnordered_Map_Bidiretional_Iterator cbegin() const {

		TUnordered_Map_Bidiretional_Iterator it;
		it.pairs_ = std::move(get_pairs_ref_vector());

		return it;
	}

	TUnordered_Map_Bidiretional_Iterator cend() const {

		TUnordered_Map_Bidiretional_Iterator it;
		it.pairs_ = std::move(get_pairs_ref_vector());
		it.pos_ = it.pairs_.size();

		return it;
	}

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
	Val get_val(Key const & key) const;
	void clear();
	bool empty() const;
	std::size_t size() const;
	
	Val operator[](Key const & key) const;
	Val & operator[](Key const & key);

private:

	Hash_Table_S_C<Key, Val, Hash, KeyEqual> * hash_table_;

	std::vector<std::pair<Key, Val> const *> get_pairs_ref_vector() const;

};


////////////////////////////////REALISE/////////////////////////

template<
	class Key,
	class Val,
	class Hash,
	class KeyEqual
>
Unordered_Map<Key, Val, Hash, KeyEqual>::
Unordered_Map() {

	hash_table_ = new Hash_Table_S_C<Key, Val, Hash, KeyEqual>();
}

template<
	class Key,
	class Val,
	class Hash,
	class KeyEqual
>
Unordered_Map<Key, Val, Hash, KeyEqual>::
Unordered_Map(Unordered_Map<Key, Val, Hash, KeyEqual> const & other) {
	
	hash_table_ = new Hash_Table_S_C<Key, Val, Hash, KeyEqual>(*other.hash_table_);
}

template<
	class Key,
	class Val,
	class Hash,
	class KeyEqual
>
Unordered_Map<Key, Val, Hash, KeyEqual>::
Unordered_Map(Unordered_Map<Key, Val, Hash, KeyEqual> && other)
	: Unordered_Map() {

	swap(other);
}

template<
	class Key,
	class Val,
	class Hash,
	class KeyEqual
>
Unordered_Map<Key, Val, Hash, KeyEqual> &
Unordered_Map<Key, Val, Hash, KeyEqual>::
operator=(Unordered_Map<Key, Val, Hash, KeyEqual> const & other) {

	if (this != &other) {
		Unordered_Map tmp(other);
		tmp.swap(*this);
	}
	return *this;
}

template<
	class Key,
	class Val,
	class Hash,
	class KeyEqual
>
Unordered_Map<Key, Val, Hash, KeyEqual> &
Unordered_Map<Key, Val, Hash, KeyEqual>::
operator=(Unordered_Map<Key, Val, Hash, KeyEqual> && other) {

	swap(other);
}

template<
	class Key,
	class Val,
	class Hash,
	class KeyEqual
>
Unordered_Map<Key, Val, Hash, KeyEqual>::
~Unordered_Map() {

	delete hash_table_;
}

template<
	class Key,
	class Val,
	class Hash,
	class KeyEqual
>
void
Unordered_Map<Key, Val, Hash, KeyEqual>::
swap(Unordered_Map<Key, Val, Hash, KeyEqual> &other) {

	std::swap(hash_table_, other.hash_table_);
}

template<
	class Key,
	class Val,
	class Hash,
	class KeyEqual
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
	class Hash,
	class KeyEqual
>
bool
Unordered_Map<Key, Val, Hash, KeyEqual>::
find(Key const & key) const {

	return hash_table_->find(key);
}

template<
	class Key,
	class Val,
	class Hash,
	class KeyEqual
>
void
Unordered_Map<Key, Val, Hash, KeyEqual>::
erase(Key const & key) {

	hash_table_->erase(key);
}

template<
	class Key,
	class Val,
	class Hash,
	class KeyEqual
>
void
Unordered_Map<Key, Val, Hash, KeyEqual>::
clear() {

	hash_table_->clear();
}

template<
	class Key,
	class Val,
	class Hash,
	class KeyEqual
>
bool
Unordered_Map<Key, Val, Hash, KeyEqual>::
empty() const {

	return hash_table_->empty();
}

template<
	class Key,
	class Val,
	class Hash,
	class KeyEqual
>
std::size_t
Unordered_Map<Key, Val, Hash, KeyEqual>::
size() const {

	return hash_table_->size();
}

template<
	class Key,
	class Val,
	class Hash,
	class KeyEqual
>
Val
Unordered_Map<Key, Val, Hash, KeyEqual>::
get_val(Key const & key) const {

	return hash_table_->get_val(key);
}

template<
	class Key,
	class Val,
	class Hash,
	class KeyEqual
>
Val
Unordered_Map<Key, Val, Hash, KeyEqual>::
operator[](Key const & key) const {

	return (*hash_table_)[key];
}

template<
	class Key,
	class Val,
	class Hash,
	class KeyEqual
>
Val &
Unordered_Map<Key, Val, Hash, KeyEqual>::
operator[](Key const & key) {

	return (*hash_table_)[key];
}

////private

template<
	class Key,
	class Val,
	class Hash,
	class KeyEqual
>
std::vector<std::pair<Key, Val> const *>
Unordered_Map<Key, Val, Hash, KeyEqual>::
get_pairs_ref_vector() const {

	return hash_table_->get_pairs_ref_vector();
}

#endif // !UN_MAP_HPP