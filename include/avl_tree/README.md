## Class avl_tree 
  Описывает сбалансированное по высоте двоичное дерево поиска: для каждой его вершины высота её двух поддеревьев различается не более чем на 1.

Структура узла:
  
    template<typename Ty, typename T>
  
    struct node
    {
  	node<Ty, T> * left, *right; // ссылки на левый и правый узлы/поддеревья соответственно.
  	Ty key; //Ключ, по которому производится вставка, удаление и поиск элемента.
  	T value; //Значение узла.
  	size_t height; //Высота или уровень, на котором находится элемент.
    //Конструкторы::
  	node<Ty, T>() : left{ nullptr }, right{ nullptr },  height{ 0 } {};
  	node<Ty, T>(Ty && data, T && value_) : left{ nullptr }, value{value_}, right { nullptr },  key{ std::move(data) }, height{ 1 } {};
  	node<Ty, T>(Ty const &data, T const &value_) : left{ nullptr }, value{ value_ }, right{ nullptr }, key{ data }, height{ 1 } {};  
    };
  
  ## Memebers
Сам класс acl_tree содержит: 
  
    node<Ty, T> * root; //Узел
    Compare *comp_; 
    size_t count_; //Количество узлов.
    
 




## Methods
*Публичные:*
	  avl_tree(); //Конструктор по умолчанию
  
	  avl_tree(std::initializer_list<std::pair<Ty, T>> list); //Конструктор с списком инициализации.
  
	  avl_tree(avl_tree<Ty, T, Compare> const &); //Конструктор копирования
  
	  avl_tree(avl_tree<Ty, T, Compare> &&); //Конструктор переноса
  
	  ~avl_tree(); //Деструктор
  
	  void insert(const Ty&, const T&); //Вставка узла с заданными значением и ключом.
  
	  void remove(const Ty&); //Удаление по заданному ключу.
  
	  node<Ty, T> * search(const Ty&) const; //Поиск по заданному ключу.
  
	
  
*Приватные:*

	//Блок копирования
	void copy_nodes(node<Ty, T> *&, node<Ty, T> const *);
	void create_node(node<Ty, T> *&, Ty const &, T const &);

	//Блок отладки параметра height
	size_t height(node<Ty, T>* Node);
	int balance_factor(node<Ty, T>* Node);
	void fixheight(node<Ty, T>* Node);

	//Правый и левый поворот дерева
	node<Ty, T>* rotateright(node<Ty, T>*);
	node<Ty, T>* rotateleft(node<Ty, T>*);

	//Очистка дерева
	void clean(node<Ty, T>*);
	void DelNode(node<Ty, T>*);

	//Балансировка.
	node<Ty, T> * balance(node<Ty, T> *);

	//Вставка, вызываемая публичным методом insert
	node<Ty, T> * insert(node<Ty, T>*, const Ty&, const T&);

	//Удаление, вызываемое публичным методом remove
	node<Ty, T> * findmin(node<Ty, T> *);
	node<Ty, T> * removemin(node<Ty, T> *);
	node<Ty, T> *  remove(node<Ty, T>*, const Ty&);

	//Метод для определения равенства деревьев.
	bool isEqual(node<Ty, T>* root2, const node<Ty, T>* root1);
	//Метод, меняющий местами два дерева.
	void swap(avl_tree<Ty, T, Compare> & other);

## Operators
	
    bool operator ==(const avl_tree& other); 
    
## OTHER
