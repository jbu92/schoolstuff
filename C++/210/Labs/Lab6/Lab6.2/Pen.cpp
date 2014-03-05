#include "Pen.h"
#include <iostream>
#include <string>
using namespace std;

Pen::Pen() : Supply() {
	penColor = 0;
	inkColor = 0;
	cout << "In default constructor of Pen\n";
}

Pen::Pen(int penColor, int inkColor, string desc, int stockNo, int quant, double price) : Supply(desc,  stockNo,  quant,  price) {
	this->penColor = penColor;
	this->inkColor = inkColor;
	cout << "In full constructor of Pen\n";
}

Pen::Pen(const Pen& p1) : Supply(p1){
	penColor = p1.penColor;
	inkColor = p1.inkColor;
	cout << "In copy constructor of Pen\n";
}

Pen::~Pen(){
	cout << "\nIn destructor of Pen ink color " << colorAsStr(inkColor) << endl;
}

void Pen::print(){
	Supply::print();
	cout << "\tPen color: " << colorAsStr(getPenColor()) << "\tInk color: " << colorAsStr(getInkColor()) << endl;;
}

string Pen::colorAsStr(int number){
	switch(number){
		case 1:
			return "black";
			break;
		case 2:
			return "blue";
			break;
		case 3:
			return "red";
			break;
		case 0:
			return "N/A";
			break;
	}
}

int Pen::getPenColor(){
	return penColor;
}

int Pen::getInkColor(){
	return inkColor;
}

void Pen::setPenColor(int penColor){
	this->penColor = penColor;
}