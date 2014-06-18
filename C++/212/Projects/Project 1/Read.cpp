/*Ident header
//Course: 4002-212
//Author: Jim Haight
//Assignment: Project 1
*/
#include <algorithm>
#include <iostream>

#include "Read.h"
using namespace std;



Read::Read(string newFileName, unsigned int * data){
	filename = newFileName;
	fin.open(filename.c_str());
	filesize = std::count(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>(), '\n');//Count the lines in the file
	//data = new int [filesize];	
	fin.close();
}

void Read::getData(unsigned int *dataStorage){
	fin.open(filename.c_str());
	int one,two,three,four; //For holding the four bytes of addressness
	getline(fin, line); //GET RID OF YON FIRST LINE
	//cout << "entering for loop\n";
	for(int i = 0; i < filesize-1; i++){ //Read ye here yon lines of yon file, one at yon time (filesize-1 because there's a blank line
		getline(fin, line);
		
		//And now we substr the shit out of it until we get to the correct (dest) field
		line = line.substr(line.find("\",\"")+3); //One Mississippi
		line = line.substr(line.find("\",\"")+3); //Two Mississippi
		line = line.substr(line.find("\",\"")+3); //Three Mississippi, there it is!
		
		//Now line is X.X.X.X","BLAHBLAHBLAHBLAHBLAH
		//So we find the next ","
		line = line.substr(0, line.find("\",\"")); //And we get rid of everything else
		
		//Make sure that what we got is an IP address and not mamma-jammin' MAC
		if(atoi((line.substr(0,line.find("."))).c_str())){
			//Separate into bytes...
			one = atoi((line.substr(0,line.find("."))).c_str());
			line = line.substr(line.find(".")+1);
			two = atoi((line.substr(0,line.find("."))).c_str());
			line = line.substr(line.find(".")+1);
			three = atoi((line.substr(0,line.find("."))).c_str());
			line = line.substr(line.find(".")+1);
			four = atoi((line.substr(0,line.find("."))).c_str());
		
			//Then convert to dotless. YEAH BETCH!
			dataStorage[i] = four + (256 * (three + (256 * (two + (256 * one)))));
		}
		
		//cout << i << endl;
	}
	//cout << "is it skipping the for loop?";
	fin.close();
}

int Read::getFileSize(){
	return filesize;
}
