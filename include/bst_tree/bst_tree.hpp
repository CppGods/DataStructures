#ifndef BST_TREE_HPP
#define BST_TREE_HPP

#include <utility>

template<class Ty>
struct node {

	Ty data_;
	node* child_1_;
	node* child_2_;
};

template<class Ty, class Compare = std::less<Ty>>
class bst_tree {

public:

	bst_tree();
	bst_tree(bst_tree const & other);
	bst_tree(bst_tree && other);
	~bst_tree();
	void swap(bst_tree & other);
	void insert(Ty const & value);
	void erase(Ty const & value);
	bool is_node(Ty const & value) const;
	std::size_t size() const;
	void clear();
	node<Ty> const * top() const;
	bst_tree & operator=(bst_tree const & other);
	bst_tree & operator=(bst_tree && other);

	template <class Args>
	void emplace(Args && args);

private:
  
	node<Ty> * root_;
	std::size_t count_;
	Compare * comp_;

	void create_node(node<Ty> *& cur, Ty const & value);
	void copy_nodes(node<Ty> *& dest, node<Ty> const * src);
	void del_node(node<Ty> *& ptr_on_cur);
	void rm(node<Ty> * cur);
	node<Ty> ** parent(Ty const & value);

	template <class Args>
	void emplace_node(node<Ty> *& cur, Args && args);
};

//////////////////////////////////REALISE//////////////////////////////


template<class Ty, class Compare = std::less<Ty>>
bst_tree<Ty, Compare>::bst_tree()
	: root_{ nullptr }
	, count_{ 0 } {

	comp_ = new Compare();
}

template<class Ty, class Compare = std::less<Ty>>
bst_tree<Ty, Compare>::bst_tree(bst_tree<Ty, Compare> const & other)
	: count_{ 0 } {

	if (other.count_ == 0) {
		root_ = nullptr;
	} else {
		copy_nodes(root_, other.root_);
	}
	comp_ = new Compare(*other.comp_);
}

template<class Ty, class Compare = std::less<Ty>>
bst_tree<Ty, Compare>::bst_tree(bst_tree<Ty, Compare> && other)
	: bst_tree() {

	swap(other);
}

template<class Ty, class Compare = std::less<Ty>>
void bst_tree<Ty, Compare>::swap(bst_tree<Ty, Compare> & other) {

	std::swap(root_, other.root_);
	std::swap(count_, other.count_);
}

template<class Ty, class Compare = std::less<Ty>>
node<Ty> const * bst_tree<Ty, Compare>::top() const {

	return root_;
}

template<class Ty, class Compare = std::less<Ty>>
bst_tree<Ty, Compare>& bst_tree<Ty, Compare>::operator=(bst_tree<Ty, Compare> const & other) {

	if (this != &other) {
		clear();
		copy_nodes(root_, other.root_);
	}
	return *this;
}

template<class Ty, class Compare = std::less<Ty>>
bst_tree<Ty, Compare>& bst_tree<Ty, Compare>::operator=(bst_tree<Ty, Compare> && other) {

	swap(other);
	return *this;
}

template<class Ty, class Compare = std::less<Ty>>
bst_tree<Ty, Compare>::~bst_tree() {

	clear();
	delete comp_;
}

template<class Ty, class Compare = std::less<Ty>>
void bst_tree<Ty, Compare>::clear() {
	
	if (root_ != nullptr) {
		rm(root_);
		root_ = nullptr;
	}
}

template<class Ty, class Compare = std::less<Ty>>
void bst_tree<Ty, Compare>::insert(Ty const & value) {

	if (root_ == nullptr) {
		create_node(root_, value);
	} else {
		node<Ty>* cur = root_;
		do {
			if ((*comp_)(value, cur->data_)) {
				if (cur->child_1_ == nullptr) {
					create_node(cur->child_1_, value);
					break;
				}
				cur = cur->child_1_;
			} else {
				if (cur->child_2_ == nullptr) {
					create_node(cur->child_2_, value);
					break;
				}
				cur = cur->child_2_;
			}
		} while (true);
	}
}

template<class Ty, class Compare = std::less<Ty>>
bool bst_tree<Ty, Compare>::is_node(Ty const & value) const {

	node<Ty> *cur = root_;

	while (cur != nullptr) {
		if (!((*comp_)(value, cur->data_) || (*comp_)(cur->data_, value))) {
			return true;
		}
		if ((*comp_)(value, cur->data_)) {
			cur = cur->child_1_;
		} else {
			cur = cur->child_2_;
		}
	}
	return false;
}

