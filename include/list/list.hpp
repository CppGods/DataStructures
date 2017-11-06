#include <iostream>

template <class Ty>
class list 
{
private:
   node *head, *tail;
   size_t count_;
   struct node
   {
       Ty data;
       node* next;
       node* prev;
       node() : next(nullptr) {};
       node(const Ty& t) : data{t}, next{nullptr}, prev{nullptr}{};
   }
public:
  list();
  list(const list& other);
  ~list();
  list& operator=(const list& other);
  bool empty() const;
  size_t size() const;
private:
  void swap(list& other);
  void clear();
};
	template <class Ty>
	list<Ty>::list(): count_{0}, head{nullptr}, tail{nullptr}{};
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
		count_=0;
		head=nullptr;
		tail=nullptr;
	}
	template <class Ty>
	list<Ty>::list(const list& other)
	{
	  	
	}
	template< typename Ty >
	bool list<Ty>::empty() const
	{
   		 return (count_==0);
   	}
	template< typename Ty >
	size_t list<Ty>::size() const
	{
   		 return count_;
   	}
}
