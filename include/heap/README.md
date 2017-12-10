Class Heap

Class Heap-(куча ) представляет собой бинарное дерево, для которого выполняется основное свойство кучи: приоритет каждой вершины больше приоритетов её потомков.

  Memebers
      Deque<T> list_; \\Двусторонняя очередь

  Methods
	    void swapcp(size_t child, size_t parent);  \\Меняет местами значения двух узлов
	    Heap();           \\Конструктор 
	    Heap(const Heap& other);    \\Конструктор копирования 
	    Heap(Heap&& other);           \\Конструктор перемещения 
	    Heap(std::initializer_list<T> init_list);  \\Инициализирующий список 
	    ~Heap();          \\Деструктор 
	    void push(T);         \\Вставка элемента
	    size_t getSize() const;           \\Возвращает количество элементов в контейнере 
	    bool empty() const;                 \\Проверяет отсутствие элементов в контейнере 
      T top() const;            \\Возвращет значение максимального элемента
	    void pop();               \\Удаляет максимальный элемент 
	    void swap(Heap& other);       \\Обменивает содержимое двух куч 
  
  Operators
      Heap& operator=(const Heap& other);   \\Оператор копирования 





