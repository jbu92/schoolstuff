#include "Node.h"
#include <iostream>

Node::Node(){
	next = NULL;
	data = 0;
}

Node::Node(int newData, NodePtr newNext){
	data = newData;
	next = newNext;
}

int Node::getInfo(){
	return data;
}

NodePtr Node::getNext(){
	return next;
}

void Node::setInfo(int newData){
	data = newData;
}

void Node::setNext(NodePtr newNext){
	next = newNext;
}