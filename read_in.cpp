#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <stdexcept>

//#include "Record.h"
#include "read_in.h"
//#include "templated_doubly.h"

using namespace std;


/*----------------------------------------------read_in.cpp---------------------------------------*/

void read_to_vector (vector<DoublyLinkedList<Record>>& book) {
 try { 
  ofstream myfile_1;
  myfile_1.open ("PhoneBook.txt",  std::ofstream::out | std::ofstream::app);
  string file("PhoneBook.txt");
  ifstream ist(file.c_str());
  if (!ist)throw FileError("can't open input file ");
  string last_name;
  string first_name;
  int uin; 
  string phone_num;
  int num_rank;
  while (ist >> last_name >> first_name >> uin >> phone_num) {
 	Record rec(last_name, first_name, uin, phone_num);
 	num_rank = get_ascii(last_name);
 	book[num_rank].insertOrderly(rec);
  }
  myfile_1.close();
}
catch(exception &e) {
  cerr << e.what() << endl;
}
}
  

void print_phonebook (const vector<DoublyLinkedList<Record>>& book) {
  for(int i = 0; i < book.size(); i++)
    cout << book[i] << endl;
}

/*---------------------------------------------------------------------------------------------*/

int get_ascii(const string& work){
  char rank;
  int num_rank;
  rank = work[0];
  num_rank = (int)toupper(rank) - 65;
  return num_rank;
}

/*---------------------------------------------------------------------------------------------*/

void menu (vector<DoublyLinkedList<Record>>& get_phone_num) {
  bool check = true;
  string inform;
  cout << "Welcome to Kyle's inplementation of a phone book." << endl;
  while(check) {
  cout << "If you would like to look up a students record type in 'continue' followed by the enter key." << endl
  << "If you would like to go into the testing phase of this program type in 'test' followed by the enter key. " << endl
  << ": "; 
  cin >> inform;
  if (inform == "continue") {
    cout << prompt(get_phone_num) << endl;
  }
  else if(inform == "test")
    check = false;
  else {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "That wasn't an option. Please follow these directions: " << endl;
       }
    }
}


Record prompt(vector<DoublyLinkedList<Record>>& get_phone_num) {
  try {
  string lastname_in;
  int holder;
  bool check = true;
  cout << "What is the last name of the student you are searching for(name must be capatilized, example: Smith )" << endl;
  cout << ": ";
  cin >> lastname_in;
  holder = get_ascii(lastname_in);
  if(holder < 0 || holder > 25) throw NoRecord("There is no record of anyone by this last name");
  return findLastName(&get_phone_num[holder], lastname_in);
}
catch (exception &e) {
  Record bad;
  cerr << e.what() << endl;
  return bad;
}
}

/*---------------------------------------------------------------------------------------------*/

Record findLastName(DoublyLinkedList<Record>* p_book, string last_name) {
  try{
  DListNode<Record>* temp = p_book->getFirst(); 
  while(temp->getElem().getLastName() != last_name && temp != p_book->getAfterLast()){
    temp = temp->getNext();
  }
  if(temp == p_book->getAfterLast()) {
    throw  NoRecord("There is no record of this person.");
  }
  if(temp->getNext()->getElem().getLastName() == last_name) {
    return findFirstName(p_book, temp, last_name);
  }
  else 
    return temp->getElem();
}
catch (exception &e) {
  Record bad;
  cerr << e.what() << endl;
  return bad;
}
}


/*---------------------------------------------------------------------------------------------*/

Record findFirstName(DoublyLinkedList<Record>* p_book, DListNode<Record>* temp, string last_name) {
  try {
  string first_name;
  cout << "There is more than one person by that last name." << endl;
  cout << "To specify who's phone number you wish to find, please input their first name(name must be capatilized, example: John )" << endl;
  cout << ": ";
  cin >> first_name;
  while(temp->getElem().getFirstName() != first_name && temp != p_book->getAfterLast()) {
    temp = temp->getNext();
  }
  if(temp == p_book->getAfterLast() || temp->getElem().getLastName() != last_name){
    throw NoRecord("There is no record of this person.");
  }
  if(temp->getNext()->getElem().getFirstName() == first_name) {
    return findUIN(p_book, temp, last_name, first_name);
  }
  else
    return temp->getElem();
  }
  catch (exception &e) {
  Record bad;
  cerr << e.what() << endl;
  return bad;
  }
}

/*---------------------------------------------------------------------------------------------*/


Record findUIN(DoublyLinkedList<Record>* p_book, DListNode<Record>* temp, string last_name, string first_name) {
  try {
  int UIN_input;
  cout << "There is more than one person by this last and first name." << endl;
  cout << "To specify who's phone number you wish to find, please input their UIN." << endl;
  cout << ": ";
  cin >> UIN_input;
  while(temp->getElem().getUIN() != UIN_input && temp != p_book->getAfterLast()){
    temp = temp->getNext();
  }
  if(temp == p_book->getAfterLast() || temp->getElem().getLastName() != last_name || 
    temp->getElem().getFirstName() != first_name){
    throw NoRecord("There is no record of this person.");
  }
  return temp->getElem();
  }
  catch (exception &e) {
  Record bad;
  cerr << e.what() << endl;
  return bad;
}
}
