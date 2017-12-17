## Class rb_tree 
  Описывает сбалансированное по высоте двоичное дерево поиска: для каждой его вершины определен цвет.
Структура узла:
  
      template <class T, class keyT>
    struct node_st
    {
  	  node_st *left, *right;  //Указатели на правое и левое поддерево
	    T value; //Значение узла
	    keyT key; //Ключ узла
	    bool red; //Цвет узла
    };
  
  ## Memebers
Сам класс acl_tree содержит: 
  
     node_st <T, keyT> *tree_root; //Дерево
	    int nodes_count; // Кол-во узлов в дереве
      Compare* comp_;
 




## Methods
*Публичные:*
	  bool isEmpty(); //Проверка на пустоту
	  void Show(std::ostream &out) const; //Вывод дерева в поток
	  RBtree(std::initializer_list<std::pair<T, keyT>> list); //Конструктор с использованием листа инициализации
	  RBtree(); //Конструктор по умолчанию
  	~RBtree(); //Деструктор
	  void Clean(); //Очистка дерева
	  node_st<T, keyT>* search(const keyT& k) const; //Поиск по ключу.
	  void Insert(T, keyT); //Вставка в дерево
	  void Remove(keyT); //Удаление
	  int GetNodesCount() const; //Получить значение переменной nodes_count
	
	


## Operators
	
    bool operator ==(const RBtree<T, keyT> &a); 
	
    
## OTHER
