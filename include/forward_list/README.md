## Class forward_list

Class forward_list описывает объект, управляющий последовательностью элементов переменной длины. Последовательность хранится в виде однонаправленного связного списка узлов, каждый из которых содержит член типа Ty

https://msdn.microsoft.com/ru-ru/library/ee373559.aspx

http://ru.cppreference.com/w/cpp/container/forward_list

template <class Ty>
class forward_list

## Memebers
struct node

	{
  
		Ty data;
    
		node* next;
    
		node() : next(nullptr) {};
    
		node(const Ty& t) : data{ t }, next{ nullptr } {};
    
	};
  
	node *head;
  
  size_t count_;

## Methods

## Operators

## OTHER
