## Class list (double_linked_list)

Class list - это двунаправленный список, который обеспечивает двунаправленный доступ, быструю вставку и удаление в любом месте контейнера, но не поддерживает прямой доступ к элементам контейнера

https://msdn.microsoft.com/ru-ru/library/802d66bt.aspx

http://ru.cppreference.com/w/cpp/container/list

template <class Ty>
class list

## Memebers
struct Node     //Структура, содержащая информацию об узле списка
{ 
  Node *prev, *next;   // Указатель на предыдущий и следующий элементы 
  T data; //Данные узла
};

node *head;   //Указатель на начало списка

size_t count;   //Количество элементов в списке


## Methods
public:

	list();   //Конструктор без параметров
	list(const list& other);   //Конструктор копирования
	~list();     //Деструктор
	bool empty() const;
	size_t size() const; //Возвращает значение переменной count_
	Ty& back() const;       //Предоставляет доступ к последнему элементу 
	Ty& front() const;         //Предоставляет доступ к первому элементу 
	void insert(size_t Index, const Ty &val);       ///Вставка элемента в указанную позицию 
	void push_back(const Ty &val);        //Вставка элемента в конец списка
	void push_front(const Ty &val);       //Вставка элемента в начало списка
	void pop_back();        //Удаление элемента из конца списка
	void pop_front();      //Удаление элемента из начала списка
private:

	void swap(list& other); //Меняет местами два списка
	void clear();     //Функция очистки списка
## Operators
	list& operator=(const list& other);       //Оператор копирующего присваивания
## OTHER
