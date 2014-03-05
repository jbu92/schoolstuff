/*Ident header
//Course: 4002-212
//Author: James Haight
*/

//Includes

#ifndef MESSAGE_H
#define MESSAGE_H

class Message{
	private:
		string src; 	//Source
		string dest; 	//Destination
		string data; 	//Data
	public:
		Message(); //Constructs empty
		Message(string src, string dest, string data); //Constructs fully
		//Currently all bools (did it work?), subject to change
		bool setSrc(string);  //Sets source
		bool setDest(string); //Sets dest
		bool setData(string); //Sets data
};

#endif