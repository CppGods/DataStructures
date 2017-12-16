#ifndef HASH_TABLE_S_C_HPP
#define HASH_TABLE_S_C_HPP

#include <utility>
#include <functional>
#include <vector>

#define CAPACITY 100
#define LOAD_FACTOR 0.5

//hash_table_using_separate_chaining
//for map
//not unique elemnts

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
> class Hash_Table_S_C {

public:

	struct Element {
		std::pair<Key, Val> data_;
		bool is_empty_ = true;
	};

	Hash_Table_S_C();
	Hash_Table_S_C(Hash_Table_S_C const & other);
	Hash_Table_S_C(Hash_Table_S_C && other);
	Hash_Table_S_C & operator=(Hash_Table_S_C const & other);
	Hash_Table_S_C & operator=(Hash_Table_S_C && other);
	~Hash_Table_S_C();
	void swap(Hash_Table_S_C & other);

	void insert(Key const & key, Val const & val);
	bool find(Key const & key) const;
	void erase(Key const & key);
	void clear();
	bool empty() const;
	std::size_t size() const;
	Val get_val(Key const & key);

	Val & operator[](Key const & key);
	Val operator[](Key const & key) const;

	std::vector<std::pair<Key, Val> const *> get_pairs_ref_vector() const;

private:

	Hash Hasher_;
	KeyEqual Equal_;
	float const load_factor_ = LOAD_FACTOR;

	std::size_t count_ = 0;
	std::size_t capacity_ = CAPACITY;
	std::vector<std::vector<Element>> HashArr_;

	void rehash();
	bool need_rehash() const;
	void ins(std::pair<Key, Val> const & data, std::vector<std::vector<Element>> & v);

	Element * fnd(Key const & key) {

		if (count_ == 0) {
			return nullptr;
		}

		std::size_t pos = Hasher_(key) % capacity_;
		std::size_t len_chain = HashArr_[pos].size();
		for (std::size_t i = 0; i < len_chain; ++i) {
			if (!(HashArr_[pos][i].is_empty_)) {
				if (Equal_(key, HashArr_[pos][i].data_.first)) {
					return &HashArr_[pos][i];
				}
			}
		}
		return nullptr;
	}
};

