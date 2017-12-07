#ifndef HASH_TABLE_O_A_HPP
#define HASH_TABLE_O_A_HPP

#include <utility>
#include <functional>
#include <vector>

//hash_table_using_open_addressing
//not unique values
//for set

#define CAPACITY 100
#define LOAD_FACTOR 0.5

template<
	class ValueType,
	class Hash = std::hash<ValueType>,
	class ValEqual = std::equal_to<ValueType>
> class Hash_Table_O_A {

public:

	struct Element {
		ValueType data_;
		bool is_empty_ = true;
	};
	
	Hash_Table_O_A();
	Hash_Table_O_A(Hash_Table_O_A const & other);
	Hash_Table_O_A(Hash_Table_O_A && other);
	Hash_Table_O_A & operator=(Hash_Table_O_A const & other);
	Hash_Table_O_A & operator=(Hash_Table_O_A && other);
	~Hash_Table_O_A();
	void swap(Hash_Table_O_A & other);

	void insert(ValueType const & val);
	bool find(ValueType const & val) const;
	void erase(ValueType const & val);
	void clear();
	bool empty() const;
	std::size_t size() const;

private:

	Hash Hasher_;
	ValEqual Equal_;
	float const load_factor_ = LOAD_FACTOR;

	std::size_t count_ = 0;
	std::size_t capacity_ = CAPACITY;
    std::vector<Element> HashArr_;

	void rehash();
	bool need_rehash();
	bool ins(ValueType const & val, std::vector<Element> & v);
	Element * fnd(ValueType const & val) {

		if (count_ == 0) {
			return nullptr;
		}

		std::size_t k = 1; //GCD(k, capacity_) = 1
		std::size_t i = 0;
		std::size_t pos = Hasher_(val) % capacity_;
		do {
			if (!HashArr_[pos].is_empty_) {
				if (Equal_(val, HashArr_[pos].data_)) {
					return &HashArr_[pos];
				}
			}
			++i;
			pos = (pos + i * k) % capacity_;
		} while (i < capacity_);

		return nullptr;
	}

};

/////////////////////////////REALISE////////////////////////

template<
	class ValueType,
	class Hash = std::hash<ValueType>,
	class ValEqual = std::equal_to<ValueType>
>	
Hash_Table_O_A<ValueType, Hash, ValEqual>::
Hash_Table_O_A() {

	HashArr_.assign(capacity_, Element());
}

template<
	class ValueType,
	class Hash = std::hash<ValueType>,
	class ValEqual = std::equal_to<ValueType>
>	
Hash_Table_O_A<ValueType, Hash, ValEqual>::
Hash_Table_O_A(Hash_Table_O_A const & other)
	: count_{ other.count_ }
	, capacity_{ other.capacity_ } {

	HashArr_.assign(capacity_, Element());
	std::copy(other.HashArr_.begin(), other.HashArr_.end(), HashArr_.begin());
}

template<
	class ValueType,
	class Hash = std::hash<ValueType>,
	class ValEqual = std::equal_to<ValueType>
>
void
Hash_Table_O_A<ValueType, Hash, ValEqual>::
swap(Hash_Table_O_A & other) {

	std::swap(count_, other.count_);
	std::swap(capacity_, other.capacity_);
	std::swap(HashArr_, other.HashArr_);
}

template<
	class ValueType,
	class Hash = std::hash<ValueType>,
	class ValEqual = std::equal_to<ValueType>
>
Hash_Table_O_A<ValueType, Hash, ValEqual> &
Hash_Table_O_A<ValueType, Hash, ValEqual>::
operator=(Hash_Table_O_A const & other) {

	if (this != &other) {
		Hash_Table_O_A tmp(other);
		tmp.swap(*this);
	}
	return *this;
}

template<
	class ValueType,
	class Hash = std::hash<ValueType>,
	class ValEqual = std::equal_to<ValueType>
>
Hash_Table_O_A<ValueType, Hash, ValEqual>::
Hash_Table_O_A(Hash_Table_O_A && other)
	: Hash_Table_O_A() {

	swap(other);
}

template<
	class ValueType,
	class Hash = std::hash<ValueType>,
	class ValEqual = std::equal_to<ValueType>
>
Hash_Table_O_A<ValueType, Hash, ValEqual> &
Hash_Table_O_A<ValueType, Hash, ValEqual>::
operator=(Hash_Table_O_A && other) {

	swap(other);
	return *this;
}

