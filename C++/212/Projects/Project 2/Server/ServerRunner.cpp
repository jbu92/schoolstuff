#include "ServerSocket.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char **argv){
	int port;
	bool done;
	string username = "Jimbo"; //Declare the valid username
	int command; //Command choice. set by GetCommand
	string parameter;
	bool authed; //whether or not the user has authed
	
	//connect, basically
	port = atoi(argv[1]);
	ServerSocket sockServer;
	cout<<"HOSTING..."<<endl;
	sockServer.StartHosting( port );
	//Connected
	
	//Send logon challenge
	sockServer.SendData("LOGON");
	
	//Get logon string and compare to valid username
	do{
		authed = sockServer.Logon(username);
	}while(!authed);
	
	do{
		command = sockServer.GetCommand(parameter);
		switch(command){
			case 1:
				sockServer.List();
				break;
			case 2:
				sockServer.Send(parameter);
				break;
			case 3:
				sockServer.Quit();
				break;
			default:
				sockServer.SendData("Unrecognized command. Try again.");
		}
	}while(command != 3);
	system("pause");
	
}
