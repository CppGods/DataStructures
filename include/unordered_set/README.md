## Class  Unordered_Set

Class Unordered_Set - это ассоциативный контейнер, который содержит неупорядоченный набор уникальных(неповторяющихся) объектов(ключей) определённого типа. Поиск, удаление и вставка операции имеют сложность, как и у хэш таблицы.

http://ru.cppreference.com/w/cpp/container/unordered_Unordered_Set

template<
	class Val,
	class Hash,
	class ValEqual
> class Unordered_Set

## Memebers

Hash_Table_O_A<Val, Hash, ValEqual> * hash_table_;

## Methods

Unordered_Set(); //констурктор по-умолчанию

Unordered_Set(Unordered_Set const & other); //констурктор копирования

Unordered_Set(Unordered_Set && other); //констурктор перемещения

~Unordered_Set(); //деструктор

void insert(Val const & value); //вставка ключа

std::size_t size() const; //число ключей

void clear(); //очистка контейнера

bool find(Val const & val) const; // проверка на вхождение

void erase(Val const & val); // удаление ключа

bool empty() const; // проверка на пустоту

void swap(Unordered_Set & other); // обменивает элементы двух контейнеров

TUnordered_Set_BidirectionalIterator cbegin(); // возвращает константный итератор на начало контейнера

TUnordered_Set_BidirectionalIterator cend(); // возвращает константный итератор на конец контейнера

## Operators

Unordered_Set & operator=(Unordered_Set const & other);

Unordered_Set & operator=(Unordered_Set && other);

bool operator>(Unordered_Set const & other);

bool operator<(Unordered_Set const & other);

bool operator==(Unordered_Set const & other);

bool operator!=(Unordered_Set const & other);

bool operator>=(Unordered_Set const & other);

bool operator<=(Unordered_Set const & other);

## Other

class TUnordered_Set_BidirectionalIterator;

template<
	class ValueType,
	class Hash,
	class ValEqual
> class Hash_Table_O_A