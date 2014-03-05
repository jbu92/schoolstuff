#include "MemPen.h"
#include <iostream>
#include <string>
using namespace std;

MemPen::MemPen() : Pen(){
	memory = 0;
	cout << "In default constructor of MemPen\n";
}

MemPen::MemPen(int memory, int penColor, int inkColor, string desc, int stockNo, int quant, double price) : Pen( penColor,  inkColor,  desc,  stockNo,  quant,  price){
	this ->memory = memory;
	cout << "In full constructor of MemPen\n";
}

MemPen::MemPen(const MemPen& p1) : Pen(p1){
	memory = p1.memory;
}

MemPen::~MemPen(){
	cout << "In destructor of MemPen memory size " << memory << endl;
}

void MemPen::print(){
	Pen::print();
	cout << "\tHas built-in memory of " << memory  << "MB\n";
}

int MemPen::getMem(){
	return memory;
}

void MemPen::setMem(int memory){
	this->memory = memory;
}
