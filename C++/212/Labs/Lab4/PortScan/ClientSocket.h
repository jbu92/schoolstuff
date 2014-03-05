#include "Socket.h"

class ClientSocket : public Socket
{
    public:
        void ConnectToServer( const char *ipAddress, int port );
        void KnockKnock( const char *ipAddress);
};

