template <class Ty>
class list {

public:

  list();
  
  list(const list& other);
  
  ~list();
  
  //...
 
  list& operator=(const list& other);
  
  //..

private:
  
  void swap(list& other);
  
  //...
};
