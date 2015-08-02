#include "Record.h"
#include <string>
#include <iostream>

using namespace std;

/*---------------------------------------------------------------------------------------------*/

bool Record::operator<(const Record& rhs) 
{
if (getLastName().compare(rhs.getLastName()) < 0) {
	return false;
}
if (getLastName().compare(rhs.getLastName()) > 0) {
	return true;
}
if(getFirstName().compare(rhs.getFirstName()) < 0) {
	return false;
}
if(getFirstName().compare(rhs.getFirstName()) > 0) {
	return true; 
} 
if(getUIN() < rhs.getUIN()) {
	return false;
}
return true;
}

/*---------------------------------------------------------------------------------------------*/


ostream& operator<<(ostream& out, const Record& rec) {
  out << endl << "Last Name: " << rec.getLastName() << endl 
      << "First Name: " << rec.getFirstName() << endl 
      << "UIN: " << rec.getUIN() << endl 
      << "Phone Number: " << rec.getPhone() << endl << endl;

  return out;
}