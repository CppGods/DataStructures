## Class Hash_Table_O_A

Class Hash_Table_O_A - это структура данных, представляющая собой таблицу ячеек с элементами определённого типа, размещёнными по заранее заданному правилу. Доступ, вставка, поиск и удаление элементов в лучшем случаем происходят за время О(1). В худшем за О(n).

template<
	class ValueType,
	class Hash = std::hash<ValueType>,
	class ValEqual = std::equal_to<ValueType>
> class Hash_Table_O_A

## Members

Hash Hasher_;

ValEqual Equal_;

float const load_factor_;

std::size_t count_;

std::size_t capacity_;

std::vector<Element> HashArr_;

## Methods

Hash_Table_O_A(); // коснтруктор по-умолчанию

Hash_Table_O_A(Hash_Table_O_A const & other); // конструктор копирования

Hash_Table_O_A(Hash_Table_O_A && other); // констуктор перемещения

~Hash_Table_O_A(); // декструктор

void swap(Hash_Table_O_A & other); // вспомогательный перемещающий метод

void insert(ValueType const & val); // метод копирующей вставки

bool find(ValueType const & val) const; // поиск по значению

void erase(ValueType const & val); // удаление по значению

void clear(); // очистка таблицы

bool empty() const; // проверка на пустоту

std::size_t size() const; // число входящих элементов

## Operators

Hash_Table_O_A & operator=(Hash_Table_O_A const & other); // оператор присваивания

Hash_Table_O_A & operator=(Hash_Table_O_A && other); // оператор перемещающего присваивания

## Other

//hash_table_using_open_addressing

//not unique values

struct Element {
		ValueType data_;
		bool is_empty_ = true;
};


## ALTARNATIVE


## Class Hash_Table_S_C

Class Hash_Table_S_C - это структура данных, представляющая собой таблицу ячеек с элементами определённого типа, размещёнными по заранее заданному правилу. Доступ, вставка, поиск и удаление элементов в лучшем случаем происходят за время О(1). В худшем за О(n). Отличия от таблицы с открытой адресацией в том, что помимо значений хранятся и ключи, а также при одном и том же хэше для разных ключей просходит объединение их в цепочку, а не поиск другой, свободной ячейки. Что даёт выйгрыш по времени поиску, но проигрыш по памяти.

template<
	class Key,
	class Val,
	class Hash = std::hash<Key>,
	class Key = std::equal_to<Key>
> class Hash_Table_S_C

## Members

Hash Hasher_;

ValEqual Equal_;

float const load_factor_;

std::size_t count_;

std::size_t capacity_;

std::vector<std::vector<Element>> HashArr_;

## Methods

Hash_Table_S_C(); // коснтруктор по-умолчанию

Hash_Table_S_C(Hash_Table_S_C const & other); // конструктор копирования

Hash_Table_S_C(Hash_Table_S_C && other); // констуктор перемещения

~Hash_Table_S_C(); // декструктор

void swap(Hash_Table_S_C & other); // вспомогательный перемещающий метод

void insert(Key const & key, Val const & val); // метод копирующей вставки

bool find(Key const & key) const; // поиск ключа

void erase(Key const & key); // удаление ключа

void clear(); // очистка таблицы

bool empty() const; // проверка на пустоту

std::size_t size() const; // число входящих элементов

## Operators

Hash_Table_S_C & operator=(Hash_Table_S_C const & other); // оператор присваивания

Hash_Table_S_C & operator=(Hash_Table_S_C && other); // оператор перемещающего присваивания

Val & operator[](Key const & key); // получает значение по ключу, можно изменить

Val operator[](Key const & key) const; // получает копию значения по ключу

## Other

//hash_table_using_separate_chaning

//not unique values

struct Element {
		std::pair<Key, Val> data_;
		bool is_empty_ = true;
};
