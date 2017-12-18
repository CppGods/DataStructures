#ifndef SET_HPP
#define SET_HPP

#include <bst_tree.hpp>
#include <vector>
#include <utility>

template<class Key, class Compare = std::less<Key>>
class set {

public:

	class TSet_Bidiretional_Iterator
		: public std::iterator<std::bidirectional_iterator_tag, Key > {

		friend class set;

	private:

		TSet_Bidiretional_Iterator()
			: ptr_{ nullptr }
			, size_{ 0 }
			, pos_{ 0 } {

		}

	public:

		TSet_Bidiretional_Iterator( TSet_Bidiretional_Iterator const & other)
			: ptr_{ nullptr }
			, size_{ other.size_ }
			, pos_ { other.pos_ } {

			if (size_) {
				ptr_ = new const Key *[size_];
				for (std::size_t i = 0; i < size_; ++i) {
					ptr_[i] = other.ptr_[i];
				}
			}
		}

		bool operator!=( TSet_Bidiretional_Iterator const & other ) const {

			return ptr_[pos_] != other.ptr_[other.pos_];
		}

		bool operator==( TSet_Bidiretional_Iterator const & other ) const {

			return ptr_[pos_] == other.ptr_[other.pos_];
		}

		const Key & operator*() const {

			return *ptr_[pos_];
		}

		TSet_Bidiretional_Iterator & operator++() {

			++pos_;
			return *this;
		}

		TSet_Bidiretional_Iterator & operator--() {

			--pos_;
			return *this;
		}

		TSet_Bidiretional_Iterator & operator++(int) {

			TSet_Bidiretional_Iterator tmp(*this);
			++pos_;
			return tmp;
		}

		TSet_Bidiretional_Iterator & operator--(int) {

			TSet_Bidiretional_Iterator tmp(*this);
			--pos_;
			return tmp;
		}

		~TSet_Bidiretional_Iterator() {

			delete[] ptr_;
		}

	private:

		const Key  ** ptr_;
		std::size_t size_;
		std::size_t pos_;
	};

	TSet_Bidiretional_Iterator cbegin() const {

		TSet_Bidiretional_Iterator it;
		std::vector<const Key *> v_keys_ref = vector_keys_ref();
		std::size_t keys_size = v_keys_ref.size();
		it.size_ = keys_size + 1;
		it.ptr_ = new const Key *[it.size_];
		for (std::size_t i = 0; i < keys_size; ++i) {
			it.ptr_[i] = v_keys_ref[i];
		}
		it.ptr_[keys_size] = nullptr;

		return it;
	}

	TSet_Bidiretional_Iterator cend() const {

		TSet_Bidiretional_Iterator it;
		std::vector<const Key *> v_keys_ref = vector_keys_ref();
		std::size_t keys_size = v_keys_ref.size();
		it.size_ = keys_size + 1;
		it.ptr_ = new const Key *[it.size_];
		for (std::size_t i = 0; i < keys_size; ++i) {
			it.ptr_[i] = v_keys_ref[i];
		}
		it.ptr_[keys_size] = nullptr;
		it.pos_ = keys_size;

		return it;
	}
	

	set();
	set(set const & other);
	set(set && other);
	~set();
	void insert(Key const & value);
	std::size_t size() const;
	void clear();
	bool find(Key const & key) const;
	void erase(Key const & key);
	bool empty() const;
	void swap(set & other);

	template <class Args>
	void emplace(Args && args);

	set & operator=(set const & other);
	set & operator=(set && other);
	bool operator>(set const & other) const;
	bool operator<(set const & other) const;
	bool operator==(set const & other) const;
	bool operator>=(set const & other) const;
	bool operator<=(set const & other) const;
	bool operator!=(set const & other) const;

private:

	bst_tree<Key>* keys_;

	std::vector<const Key *> vector_keys_ref() const;
	void get_key(std::vector<const Key *> & vector, node<Key> const * from, std::size_t & cur) const;
};

////////////////////////////////////////REALISE////////////////////////////////////////


template<class Key, class Compare = std::less<Key>>
set<Key, Compare>::set() {

	keys_ = new bst_tree<Key, Compare>();
}

template<class Key, class Compare = std::less<Key>>
set<Key, Compare>::set(set<Key, Compare> && other) 
	: set() {

	swap(other);
}

