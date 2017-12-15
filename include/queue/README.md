## Class queue

Class queue описывает объект, управляющий последовательностью элементов переменной длины. Является классом-адаптером над forward_list.
Принцип работы - FIFO.


## Memebers
	forward_list<Ty> _items;

## Methods
*Публичные:*

 	 queue(); //Конструктор по умолчанию
	~queue(); //Деструктор
	void enqueue(const Ty& value); // вставка элемента в очередь по значению
	Ty dequeue(); // Удаление элемента.
	size_t count(); //Возвращает кол-во элементов в очереди.
	void show(); //Выводит очередь на экран
	void swap(queue& other); //Меняет местами два объекта.
	queue (const queue& other) = default; //Конструктор копирования
	queue(queue&& other); //конструктор переноса
	queue(std::initializer_list<Ty> list); //Конструктор с использованием листа инициализации

## Operators
	queue& operator=(const queue& other); //Оператор копирующего присваивания
	queue& operator=(queue&& other) = default; // Оператор переноса

## OTHER
