#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>
#include <stdexcept>
#include <vector>
//#include "Record.h"
#include "templated_doubly.h"

using namespace std;

/*----------------------------------------------read_in.h---------------------------------------*/

void menu (vector<DoublyLinkedList<Record>>& get_phone_num);

/*----------------------------------------------------------------------------------------*/

void read_to_vector (vector<DoublyLinkedList<Record>>& book);

/*----------------------------------------------------------------------------------------*/

void print_phonebook (const vector<DoublyLinkedList<Record>>& book);

/*----------------------------------------------------------------------------------------*/

int get_ascii(const string& work);

/*----------------------------------------------------------------------------------------*/

Record prompt(vector<DoublyLinkedList<Record>>& get_phone_num);

/*----------------------------------------------------------------------------------------*/

Record findLastName(DoublyLinkedList<Record>* p_book, string last_name);

/*----------------------------------------------------------------------------------------*/

Record findFirstName(DoublyLinkedList<Record>* p_book, DListNode<Record>* temp, string last_name);

/*---------------------------------------------------------------------------------------*/

Record findUIN(DoublyLinkedList<Record>* p_book, DListNode<Record>* temp, string last_name, string first_name);
