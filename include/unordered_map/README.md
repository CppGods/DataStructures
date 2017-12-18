## Class Unordered_Map
Class Unordered_Map - это структура данных, являющаяся ассоциативным контейнером, который содержит пары ключ-значение с уникальными ключами. Поиск, вставка и удаление выполняются примерно за константное время.

template<
	class Key,
	class Val,
	class Hash,
	class KeyEqual
> class Unordered_Map

## Members

Hash_Table_S_C<Key, Val, Hash, KeyEqual> * hash_table_;

## Methods

Unordered_Map(); // коснтруктор по-умолчанию

Unordered_Map(Unordered_Map const & other); // конструктор копирования

Unordered_Map(Unordered_Map && other); // констуктор перемещения

~Unordered_Map(); // декструктор

TUnordered_Map_Bidiretional_Iterator cbegin() const; // возращает объект - двунаправленный константый итератор на начало

TUnordered_Map_Bidiretional_Iterator cend() const; // возращает объект - двунаправленный константый итератор на конец

void swap(Unordered_Map & other); // вспомогательный перемещающий метод

void insert(Key const & key, Val const & val); // метод копирующей вставки

bool find(Key const & key) const; // поиск ключа

void erase(Key const & key); // удаление ключа

Val get_val(Key const & key) const; // возвращение значения по ключу

void clear(); // очистка таблицы

bool empty() const; // проверка на пустоту

std::size_t size() const; // число входящих элементов

## Operators

Unordered_Map & operator=(Unordered_Map const & other); // оператор присваивания

Unordered_Map & operator=(Unordered_Map && other); // оператор перемещающего присваивания

Val & operator[](Key const & key); // получает значение по ключу, можно изменить

Val operator[](Key const & key) const; // получает копию значения по ключу

## Other

class TUnordered_Map_Bidiretional_Iterator; // двунаправленный константный итератор