template<class Ty, class Compare = std::less<Ty>>
size_t bst_tree<Ty, Compare>::size() const {

	return count_;
}

template<class Ty, class Compare = std::less<Ty>>
void bst_tree<Ty, Compare>::erase(Ty const & value) {

	if (count_ == 0) {
		return;
	}
	node<Ty> ** ptr_on_cur = parent(value);
	if (*ptr_on_cur != nullptr) {
		del_node(*ptr_on_cur);
	}
}

template <class Ty, class Compare = std::less<Ty >>
template <class Args>
void
bst_tree<Ty, Compare>::emplace(Args && args) {

	if (root_ == nullptr) {
		emplace_node(root_, args);
	} else {
		node<Ty> * cur = root_;
		node<Ty> value;
		value.data_ = std::move(Ty(args));
		do {
			if ((*comp_)(value.data_, cur->data_)) {
				if (cur->child_1_ == nullptr) {
					emplace_node(cur->child_1_, args);
					break;
				}
				cur = cur->child_1_;
			} else {
				if (cur->child_2_ == nullptr) {
					emplace_node(cur->child_2_, args);
					break;
				}
				cur = cur->child_2_;
			}
		} while (true);
	}
}

template<class Ty, class Compare = std::less<Ty>>
void bst_tree<Ty, Compare>::create_node(node<Ty> *& cur, Ty const & value) {

	cur = new node<Ty>();
	cur->data_ = value;
	cur->child_1_ = nullptr;
	cur->child_2_ = nullptr;
	++count_;
}

template<class Ty, class Compare = std::less<Ty>>
void bst_tree<Ty, Compare>::copy_nodes(node<Ty> *& dest, node<Ty> const * src) {

	if (src != nullptr) {
		create_node(dest, src->data_);
		copy_nodes(dest->child_1_, src->child_1_);
		copy_nodes(dest->child_2_, src->child_2_);
	} else {
		dest = nullptr;
	}
}

template<class Ty, class Compare = std::less<Ty>>
void bst_tree<Ty, Compare>::rm(node<Ty> * cur) {

	if (cur->child_1_ != nullptr) {
		rm(cur->child_1_);
	}
	if (cur->child_2_ != nullptr) {
		rm(cur->child_2_);
	}
	delete cur;
	--count_;
}

template<class Ty, class Compare = std::less<Ty>>
void bst_tree<Ty, Compare>::del_node(node<Ty> *& ptr_on_cur) {

	node<Ty> * last_left_leaf_in_right = ptr_on_cur;
	if (last_left_leaf_in_right->child_2_ == nullptr) {
		ptr_on_cur = ptr_on_cur->child_1_;
		delete last_left_leaf_in_right;
		--count_;
		return;
	} else {
		last_left_leaf_in_right = last_left_leaf_in_right->child_2_;
	}
	while (last_left_leaf_in_right->child_1_ != nullptr) {
		last_left_leaf_in_right = last_left_leaf_in_right->child_1_;
	}
	last_left_leaf_in_right->child_1_ = ptr_on_cur->child_1_;
	last_left_leaf_in_right = ptr_on_cur;
	ptr_on_cur = ptr_on_cur->child_2_;
	delete last_left_leaf_in_right;
	--count_;
}

template<class Ty, class Compare = std::less<Ty>>
node<Ty>** bst_tree<Ty, Compare>::parent(Ty const & value) {

	node<Ty> ** cur = &root_;
	while ((*cur != nullptr) && ((*cur)->data_ != value)) {
		if ((*comp_)((*cur)->data_, value)) {
			cur = &(*cur)->child_2_;
		} else {
			cur = &(*cur)->child_1_;
		}
	}
	return cur;
}

template <class Ty, class Compare = std::less<Ty >>
template <class Args>
void
bst_tree<Ty, Compare>::emplace_node(node<Ty> *& cur, Args && args) {

	cur = new node<Ty>();
	cur->data_ = std::move(Ty(args));
	cur->child_1_ = nullptr;
	cur->child_2_ = nullptr;
	++count_;
}

#endif // !BST_TREE_HPP