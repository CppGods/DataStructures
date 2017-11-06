## Class bst_tree

Class bst_tree - это структура, обеспечивающая эффективный способ хранения данных, взаимодействие с которыми обычно ценивается логарифмической сложностью. Служит для поддержки ассоциативных контейнеров(set/map)

template <class Ty>
class bst_tree

## Memebers

node<Ty> root_

size_t count_

## Methods

bst_tree() //констурктор по-умолчанию

bst_tree(const bst_tree& other) //констурктор копирования

~bst_tree() //деструктор

void insert(const Ty& value); //вставка элемента

void pop_all_with(const Ty& value, node<Ty>** this_ = &root_); //вычленение всех элементов со значением value

const node<Ty>* is_node(const Ty& value) const; // проверка на вхождение

size_t size() const; //число узлов

void clear(node<Ty>* this_ = root_); //очистка всех узлов

void create_node(node<Ty>*& this_, const Ty& value); //констурктор узла

void copy_nodes(node<Ty>*& dest, const node<Ty>* src); //копирование узлов поддерева

void del(node<Ty>** this_); //удаление узла, на который указывает *this_

## Operators

bst_tree& operator=(const bst_tree& other);

## OTHER

template<typename T>
struct node<T> {
	
	T data_;
	node<T>* child_1_;
	node<T>* child_2_;
}
