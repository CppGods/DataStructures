template <class Ty>
class stack {

public:

	//methods

/*
stack::empty	Проверяет, является ли stack пустым.
stack::pop		Удаляет элемент из верхней части stack.
stack::push	    Добавляет элемент в верхнюю часть stack.
stack::size	    Возвращает количество элементов в контейнере stack.
stack::Top	    Возвращает ссылку на элемент в верхней части stack.
*/
	//...

	//operators

	//...

private:

	//members

	Ty* array_;
	size_t size_array_;
	size_t count_;
};
