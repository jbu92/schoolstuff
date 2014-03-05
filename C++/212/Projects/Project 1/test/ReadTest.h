/*Ident header
//Course: 4002-212
//Author: James Haight
*/
#include <iostream>
#include "Read.h"
using namespace std;

int main(){
	int * data; //Because dynamic allocation was failing at 2048
	Read readFile("Captured12072008.csv", data);
	readFile.getData(data);
}