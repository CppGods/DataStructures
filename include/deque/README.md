## Class deque

Class deque-(двусторонняя очередь) представляет собой последовательный индексированный контейнер, который позволяет быстро вставлять и удалять элементы в начало и в конец.

http://ru.cppreference.com/w/cpp/container/deque

## Memebers
  		list<Type> _data;   //Список
  
## Methods

	  	Deque();		\\Конструктор
	  	~Deque();		\\Деструктор
	  	Deque(const Type& value);		\\конструктор копирования 
	  	size_t size();		\\Возвращает количество элементов в контейнере 
		void swap(Deque& other); 		\\Обменивает содержимое 
		Type&	at(size_t Index); 		\\Предоставляет доступ к указанному элементу
		Type& back() const;			\\Предоставляет доступ к последнему элементу 
	  	Type& front() const;		\\Предоставляет доступ к первому элементу 
		bool empty() const;			\\Проверяет отсутствие элементов в контейнере 
	  	void insert(size_t Index, const Type &val);			\\Вставляет элементы в указанную позицию 
	  	void clear();		\\Очищает контейнер 
	  	void push_back(const Type &val);		\\Добавляет элемент в конец 
	  	void push_front(const Type &val);		\\Добавляет элементы в начало  
		void pop_back();		\\Удаляет последний элемент
		void pop_front();		\\Удаляет первый элемент 
     	void erase(size_t Index);		\\Удаляет элемент из указанной позиции 
    
## Operators

		Deque& operator=(const Deque& other);
		Type& operator[](size_t Index);
