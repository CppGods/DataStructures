
#include <iostream>
#include <string>

template <class T, class keyT>
struct node_st
{
	node_st *left, *right;
	T value;
	keyT key;
	bool red;
	void Show(std::ostream &out, int level) const;
};


template <class T, class keyT, class Compare = std::less<keyT>>
class RBtree
{
	node_st <T, keyT> *tree_root;
	int nodes_count;
	Compare* comp_;
private:
	node_st <T, keyT>* NewNode(T value, keyT key);
	void DelNode(node_st<T, keyT>*);
	void Clean(node_st<T, keyT>*);
	node_st <T, keyT>* Rotate21(node_st<T, keyT>* node);
	node_st <T, keyT>* Rotate12(node_st<T, keyT>* node);
	void BalanceInsert(node_st<T, keyT>**);
	bool BalanceRemove1(node_st<T, keyT>**);
	bool BalanceRemove2(node_st<T, keyT>**);
	bool Insert(T&, keyT&, node_st<T, keyT>**);
	bool GetMin(node_st<T, keyT>**, node_st<T, keyT>**);
	bool Remove(node_st<T, keyT>**, keyT&);
	bool isEqual(node_st<T, keyT>* root2, const node_st<T, keyT>* root1);
	void swap(RBtree<T, keyT, Compare> & other);

public:
	bool isEmpty();
	void Show(std::ostream &out) const;
	RBtree(std::initializer_list<std::pair<T, keyT>> list);
	RBtree();
	~RBtree();
	void Clean();
	node_st<T, keyT>* search(const keyT& k) const;
	void Insert(T, keyT);
	void Remove(keyT);
	int GetNodesCount() const;
	bool operator ==(const RBtree<T, keyT> &a)
	{

		return isEqual(tree_root, a.tree_root);
	}
};

template <class T, class keyT, class Compare>
node_st <T, keyT>* RBtree<T, keyT, Compare>::NewNode(T value, keyT key)
{
	node_st <T, keyT> * node = new node_st <T, keyT>;
	node->value = value;
	node->key = key;
	node->left = nullptr;
	node->right = nullptr;
	node->red = true;
	nodes_count++;
	return node;
}

template <class T, class keyT, class Compare>
void RBtree<T, keyT, Compare>::DelNode(node_st<T, keyT>* node)
{
	nodes_count--;
	delete node;
}

template <class T, class keyT, class Compare >
void RBtree<T, keyT, Compare>::Clean(node_st <T, keyT> *node)
{
	if (!node) return;
	Clean(node->left);
	Clean(node->right);
	DelNode(node);
}

template <class T, class keyT, class Compare>
node_st<T, keyT>* RBtree<T, keyT, Compare>:: Rotate21(node_st<T, keyT>* node)
{
	node_st <T, keyT> *right = node->right;
	node_st <T, keyT> *root_st = right->left;
	right->left = node;
	node->right = root_st;
	return right;
}

template <class T, class keyT, class Compare>
node_st<T, keyT>* RBtree<T, keyT, Compare>::Rotate12(node_st<T, keyT>* node)
{
	node_st <T, keyT> *left = node->left;
	node_st <T, keyT> *root_st = left->right;
	left->right = node;
	node->left = root_st;
	return left;
}

template <class T, class keyT, class Compare>
void RBtree<T, keyT, Compare>::BalanceInsert(node_st<T, keyT> **root)
{
	node_st <T, keyT> *left, *right, *lx1, *rx1;
	node_st <T, keyT> *node = *root;
	if (node->red) return;
	left = node->left;
	right = node->right;
	if (left && left->red)
	{
		rx1 = left->right;
		if (rx1 && rx1->red) left = node->left = Rotate21(left);
		lx1 = left->left;
		if (lx1 && lx1->red) {
			node->red = true;
			left->red = false;
			if (right && right->red) {
				lx1->red = true;
				right->red = false;
				return;
			}
			*root = Rotate12(node);
			return;
		}
	}

	if (right && right->red) {
		lx1 = right->left;
		if (lx1 && lx1->red) right = node->right = Rotate12(right);
		rx1 = right->right;
		if (rx1 &&rx1->red) {
			node->red = true;
			right->red = false;
			if (left && left->red) {
				rx1->red = true;
				left->red = false;
				return;
			}
			*root = Rotate21(node);
			return;
		}
	}
}

