#include "tbook.h"
#include <string>
#include <fstream>
#include <iostream>
using std::cout;

//See tbook.h for function descriptions

Tbook::Tbook(){
	entries = 0;
	ifstream fin;
	string line, name, areaCode, number;
	fin.open("rolodex.txt");
	if(fin.is_open()){ //Make sure file opens
		while(!fin.eof()){ //Read lines till the end of the file
			getline(fin, line); //Read the line
			if(line != ""){//In case there's a blank line at the end
				name = line.substr(0,line.find(","));
				areaCode = line.substr(line.find(",")+1,3);
				number = line.substr(line.length()-7);
				rolodex[entries].setName(name);
				rolodex[entries].setAreaCode(areaCode);
				rolodex[entries].setNumber(number);
				entries++;
			}
		}
		fin.close();
	}
}

void Tbook::write(Telephone entry){
	ofstream fout;
	fout.open("rolodex.txt", ios::app); //Open file in append mode, since there's no delete function, no biggie
	fout << endl << entry.getName() << "," << entry.getAreaCode() << "," << entry.getNumber(); //Add latest entry to the end of the file
	fout.close();
}

void Tbook::print(){
	cout << "Contact Information\n";
	//Run through rolodex, print each Telephone entry
	for(int i = 0; i < entries; i++){
		rolodex[i].print();
	}
}

Telephone Tbook::lookup(string name){
	string currName; //Current name to be checked
	bool success = false;
	Telephone empty;
	for(int i = 0; i < entries; i++){ //Run through the rolodex, checking names
		currName = rolodex[i].getName();
		if(currName == name){ //If found, return it
			return rolodex[i];
			success = true;
		}
	}
	if(!success){
		return empty; //If not found, return empty telephone
	}
}

bool Tbook::is_full(){
	if(entries <= 10)
		return false;
	else
		return true;
}

void Tbook::add(Telephone newEntry){
	if(!is_full()){ //Add entry if rolodex not full
		rolodex[entries] = newEntry;
		entries++;
		write(newEntry);
	}
	else{
		cerr << "Rolodex is full";
	}
}