/////////////////////////////REALISE////////////////////////

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
Hash_Table_S_C<Key, Val, Hash, KeyEqual>::
Hash_Table_S_C() {

	HashArr_.assign(capacity_, std::vector<Element>());
	for (std::size_t i = 0; i < capacity_; ++i) {
		HashArr_[i].assign(1, Element());
	}
}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
Hash_Table_S_C<Key, Val, Hash, KeyEqual>::
Hash_Table_S_C(Hash_Table_S_C const & other)
	: count_{ other.count_ }
	, capacity_{ other.capacity_ } {

	HashArr_.assign(capacity_, std::vector<Element>());
	std::copy(other.HashArr_.begin(), other.HashArr_.end(), HashArr_.begin());
}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
void
Hash_Table_S_C<Key, Val, Hash, KeyEqual>::
swap(Hash_Table_S_C & other) {

	std::swap(count_, other.count_);
	std::swap(capacity_, other.capacity_);
	std::swap(HashArr_, other.HashArr_);
}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
Hash_Table_S_C<Key, Val, Hash, KeyEqual> &
Hash_Table_S_C<Key, Val, Hash, KeyEqual>::
operator=(Hash_Table_S_C const & other) {

	if (this != &other) {
		Hash_Table_S_C tmp(other);
		tmp.swap(*this);
	}
	return *this;
}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
Hash_Table_S_C<Key, Val, Hash, KeyEqual>::
Hash_Table_S_C(Hash_Table_S_C && other)
	: Hash_Table_S_C() {

	swap(other);
}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
Hash_Table_S_C<Key, Val, Hash, KeyEqual> &
Hash_Table_S_C<Key, Val, Hash, KeyEqual>::
operator=(Hash_Table_S_C && other) {

	swap(other);
	return *this;
}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
Hash_Table_S_C<Key, Val, Hash, KeyEqual>::
~Hash_Table_S_C() {

}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
bool
Hash_Table_S_C<Key, Val, Hash, KeyEqual>::
empty() const {

	return (count_ == 0);
}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
std::size_t
Hash_Table_S_C<Key, Val, Hash, KeyEqual>::
size() const {

	return count_;
}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
void
Hash_Table_S_C<Key, Val, Hash, KeyEqual>::
insert(Key const & key, Val const & val) {

	if (need_rehash()) {
		rehash();
	}
	ins(std::pair<Key, Val>(key, val), HashArr_);
	++count_;
}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
bool
Hash_Table_S_C<Key, Val, Hash, KeyEqual>::
find(Key const & key) const {

	if (count_ == 0) {
		return false;
	}
	
	std::size_t pos = Hasher_(key) % capacity_;
	std::size_t len_chain = HashArr_[pos].size();
	for (std::size_t i = 0; i < len_chain; ++i) {
		if (!(HashArr_[pos][i].is_empty_)) {
			if (Equal_(key, HashArr_[pos][i].data_.first)) {
				return true;
			}
		}
	}
	return false;
}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
void
Hash_Table_S_C<Key, Val, Hash, KeyEqual>::
erase(Key const & key) {

	Element * ptr = fnd(key);
	if (ptr != nullptr) {
		ptr->data_.~pair();
		ptr->is_empty_ = true;
		--count_;
	}
}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
void
Hash_Table_S_C<Key, Val, Hash, KeyEqual>::
clear() {

	HashArr_.clear();
	HashArr_.assign(CAPACITY, std::vector<Element>());
	for (std::size_t i = 0; i < CAPACITY; ++i) {
		HashArr_[i].assign(1, Element());
	}
	capacity_ = CAPACITY;
	count_ = 0;
}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
std::vector<std::pair<Key, Val> const *>
Hash_Table_S_C<Key, Val, Hash, KeyEqual>::
get_pairs_ref_vector() const {

	std::vector<std::pair<Key, Val> const *> v_ref;
	v_ref.assign(count_);
	std::size_t count = 0;
	for (std::size_t i = 0; i < capacity_) {
		std::size_t len_chain = HashArr_[i].size();
		for (std::size_t j = 0; j < len_chain; ++j) {
			if (!(HashArr_[i][j].is_empty_)) {
				v_ref[count] = &HashArr_[i][j].data_;
				++count;
			}
			if (count == count_) {
				break;
			}
		}
		if (count == count_) {
			break;
		}
	}

	return v_ref;
}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
Val
Hash_Table_S_C<Key, Val, Hash, KeyEqual>::
get_val(Key const & key) {

	Element * el = fnd(key);
	if (el == nullptr) {
		return Val();
	}
	return el->data_.second;
}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
Val &
Hash_Table_S_C<Key, Val, Hash, KeyEqual>::
operator[](Key const & key) {

	Element * el = fnd(key);
	if (el == nullptr) {
		insert(key, Val());
		el = fnd(key);
	}
	return el->data_.second;
}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
Val
Hash_Table_S_C<Key, Val, Hash, KeyEqual>::
operator[](Key const & key) const {

	std::size_t pos = Hasher_(key) % capacity_;
	std::size_t len_chain = HashArr_[pos].size();
	for (std::size_t i = 0; i < len_chain; ++i) {
		if (!(HashArr_[pos][i].is_empty_)) {
			if (Equal_(key, HashArr_[pos][i].data_.first)) {
				return HashArr_[pos][i].data_.second;
			}
		}
	}
	return Val();
}


////private

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
bool
Hash_Table_S_C<Key, Val, Hash, KeyEqual>::
need_rehash() const {

	return ((count_ * 1.0) / capacity_ >= load_factor_);
}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
void
Hash_Table_S_C<Key, Val, Hash, KeyEqual>::
rehash() {

	std::size_t new_capacity = capacity_ * 10;
	std::vector<std::vector<Element>> new_HashArr;
	new_HashArr.assign(new_capacity, std::vector<Element>());
	for (std::size_t i = 0; i < new_capacity; ++i) {
		new_HashArr[i].assign(1, Element());
	}
	for (std::size_t i = 0; i < capacity_; ++i) {
			std::size_t len_chain = HashArr_[i].size();
			for (std::size_t j = 0; j < len_chain; ++j) {
				if (!(HashArr_[i][j].is_empty_)) {
					ins(HashArr_[i][j].data_, new_HashArr);
			}
		}
	}
	HashArr_.swap(new_HashArr);
	capacity_ = new_capacity;
}

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>
>
void
Hash_Table_S_C<Key, Val, Hash, KeyEqual>::
ins(std::pair<Key, Val> const & data, std::vector<std::vector<Element>> & v) {

	std::size_t pos = Hasher_(data.first) % capacity_;
	if (v[pos][0].is_empty_) {
		v[pos][0].is_empty_ = false;
		v[pos][0].data_ = data;
	} else {
		std::size_t len_chain = v[pos].size();
		for (std::size_t i = 1; i < len_chain; ++i) {
			if (v[pos][i].is_empty_) {
				v[pos][i].is_empty_ = false;
				v[pos][i].data_ = data;
				return;
			}
		}
		v[pos].push_back(Element());
		v[pos][len_chain].data_ = data;
		v[pos][len_chain].is_empty_ = false;
	}
}

#endif // !HASH_TABLE_S_C_HPP