template <class T, class keyT, class Compare >
bool  RBtree<T, keyT, Compare>::BalanceRemove1(node_st<T, keyT>  **root)
{
	node_st<T, keyT>  *node = *root;
	node_st<T, keyT>  *left = node->left;
	node_st<T, keyT>  *right = node->right;
	if (left && left->red)
	{
		left->red = false;
		return false;
	}
	if (right && right->red)
	{
		node->red = true;
		right->red = false;
		node = *root = Rotate21(node);
		if (BalanceRemove1(&node->left)) node->left->red = false;
		return false;
	}

	unsigned int mask = 0;
	node_st<T, keyT>  *p21 = right->left;
	node_st<T, keyT>  *p22 = right->right;
	if (p21 && p21->red) mask |= 1;
	if (p22 && p22->red) mask |= 2;
	switch (mask)
	{
	case 0:
		right->red = true;
		return true;
	case 1:
	case 3:
		right->red = true;
		p21->red = false;
		right = node->right = Rotate12(right);
		p22 = right->right;
	case 2:
		right->red = node->red;
		p22->red = node->red = false;
		*root = Rotate21(node);
	}
	return false;
}

template <class T, class keyT, class Compare>
bool  RBtree<T, keyT, Compare>::BalanceRemove2(node_st<T, keyT>  **root)
{
	node_st<T, keyT> *node = *root;
	node_st<T, keyT> *left = node->left;
	node_st <T, keyT> *right = node->right;
	if (right && right->red)
	{
		right->red = false;
		return false;
	}
	if (left && left->red) {
		node->red = true;
		left->red = false;
		node = *root = Rotate12(node);
		if (BalanceRemove2(&node->right)) node->right->red = false;
		return false;
	}
	unsigned int mask = 0;
	node_st <T, keyT> *p11 = left->left;
	node_st <T, keyT> *p12 = left->right;
	if (p11 && p11->red) mask |= 1;
	if (p12 && p12->red) mask |= 2;
switch (mask) {
case 0:
	left->red = true;
	return true;
case 2:
case 3:
	left->red = true;
	p12->red = false;
	left = node->left = Rotate21(left);
	p11 = left->left;
case 1:
	left->red = node->red;
	p11->red = node->red = false;
	*root = Rotate12(node);
}
return false;
}

template <class T, class keyT, class Compare>
bool  RBtree<T, keyT, Compare>::Insert(T &value, keyT &key, node_st<T, keyT>  **root)
{
	node_st <T, keyT> *node = *root;
	if (!node) *root = NewNode(value, key);
	else {
		bool is_r = ((!(*comp_)(key, node->key)) && (!(*comp_)(node->key, key)));
		if (is_r) return true;
		if (Insert(value, key, key < node->key ? &node->left : &node->right)) return true;
		BalanceInsert(root);
	}
	return false;
}

template <class T, class keyT, class Compare>
bool  RBtree<T, keyT, Compare>::GetMin(node_st<T, keyT>  **root, node_st<T, keyT>  **res)
{
	node_st<T, keyT>  *node = *root;
	if (node->left) {
		if (GetMin(&node->left, res)) return BalanceRemove1(root);
	}
	else {
		*root = node->right;
		*res = node;
		return !node->red;
	}
	return false;
}

