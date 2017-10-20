//NAME: Brandon Hahn
//SECTION: 4
#include <iostream>
using namespace std;

class Distance{
//iostream operators
	friend ostream& operator << (ostream& o,const Distance& d);
	friend istream& operator >> (istream& i, Distance& d);
//basic maths	
	friend Distance operator+(const Distance& d1, const Distance& d2);
	friend Distance operator-(const Distance& d1, const Distance& d2);
	friend Distance operator*(const Distance& d1, int i);
//comparison overloads
	friend bool operator>(const Distance& d1, const Distance& d2);
	friend bool operator<(const Distance& d1, const Distance& d2);
	friend bool operator>=(const Distance& d1, const Distance& d2);
	friend bool operator<=(const Distance& d1, const Distance& d2);
	friend bool operator==(const Distance& d1, const Distance& d2);
	friend bool operator!=(const Distance& d1, const Distance& d2);

//	friend Distance operator++(int);
public:
	Distance();
	Distance(int inch);
	Distance(int mile, int yard, int foot, int inch);
//increment overloads
	Distance& operator++();
	Distance operator++(int);
	Distance& operator--();
	Distance operator--(int);

private:
	int miles, yards, feet, inches;
};