template<
	class ValueType,
	class Hash = std::hash<ValueType>,
	class ValEqual = std::equal_to<ValueType>
>
Hash_Table_O_A<ValueType, Hash, ValEqual>::
~Hash_Table_O_A() {

}

template<
	class ValueType,
	class Hash = std::hash<ValueType>,
	class ValEqual = std::equal_to<ValueType>
>
void
Hash_Table_O_A<ValueType, Hash, ValEqual>::
clear() {

	HashArr_.clear();
	HashArr_.assign(CAPACITY, Element());
	capacity_ = CAPACITY;
	count_ = 0;
}

template<
	class ValueType,
	class Hash = std::hash<ValueType>,
	class ValEqual = std::equal_to<ValueType>
>
bool
Hash_Table_O_A<ValueType, Hash, ValEqual>::
empty() const {

	return count_ == 0;
}

template<
	class ValueType,
	class Hash = std::hash<ValueType>,
	class ValEqual = std::equal_to<ValueType>
>
std::size_t
Hash_Table_O_A<ValueType, Hash, ValEqual>::
size() const {

	return count_;
}

template<
	class ValueType,
	class Hash = std::hash<ValueType>,
	class ValEqual = std::equal_to<ValueType>
>
void
Hash_Table_O_A<ValueType, Hash, ValEqual>::
insert(ValueType const & val) {

	if (need_rehash()) {
		rehash();
	}
	if (ins(val, HashArr_)) {
		++count_;
	}
}

template<
	class ValueType,
	class Hash = std::hash<ValueType>,
	class ValEqual = std::equal_to<ValueType>
>
bool
Hash_Table_O_A<ValueType, Hash, ValEqual>::
find(ValueType const & val) const {

	if (count_ == 0) {
		return false;
	}
	std::size_t k = 1; //GCD(k, capacity_) = 1
	std::size_t i = 0;
	std::size_t pos = Hasher_(val) % capacity_;
	do {
		if (!HashArr_[pos].is_empty_) {
			if (Equal_(val, HashArr_[pos].data_)) {
				return true;
			}
		}
		++i;
		pos = (pos + i * k) % capacity_;
	} while (i < capacity_);
	return false;
}

template<
	class ValueType,
	class Hash = std::hash<ValueType>,
	class ValEqual = std::equal_to<ValueType>
>
void
Hash_Table_O_A<ValueType, Hash, ValEqual>::
erase(ValueType const & val) {

	Element * ptr = fnd(val);
	if (ptr != nullptr) {
		ptr->data_.~ValueType();
		ptr->is_empty_ = true;
		--count_;
	}
}

template<
	class ValueType,
	class Hash = std::hash<ValueType>,
	class ValEqual = std::equal_to<ValueType>
>
void
Hash_Table_O_A<ValueType, Hash, ValEqual>::
rehash() {

	std::size_t new_capacity = capacity_ * 10;
	std::vector<Element> new_HashArr;
	new_HashArr.assign(new_capacity, Element());
	for (std::size_t i = 0; i < capacity_; ++i) {
		if (!(HashArr_[i].is_empty_)) {
			ins(HashArr_[i].data_, new_HashArr);
		}
	}
	HashArr_.swap(new_HashArr);
	capacity_ = new_capacity;
}

template<
	class ValueType,
	class Hash = std::hash<ValueType>,
	class ValEqual = std::equal_to<ValueType>
>
bool
Hash_Table_O_A<ValueType, Hash, ValEqual>::
ins(ValueType const & val, std::vector<Element> & v) {

	std::size_t k = 1; //GCD(k, capacity_) = 1
	std::size_t i = 0;
	std::size_t pos = Hasher_(val) % capacity_;
	do {
		if (v[pos].is_empty_) {
			v[pos].data_ = val;
			v[pos].is_empty_ = false;
			return true;
		}
		++i;
		pos = (pos + i * k) % capacity_;
	} while (i < capacity_);

	return false;
}

template<
	class ValueType,
	class Hash = std::hash<ValueType>,
	class ValEqual = std::equal_to<ValueType>
>
bool
Hash_Table_O_A<ValueType, Hash, ValEqual>::
need_rehash() {

	return ((count_ * 1.0) / capacity_ >= load_factor_);
}

#endif // !HASH_TABLE_O_A_HPP