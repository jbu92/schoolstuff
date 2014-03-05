class Node{
	private:
		int data;
		Node * next;
	public:
		Node();
		Node(int, Node*);
		int getInfo();
		Node* getNext();
		void setInfo(int);
		void setNext(Node*);
};
typedef Node* NodePtr;