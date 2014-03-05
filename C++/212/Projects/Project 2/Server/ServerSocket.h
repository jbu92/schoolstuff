#include "Socket.h"
#include <string>
class ServerSocket : public Socket
{
    public:
        void Listen();
        void Bind( int port );
        void StartHosting( int port ); //Add a logon challenge (change from HELO)
		int GetCommand(string &parameter); //Get command from client
		bool Logon(string username); //Logon procedure
		void List(); //List command
		void Send(string parameter); //Send command
		void Quit(); //Quit command
};
