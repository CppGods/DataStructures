#include"include\bst_tree\bst_tree.hpp"

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

	std::size_t list_keys(Key * list, std::size_t const count) const;

	set & operator=(set const & other);

	bool operator>(set const & other);

	bool operator<(set const & other);

	bool operator==(set const & other);

	bool operator>=(set const & other);

	bool operator<=(set const & other);

private:

	bst_tree<Key>* keys_;

	Compare* key_comp_;

	void get_key(Key * list, node<Key> const * from, std::size_t & cur, std::size_t const max);
};

////////////////////////////////////////REALISE////////////////////////////////////////

template<class Key, class Compare = std::less<Key>>
set<Key, Compare>::set() {

	keys_ = new bst_tree<Key>();
	key_comp_ = new Compare();
}

template<class Key, class Compare = std::less<Key>>
set<Key, Compare>::set(set<Key, Compare> const & other) {

	keys_ = new bst_tree<Key>(*other.keys_);
	key_comp_ = new Compare(*other.key_comp_);
}

template<class Key, class Compare = std::less<Key>>
set<Key, Compare>::~set() {

	delete keys_;
	delete key_comp_;
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

	if (size() == 0) {
		return;
	}

	node<Key>** cur = &keys_->root_;
	while (((*cur) != nullptr) && ((*cur)->data_ != key)) {
		if ((*key_comp_)((*cur)->data_, key)) {
			cur = &(*cur)->child_2_;
		} else {
			cur = &(*cur)->child_1_;
		}
	}
	keys_->del_node(*cur);
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

	if (keys_->root_ == nullptr) {
		keys_->create_node(keys_->root_, key);
	} else {
		node<Key>* cur = keys_->root_;
		do {
			if ((*key_comp_)(key, cur->data_)) {
				if (cur->child_1_ == nullptr) {
					keys_->create_node(cur->child_1_, key);
					break;
				}
				cur = cur->child_1_;
			} else {
				if (cur->child_2_ == nullptr) {
					keys_->create_node(cur->child_2_, key);
					break;
				}
				cur = cur->child_2_;
			}
		} while (true);
	}
}

template<class Key, class Compare = std::less<Key>>
void set<Key, Compare>::swap(set & other) {

	std::swap(keys_, other.keys_);
	std::swap(key_copm_, other.key_comp);
}

template<class Key, class Compare = std::less<Key>>
std::size_t set<Key, Compare>::list_keys(Key * list, std::size_t const count) const {

	if (size() < count || count == 0 || list == nullptr) {
		return 0;
	}
	std::size_t i = 0;
	get_key(list, keys_->root_, i, count);
	
	return i;
}

template<class Key, class Compare = std::less<Key>>
void set<Key, Compare>::get_key(Key * list, node<Key> const * from, std::size_t & cur, std::size_t const max) {
	
	if (cur == 0) {
		return;
	}

	if (from->child_1_ != nullptr) {
		get_key(list, from->child_1_, cur, max);
	}

	if ((cur == max) || (cur == size())) {
		return;
	}

	list[cur] = from->data_;
	++cur;

	if (from->child_2_ != nullptr) {
		get_key(list, from->child_2_, cur, max);
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
bool set<Key, Compare>::operator>=(set<Key, Compare> const & other) {

	std::size_t sz_other = other.size();
	std::size_t sz_cur = size()
	if (sz_cur < sz_other) {
		return false;
	}
	Key const * list = other.list_keys(sz_other);
	for (std::size_t i = 0; i < sz_other; ++i) {
		if (find(list[i]) == false) {
			return false;
		}
	}
	delete[] list;
	return true;
}

template<class Key, class Compare = std::less<Key>>
bool set<Key, Compare>::operator<=(set<Key, Compare> const & other) {

	return (other >= *this);
}

template<class Key, class Compare = std::less<Key>>
bool set<Key, Compare>::operator==(set<Key, Compare> const & other) {

	return ((*this >= other) && (other >= *this));
}

template<class Key, class Compare = std::less<Key>>
bool set<Key, Compare>::operator>(set<Key, Compare> const & other) {

	return ((*this >= other) && (!(*this <= other)));
}

template<class Key, class Compare = std::less<Key>>
bool set<Key, Compare>::operator<(set<Key, Compare> const & other) {

	return (other > *this);
}