#include "ServerSocket.h"
#include <fstream>
using namespace std;

void ServerSocket::StartHosting( int port ){
     Bind( port );
     Listen();
}

void ServerSocket::Listen(){
    //cout<<"LISTEN FOR CLIENT..."<<endl;
    
    if ( listen ( mySocket, 1 ) == SOCKET_ERROR ){
        cerr<<"ServerSocket: Error listening on socket\n";
        system("pause");
        WSACleanup();
        exit(15);
    }
    
    //cout<<"ACCEPT CONNECTION..."<<endl;
    
    acceptSocket = accept( myBackup, NULL, NULL );
    while ( acceptSocket == SOCKET_ERROR ){
        acceptSocket = accept( myBackup, NULL, NULL );
    }
    mySocket = acceptSocket;
}

void ServerSocket::Bind( int port ){
    myAddress.sin_family = AF_INET;
    myAddress.sin_addr.s_addr = inet_addr( "0.0.0.0" );
    myAddress.sin_port = htons( port );
    
    //cout<<"BIND TO PORT "<<port<<endl;

    if ( bind ( mySocket, (SOCKADDR*) &myAddress, sizeof( myAddress) ) == SOCKET_ERROR ){
        cerr<<"ServerSocket: Failed to connect\n";
        system("pause");
        WSACleanup();
        exit(14);
	}
}

int ServerSocket::GetCommand(string &parameter){
	string command;
	string message_str;
	char message[STRLEN];
	RecvData(message,STRLEN);
	message_str=message;
	if(message_str.find(' ') > 1){
		command = message_str.substr(0,message_str.find(" "));
		parameter = message_str.substr(message_str.find(" ")+1);
	}
	else{
		command = message;
	}
	//use strcmp to do a switchcase for the rest of the shit, maybe make it a return value
	//maybe break it up with substr to get dem parameters?
	if(strcmp(command.c_str(),"list") == 0){
		cout << "list";
		return 1;
	}
	else if(strcmp(command.c_str(),"send") == 0){
		cout << "send";
		return 2;
	}
	else if(strcmp(command.c_str(),"quit") == 0){
		cout << "quittttted";
		return 3;
	}
	else{
		//Default. unrecognized command.
		return 4;
	}
	
}

bool ServerSocket::Logon(string username){
	//Validate logon name, basically...
	char message[STRLEN];
	RecvData(message,STRLEN);
	if(strcmp(message,username.c_str())==0){
		cout << "username accepted\n";
		SendData("Username Accepted");
		return true;
	}
	else{
		SendData("Incorrect logon. please try again");
		return false;
	}
}

void ServerSocket::List(){
	//Send the file list
	string line;
	char c_line[STRLEN];
	system("dir >> list.txt");
	ifstream fin;
	fin.open("list.txt");
	while(!fin.eof()){
		getline(fin,line);
		strcpy(c_line, line.c_str());
		SendData(c_line);
	}
	fin.close();
	//SendData("listing penises");
}

void ServerSocket::Send(string parameter){
	//Receive the file
	string line;
	char c_line[STRLEN];
	ifstream fin;
	fin.open(parameter.c_str());
	while(!fin.eof()){
		getline(fin,line);
		strcpy(c_line, line.c_str());
		SendData(c_line);
	}
	SendData("EOFEOFEOFEOFEOFEOF");
	
	
}

void ServerSocket::Quit(){
	SendData("GOODBYE");
}
