#include "ClientSocket.h"

int main(int argc, char **argv){
	int port;
	string ipAddress;
	bool done = FALSE;
	char recMessage[STRLEN];
    char sendMessage[STRLEN];
	string input;
    
    port = atoi(argv[1]);
	//Client
	cout<<"Enter an IP address, 127.0.0.1 is the loopback address"<<endl;
	cin>>ipAddress;
	ClientSocket sockClient;
	cout<<"ATTEMPTING TO CONNECT..."<<endl;
	sockClient.ConnectToServer( ipAddress.c_str(), port );
	//Connected
	//sockClient.RecvData(recMessage, STRLEN);//Get ye here yon connection message
	//cout << recMessage<<endl;
	while ( !done ){     
		//sockClient.GetAndSendMessage(); //Sends input message
		input = sockClient.UserInput("test.txt");
		cout<<"\t--WAIT--"<<endl;
		sockClient.RecvData( recMessage, STRLEN );
		cout<<"Recv > "<<recMessage<<endl;
		/*
		if ( strcmp( recMessage, "end" ) == 0 || strcmp( sendMessage, "end" ) == 0 ){
			done = true;
		}
		*/
		
	}
	sockClient.CloseConnection();
}
