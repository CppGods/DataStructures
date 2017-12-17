#include <iostream>
#include <utility>
template<typename Ty, typename T>
struct node
{
	node<Ty, T> * left, *right;
	Ty key;
	T value;
	size_t height;
	node<Ty, T>() : left{ nullptr }, right{ nullptr }, height{ 0 } {};
	node<Ty, T>(Ty && data, T && value_) : left{ nullptr }, value{ value_ }, right{ nullptr }, key{ std::move(data) }, height{ 1 } {};
	node<Ty, T>(Ty const &data, T const &value_) : left{ nullptr }, value{ value_ }, right{ nullptr }, key{ data }, height{ 1 } {};
};


template<typename Ty, typename T, class Compare = std::less<Ty>>
class avl_tree
{
private:
	node<Ty, T> * root;
	Compare *comp_;
	size_t count_;

private:
	/////copy///
	void copy_nodes(node<Ty, T> *&, node<Ty, T> const *);
	void create_node(node<Ty, T> *&, Ty const &, T const &);

	/////height helping///
	size_t height(node<Ty, T>* Node);
	int balance_factor(node<Ty, T>* Node);
	void fixheight(node<Ty, T>* Node);

	///////rotates//////
	node<Ty, T>* rotateright(node<Ty, T>*);
	node<Ty, T>* rotateleft(node<Ty, T>*);

	///////clean////
	void clean(node<Ty, T>*);
	void DelNode(node<Ty, T>*);

	///////balanced///////////
	node<Ty, T> * balance(node<Ty, T> *);

	///////////ins///////////
	node<Ty, T> * insert(node<Ty, T>*, const T&, const Ty&);

	//////////remove
	node<Ty, T> * findmin(node<Ty, T> *);
	node<Ty, T> * removemin(node<Ty, T> *);
	node<Ty, T> *  remove(node<Ty, T>*, const Ty&);

	///for test////
	bool isEqual(node<Ty, T>* root2, const node<Ty, T>* root1);
	////for constr///
	void swap(avl_tree<Ty, T, Compare> & other);
	
public:
	avl_tree();
	avl_tree(std::initializer_list<std::pair<Ty, T>> list);
	avl_tree(avl_tree<Ty, T, Compare> const &);
	avl_tree(avl_tree<Ty, T, Compare> &&);
	~avl_tree();
	void insert(const T&, const Ty&);
	void remove(const Ty&);
	node<Ty, T> * search(const T&) const;
	bool operator ==(const avl_tree& other);
	bool isEmpty();
};

/////copy////

template<typename Ty, typename T, class Compare >
void avl_tree<Ty, T, Compare>::create_node(node<Ty, T> *& cur, Ty const & k, T const & value_)
{
	cur = new node<Ty, T>();
	cur->key = k;
	cur->value = value_;
	cur->left = nullptr;
	cur->right = nullptr;
	++count_;
};

template<class Ty, class T, class Compare>
void avl_tree<Ty, T, Compare>::copy_nodes(node<Ty, T> *& dest, node<Ty, T> const * src)
{

	if (src != nullptr)
	{
		create_node(dest, src->key, src->value);
		copy_nodes(dest->left, src->left);
		copy_nodes(dest->right, src->right);
	}
	else
	{
		dest = nullptr;
	}
};


/////constr///
template<class Ty, class T, class Compare>
avl_tree<Ty, T, Compare>::avl_tree() : count_{ 0 }, root{ nullptr }
{
	comp_ = new Compare();
};

template<class Ty, class T, class Compare>
void avl_tree<Ty, T, Compare>::swap(avl_tree<Ty, T, Compare> & other)
{
	std::swap(root, other.root);
	std::swap(count_, other.count_);
	std::swap(comp_, other.comp_);
};

template<class Ty, class T, class Compare>
avl_tree<Ty, T, Compare>::avl_tree(avl_tree<Ty, T, Compare>  && tmp) : count_{ 0 }
{
	root = nullptr;
	swap(tmp);
};



template<class Ty, class T, class Compare>
avl_tree<Ty, T, Compare>::avl_tree(avl_tree<Ty, T, Compare> const & other) : count_{ 0 }
{
	if (other.count_ == 0) {
		root = nullptr;
	}
	else {
		copy_nodes(root, other.root);
	}
	comp_ = new Compare(*other.comp_);
};

/////

template<class Ty, class T, class Compare>
avl_tree<Ty, T, Compare>::avl_tree(std::initializer_list<std::pair<Ty, T>> list)
{
	root = nullptr;
	count_ = 0;
	for (auto& item : list)
	{
		insert(item.first, item.second);
	}
	comp_ = new Compare();

};





///////clean////////
template<class Ty, class T, class Compare>
avl_tree<Ty, T, Compare>::~avl_tree()
{
	clean(root);
};

template<class Ty, class T, class Compare>
void avl_tree<Ty, T, Compare>::clean(node<Ty, T> *Node)
{
	if (Node == nullptr) return;
	clean(Node->left);
	clean(Node->right);
	DelNode(Node);
};

