## Class Hash_Table_O_A

Class Hash_Table_O_A - это структура данных, представляющая собой таблицу ячеек с элементами определённого типа, размещёнными по заранее заданному правилу. Доступ, вставка, поиск и удаление элементов в лучшем случаем происходят за время О(1). В худшем за О(n).

template<
	class ValueType,
	class Hash = std::hash<ValueType>,
	class ValEqual = std::equal_to<ValueType>
> class Hash_Table_O_A

## Memmbers

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