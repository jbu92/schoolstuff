#include <iostream>
#include "Commission.h"
using namespace std;

Commission::Commission(){
	cout << "In default constructor\n";
	idNum = 0;
	base = 0;
	sales = 0;
	rate = 0;
}

Commission::Commission(int newIdNum, double newBase, double newSales, double newRate){
	cout << "In initializing constructor\n";
	idNum = newIdNum;
	base = newBase;
	sales = newSales;
	rate = newRate;
}

Commission::~Commission(){
	cout << "In destructor for id num: " << idNum << endl;
}

void Commission::copy(Commission input){
	idNum = input.idNum;
	base = input.base;
	sales = input.sales;
	rate = input.rate;
}

/*
Correct way to do a "copy constructor":
Commission::Commission(const Commission & orig){
	idNum = orig.idNum;
	base = orig.base;
	sales = orig.sales;
	rate = orig.rate;
}
*/

bool Commission::setIdNum(int newIdNum){
	if(newIdNum > 0 && newIdNum < 999){
		idNum = newIdNum;
		return true;
	}
	else
		return false;
}

bool Commission::setBase(double newBase){
	if(newBase > 0){
		base = newBase;
		return true;
	}
	else
		return false;
}

bool Commission::setSales(double newSales){
	if(newSales > 0){
		sales = newSales;
		return true;
	}
	else
		return false;
}

bool Commission::setRate(double newRate){
	if(newRate > 0 && newRate < .2){
		rate = newRate;
		return true;
	}
	else
		return false;
}

int Commission::getIdNum(){
	return idNum;
}

double Commission::getBase(){
	return base;
}

double Commission::getSales(){
	return sales;
}

double Commission::getRate(){
	return rate;
}

double Commission::calcSalary(){
	double salary;
	salary = base + sales * rate;
	return salary;
}

void Commission::operator= (const Commission& input){
	idNum = input.idNum;
	base = input.base;
	sales = input.sales;
	rate = input.rate;
}

bool Commission::operator== (const Commission& commission2){
	if(commission2.base == base && commission2.idNum == idNum && commission2.sales == sales && commission2.rate == rate){
		return true;
	}
	else
		return false;
}
