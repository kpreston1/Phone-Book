#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>
#include <stdexcept>
#include "Record.h"

using namespace std;

/*-------------Exception for handeling records that do not exist--------------*/

struct NoRecord : std::range_error {
  explicit NoRecord(char const* msg=NULL): range_error(msg) {}
};

/*----------------------------------------------------------------------------*/

struct FileError : std::range_error {
  explicit FileError(char const* msg=NULL): range_error(msg) {}
};

// extend range_error from <stdexcept>
struct EmptyDLinkedListException : std::range_error {
  explicit EmptyDLinkedListException(char const* msg=NULL): range_error(msg) {}
};

/*----------------------------------------------------------------------------*/

template <class T>
class DoublyLinkedList; // class declaration
template <class N>
// list node
class DListNode {
private: N obj;
  DListNode *prev, *next;
  template <class T>
  friend class DoublyLinkedList;
public:
  DListNode(N e=N(), DListNode *p = NULL, DListNode *n = NULL)
    : obj(e), prev(p), next(n) {}
  N getElem() const { return obj; }
  DListNode * getNext() const { return next; }
  DListNode * getPrev() const { return prev; }
};

/*----------------------------------------------------------------------------*/

// doubly linked list
template <class T>
class DoublyLinkedList {
protected: DListNode<T> header, trailer;
public:
  DoublyLinkedList() : header(T()), trailer(T()) // constructor
  { header.next = &trailer; trailer.prev = &header; }
  DoublyLinkedList(const DoublyLinkedList& dll); // copy constructor
  ~DoublyLinkedList(); // destructor
  DoublyLinkedList& operator=(const DoublyLinkedList& dll); // assignment operator
  // return the pointer to the first node
  DListNode<T> *getFirst() const { return header.next; } 
  // return the pointer to the trailer
  const DListNode<T> *getAfterLast() const { return &trailer; }
  // return if the list is empty
  bool isEmpty() const { return header.next == &trailer; }
  T first() const; // return the first object
  T last() const; // return the last object
  void insertFirst(T newobj); // insert to the first of the list
  T removeFirst(); // remove the first node
  void insertLast(T newobj); // insert to the last of the list
  T removeLast(); // remove the last node
  DListNode<T>* insertOrderly(const T& rec);
};

template<typename T>
Record findLastName(DoublyLinkedList<T>* p_book, string i_1);
template<typename T>
Record findFirstName(DoublyLinkedList<T>* p_book, DListNode<T>* temp);
template<typename T>
Record findUIN(DoublyLinkedList<T>* p_book, DListNode<T>* temp);

/*----------------------------------------------------------------------------*/

// output operator declaration
template<typename T>
ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll);

/*----------------------------------------------------------------------------*/

// copy constructor
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& dll) //O(n)
{
  // Initialize the list
  header = T(); trailer = T();
  header.next = &trailer; trailer.prev = &header;
  DListNode<T> *node = dll.getFirst();

  header.next = node;
  while(node != dll.getAfterLast()) { // runs n times, O(n)
    insertLast(node->getElem());
    node = node->getNext();
  }

/*----------------------------------------------------------------------------*/

}
// assignment operator
template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& dll) //O(n)
{
  if(this == &dll) {
    return *this;
  }
  // Delete the whole list
  DListNode<T> *prev_node, *node = header.next;
  while (node != &trailer) { //runs n times, O(n)
    prev_node = node;
    node = node->next;
    delete prev_node;
  }
  node = dll.getFirst();
  header.next = node;
  while(node != dll.getAfterLast()) { //runs n times, O(n)
    insertLast(node->getElem());
    node = node->getNext();
  }

  return *this;
}

/*----------------------------------------------------------------------------*/

// insert the object to the first of the linked list
template<typename T>
void DoublyLinkedList<T>::insertFirst(T newobj)
{ 
  DListNode<T> *newNode = new DListNode<T>(newobj, &header, header.next);
  header.next->prev = newNode;
  header.next = newNode;
}

/*----------------------------------------------------------------------------*/

// insert the object to the last of the linked list
template<typename T>
void DoublyLinkedList<T>::insertLast(T newobj)
{
  DListNode<T> *newNode = new DListNode<T>(newobj, trailer.prev,&trailer);
  trailer.prev->next = newNode;
  trailer.prev = newNode;
}

/*----------------------------------------------------------------------------*/

// remove the first object of the list
template<typename T>
T DoublyLinkedList<T>::removeFirst()
{ 
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  DListNode<T> *node = header.next;
  node->next->prev = &header;
  header.next = node->next;
  T obj = node->obj;
  delete node;
  return obj;
}

/*----------------------------------------------------------------------------*/

// remove the last object of the list
template<typename T>
T DoublyLinkedList<T>::removeLast()
{
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  DListNode<T> *node = trailer.prev;
  node->prev->next = &trailer;
  trailer.prev = node->prev;
  T obj = node->obj;
  delete node;
  return obj;
}

/*----------------------------------------------------------------------------*/

// destructor
template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
  DListNode<T> *prev_node, *node = header.next;
  while (node != &trailer) {
    prev_node = node;
    node = node->next;
    delete prev_node;
  }
  header.next = &trailer;
  trailer.prev = &header;
}

/*----------------------------------------------------------------------------*/

// return the first object
template<typename T>
T DoublyLinkedList<T>::first() const
{ 
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  return header.next->obj;
}

/*----------------------------------------------------------------------------*/

// return the last object
template<typename T>
T DoublyLinkedList<T>::last() const
{
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  return trailer.prev->obj;
}

/*----------------------------------------------------------------------------*/

// return the list length
template<typename T>
T DoublyLinkedListLength(DoublyLinkedList<T>& dll) {
  DListNode<T> *current = dll.getFirst();
  int count = 0;
  while(current != dll.getAfterLast()) {
    count++;
    current = current->getNext(); //iterate
  }
  return count;
}

/*----------------------------------------------------------------------------*/

// output operator
template<typename T>
ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll) {
  DListNode<T> *node = dll.getFirst();
  while(node != dll.getAfterLast()) { //runs n times, O(n)
    if(!dll.isEmpty())
    out << node->getElem();
    node = node->getNext();
}
  
  return out;
}


/*---------------------------------------------------------------------------------------------*/

template<typename T>
DListNode<T>* DoublyLinkedList<T>::insertOrderly(const T& rec)
{
	DListNode<T> *new_rec = new DListNode<T>(rec);
	DListNode<T> *temp = header.next;
  if(temp == getAfterLast()) {
    insertLast(rec);
    return header.next;
  }
	while( temp != getAfterLast()) {
    if (temp->getElem() < new_rec->getElem()) {
      new_rec->next = temp;
      new_rec->prev = temp->prev;
      temp->prev->next = new_rec;
      temp->prev = new_rec;
      return new_rec;
    }
    temp = temp->next;
	}
  insertLast(rec);
	return trailer.prev;
}