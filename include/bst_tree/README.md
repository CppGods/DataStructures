## Class bst_tree

Class bst_tree - это структура, обеспечивающая эффективный способ хранения данных, взаимодействие с которыми обычно ценивается логарифмической сложностью. Служит для поддержки ассоциативных контейнеров(set/map)

template <class Ty, class Compare = std::less<Ty>>
class bst_tree

## Memebers

node<Ty> root_

std::size_t count_

Compare* comp_;

## Methods

bst_tree(); //констурктор по-умолчанию

bst_tree(const bst_tree& other); //констурктор копирования

bst_tree(bst_tree && other); //конструктор переноса

~bst_tree(); //деструктор

void insert(const Ty& value); //вставка элемента

void erase(const Ty& value); //вычленение всех элементов со значением value

template <class Args>
void emplace(Args && args); // формирует элемент конструктором с параметрами args и перемещает его в дерево

bool is_node(const Ty& value) const; // проверка на вхождение

std::size_t size() const; //число узлов

void clear(); //очистка всех узлов

## Operators

bst_tree& operator=(const bst_tree & other);

bst_tree& operator=(bst_tree && other);

## OTHER

template<typename T>
struct node<T>