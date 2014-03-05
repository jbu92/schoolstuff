#include "write.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Write::Write()
{
}

void Write::Output(unsigned int * data, int size, string filename)
{	
	int octet[4];

	ofstream writeFile;
	writeFile.open(filename.c_str());
	int add;
	for(int i=0; i<size; i++)
	{
		if (data[i] != 0){
			add = data[i];
			
			//and first byte with 255
			//might not be portable :(
			octet[0] = add & 0xFF;
			//shift right 8
			octet[1] = (add>>8) & 0xFF;
			octet[2] = (add>>16) & 0xFF;
			octet[3] = (add>>24) & 0xFF;

			//printf("%d.%d.%d.%d", octet[3],octet[2],octet[1],octet[0]);
			writeFile << octet[3]<< "." << octet[2]<< "." << octet[1]<<"." << octet[0] << endl;
			//cout << i << endl;
			}
	}

	//writeFile << data;
	writeFile.close();
}