## Class stack

Класс адаптера контейнера шаблона, который предоставляет ограничение функциональности, ограничивая доступ к элементу, который был последним добавлен в некоторый тип базового контейнера. Класс стека используется в том случае, когда важно пояснить, что в контейнере выполняются только операции стека.

https://msdn.microsoft.com/ru-ru/library/56fa1zk5.aspx

http://ru.cppreference.com/w/cpp/container/stack

template <class Ty>  
class stack

## Members

Ty* array_

size_t size_array_

size_t count_

## Methods

stack::empty	Проверяет, является ли stack пустым.

stack::pop		Удаляет элемент из верхней части stack.

stack::push	    Добавляет элемент в верхнюю часть stack.

stack::size	    Возвращает количество элементов в контейнере stack.

stack::Top	    Возвращает ссылку на элемент в верхней части stack.


## Operators

## OTHER
