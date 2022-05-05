// Nhan Nguyen & Evan Brannon-Wu
// CS-124
#include "binarytree.h"

/*
  Constructor for BinaryTree.
*/
BinaryTree::BinaryTree(){
  root = nullptr; // Set root to nullptr
}
/*
  FIll the tree with morse data.
*/
void BinaryTree::fillTree(){
  if (root == nullptr){
    root = new Node; // All the time root should be nullptr,
    root->data = ' '; // So this will essentially set it up.
    root->left = nullptr;
    root->right = nullptr;
  } // Set the left and right pointers to null.
  std::ifstream input;
  input.open("morse2021.txt");
  std::string letter;
  std::string morse;
  Node *ptr = root;
  // The file is opened and data is sent into
  while (!input.eof()){ // string variables.
    input >> letter;
    input >> morse;
    for (int i = 0; i < morse.size(); i++){
      if (morse[i] == '.'){ // If-else blocks form the 
        if (ptr->left == nullptr){ // path for the morse
          ptr->left = new Node; // to traverse.
          ptr->left->data = ' '; // If left is null, create a node
          ptr->left->left = nullptr; // and go into it.
          ptr->left->right = nullptr;
        }
        ptr = ptr->left;
      }
      else{
        if (ptr->right == nullptr){
          ptr->right = new Node; // Similar process as above, just
          ptr->right->data = ' '; // for right.
          ptr->right->left = nullptr;
          ptr->right->right = nullptr;
        }
        ptr = ptr->right;
      }
    }
    ptr->data = letter[0]; // At the end of the morse string,
    ptr = root; // Set the data to the letter and repeat.
  }
  input.close(); // Close filestream
}
/*
  @param String that is the morse
  @return Character of which the morse represents.
*/
char BinaryTree::decode(std::string morse){
  Node *ptr = root;
  for (int i = 0; i < morse.size(); i++){
    if (morse[i] == '.'){
      ptr = ptr->left;
    } // Essentially, the tree is traversed until the 
    else{ // end of the string.
      ptr = ptr->right;
    }
  } // Then the character at that point is returned,
  return ptr->data; // giving back the letter the morse represents.
}
/*
  Print function to print in order.
*/
void BinaryTree::print() const{
  print_inorder(root);
}
/*
  @param Node pointer used to traverse.
*/
void BinaryTree::print_inorder(Node *ptr) const{
  if (ptr == nullptr){
    return;
  } // Recursive function to go into the nodes and print data.
  print_inorder(ptr->left);
  std::cout << ptr->data;
  print_inorder(ptr->right);
}
/*
  @param Node ptr used to traverse.
*/
void BinaryTree::clear(Node *&ptr){
  if (ptr == nullptr){
    return;
  } // Basically a post-order traverse to clear
  clear(ptr->left); // the tree.
  clear(ptr->right);
  delete ptr;
}
/*
  Because the Node class is private, a function
  call to clear with root as parameter is required.
*/
void BinaryTree::clearTree(){
  clear(root);
}