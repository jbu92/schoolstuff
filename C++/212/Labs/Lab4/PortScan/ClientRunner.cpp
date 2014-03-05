#include "ClientSocket.h"

int main(int argc, char **argv){
	int port;
	string ipAddress = "127.0.0.1";
	//bool done = FALSE;
	char recMessage[STRLEN] = "\0";
	char sendMessage[STRLEN];
   	//Client
   	cout<<"Enter an IP address, 127.0.0.1 is the loopback address"<<endl;
   	//cin>>ipAddress;
   	ClientSocket sockClient;
	//port = atoi(argv[1]);
	cout << "AND AWAY WE GO!\n";
	
	sockClient.KnockKnock( ipAddress.c_str());
	
	sockClient.CloseConnection();
system("pause");
}
