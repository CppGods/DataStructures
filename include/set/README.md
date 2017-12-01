## Class set

Class set - это ассоциативный контейнер, который содержит упорядоченный набор уникальных(неповторяющихся) объектов(ключей) определённого типа, которые отсортированы по заранее заданному алгоритму. Поиск, удаление и вставка операции имеют логарифмическую сложность.

http://ru.cppreference.com/w/cpp/container/set

template<
    class Key,
    class Compare = std::less<Key>,
> class set;

## Memebers

bst_tree<Key> keys_;

Compare* key_comp_;

## Methods

set(); //констурктор по-умолчанию

set(set const & other); //констурктор копирования

~set(); //деструктор

void insert(Key const & value); //вставка ключа

std::size_t size() const; //число ключей

void clear(); //очистка контейнера

bool find(Key const & key) const; // проверка на вхождение

void erase(Key const & key); // удаление ключа

bool empty() const; // проверка на пустоту

void swap(set & other); // обменивает элементы двух контейнеров

TSetBidirectionalIterator cbegin(); // возвращает константный итератор на начало контейнера

TSetBidirectionalIterator cend(); // возвращает константный итератор на конец контейнера

## Operators

set & operator=(set const & other);

bool operator>(set const & other);

bool operator<(set const & other);

bool operator==(set const & other);

bool operator>=(set const & other);

bool operator<=(set const & other);

## Other

class TSetBidirectionalIterator;

template <class Ty>
class bst_tree