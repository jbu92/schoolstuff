#include "telephone.h"
#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;

//See telephone.h for function definitions

Telephone::Telephone(){
	name = "";
	areaCode = "";
	number = "";
}

Telephone::Telephone(string newName, string newAreaCode, string newNumber){
	name = newName;
	areaCode = newAreaCode;
	number = newNumber;
}

void Telephone::print(){
	//Even though the first paragraph of the instructions say to format it as (XXX) XXX-XXXX, since you later say NOT to do that.
	cout << name << "," << areaCode << "," << number << endl;
}

string Telephone::getName(){
	//Preeeeeetty self-explanitory...
	return name;
}

int Telephone::getAreaCode(){
	int i = atoi(areaCode.c_str());
	return i;
}

int Telephone::getNumber(){
	int i = atoi(number.c_str());
	return i;
}

void Telephone::setName(string newName){
	name = newName;
}

bool Telephone::setAreaCode(string newAreaCode){
	int i = atoi(newAreaCode.c_str());
	if(i > 100 && i < 1000){ //Input validation
		areaCode = newAreaCode;
		return true;
	}
	else{ //Defaultification
		areaCode = "100";
		return false;
	}
}

bool Telephone::setNumber(string newNumber){
	int j = atoi(newNumber.c_str());
	if(j >= 1000000 && j < 10000000){ //Input validation
		number = newNumber;
		return true;
	}
	else{ //Defaultification
		number = "1000000"; 
		return false;
	}
}
