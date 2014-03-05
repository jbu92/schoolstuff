#include "ServerSocket.h"
#include <iostream>
using namespace std;

int main(int argc, char **argv){
	int port;
	bool done;
	char recMessage[STRLEN];
    char sendMessage[STRLEN];
	
	port = atoi(argv[1]);
	ServerSocket sockServer;
	cout<<"HOSTING..."<<endl;
	sockServer.StartHosting( port );
	//Connected
	sockServer.SendData("HELO");//Send ye here yon connection message
	while ( !done )
	{
		cout<<"\t--WAIT--"<<endl;
		sockServer.RecvData( recMessage, STRLEN );
		cout<<"Recv > "<<recMessage<<endl;
		sockServer.GetAndSendMessage();
		if ( strcmp( recMessage, "end" ) == 0 || strcmp( sendMessage, "end" ) == 0 ){
			done = true;
		}
	}
}
