## Class map

Class map - это структура данных, являющаяся упорядоченным ассоциативным контейнером, который содержит пары ключ-значение с уникальными ключами. Поиск, встаква, и удаление происходит примерно за то же время, что и у 
avl дерева.

template<
	class Key,
	class Val,
	class Compare
> class map;

## Members

avl_tree<Key, Val, Hash, KeyEqual> * pairs_;

## Methods

map(); // коснтруктор по-умолчанию

map(map const & other); // конструктор копирования

map(map && other); // констуктор перемещения

~map(); // декструктор

Tmap_Bidiretional_Iterator cbegin() const; // возращает объект - двунаправленный константый итератор на начало

Tmap_Bidiretional_Iterator cend() const; // возращает объект - двунаправленный константый итератор на конец

void swap(map & other); // вспомогательный перемещающий метод

void insert(Key const & key, Val const & val); // метод копирующей вставки

bool find(Key const & key) const; // поиск ключа

void erase(Key const & key); // удаление ключа

Val get_val(Key const & key) const; // возвращение значения по ключу

void clear(); // очистка таблицы

bool empty() const; // проверка на пустоту

std::size_t size() const; // число входящих элементов

## Operators

map & operator=(map const & other); // оператор присваивания

map & operator=(map && other); // оператор перемещающего присваивания

Val operator[](Key const & key) const; // получает копию значения по ключу

## Other

class Tmap_Bidiretional_Iterator; // двунаправленный константный итератор

template<
	class Ty,
	class T,
	class Compare
> class avl_tree; // avl дерево, на котором основан map

