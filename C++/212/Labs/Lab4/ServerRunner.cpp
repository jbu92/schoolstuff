#include "ServerSocket.h"

int main(){
	int port = 8888;
	string ipAddress;
	bool done;
	char recMessage[STRLEN];
    char sendMessage[STRLEN];
	
	ServerSocket sockServer;
	cout<<"HOSTING..."<<endl;
	sockServer.StartHosting( port );
	//Connected
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