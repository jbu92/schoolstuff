/*Ident header
//Course: 4002-212
//Author: James Haight
*/

//Includes
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#ifndef SERVER_H
#define SERVER_H

class Server{
	private:
	public:
		Server();
		~Server();
		//Currently all bools (did it work?), subject to change
		bool helo(); 	//HELO, initiates connection
		bool vrfy(); 	//VRFY, authenticates user
		bool mail(); 	//MAIL, starts message
		bool rcpt(); 	//RCPT, adds recipient to message
		bool data(); 	//DATA, adds data to message
		bool quit(); 	//QUIT, kills session
		bool logMsg(); 	//logs message
		bool send();	//sends message (run log internally)
};

#endif

/*
YET TO BE ADDDRESSED:
Errors
Sockets
Threads
Variables
	Message queue
	Known servers (linked list?)
	File names
		Logs
		Users
		Mail boxes
	
File i/o
*/