template <class T, class keyT, class Compare>
bool  RBtree<T, keyT, Compare>::Remove(node_st<T, keyT>  **root, keyT &key)
{
	node_st<T, keyT> *t, *node = *root;
	if (!node) return false;
	if ((*comp_)(node->key, key))
	{
		if (Remove(&node->right, key))
			return BalanceRemove2(root);
	}
	else if ((*comp_)(key, node->key))
	{
		if (Remove(&node->left, key))	return BalanceRemove1(root);
	}
	else {
		bool res;
		if (!node->right) {
			*root = node->left;
			res = !node->red;
		}
		else {
			res = GetMin(&node->right, root);
			t = *root;
			t->red = node->red;
			t->left = node->left;
			t->right = node->right;
			if (res) res = BalanceRemove2(root);
		}
		DelNode(node);
		return res;
	}
	return 0;
}

template <class T, class keyT, class Compare>
bool RBtree<T, keyT, Compare>::isEqual(node_st<T, keyT>* root2, const node_st<T, keyT>* root1)
{
	return (root2&&root1 ? root2->value == root1->value&& root2->key == root1->key&&isEqual(root2->left, root1->left) && isEqual(root2->right, root1->right) : !root2 && !root1);
};

template <class T, class keyT, class Compare>
bool RBtree<T, keyT, Compare>::isEmpty()
{
	node_st<T, keyT>* root1 = nullptr;
	return isEqual(tree_root, root1);
}

template <class T, class keyT, class Compare>
void RBtree<T, keyT, Compare>::Show(std::ostream &out) const
{
	tree_root->Show(out, 0);
}

template <class T, class keyT, class Compare>
RBtree<T, keyT, Compare>::RBtree(std::initializer_list<std::pair<T, keyT>> list)
{
	tree_root = nullptr;
	nodes_count = 0;

	for (auto& item : list)
	{
		Insert(item.first, item.second);
	}
}

template <class T, class keyT, class Compare>
RBtree<T, keyT, Compare>::RBtree()
{
	comp_ = new Compare();
	tree_root = nullptr;
	nodes_count = 0;
}


template <class T, class keyT, class Compare>
RBtree<T, keyT, Compare>::~RBtree()
{
	Clean(tree_root);
}
template <class T, class keyT, class Compare>
int RBtree<T, keyT, Compare>::GetNodesCount() const
{
	return nodes_count;
}

template <class T, class keyT>
void node_st<T, keyT>::Show(std::ostream &out, int level) const
{
	const node_st<T, keyT>*tr = this;

	if (tr) tr->right->Show(out, level + 1);
	for (int i = 0; i<level; i++)
		out << "   ";

	if (tr)
	{
		std::string is_red = "black";
		if (red) is_red = "red";
		out << tr->value<<" "<<tr->key << "\n";
		for (int i = 0; i<level; i++)
			out << "   ";
		out << is_red <<std::endl;
	}
	else out << "End" << std::endl;
	if (tr) tr->left->Show(out, level + 1);
}

template <class T, class keyT, class Compare>
void RBtree<T, keyT, Compare>::Insert(T value, keyT key)
{
	Insert(value, key, &tree_root);
	if (tree_root) tree_root->red = false;
}	

template <class T, class keyT, class Compare>
void RBtree<T, keyT, Compare>::Remove(keyT key)
{
	Remove(&tree_root, key);
}

template <class T, class keyT, class Compare>
void RBtree<T, keyT, Compare>::Clean()
{
	Clean(tree_root);
	tree_root = nullptr;
}

template <class T, class keyT, class Compare>
node_st<T, keyT>* RBtree<T, keyT, Compare>::search(const keyT& k) const
{
	node_st<T, keyT> * tr = tree_root;
	while (tr != nullptr)
	{
		if ((!(*comp_)(tr->key, k)) && (!(*comp_)(k, tr->key)))
			break;
		else
		{
			if ((*comp_)(tr->key, k))
				tr = tr->right;
			else tr = tr->left;
		}
	}
	return tr;
};


template<class T, class keyT, class Compare>
void RBtree<T, keyT, Compare>::swap(RBtree<T, keyT, Compare> & other)
{
	std::swap(tree_root, other.tree_root);
	std::swap(nodes_count, other.nodes_count);
	std::swap(comp_, other.comp_);
};
