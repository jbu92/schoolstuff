/*
//Course: 4050-212
//Author: Jim Haight
//Assignment: SMTP Final Project
//Purpose: This file contains the necessary wrappers for the Socket class.
*/

#include "ClientSocket.h"
#include <fstream>
#include <string>
#include <iostream>
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

}

string ClientSocket::UserInput(){
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
	cout << "Transferring file. This may take a moment.\n";
	RecvData(c_line,STRLEN);
	while(strcmp(c_line,"EOFEOFEOFEOFEOFEOF") != 0){
		fout << c_line << endl;
		//cout << c_line << endl;
		//system("pause");
		RecvData(c_line,STRLEN);
	}
	fout.close();
	SendData("EOF OK");
	RecvData(c_line,STRLEN);
	if(strcmp(c_line,"OK")!=0){
		cout << "ERROR\n";
	}
}

bool ClientSocket::Logon(){
	char message[STRLEN],recMessage[STRLEN];
    cin.ignore();//without this, it gets the return char from the last cin and ignores the following one!
    cout<<"Logon > ";
    cin.get( message, STRLEN );
    SendData( message );
	RecvData(recMessage,STRLEN);
	cout << recMessage << endl;
	if(strcmp(recMessage,"WELCOME")==0){
		return true;
	}
	else{
		return false;
	}
}
