//Evan Brannon-Wu & Nhan Nguyen
//Lab 04 - Morse Code
//This program takes in a text file of data (text or morse)
//Another text file is used as a conversion masterlist
//If text, hash table is used to convert to morse
//If morse, binary trees are used to convert to text
#include <iostream>
#include <fstream>
#include "binarytree.h"
#include "hashtable.h"

const int SIZE = 55; //Constant size used for the hash table

char menu()
{
    char choice; //Temporary variable that holds the choice of the user
    std::cout << "\nWelcome to the Morse Code Algorithm Program."
              << "\nThis program takes in a text file filled with regular or morse text."
              << "\nThe lines will be changed to the opposite format and outputted to the user."
              << "\nWould you like to try this program? Y or N: ";
    std::cin >> choice;
    choice = tolower(choice); //Lowers input so that multiple cases aren't needed
    return choice; 
}

//Function used to hold all of the basic implentations and function calls of hash table
//Takes in the hashtable object, the table itself and the file that is used
void encode(HashTable h, Node *table[], std::string file)
{
  char letter;
  std::string temp; //temporary that will hold the completed conversion data
  std::string inTemp; //temporary that will hold original text data 

  std::ifstream in;
  in.open(file);
  while(!in.eof()) //Until the end of the file
  {
    in.get(letter);
    letter = toupper(letter); //Needs to be uppercased so it can work properly with morse conversion
    temp = h.replace(letter, table);
  }
  in.close();

  in.open(file);
  std::getline(in, inTemp, '\0'); //Takes in the whole file

  std::cout << "\nConverted to Morse:\n" << temp;
  std::ofstream ofs; //Used to write over text file
  ofs.open(file);
  ofs << "Original Data:\n" << inTemp; //Changes the original file to add header before readdding original
  ofs << "\n\nMorse Conversion:\n" << temp; 
  ofs.close();

  //h.clear(table, 35); 
}

//Function used to add the masterlist into the hash table
//Takes in the hash table object and the table
void fillHash(HashTable h, Node *table[])
{
  std::ifstream ifs;
  std::string t1; //temporary that holds the letter character
  std::string t2; //temporary that holds the morse string
  ifs.open("morse2021.txt"); //Opens the masterlist
  while (!ifs.eof()) //Until the end of the file
  {
    ifs >> t1;
    ifs >> t2;
    for (int i = 0; i < t1.size(); i++) //Makes sure the whole string of charcters is added into the table
    {
      h.add(t1[i], t2, table); //Function call
    }
    h.add(' ', " ", table); //Ensures that spaces are added into table
  }

  ifs.close();
}

//Function to print out the original data to the user
void printOriginal(std::string file)
{
  std::string line = "";
  char letter;
  std::ifstream ifs;
  ifs.open(file);
  std::cout << "\nOriginal Data File:\n";
  while(!ifs.eof()) //Until the end of the file
  {
    ifs.get(letter);
    line += letter; //Continously adds the new character into one whole piece
  }
  std::cout << line; //Prints into the console
  std::cout << std::endl;
  ifs.close();
}
/*
  @param String to be converted to lower case.
  @return String that is converted.
*/
std::string convertLower(std::string d){
  std::string temp = "";
  for (int i = 0; i < d.size(); i++){
    if (i == 0){ // Beginning of string, capitalize it.
      temp += toupper(d[i]);
    }
    else if (d[i] == ' '){ 
      d[i+1] = toupper(d[i+1]);
      temp += d[i+1];
      temp += tolower(d[i+2]);
      i++; // Otherwise, if space is encountered, character manipulation
      i++; // To setup for next sentence.
	  }
    else{
      while (d[i] != '.'){
        temp += tolower(d[i]);
        i+=1; // After a capital, lowercase everything until a period to form
      } // a sentence.
		  temp += '.';
      temp += ' ';
    }
  }
  return temp;
}
/*
  @param BinaryTree object to decode a file.
  @param String that is the name of the file.
*/
void binaryDecode(BinaryTree b, std::string file){
  std::ifstream ifs;
  ifs.open(file); // Open the file
  char letter;
  std::string temp = "";
  std::string og; // Variables to hold input, morse strings,
  std::string morse = ""; // and conversion data.
  std::string sentence = "";
  int i = 0;
  ifs.get(letter);
  while (!ifs.eof()){
    while (!isspace(letter) && letter != '\n'){
      temp += letter; // While each letter is grabbed and not a space
      ifs.get(letter); // or a newline, add it to temp.
    } // Then, it is decoded and concatted to sentence.
    sentence += b.decode(temp);
    temp = ""; // Reset and repeat until end of file.
    ifs.get(letter);
  }
  sentence = convertLower(sentence);
  ifs.close(); // Sentence is converted and original data is stored to prepare
  ifs.open(file); // for file modification.
  std::getline(ifs, og, '\0');
  ifs.close(); // Grab all the og data, store it, output it, then output
  std::cout << std::endl << "Deconverted from Morse:" << std::endl;
  std::cout << sentence; // into the file, along with morse conversion.
  std::ofstream ofs;
  ofs.open(file);
  ofs << "Original Data: \n" << og;
  ofs << "\n\nMorse Conversion:\n" << sentence;
  ofs.close();
}

int main()
{
  std::string c; //temporary string that helps the autodetection to look at first piece of data
  std::string fileName;
  std::ifstream ifs;

  char user = menu();
  while (user != 'n' && user != 'y') //Acts as a default
  {
    std::cout << "\nInvalid Choice. Please Try Again.\n";
    user = menu();
  }
  while (user == 'y') 
  {
    BinaryTree b; 
    b.fillTree();
    HashTable hash; //Hash object
    Node *table[SIZE]; //Hash table of nodes
    for (int i = 0; i < SIZE; i++)
    {
      table[i] = nullptr; //Ensures that table is completely cleared and empty
    }

    std::cout << "\nWhat file would you like to test with?: ";
    std::cin >> fileName;
    ifs.open(fileName);

    if(!ifs) //Acts a default if file not found
    {
      while (!ifs) //Runs continously until found
      {
        std::cout << "\nFile could not be found. Please try again: ";
        std::cin >> fileName;
        ifs.open(fileName);
      }
    }

    ifs >> c;
    ifs.close();

    if(isalpha(c[0])) //If letter is found in the first character of the first string, calls hash table functions
    {
      printOriginal(fileName); //Allows the user to see original data
      fillHash(hash, table); //Allows the table to hold the conversion list
      encode(hash, table, fileName); //Runs the bulk of the function calls
    }
    else //If puncutation or anything else is found, calls binary tree functions
    {
      printOriginal(fileName); //Allows the user to see original data
      binaryDecode(b, fileName);
    }
    hash.clear(table, SIZE); //Clears for memory allocation
    b.clearTree(); //Clears for memory allocation
    std::cout << "\nWould you like to run again?(y/n): ";
    std::cin >> user;
    while (user != 'y' && user != 'n')
    {
      std::cout << "\nInvalid Choice. Please Try Again.\n";
      std::cout << "\nWould you like to run again?(y/n): ";
      std::cin >> user;
    }
  }
  if (user == 'n') //Exiting message if 'n' is chosen
  {
    std::cout << "\nThank you! Exiting Program....\n";
    return 0;
  }
}

