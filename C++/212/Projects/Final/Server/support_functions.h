/*
 *	212 SMTP Server, Final Project
 *	Group:      Sunnyvale
 *	Professor:  Dan Kennedy
 *	October/November, 2012
 *
 *	support_functions.h
 *		All code contained within in property of IAN FLOURNOY
 *		This code cannot be modified, reproduced or sampled 
 *		without expressed written consent of the author.
 *
 *	Contact: icf6667@rit.edu
 *
 *	*NOTE Any code that's beyond the 80 column limit hurts me.
 *		Attribute lines such as 604 to late-night coding shenanigans 
*/
#ifndef SUPPORT_H
#define SUPPORT_H

/* ptoupper - Partial To Upper
 *
 *	Given a string pointer and length
 *	ptoupper will convert length amount of characters of the string
 *
 *
 *	This is used to ensure case insensitivity with recv'd commands
*/
void touppern(char* str, size_t len) {

	for (int i=0; i<len; i++) {
		
		str[i] = toupper(str[i]);
	
	}

}

/*	mail_flags
 *
 *	Internal structure used to control the "state-machine" that handles the
 *		SMTP protocol.
*/
struct mail_flags {

	bool noop;
	bool rset;
	int message;
	
};


/*
 *	extractAddress
 *	Pretty self-explanatory
 */
bool extractAddress(char* from, char* to) {

	char *waccaStart = strchr(from, '<'); 
	char *waccaEnd   = strchr(from, '>');
	
	// Could not find waccas :(
	if (waccaStart == NULL || waccaEnd == NULL) return false;
	
	// Emtpy waccas
	if ((waccaEnd-waccaStart-1) == 0) return false;

	strncpy(to, waccaStart+1, (waccaEnd-waccaStart-1));

	return true;
	
}

/*
 *	extractDomain
 *	Pretty self-explanatory
 */
bool extractDomain(char* from, char* to) {

	char *apetail = strchr(from, '@'); 
	
	// Could not find waccas :(
	if (apetail == NULL) return false;

	strcpy(to, apetail+1);

	return true;
	
}

/*
 *	extractUser
 *	Pretty self-explanatory
 */
bool extractUser(char* from, char* to) {

	char *apetail = strchr(from, '@');
	
	// Could not find waccas :(
	if (apetail == NULL) return false;

	strncpy(to, from, (strlen(from)-strlen(apetail)));
	//printf("\t%p\n", apetail);

	return true;
	
}

/*
 *	debastardize
 *	Pretty self-explanatory, makes sure we are somewhat compatible with others
 */
bool debastardize(char* str) {

	char* c;
	if (strlen(str) == 0) return false;
	
	// Walk backwards through the string until we find ! \r or ! \n
	for (int i=strlen(str)-1; i > 0; i--) {
	
		c = strrchr(str, '\r');

		if (c) {
			*c = '\0';
			continue;
		}
		
		c = strrchr(str, '\n');
		if (c) {
			*c = '\0';
			continue;
		}
		
		break;	
	}
	
	return true;

}

/*
 *	checkUser
 *	Pretty self-explanatory
 */
bool checkUser(char* user, char** users) {

	touppern(user, strlen(user));

	for (int i=0; i<100; i++) {
	
		touppern(users[i], strlen(users[i]));
		
		if (users[i] == NULL) return false;
		if (strcmp(user, users[i]) == 0) return true;
	
	}
	
	return false;

}

/*
 *	getUID
 *	Pretty self-explanatory, never used
 */
int getUID(char* user, char** users) {
	
	for (int i=0; i<100; i++) {
		
		if (users[i] == NULL) return -1;
		if (strcmp(user, users[i]) == 0) return i;
	
	}
	
	return -1;
	

}


#endif
