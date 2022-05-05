// Nhan Nguyen & Evan Brannon-Wu
// CS-124
#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <iostream>
#include <fstream>
class BinaryTree{
public: // Class for BinaryTree
  BinaryTree(); // Constructor.
  void print() const; // Print function that calls print_inorder.
  void fillTree(); // Fill the tree with the cipher.
  char decode(std::string); // Decode a morse string.
  void clearTree(); // Clear the tree. Calls clear.
private:
  class Node{
  private: // Nested class to prevent clash with Node with 
      char data; // Hash table.
      Node *left;
      Node *right;
  friend class BinaryTree; // Friend to access data.
  };
  Node *root; // Root of the tree.
  void print_inorder(Node* ptr) const;
  void clear(Node *&); // Functions that require accessing Node.
};
#endif
