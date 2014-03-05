//#include "write.h"
#include "sort.h"
#include <iostream>
using namespace std;
int main(){
	unsigned int niggertitties[3] = {3232235777, 3249012993, 134744072};
	Sort sortObject;
	//Write writeObject;
	sortObject.sortArray(niggertitties,3);
	//writeObject.Output(niggertitties,3,"titttttties.txt");
	cout << niggertitties[0] << endl << niggertitties[1] << endl << niggertitties[3];
}