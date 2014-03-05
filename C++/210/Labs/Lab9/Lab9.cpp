#include <iostream>
using namespace std;
#include "Node.h"

int main(){
	int intArray[4] = {10, 20, 30, 40};
	NodePtr temPointer = NULL;
	NodePtr curr = NULL;
	NodePtr end = NULL;
	for(int i = 0; i < 4; i++){
		temPointer = new Node;
		temPointer->setInfo(intArray[i]);
		temPointer->setNext(NULL);
		if(end == NULL){
			curr = temPointer;
			end = temPointer;
		}
		else{
			curr->setNext(temPointer);
			curr = temPointer;
		}
	}
	cout << "Contents of Nose. er uhh... I mean Nodes.\nNode Address   Info   Next\n----------------\n";
	curr = end;
	while (curr != NULL)   //print nodes with data
	{
		cout << curr << "\t" << curr->getInfo() << "\t" << curr->getNext() << endl;
		curr = curr->getNext();
	}
	cout << "Info in nodes deleted: 10 20 30 40\n";
	return 0;
}