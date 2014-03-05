#include "ClientSocket.h"
#include <fstream>
#include <string>
using namespace std;

void ClientSocket::ConnectToServer( const char *ipAddress, int port ){
    myAddress.sin_family = AF_INET;
    myAddress.sin_addr.s_addr = inet_addr( ipAddress );
    myAddress.sin_port = htons( port );
    char boop[STRLEN];
    //cout<<"CONNECTED"<<endl;

    if ( connect( mySocket, (SOCKADDR*) &myAddress, sizeof( myAddress ) ) == SOCKET_ERROR ){
        cerr<<"ClientSocket: Failed to connect\n";
        system("pause");
        WSACleanup();
        exit(13);
    } 
    else{
         RecvData(boop, STRLEN);
         cout << boop << endl;
         }
}

string ClientSocket::UserInput(string filename){
    string userInput;
	char message[STRLEN];
    cin.ignore();//without this, it gets the return char from the last cin and ignores the following one!
    cout<<"Send > ";
    cin.get( message, STRLEN );
    SendData( message );
	userInput = message;
	return userInput;
}

void ClientSocket::GetFile(string filename){
	string line;
	char c_line[STRLEN];
	ofstream fout;
	fout.open(filename.c_str());
	
	RecvData(c_line,STRLEN);
	while(strcmp(c_line,"EOFEOFEOFEOFEOFEOF") != 0){
		fout << c_line;
		RecvData(c_line,STRLEN);
	}
}
