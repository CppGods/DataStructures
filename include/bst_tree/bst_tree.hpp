template <class Ty>
class bst_tree {

public:

  bst_tree();
  
  bst_tree(const bst_tree& other);
  
  ~bst_tree();
  
  //...
 
  bst_tree& operator=(const bst_tree& other);
  
  //..

private:
  
  void swap(bst_tree& other);
  
  //...
};
