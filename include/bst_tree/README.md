## Class bst_tree

Class bst_tree - это структура, обеспечивающая эффективный способ хранения данных, взаимодействие с которыми обычно ценивается логарифмической сложностью. Служит для поддержки ассоциативных контейнеров(set/map)

template <class Ty>
class bst_tree

## Memebers

node<Ty> root_

std::size_t count_

## Methods

bst_tree(); //констурктор по-умолчанию

bst_tree(const bst_tree& other); //констурктор копирования

~bst_tree(); //деструктор

void insert(const Ty& value); //вставка элемента

void erase(const Ty& value); //вычленение всех элементов со значением value

bool is_node(const Ty& value) const; // проверка на вхождение

std::size_t size() const; //число узлов

void clear(); //очистка всех узлов

## Operators

bst_tree& operator=(const bst_tree& other);

## OTHER

template<typename T>
struct node<T> {
	
	T data_;
	node<T>* child_1_;
	node<T>* child_2_;
}

template<class Key, class Compare = std::less<Key>>
friend class set;