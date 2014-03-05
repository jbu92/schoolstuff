#include "sort.h"
#include <iostream>
#include <algorithm>

using namespace std;
Sort::Sort(){

}
void Sort::sortArray(unsigned int * data, int size){
	
	unsigned int temp[size]; //YAY TEMPORARY ARRAYS
	//std::sort(data, data + size);
	int count = 0;
	for(int i = 0; i< size; i++){
		
			
		for(int j = 0; j < i; j++){
			if (data[i] != temp[j]){
				if (data[i] < temp[j]){
					for(int k = count; k > j; k--){
						temp[k+1] = temp[k]; //Downshift to make room
					}
					temp[j] = data[i];
					count++; 
				}
			}
			
		}
	}
	data = temp;
}
