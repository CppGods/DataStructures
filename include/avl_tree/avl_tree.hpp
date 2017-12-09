
#include <iostream>
#include <utility>


template<typename Ty>
struct node
{
	node<Ty> * left, * right, *parent;
	Ty key;
	size_t height;
	node<Ty>(): left{ nullptr }, right{ nullptr }, parent{ nullptr }, height{0} {};
	node<Ty>(Ty && data) : left{ nullptr }, right{ nullptr }, parent{ nullptr }, key{ std::move(data) }, height{ 1 } {};
	node<Ty>(Ty const& data) : left{ nullptr }, right{ nullptr }, parent{ nullptr }, key{ data }, height{ 1 } {};
}; 


template<typename Ty, class Compare = std::less<Ty>>
class avl_tree
{
private:
	node<Ty> * root;
	Compare *comp_;
	size_t count_;

private:
	/////copy///
	void copy_nodes(node<Ty> *&, node<Ty> const *);
	void create_node(node<Ty> *&, Ty const &);

	/////height helping///
	size_t height(node<Ty>* Node);
	int balance_factor(node<Ty>* Node);
	void fixheight(node<Ty>* Node);

	///////rotates//////
	node<Ty>* rotateright(node<Ty>* );
	node<Ty>* rotateleft(node<Ty>* );

	///////clean////
	void clean(node<Ty> *);
	void DelNode(node<Ty>*);

	///////balanced///////////
	node<Ty> * balance(node<Ty> *);

	///////////ins///////////
	node<Ty> * insert(node<Ty>*, const Ty&);

	//////////remove
	node<Ty> * findmin(node<Ty> *);
	node<Ty> * removemin(node<Ty> *);
	node<Ty> *  remove(node<Ty>* , const Ty& );

	///for test////
	bool isEqual(node<Ty>* root2, const node<Ty>* root1);
////for constr///
	void swap(avl_tree<Ty, Compare> & other);

public:
	avl_tree();
	avl_tree(std::initializer_list<Ty> list);
	avl_tree(avl_tree<Ty, Compare> const &);
	avl_tree(avl_tree<Ty, Compare> && );
	~avl_tree();
	void insert(const Ty& );
	void remove(const Ty& );
	node<Ty> * search(const Ty& ) const;
	bool operator ==(const avl_tree& other);
};

/////copy////
template<class Ty, class Compare = std::less<Ty>>
void avl_tree<Ty, Compare>::create_node(node<Ty> *& cur, Ty const & value) {

	cur = new node<Ty>();
	cur->key = value;
	cur->left = nullptr;
	cur->right = nullptr;
	++count_;
}

template<class Ty, class Compare = std::less<Ty>>
void avl_tree<Ty, Compare>::copy_nodes(node<Ty> *& dest, node<Ty> const * src) {

	if (src != nullptr) {
		create_node(dest, src->key);
		copy_nodes(dest->left, src->left);
		copy_nodes(dest->right, src->right);
	}
	else {
		dest = nullptr;
	}
}


/////constr///
template<class Ty, class Compare = std::less<Ty>>
avl_tree<Ty, Compare>:: avl_tree() : count_{ 0 }, root { nullptr } 
{
	comp_ = new Compare();
};

template<class Ty, class Compare = std::less<Ty>>
void avl_tree<Ty, Compare>:: swap (avl_tree<Ty, Compare> & other)
{
	std::swap(root, other.root);
	std::swap(count_, other.count_);
	std::swap(comp_, other.comp_);
}

template<class Ty, class Compare = std::less<Ty>>
avl_tree<Ty, Compare>::avl_tree(avl_tree<Ty, Compare>  && tmp) : count_{ 0 }
{
	root = nullptr;
	swap(tmp);
};



template<class Ty, class Compare = std::less<Ty>>
avl_tree<Ty, Compare>::avl_tree(avl_tree<Ty, Compare> const & other) : count_{ 0 }
{
		if (other.count_ == 0) {
			root = nullptr;
		}
		else {
			copy_nodes(root, other.root);
		}
		comp_ = new Compare(*other.comp_);
};


template<class Ty, class Compare = std::less<Ty>>
avl_tree<Ty, Compare>::avl_tree(std::initializer_list<Ty> list)
{
	root = nullptr;
	count_ = 0;
	for (auto& item : list)
	{
		insert(item);
	}

};





///////clean////////
template<class Ty, class Compare = std::less<Ty>>
avl_tree<Ty, Compare>::~avl_tree() 
{
	clean(root);
};

template<class Ty, class Compare = std::less<Ty>>
void avl_tree<Ty, Compare>::clean(node<Ty> *Node)
{
	if (Node==nullptr) return;
	clean(Node->left);
	clean(Node->right);
	DelNode(Node);
};

template <class Ty, class Compare = std::less<Ty>>
void avl_tree<Ty, Compare>::DelNode(node<Ty> *Node)
{
	--count_;
	delete Node;
};

