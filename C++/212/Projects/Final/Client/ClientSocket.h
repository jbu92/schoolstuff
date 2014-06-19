/*
//Course: 4050-212
//Author: Jim Haight
//Assignment: SMTP Final Project
*/

#include "Socket.h"
#include <string>
using namespace std;

class ClientSocket : public Socket
{
    public:
		void GetFile(string filename);
        void ConnectToServer( const char *ipAddress, int port );
		string UserInput();
		bool Logon();
};

