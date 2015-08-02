#include <string>
#include <iostream>

using namespace std;

/*---------------------------record class------------------------------*/

class Record {
private: 
	string last_name, first_name, phone;
	int uin = 0;
public:  
	Record(string l = "", string f = "", int u = 0, string p_num = "") :
	last_name(l), first_name(f), uin(u), phone(p_num) {}
	string getFirstName() const { return first_name; }
	string getLastName() const { return last_name; }
	int getUIN() const { return uin; }
	string getPhone() const { return phone; }
	bool operator<(const Record& rhs);
};

/*--------------------------------------------------------------------*/

ostream& operator<<(ostream& out, const Record& rec);
 