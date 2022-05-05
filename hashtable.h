//hashtable.h
#ifndef HASHTABLE_H
#define HASHTABLE_H

class Node
{
  private:
      char data; //Allows node to hold the character letter contributed to morse
      std::string morse; //Allows node to hold the morse conversion of a letter
      Node *next; 
  friend class HashTable; //Allows for HashTable to work with this class
};

class HashTable
{
public:
    int hash_code(char d);
    void add(const char &d, std::string m, Node* table[]);
    int find(const char &d, Node* table[]);
    void clear(Node *table[], int size);
    std::string replace(const char &l, Node* table[]);
    void print(Node *table[], int size);
private:
    std::string line; //Variable that can be used for multiple functions
};

#endif