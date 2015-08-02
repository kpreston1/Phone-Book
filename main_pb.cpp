#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>
#include <stdexcept>
#include <vector>
//#include "Record.h"
#include "read_in.h"
//#include "templated_doubly.h"

using namespace std;

int main() {
	vector<DoublyLinkedList<Record>> point(26);
	read_to_vector(point);
	print_phonebook(point);
	menu(point);



	cout << "Testing to see if the Record class stores it's data correctly." << endl;
	Record r("Preston", "Kyle", 749873924, "1283791273");
	cout << r << endl;
	cout << "Testing to see if the Record object 'r' is inserted into the double linked list 'list' properly." << endl;
	DoublyLinkedList<Record> list;
	list.insertFirst(r);
	cout << list << endl;

    cout << "Testing to see if the Record object 'k' is inserted properly using insertOrderly." << endl;

	Record k("Peterson", "Micah", 749873924, "1283791273");
	list.insertOrderly(k);

	cout << list << endl;

	menu(point);

}