template<class Key, class Compare = std::less<Key>>
set<Key, Compare>::set(set<Key, Compare> const & other) {

	keys_ = new bst_tree<Key, Compare>(*other.keys_);
}

template<class Key, class Compare = std::less<Key>>
set<Key, Compare>::~set() {

	delete keys_;
}

template<class Key, class Compare = std::less<Key>>
std::size_t set<Key, Compare>::size() const {

	return keys_->size();
}

template<class Key, class Compare = std::less<Key>>
void set<Key, Compare>::clear() {

	keys_->clear();
}


template<class Key, class Compare = std::less<Key>>
bool set<Key, Compare>::find(Key const & key) const {

	return keys_->is_node(key);
}

template<class Key, class Compare = std::less<Key>>
void set<Key, Compare>::erase(Key const & key) {

	keys_->erase(key);
}


template<class Key, class Compare = std::less<Key>>
bool set<Key, Compare>::empty() const {

	return size() == 0;
}


template<class Key, class Compare = std::less<Key>>
void set<Key, Compare>::insert(Key const & key) {

	if (find(key)) {
		return;
	}
	keys_->insert(key);
}

template<class Key, class Compare = std::less<Key>>
void set<Key, Compare>::swap(set & other) {

	std::swap(keys_, other.keys_);
}

template <class Key, class Compare = std::less<Key>>
template <class Args>
void
set<Key, Compare>::emplace(Args && args) {

	keys_->emplace(args);
}

template<class Key, class Compare = std::less<Key>>
set<Key, Compare> & set<Key, Compare>::operator=(set<Key, Compare>  && other) {

	swap(other);
	return *this;
}

template<class Key, class Compare = std::less<Key>>
set<Key, Compare> & set<Key, Compare>::operator=(set<Key, Compare> const & other) {

	if (this != &other) {
		set<Key, Compare> tmp(other);
		tmp.swap(*this);
	}
	return *this;
}

template<class Key, class Compare = std::less<Key>>
bool set<Key, Compare>::operator>=(set<Key, Compare> const & other) const {

	std::size_t sz_other = other.size();
	std::size_t sz_cur = size();
	if (sz_cur < sz_other) {
		return false;
	}
	if (sz_other == 0 ) {
		return true;
	}
	
	TSet_Bidiretional_Iterator const_it_this = cbegin();
	TSet_Bidiretional_Iterator const_it_last_other = other.cend();
	for (TSet_Bidiretional_Iterator it = other.cbegin(); it != const_it_last_other; ++it, ++const_it_this) {
		if (*it != *const_it_this) {
			return false;
		}
	}
	return true;
}

template<class Key, class Compare = std::less<Key>>
bool set<Key, Compare>::operator<=(set<Key, Compare> const & other) const {

	return (other >= *this);
}

template<class Key, class Compare = std::less<Key>>
bool set<Key, Compare>::operator==(set<Key, Compare> const & other) const {

	return ((*this >= other) && (other >= *this));
}

template<class Key, class Compare = std::less<Key>>
bool set<Key, Compare>::operator>(set<Key, Compare> const & other) const {

	return ((*this >= other) && (!(*this <= other)));
}

template<class Key, class Compare = std::less<Key>>
bool set<Key, Compare>::operator<(set<Key, Compare> const & other) const {

	return (other > *this);
}

template<class Key, class Compare = std::less<Key>>
bool set<Key, Compare>::operator!=(set<Key, Compare> const & other) const {

	return !(*this == other);
}

////private

template<class Key, class Compare = std::less<Key>>
std::vector<const Key *> set<Key, Compare>::vector_keys_ref() const {

	std::vector<const Key *> vector;
	if ((keys_->top() == nullptr)) {
		return vector;
	}
	std::size_t i = 0;
	get_key(vector, keys_->top(), i);

	return vector;
}

template<class Key, class Compare = std::less<Key>>
void set<Key, Compare>::get_key(std::vector<const Key *> & vector, node<Key> const * from, std::size_t & cur) const {

	if (from->child_1_ != nullptr) {
		get_key(vector, from->child_1_, cur);
	}

	if (cur == size()) {
		return;
	}

	vector.push_back(&from->data_);
	++cur;

	if (from->child_2_ != nullptr) {
		get_key(vector, from->child_2_, cur);
	}

}

#endif //!SET_HPP