/*
//Course: 4050-212
//Author: Jim Haight
//Derivative of code provided by Dan Kennedy
//Assignment: SMTP Final Project
*/

#pragma once
#include <iostream>
#include "WinSock2.h"
using namespace std;
const int STRLEN = 256;
class Socket
{
    protected:
        WSADATA wsaData;
        SOCKET mySocket;
        SOCKET myBackup;
        SOCKET acceptSocket;
        sockaddr_in myAddress;
    public:
        Socket();
        ~Socket();
        bool SendData( char* );
        bool RecvData( char*, int );
        void CloseConnection();
        void GetAndSendMessage();
};
