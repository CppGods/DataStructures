template<typename T>
struct node {

	T data_;
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

	void pop_all_with(const Ty& value, node<Ty>** this_ = &root_);

	const node<Ty>* is_node(const Ty& value) const;

	size_t size() const;

	void clear(node<Ty>* this_ = root_);
 
	bst_tree& operator=(const bst_tree& other);

private:
  
	node<Ty>* root_;
	size_t count_;

	void create_node(node<Ty>*& this_, const Ty& value);

	void copy_nodes(node<Ty>*& dest, const node<Ty>* src);

	void del(node<Ty>** this_);
};

//////////////////////////////////REALISE//////////////////////////////

template<class Ty>
void bst_tree<Ty>::create_node(node<Ty>*& this_, const Ty& value) {

	this_ = new node<Ty>();
	this_->data = value;
	this_->child_1_ = nullptr;
	this_->child_2_ = nullptr;
	++count_;
}

template<class Ty>
void bst_tree<Ty>::copy_nodes(node<Ty>*& dest, const node<Ty>* src) {

	if (src != nullptr) {
		create_node(dest, src->data_);
		copy_nodes(dest->child_1_, src->child_1_);
		copy_nodes(dest->child_2_, src->child_2_);
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
	count_{other->count_} {

	if (count_ == 0) {
		root_ = nullptr;
	} else {
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
bst_tree<Ty>::clear(node<Ty>* this_ = root_) {

	if (this_->child_1_ != nullptr) {
		clear(this_->child_1_);
	}
	if (this_->child_2_ != nullptr) {
		clear(this_->child_2_);
	}
	--count_;
	delete this_;
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
const node<Ty>* bst_tree<Ty>::is_node(const Ty& value) const {

	node<Ty> *cur = root_;

	while (cur != nullptr) {
		if (cur->data_ == value) {
			return cur;
		}
		if (value < cur->data_) {
			cur = cur->child_1_;
		} else {
			cur = cur->child_2_;
		}
	}

	return nullptr;
}

template<class Ty>
size_t bst_tree<Ty>::size() const {

	return count_;
}

template<class Ty>
void bst_tree<Ty>::del(node<Ty>** this_) {

	node<Ty>* left_leaf = *this_;
	if ((*this_)->child_2_ == nullptr) {
		*this_ = left_leaf->child_1_;
	} else {
		left_leaf = left_leaf->child_2_;
		while (left_leaf->child_1_ != nullptr) {
			left_leaf = left_leaf->child_1_;
		}
		left_leaf->child_1_ = (*this_)->child_1_;
		left_leaf = *this_;
		*this_ = left_leaf->child_2_;
	}
	delete left_leaf;
}

template<class Ty>
void bst_tree<Ty>::pop_all_with(const Ty& value, node<Ty>** this_ = &root_) {

	while (*this_ != nullptr && (*this_)->data_ == value) {
		del(this_);
		--count_;
	}

	if (*this_ = nullptr) {
		return;
	}

	if (value > (*this_)->data_) {
		pop_all_with(value, (*this_)->&child_2_);
	} else {
		pop_all_with(value, (*this_)->&child_1_);
	}
}

