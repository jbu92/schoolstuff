#include "ServerSocket.h"

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