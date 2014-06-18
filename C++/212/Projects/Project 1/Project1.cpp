/*Ident header
//Course: 4002-212
//Author: Jim Haight
*/
#include <iostream>

#include "Read.h"
#include "Write.h"
#include "Sort.h"
using namespace std;

int main(){
	unsigned int data[20000];
	
	Read readObject("Captured12072008.csv", data);
	Write writeObject;
	Sort sortObject;
	
	readObject.getData(data);
	sortObject.sortArray(data, readObject.getFileSize());
	writeObject.Output(data, readObject.getFileSize(), "Ye Olde Output File.txt");
	
	//system("echo HEY LOOK ITS AN EXTERNAL FUNCTION CALL");
	return 0;
}
