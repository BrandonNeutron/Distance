//NAME: Brandon Hahn
//SECTION: 4
#include <iostream>
#include "distance.h"
using namespace std;

//steadily adds stuff into the ostream thing
ostream& operator <<(ostream& o, const Distance& d){
	o << '(';
	if(d.miles > 0)
		o << d.miles << "m ";
	if(d.yards > 0)
		o << d.yards << "y ";
	if(d.feet > 0)
		o << d.feet << "' ";
	if(d.inches >= 0)
		o << d.inches << "\"";
	o << ')';
	return o;
}

//adds it all in at once, then simplifies it all
istream& operator >>(istream& i,Distance& d){
	char comma;
	i >> d.miles >> comma >> d.yards >> comma >> d.feet >> comma >> d.inches;
	if (d.inches >= 12){
		d.feet = d.feet + (d.inches / 12);
		d.inches = d.inches % 12;
	}
	if(d.feet >= 3){
		d.yards = d.yards + (d.feet /3);
		d.feet = d.feet % 3;
	}
	if (d.yards >= 1760){
		d.miles = d.miles + (d.yards /1760);
		d.yards = d.yards % 1760;
	}
	return i;
}

//adds each one, then simplifies
Distance operator+(const Distance& d1, const Distance& d2){
	Distance d3;
	d3.miles = d1.miles + d2.miles;
	d3.yards = d1.yards + d2.yards;
	d3.feet = d1.feet + d2.feet;
	d3.inches = d1.inches + d2.inches;

	if(d3.inches >=12){
		d3.feet = d3.feet + (d3.inches /12);
		d3.inches = d3.inches % 12;
	}
	if(d3.feet >= 3){
		d3.yards = d3.yards + (d3.feet/3);
		d3.feet = d3.feet % 3;
	}
	if(d3.yards >= 1760){
		d3.miles = d3.miles + (d3.yards/1760);
		d3.yards = d3.yards % 1760;
	}
	return d3;
}

Distance operator-(const Distance& d1, const Distance& d2){
	Distance d3;
	d3.inches = d1.inches - d2.inches;
	d3.feet = d1.feet - d2.feet;
	d3.yards = d1.yards - d2.yards;
	d3.miles = d1.miles - d2.miles;
//uses already overloaded comparison op to check
	if (d2 > d1){
		d3.inches = 0;
		d3.feet = 0;
		d3.yards = 0;
		d3.miles = 0;
		return d3;
	}
//provided the thing isn't smaller than what's being subtracted,
//it simplifies
	if (d3.yards < 0){
		d3.miles = d3.miles - 1;
		d3.yards = d3.yards + 1760;
	}
	if (d3.feet < 0){
		d3.yards = d3.yards - 1;
		d3.feet = d3.feet + 3;
	}
	if (d3.inches < 0){
		d3.feet = d3.feet - 1;
		d3.inches = d3.inches + 12;
	}
	return d3;
}

Distance operator*(const Distance& d1, int i){
	Distance d2;
	d2.miles = d1.miles * i;
	d2.yards = d1.yards * i;
	d2.feet = d1.feet * i;
	d2.inches = d1.inches * i;

	if(d2.inches >= 12){
		d2.feet = d2.feet + (d2.inches / 12);
		d2.inches = d2.inches % 12;
	}
	if(d2.feet >= 3){
		d2.yards = d2.yards + (d2.feet /3);
		d2.feet = d2.feet % 3;
	}
	if(d2.yards >= 1760){
		d2.miles = d2.miles + (d2.yards/1760);
		d2.yards = d2.yards % 1760;
	}
	return d2;
}

//still not sure if all of the == are necessary,
//but it works and i don't want to alter it
bool operator>(const Distance& d1, const Distance& d2){
	if (d1.miles > d2.miles)
		return true;
	if (d1.miles == d2.miles && d1.yards > d2.yards)
		return true;
	if (d1.miles == d2.miles && d1.yards == d2.yards && d1.feet > d2.feet)
		return true;
	if (d1.miles == d2.miles && d1.yards == d2.yards && d1.feet == d2.feet && d1.inches > d2.inches)
		return true;
	return false;
}

