#include"bst_tree.hpp"
#include<vector>

template<class Key, class Compare = std::less<Key>>
class set {

public:

	set();

	set(set const & other);

	~set();

	void insert(Key const & value);

	std::size_t size() const;

	void clear();

	bool find(Key const & key) const;

	void erase(Key const & key);

	bool empty() const;

	void swap(set & other);

	std::vector<Key> vector_keys(std::size_t const max) const;

	set & operator=(set const & other);

	bool operator>(set const & other) const;

	bool operator<(set const & other) const;

	bool operator==(set const & other) const;

	bool operator>=(set const & other) const;

	bool operator<=(set const & other) const;

private:

	bst_tree<Key>* keys_;

	void get_key(std::vector<Key> & list, node<Key> const * from, std::size_t & cur, std::size_t const max) const;
};

////////////////////////////////////////REALISE////////////////////////////////////////

template<class Key, class Compare = std::less<Key>>
set<Key, Compare>::set() {

	keys_ = new bst_tree<Key, Compare>();
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

template<class Key, class Compare = std::less<Key>>
std::vector<Key> set<Key, Compare>::vector_keys(std::size_t const max) const {

	std::vector<Key> vector;
	if ((max == 0) || (keys_->top() == nullptr)) {
		return vector;
	}
	std::size_t i = 0;
	get_key(vector, keys_->top(), i, max);
	
	return vector;
}

template<class Key, class Compare = std::less<Key>>
void set<Key, Compare>::get_key(std::vector<Key> & vector, node<Key> const * from, std::size_t & cur, std::size_t const max) const {
	
	if (from->child_1_ != nullptr) {
		get_key(vector, from->child_1_, cur, max);
	}

	if ((cur == max) || (cur == size())) {
		return;
	}

	vector.push_back(from->data_);
	++cur;

	if (from->child_2_ != nullptr) {
		get_key(vector, from->child_2_, cur, max);
	}
	
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
	if (sz_cur == 0 || sz_other == 0) {
		return true;
	}
	std::vector<Key> vector = other.vector_keys(sz_other);
	for (std::size_t i = 0; i < sz_other; ++i) {
		if (find(vector[i]) == false) {
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