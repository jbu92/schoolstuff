#include "sort.h"
#include <iostream>
#include <algorithm>

using namespace std;
Sort::Sort(){

}
void Sort::sortArray(unsigned int * data, int size){
	
	//unsigned int temp[size]; //YAY TEMPORARY ARRAYS
	
	//sort array
	std::sort(data, data + size);

	
	for(int i = 0; i< size; i++){
		
		if(data[i] == data[i+1]){
			data[i] = 0;
		}
	}
		
	
	
	
	/*
	int count = 0;

				
				if (data[i] < temp[j]){
					for(int k = count; k > j; k--){
						temp[k+1] = temp[k]; //Downshift to make room
					}
					temp[j] = data[i];
					count++; 
				}
			}
			
		}
		cout << i << endl;
	}
	
	*/
	//data = temp;
}