bool operator<(const Distance& d1, const Distance& d2){
	if(d2.miles > d1.miles)
		return true;
	if(d2.miles == d1.miles && d2.yards > d1.yards)
		return true;
	if(d2.miles == d1.miles && d2.yards == d1.yards && d2.feet > d1.feet)
		return true;
	if(d2.miles == d1.miles && d2.yards == d1.yards && d2.feet == d1.feet && d2.inches > d1.inches)
		return true;
	return false;
}

bool operator==(const Distance& d1, const Distance& d2){
	if(d1.miles == d2.miles && d1.yards == d2.yards && d1.feet == d2.feet && d1.inches == d2.inches)
		return true;
	return false;
}

//these three ops use other overloaded comparison ops
bool operator>=(const Distance& d1, const Distance& d2){
	if (d1 > d2 || d1 == d2)
		return true;
	return false;
}

bool operator<=(const Distance& d1, const Distance& d2){
	if(d2 > d1 || d2 == d1)
		return true;
	return false;
}

bool operator!=(const Distance& d1, const Distance& d2){
	if (d1==d2)
		return false;
	return true;
}

//makes a temp Distance object, then increments, then returns temp
Distance Distance::operator++(int){
	Distance d = *this;

	++inches;

	if(inches == 12){
		++feet;
		inches = 0;
	}
	if(feet == 3){
		++yards;
		feet = 0;
	}
	if(yards == 1760){
		++miles;
		yards = 0;
	}
	return d;
}

//just straight up increments it
Distance& Distance::operator++(){
	++inches;
	
	if(inches == 12){
		++feet;
		inches = 0;
	}
	if(feet == 3){
		++yards;
		feet = 0;
	}
	if(yards == 1760){
		++miles;
		yards = 0;
	}
	return *this;
}

//same as before, uses a temp object to post-increment
Distance Distance::operator--(int){
	Distance d = *this;
	
	if(miles == 0 && yards == 0 && feet == 0 && inches == 0)
		return d;
	--inches;

	if(inches < 0){
		--feet;
		inches = inches + 12;
	}
	if(feet < 0){
		--yards;
		feet = feet + 3;
	}
	if(yards < 0){
		--miles;
		yards = yards + 1760;
	}
	return d;
}

Distance& Distance::operator--(){
	if(miles == 0 && yards == 0 && feet == 0 && inches == 0)
		return *this;
	--inches;
	if(inches < 0){
		--feet;
		inches = inches + 12;
	}
	if(feet <0){
		--yards;
		feet = feet + 3;
	}
	if(yards < 0){
		--miles;
		yards = yards + 1760;
	}
	return *this;
}

//boring old constructors
Distance::Distance(){
	miles = 0;
	yards = 0;
	feet = 0;
	inches = 0;
}

Distance::Distance(int inch){
	if (inch < 0)
		inches = 0;
	else
		inches = inch;
	feet = 0;
	yards = 0;
	miles = 0;
	if (inches >= 12){
		feet = inches / 12;
		inches = inches % 12;
	}
	if (feet >= 3){
		yards = feet / 3;
		feet = feet % 3;
	}
	if (yards >= 1760){
		miles = yards / 1760;
		yards = yards % 1760;
	}
}

Distance::Distance(int mile, int yard, int foot, int inch){
	miles = mile;
	yards = yard;
	feet = foot;
	inches = inch;
	if(miles < 0 || yards < 0 || feet < 0 || inches < 0){
		miles = 0;
		yards = 0;
		feet = 0;
		inches = 0;
	}
	if(inches >= 12){
		feet = feet + (inches / 12);
		inches = inches % 12;
	}
	if(feet >= 3){
		yards = yards + (feet / 3);
		feet = feet % 3;
	}
	if(yards >= 1760){
		miles = miles + (yards / 1760);
		yards = yards % 1760;
	}

}