template<class Ty, class T, class Compare>
void avl_tree<Ty, T, Compare>::DelNode(node<Ty, T> *Node)
{
	--count_;
	delete Node;
};

/////////////balanced////////////
template<class Ty, class T, class Compare>
node<Ty, T> * avl_tree<Ty, T, Compare>::balance(node<Ty, T> * Node)
{
	fixheight(Node);
	if (balance_factor(Node) == 2)
	{
		if (balance_factor(Node->right) < 0)
			Node->right = rotateright(Node->right);
		return rotateleft(Node);
	}
	if (balance_factor(Node) == -2)
	{
		if (balance_factor(Node->left) > 0)
			Node->left = rotateleft(Node->left);
		return rotateright(Node);
	}
	return Node; //no balance, all are good.
};

////height helping//////
template<class Ty, class T, class Compare>
size_t avl_tree<Ty, T, Compare>::height(node<Ty, T>* Node)
{
	return Node ? Node->height : 0;
};

template<class Ty, class T, class Compare>
int avl_tree<Ty, T, Compare>::balance_factor(node<Ty, T>* Node)
{
	return height(Node->right) - height(Node->left);
};

template<class Ty, class T, class Compare>
void avl_tree<Ty, T, Compare>::fixheight(node<Ty, T>* Node)
{
	size_t hleft = height(Node->left);
	size_t hright = height(Node->right);
	Node->height = (hleft>hright ? hleft : hright) + 1;
};


/////////equal////////////
template<class Ty, class T, class Compare>
bool avl_tree<Ty, T, Compare>::isEqual(node<Ty, T>* root2, const node<Ty, T>* root1)
{
	return (root2&&root1 ? root2->key == root1->key&& root2->value == root1->value&&isEqual(root2->left, root1->left) && isEqual(root2->right, root1->right) : !root2 && !root1);
};

template<class Ty, class T, class Compare>
bool avl_tree<Ty, T, Compare>::isEmpty()
{
	node <Ty, T>* root1 = nullptr;
	return isEqual(root, root1);
};

template<class Ty, class T, class Compare>
bool avl_tree<Ty, T, Compare>:: operator ==(const avl_tree& other)
{
	return isEqual(root, other.root);
};

template<class Ty, class T, class Compare>
node<Ty, T>* avl_tree<Ty, T, Compare>::search(const T& k) const
{
	node<Ty, T> * tr = root;
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


//////rotates/////
template<class Ty, class T, class Compare>
node<Ty, T>* avl_tree<Ty, T, Compare>::rotateright(node<Ty, T>* p)
{
	node<Ty, T>* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
};

template<class Ty, class T, class Compare>
node<Ty, T>* avl_tree<Ty, T, Compare>::rotateleft(node<Ty, T>* q)
{
	node<Ty, T>* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
};

/////////////insert////////
template<class Ty, class T, class Compare>
node<Ty, T>* avl_tree<Ty, T, Compare>::insert(node<Ty, T>* Node, const T &value_, const Ty &k)
{
	if (Node == NULL)
	{
		Node = new node<Ty, T>;
		Node->key = k;
		Node->value = value_;
		Node->height = 1;
		Node->left = nullptr;
		Node->right = nullptr;

		return Node;
	}
	else if ((*comp_)(k, Node->key))
	{
		Node->left = insert(Node->left, value_, k);
		Node = balance(Node);
	}
	else if (((*comp_)(Node->key, k)) ) 
	{
		Node->right = insert(Node->right,  value_, k);
		Node = balance(Node);
	}
	return Node;
};

template<class Ty, class T, class Compare>
void  avl_tree<Ty, T, Compare>::insert(const T &value, const Ty& k)
{
	root = insert(root, value, k);
	++count_;
};


//////////min//////////
template<class Ty, class T, class Compare>
node<Ty, T>*  avl_tree<Ty, T, Compare>::findmin(node<Ty, T>* Node)
{
	return Node->left ? findmin(Node->left) : Node;
};

template<class Ty, class T, class Compare>
node<Ty, T>*  avl_tree<Ty, T, Compare>::removemin(node<Ty, T>* Node)
{
	if (Node->left == nullptr)
	{
		return Node->right;
	}
	Node->left = removemin(Node->left);
	return balance(Node);
};

///////////remove/////////
template<class Ty, class T, class Compare>
node<Ty, T>*  avl_tree<Ty, T, Compare>::remove(node<Ty, T>* Node, const Ty &k)
{
	if (!Node) return nullptr;
	if ((*comp_)(k, Node->key))
		Node->left = remove(Node->left, k);
	else if ((*comp_)(Node->key, k))
		Node->right = remove(Node->right, k);
	else
	{
		node<Ty, T>* q = Node->left;
		node<Ty, T>* r = Node->right;
		delete Node;
		if (!r) return q;
		node<Ty, T>* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(Node);
};

template<class Ty, class T, class Compare>
void  avl_tree<Ty, T, Compare>::remove(const Ty &k)
{
	root = remove(root, k);
	--count_;

};
