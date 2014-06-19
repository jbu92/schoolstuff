/*
//Course: 4050-212
//Author: Jim Haight
//Assignment: SMTP Final Project
//Purpose: This file contains the main function of the client program.
*/

#include "ClientSocket.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
using namespace std;

int menu();
void sendMail(ClientSocket&,string,string);
void getMail(string ipAddress);
std::string encrypt(std::string source);
bool getYesNo(string prompt);
int getStatus(ClientSocket&); //gets status code from server

const int SMTPPORT = 4040;
const int MRPPORT = 4242; 

int main(int argc, char **argv){
//	int port = 4040;
	string ipAddress, myIP, message;
	char recMessage[STRLEN];
	char sendMessage[STRLEN];
	string input, command, parameter;
	bool authed = false; //Whether or not you've authenticated
	int menuOption;
	ClientSocket sockClient;
	
	//Client
	cout<<"Enter the IP address of the server you would like to connect to: ";
	cin>>ipAddress;
	cout << "Enter your own IP address: ";
	cin >> myIP;
	
	
	//
	//MENU
	//
	do{
		menuOption = menu();
		switch(menuOption){
			case 1:
				sendMail(sockClient, ipAddress, myIP);
				break;
			case 2:
				getMail(ipAddress);
				break;
			default:
				cout << "Invalid input, please try again\nPress enter to return to menu";
			    cin.ignore(1000,'\n');
			    cin.ignore(1000,'\n');
		}
	}while(menuOption != -1);
	
	//sockClient.CloseConnection();
}

int menu(){
	int choice;
	
    system("cls");
	cout << "====================================================" << endl;
	cout << "===               Ye Olde Menu                   ===" << endl;
	cout << "====================================================" << endl << endl;
	cout << left << setw(20) << "1  - Send a message" << endl;
	cout << left << setw(20) << "2  - Check mails"    << endl;
	cout << left << setw(20) << "-1 - Quit"    << endl;
	cout << "====================================================" << endl;
	cout << right << setw(20) << "SELECT OPTION --> ";
	cin >> choice;
	
	return choice;
	
}

int getStatus(ClientSocket& sockClient){
	char c_line[STRLEN];
	string line;
	int status;
	

	for(int i=0; i < STRLEN; i++){
		c_line[i] = 0;
	}

	sockClient.RecvData(c_line,STRLEN);
	line = c_line;
	line = line.substr(0,3); //first 3 characters are the status code
	status = atoi(line.c_str());
	cout << "Received: " << c_line << endl;
	//cout << "status: " << status << endl;
	return status;
}

bool getYesNo(string prompt){
	char response;
	do{
		cout << prompt << " (Y/N) ";
		cin >> response;
		cin.ignore(1000, '\n');
		response = toupper(response);
		if(response != 'Y' && response != 'N')
			cout << "Please enter Y or N.\n";
	}while (response != 'Y' && response != 'N');
	if(response == 'Y')
		return true;
	else
		return false;
}

void getMail(string ipAddress){
	ClientSocket sockClient;
	string response = "", srvReply = "", fullMessage = "";
	bool encryption, moremessages;
	char chResponse;
	int status;
	char buffer[STRLEN];
	
	
	cout << "Please enter your email address (user@IP): ";
	cin >> response;
	
	sockClient.ConnectToServer( ipAddress.c_str(), MRPPORT );
	status = getStatus(sockClient);
	//send IDENT response
	fullMessage = "IDENT ";
	fullMessage.append(response);
	strcpy(buffer, fullMessage.c_str());
	sockClient.SendData(buffer);
	status = getStatus(sockClient);
	//check status
	do
	{
		fullMessage = "";
		sockClient.SendData("GETMAIL");
		status = getStatus(sockClient);
		//check status
		if(status == 404){
			//404 MBox Empty
			cout << "No more messages.\n";
			break;
		}
		//get from
		sockClient.RecvData(buffer, STRLEN);
		cout << buffer<<endl;
		//get to
		sockClient.RecvData(buffer, STRLEN);
		cout << buffer<<endl;
		//send 250
		sockClient.SendData("250 Got it, yo");
		//get "DATA"
		sockClient.RecvData(buffer, STRLEN);
		sockClient.SendData("354 end data with <cr><lf>.<cr><lf>");
		
		while(strcmp(srvReply.c_str(), "\r\n.\r\n") != 0)
		{
			//Receive mails, get this code from ian/vlad when they haz it.
			sockClient.RecvData(buffer, STRLEN);
			srvReply = buffer;
			fullMessage.append(srvReply);
			fullMessage.append("\n");
		}
		cout << fullMessage;
		if(getYesNo("Would you like to decrypt the previous message?")){
			fullMessage = encrypt(fullMessage);
			cout << fullMessage;
		}
		moremessages = getYesNo("Would you like to retrieve the next message?");
		if(!moremessages){
			sockClient.SendData("QUIT\r\n");
		}
	}while(moremessages);
	sockClient.CloseConnection();
}

