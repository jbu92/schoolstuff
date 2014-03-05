#include "Supply.h"
#include <string>
#include <iostream>
using namespace std;
Supply::Supply(){
	desc = "Unknown";
	stockNo = 0;
	quant = 0;
	price = 0;
	cout << "In default constructor\n";
}
Supply::Supply(string desc, int stockNo, int quant, double price){
	this->desc = desc;
	this->stockNo = stockNo;
	this->quant = quant;
	this->price = price;
	cout << "In full constructor\n";
}
Supply::Supply(const Supply& s2){
	desc = s2.desc;
	stockNo = s2.stockNo;
	quant = s2.quant;
	price = s2.price;
	cout << "In copy constructor\n";
}
Supply::~Supply(){
	cout << "In destructor. Price: " << price << endl;
}
void Supply::print(){
	cout << desc << endl << "\t" << stockNo << "\t" << quant << "\t" << price << endl;
}
double Supply::getPrice(){
	return price;
}
void Supply::setPrice(double price){
	this->price = price;
}