/////////////balanced////////////
template <class Ty, class Compare = std::less<Ty>>
node<Ty> * avl_tree<Ty, Compare>::balance(node<Ty> * Node)
{
	fixheight(Node);
	if (balance_factor(Node)== 2)
	{
		if (balance_factor(Node->right) < 0)
			Node->right = rotateright(Node->right);
		return rotateleft(Node);
	}
	if (balance_factor(Node)== -2)
	{
		if (balance_factor(Node->left) > 0)
			Node->left = rotateleft(Node->left);
		return rotateright(Node);
	}
	return Node; //no balance, all are good.
}

////height helping//////
template<class Ty, class Compare = std::less<Ty>>
size_t avl_tree<Ty, Compare>::height(node<Ty>* Node)
{
	return Node ? Node->height : 0;
};

template<class Ty, class Compare = std::less<Ty>>
int avl_tree<Ty, Compare>::balance_factor(node<Ty>* Node)
{
	return height(Node->right) - height(Node->left);
};

template<class Ty, class Compare = std::less<Ty>>
void avl_tree<Ty, Compare>:: fixheight(node<Ty>* Node)
{
	size_t hleft = height(Node->left);
	size_t hright = height(Node->right);
	Node->height = (hleft>hright ? hleft : hright) + 1;
};


/////////equal////////////
template<class Ty, class Compare = std::less<Ty>>
bool avl_tree<Ty, Compare>:: isEqual(node<Ty>* root2, const node<Ty>* root1)
{
	return (root2&&root1 ? root2->key == root1->key&&isEqual(root2->left, root1->left) && isEqual(root2->right, root1->right) : !root2 && !root1);
};

template<class Ty, class Compare = std::less<Ty>>
bool avl_tree<Ty, Compare>:: operator ==(const avl_tree& other)
{
	return isEqual(root, other.root);
}

template<class Ty, class Compare = std::less<Ty>>
node<Ty>* avl_tree<Ty, Compare>:: search(const Ty& k) const
{
	node<Ty> * tr = root;
	while (tr != nullptr)
	{
		if ((!(*comp_)(tr->key, k))&& (!(*comp_)(tr->key, k)))
			break;
		else
		{
			if ((*comp_)(tr->key, k))
				tr = tr->right;
			else tr =tr->left;
		}
	}
	return tr;
};


//////rotates/////
template<class Ty, class Compare = std::less<Ty>>
node<Ty>* avl_tree<Ty, Compare>:: rotateright(node<Ty>* p)
{
	node<Ty>* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
};
template<class Ty, class Compare = std::less<Ty>>
node<Ty>* avl_tree<Ty, Compare>::rotateleft(node<Ty>* q)
{
	node<Ty>* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
};

/////////////insert////////
template<class Ty, class Compare = std::less<Ty>>
node<Ty>* avl_tree<Ty, Compare>:: insert(node<Ty>* Node, const Ty &value)
{
	if (Node == NULL)
	{
		Node = new node<Ty>;
		Node->key = value;
		Node->height = 1;
		Node->left = nullptr;
		Node->right = nullptr;
		
		return Node;
	}
	else if ((*comp_)(value, Node->key))
	{
		Node->left = insert(Node->left, value);
		Node = balance(Node);
	}
	else if (((*comp_)( Node->key, value))||( (!(*comp_)(value, Node->key))&&(!(*comp_)(Node->key, value))))
	{
		Node->right = insert(Node->right, value);
		Node = balance(Node);
	}
	return Node;
}

template<class Ty, class Compare = std::less<Ty>>
void  avl_tree<Ty, Compare>::insert(const Ty &k)
{
	root=insert(root, k);
	++count_;
}


//////////min//////////
template<class Ty, class Compare = std::less<Ty>>
node<Ty>*  avl_tree<Ty, Compare>::findmin(node<Ty>* Node)  
{
	return Node->left ? findmin(Node->left) : Node;
}

template<class Ty, class Compare = std::less<Ty>>
node<Ty>*  avl_tree<Ty, Compare>::removemin(node<Ty>* Node)
{
	if (Node->left == nullptr)
	{
		return Node->right;
	}
	Node->left = removemin(Node->left);
	return balance(Node);
}

///////////remove/////////
template<class Ty, class Compare = std::less<Ty>>
node<Ty>*  avl_tree<Ty, Compare>::remove(node<Ty>* Node, const Ty &k)
{
	if (!Node) return nullptr;
	if ((*comp_)(k, Node->key))
		Node->left = remove(Node->left, k);
	else if ((*comp_)(Node->key, k))
		Node->right = remove(Node->right, k);
	else 
	{
		node<Ty>* q = Node->left;
		node<Ty>* r = Node->right;
		delete Node;
		if (!r) return q;
		node<Ty>* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(Node);
}

template<class Ty, class Compare = std::less<Ty>>
void  avl_tree<Ty, Compare>::remove(const Ty &k)
{
	root=remove(root, k);
	--count_;
	
}
