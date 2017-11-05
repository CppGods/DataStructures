#include <iostream>

template <class Ty>
class list 
{
private:
   node* head;
   size_t count;
   struct node
   {
       Ty data;
       node* next;
   }
public:
  list();
  list(const list& other);
  ~list();
  list& operator=(const list& other);
private:
  void swap(list& other);
};
template <class Ty>
list<Ty>::list(): count{0}, head{nullptr}{};
template <class Ty>
list<Ty>::~list()
{
	clear();
}
template <class Ty>
void list<Ty>::clear()
{
	node *cur_ = head;
		node *deleted_ = head;
		while (deleted_!=nullptr)
		{
			  cur_=cur_->next;
			  delete deleted_;
			  deleted_=cur_;
		}
	count=0;
	head=nullptr;
}
template <class Ty>
list<Ty>::list(const list& other)
{
  	count=other.count;
	while (other.head!=nullptr)
	{
		add(oter.head);
	}
	
}
