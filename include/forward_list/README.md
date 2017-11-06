## Class forward_list

Class forward_list описывает объект, управляющий последовательностью элементов переменной длины. Последовательность хранится в виде однонаправленного связного списка узлов, каждый из которых содержит член типа Ty

https://msdn.microsoft.com/ru-ru/library/ee373559.aspx

http://ru.cppreference.com/w/cpp/container/forward_list

template <class Ty>
class forward_list

## Memebers
	struct node //структура, содержащая информацию об узле списка

	{
  
		Ty data;
    
		node* next;
    
		node() : next(nullptr) {};
    
		node(const Ty& t) : data{ t }, next{ nullptr } {};
    
	};
  
	node *head; //Головной элемент списка
  
 	size_t count_; //Кол-во элементов списка

## Methods
*Публичные:*

	forward_list() : count_{ 0 }, head{ nullptr } {}; //Конструктор без параметров
	
	forward_list(const forward_list& other); //Конструктор копирования
	
	~forward_list(); //Деструктор
	
	void clear(); //Функция очистки списка
	
	//Далее представлены 4 функции для вставки элемента в начало и конец списка
	void emplace_back(const Ty& val);
	
	void emplace_front(const Ty &val);
	
	void emplace_back(const Ty&& val);
	
	void emplace_front(const Ty &&val); 
	
	void pop_back(); //Удаление последнего элемента списка
	
	void pop_front(); //Удаление первого элемента списка
	
	size_t count() const; //Возвращает значение переменной count_
*Приватные:*

	void swap(forward_list& other); //Меняет местами два списка

## Operators
	forward_list& operator=(const forward_list& other); //Операор копирующего присваивания

## OTHER
