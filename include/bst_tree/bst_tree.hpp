#ifndef BST_TREE_HPP
#define BST_TREE_HPP

template<class Key, class Compare = std::less<Key>>
class set;

template<class Ty>
struct node {

	Ty data_;
	node* child_1_;
	node* child_2_;
};


template<class Ty>
class bst_tree {

public:

	bst_tree();
  
	bst_tree(const bst_tree& other);
  
	~bst_tree();

	void insert(const Ty& value);

	void erase(const Ty& value);

	bool is_node(const Ty& value) const;

	std::size_t size() const;

	void clear();
 
	bst_tree& operator=(const bst_tree& other);

private:
  
	node<Ty>* root_;

	std::size_t count_;

	void create_node(node<Ty>*& cur, const Ty& value);

	void copy_nodes(node<Ty>*& dest, const node<Ty>* src);

	void del_node(node<Ty>*& cur);

	void rm(node<Ty>* cur);

	node<Ty>** parent(const Ty& value);

	template<class Key, class Compare = std::less<Key>>
	friend class set;

};

//////////////////////////////////REALISE//////////////////////////////

template<class Ty>
void bst_tree<Ty>::create_node(node<Ty>*& cur, const Ty& value) {

	cur = new node<Ty>();
	cur->data_ = value;
	cur->child_1_ = nullptr;
	cur->child_2_ = nullptr;
	++count_;
}

template<class Ty>
void bst_tree<Ty>::copy_nodes(node<Ty>*& dest, const node<Ty>* src) {

	if (src != nullptr) {
		create_node(dest, src->data_);
		copy_nodes(dest->child_1_, src->child_1_);
		copy_nodes(dest->child_2_, src->child_2_);
	} else {
		dest = nullptr;
	}
}

template<class Ty>
bst_tree<Ty>::bst_tree()
	:
	root_{ nullptr },
	count_{ 0 } {


}

template<class Ty>
bst_tree<Ty>::bst_tree(const bst_tree<Ty>& other)
	:
	count_{ 0 } {

	if (other.count_ == 0) {
		root_ = nullptr;
	} else {
		count_ = other.count_();
		copy_nodes(root_, other.root_);
	}

}

template<class Ty>
bst_tree<Ty>& bst_tree<Ty>::operator=(const bst_tree<Ty>& other) {

	if (this != &other) {
		clear();
		copy_nodes(root_, other.root_);
	}
	return *this;
}


template<class Ty>
bst_tree<Ty>::~bst_tree() {

	clear();
}

template<class Ty>
void bst_tree<Ty>::clear() {
	
	if (root_ != nullptr) {
		rm(root_);
		root_ = nullptr;
	}
}

template<class Ty>
void bst_tree<Ty>::rm(node<Ty>* cur) {

	if (cur->child_1_ != nullptr) {
		rm(cur->child_1_);
	}
	if (cur->child_2_ != nullptr) {
		rm(cur->child_2_);
	}

	delete cur;
	--count_;
}

template<class Ty>
void bst_tree<Ty>::insert(const Ty& value) {

	if (root_ == nullptr) {
		create_node(root_, value);
	} else {
		node<Ty>* cur = root_;
		do {
			if (value < cur->data_) {
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

template<class Ty>
bool bst_tree<Ty>::is_node(const Ty& value) const {

	node<Ty> *cur = root_;

	while (cur != nullptr) {
		if (cur->data_ == value) {
			return true;
		}
		if (value < cur->data_) {
			cur = cur->child_1_;
		} else {
			cur = cur->child_2_;
		}
	}

	return false;
}

template<class Ty>
size_t bst_tree<Ty>::size() const {

	return count_;
}

template<class Ty>
void bst_tree<Ty>::del_node(node<Ty>*& cur) {

	if (cur == nullptr) {
		return;
	}

	node<Ty>* left_leaf = cur;
	if (left_leaf->child_2_ == nullptr) {
		if (left_leaf->child_1_ == nullptr) {
			delete left_leaf;
			cur = nullptr;
			--count_;
			return;
		} else {
			left_leaf = left_leaf->child_1_;
		}
	} else {
		left_leaf = left_leaf->child_2_;
	}
	while (left_leaf->child_1_ != nullptr) {
		left_leaf = left_leaf->child_1_;
	}
	left_leaf->child_1_ = cur->child_1_;
	left_leaf = cur;
	cur = cur->child_2_;
	delete left_leaf;
	--count_;
}

template<class Ty>
node<Ty>** bst_tree<Ty>::parent(const Ty& value) {
	
	if (count_ == 0) {
		return nullptr;
	}

	node<Ty>*& cur = root_;
	while ((cur != nullptr) && (cur->data_ != value)) {
		if (cur->data_ < value) {
			cur = cur->child_2_;
		} else {
			cur = cur->child_1_;
		}
	}

	return &cur;
}

template<class Ty>
void bst_tree<Ty>::erase(const Ty& value) {
	
	if (count_ == 0) {
		return;
	}
	node<Ty>*& cur = *parent(value);
	del_node(cur);
}

#endif // !BST_TREE_HPP