void sendMail(ClientSocket& sockClient, string ipAddress, string myIP){
	string to, from, subject, message;
	bool encryption;
	int status;
	char buffer[STRLEN];
	string messageToSend;
	
	cout<<"ATTEMPTING TO CONNECT..."<<endl;
	sockClient.ConnectToServer( ipAddress.c_str(), SMTPPORT );
	//Connected

	status = getStatus(sockClient);

	if(status != 220){
		cout << "Error encountered. Exiting.";
		system("pause");
		exit(0);
	}

	//
	//HELO
	//
    messageToSend = "HELO ";
	messageToSend.append(myIP);
	messageToSend.append("\r\n");
	//memset(buffer, '\0', sizeof(buffer));
	strcpy(buffer, messageToSend.c_str());
	Sleep(500);
	
	sockClient.SendData(buffer);
	
	status = getStatus(sockClient);
	
	if(status != 250){
		cout << "Error encountered. Exiting.";
		system("pause");
		//exit(0);
	}
	
	encryption = getYesNo("Would you like to encrypt this message?");
	cout << "Enter your email: ";
	getline(cin, from);
	
	//send MAIL FROM: from
	messageToSend = "MAIL FROM:<";
	messageToSend.append(from);
	messageToSend.append(">\r\n");
	strcpy(buffer, messageToSend.c_str());
	sockClient.SendData(buffer);
	
	status = getStatus(sockClient);
	
	if(status != 250){
		cout << "Error encountered. Exiting.";
		system("pause");
		//exit(0);
	}
	
	cout << "Enter recipient: ";
	getline(cin, to);
	
	
	//send RCPT TO: to
	messageToSend = "RCPT TO:<";
	messageToSend.append(to);
		messageToSend.append(">\r\n");
	strcpy(buffer, messageToSend.c_str());
	sockClient.SendData(buffer);
	
	status = getStatus(sockClient);
	
	if(status != 250){
		cout << "Error encountered. Exiting.";
		system("pause");
		//exit(0);
	}
	
	cout << "Type your message. End with a blank line containing a single period.\n";
	sockClient.SendData("DATA\r\n");
	
	status = getStatus(sockClient);
	
	if(status != 354){
		cout << "Error encountered. Exiting.";
		system("pause");
		//exit(0);
	}
	
	while(strcmp(".", message.c_str()) != 0 && strcmp(".\n", message.c_str()) != 0  ){
		getline(cin, message);
		if(strcmp(".", message.c_str()) != 0){
			if(encryption){
				message = encrypt(message);
			}
			//send message
			message.append("\n");
			strcpy(buffer, message.c_str());
			sockClient.SendData(buffer);
		}
		else{
			sockClient.SendData("\r\n.\r\n");
		}
	}
	
	status = getStatus(sockClient);
	
	sockClient.SendData("QUIT\r\n");
	sockClient.CloseConnection();
}

std::string encrypt(std::string source){
	std::string transformed;
	for (size_t i = 0; i < source.size(); ++i) {
		if (isalpha(source[i])) {
			if ((tolower(source[i]) - '`') < 14)
				transformed.append(1, source[i] + 13);
			else
				transformed.append(1, source[i] - 13);
		} else {
			transformed.append(1, source[i]);
		}
	}
	return transformed;
}
