## Class deque

Class deque-(двусторонняя очередь) представляет собой последовательный индексированный контейнер, который позволяет быстро вставлять и удалять элементы в начало и в конец.

http://ru.cppreference.com/w/cpp/container/list


## Memebers
  list<Type> _data;   //Список
  
## Methods

	  	Deque();
	  	~Deque();
	  	Deque(const Type& value);
	  	size_t size();
		  void swap(Deque& other);
		  Type&	at(size_t Index);
		  Type& back() const;
	  	Type& front() const;
		  bool empty() const;
	  	void insert(size_t Index, const Type &val);
	  	void clear();
	  	void push_back(const Type &val);
	  	void push_front(const Type &val);
		  void pop_back();
		  void pop_front();
      void erase(size_t Index);
    
## Operators

    Deque& operator=(const Deque& other);
		Type& operator[](size_t Index);
