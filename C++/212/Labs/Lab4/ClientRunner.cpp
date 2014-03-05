#include "ClientSocket.h"
#include <iostream>
using namespace std;

int main(){
	int port = 8888;
	string ipAddress;
	bool done;
	char recMessage[STRLEN];
    char sendMessage[STRLEN];

	//Client
	cout<<"Enter an IP address, 127.0.0.1 is the loopback address"<<endl;
	cin>>ipAddress;
	ClientSocket sockClient;
	cout<<"ATTEMPTING TO CONNECT..."<<endl;
	sockClient.ConnectToServer( ipAddress.c_str(), port );
	//Connected
	while ( !done ){     
		sockClient.GetAndSendMessage();
		cout<<"\t--WAIT--"<<endl;
		sockClient.RecvData( recMessage, STRLEN );
		cout<<"Recv > "<<recMessage<<endl;
		if ( strcmp( recMessage, "end" ) == 0 || strcmp( sendMessage, "end" ) == 0 ){
			done = true;
		}
	}
	sockClient.CloseConnection();
}