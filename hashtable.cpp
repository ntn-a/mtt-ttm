//hashtable.cpp
// Code obtained from W10 Hash Table In-Class Practice
// Group Members: Evan, Dmitry, Nhan & Zara
#include <iostream>
#include "hashtable.h"

/* Purpose: Calculates hash code for character
@param file inputted letter
*/
int HashTable::hash_code(char d)
{
    int h = 0;
    int x = int(d); //finds the ASCII value for the character
    if (d == ' '){
      h = 32;
    }
    else if (ispunct(d)) //? = 63 . = 46 , = 44 ' = 39
    {
      h = x - 13; //index = 50 33 31 26
    }
    else //Alphabet Decimals 65-90, indexes 0-24
    {
      h = x - 65;
    }
    return h;
}

/*Purpose: add data to hash table
@param character to add to hash code
@param string to add to hash code
@param array of pointers, hash table
*/
void HashTable::add(const char &d, std::string m, Node* table[])
{
    int index = hash_code(d);
    Node *newNode = new Node;
    newNode->data = d; //character value contributed to letter
    newNode->morse = m; //string value that holds morse conversion
    newNode->next = nullptr;
    if (table[index] == nullptr) //If nothing is found
    {
        table[index] = newNode;
    }
    else
    {
        newNode->next = table[index];
        table[index] = newNode;
    }
}

/* Purpose: checks if name is found in table
  @param String that is to be used to search
  @param Array of pointers which is the hash table
  @return true/false if name is/not found
*/
int HashTable::find(const char &d, Node *table[])
{
    int i = 0;               // Get the hash of the string and
    int index = hash_code(d); // check the array for the index.
    while (i < 55 && table[i] != table[index])
    {
        i++;
    }
    // If the index is found, search the linked list
    if (table[i] == table[index]) 
    {
        Node *temp = table[index]; // until data is found,
        if (temp == nullptr)
        { // or nullptr.
            return -1;
        }
        while (temp->next != nullptr && temp->data != d)
        {
            temp = temp->next;
        } // If the data is found, return index of location.
        if (temp->data == d)
        {
          return index;
        }

        else
        {                 // If index is found, but value is not,
            return -1; // return false.
        }
    }
    else
    { // If index is not found at all, return false.
        return -1;
    }
}

/*Purpose:Function to clear the whole table
@param hash table
@param size of table
*/
void HashTable::clear(Node *table[], int size)
{
    for (int i = 0; i < size; i++)
    { // Loop the size of
        while (table[i] != nullptr)
        {                             // array.
            Node *removed = table[i]; // Delete nodes
            table[i] = removed->next; // As traversed.
            delete removed;
        }
    }
}

/*Purpose:Function to clear the whole table
@param hash table
@param size of table
*/
std::string HashTable::replace(const char &l, Node* table[])
{
    int value = 0;
    value = find(l, table);
    if (value == -1) //Error Case (which shouldn't happen)
    {
      std::cout << "\nError, was not found.";
    }
    else
    {
      line += table[value]->morse + " ";
    }
    return line;
}
