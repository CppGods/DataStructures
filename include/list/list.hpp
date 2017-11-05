#include <iostream>

template <class Ty>
class list 
{
private:
   node *head, *tail;
   size_t count;
   struct node
   {
       Ty data;
       node* next;
       node* prev;
       node() : next(nullptr) {};
       node(const Ty& t) : data{t}, next{nullptr}, prev(nullptr){};
   }
public:
  list();
  list(const list& other);
  ~list();
  list& operator=(const list& other);
  bool empty();
  size_t size();
private:
  void swap(list& other);
  void clear();
};
	template <class Ty>
	list<Ty>::list(): count{0}, head{nullptr}, tail{nullptr}{};
	template <class Ty>
	list<Ty>::~list()
	{
		clear();
	}
	template <class Ty>
	void list<Ty>::clear()
	{
		while (head) 
     		{
        		 tail=head->next; 
        		 delete head;
         		 head=tail; 
     		}
		count=0;
		head=nullptr;
		tail=nullptr;
	}
	template <class Ty>
	list<Ty>::list(const list& other)
	{
	  	count=other.count;
		while (other.head!=nullptr)
		{
			add(oter.head);
			other.head=other.head->next;
		}
	}
	template< typename Ty >
	bool list<Ty>::empty() 
	{
   		 return (count==0);
   	}
	template< typename Ty >
	size_t list<Ty>::size() 
	{
   		 return count;
   	}
}
