template <class Ty>
class forward_list {

public:

  forward_list();
  
  forward_list(const forward_list& other);
  
  ~forward_list();
  
  //...
 
  forward_list& operator=(const forward_list& other);
  
  //..

private:
  
  void swap(forward_list& other);
  
  //...
};
