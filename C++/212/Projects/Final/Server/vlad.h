/*
 *	212 SMTP Server, Final Project
 *	Group:      Sunnyvale
 *	Professor:  Dan Kennedy
 *	October/November, 2012
 *
 *	vlad.h
 *		All code contained within in property of VLAD IONESCU
 *		This code cannot be modified, reproduced or sampled 
 *		without expressed written consent of the author.
 *
 *	Contact: vxi6514@rit.edu
*/

// message struct. includes from, to, and body
struct message {
    char from[321]; // 64 max for local-part, 255 max for domain, 1 for @, 1 for \0
    char to[321]; // 64 max for local-part, 255 max for domain, 1 for @, 1 for \0
    struct data* contents; // struct of message data
};

// linked list of to addresses
struct data {
    char line[1009]; // 1000 max for a line of the message, 8 for <CR><LF>, 1 for \0
    struct data *next; // pointer to next item in linked list
};


// takes a message struct and populates a string with a comma separated list of the struct's contents
// returns true if success, false if otherwise
bool serialize(const struct message *dios_mio, char *serialized_string) {
    if(!dios_mio || !serialized_string) return false; // check params are being passed

    if(dios_mio->from[0] == '\0') return false; // check that from field isn't empty
    if(dios_mio->to[0] == '\0') return false; // check that to field isn't empty

    // no fuck you. do this outside.
    // memset(&serialized_string, '\0', strlen(&&serialized_string)); // set serialized_string to empty

    // initalize serialized_string
    //serialized_string = "\""; // start csv with an opening "
	strcat(serialized_string, "\"");
	
    // 'from' in struct becomes first field in csv
    strncat(serialized_string, dios_mio->from, strlen(dios_mio->from));
    strncat(serialized_string, "\",\"", 3);

    // 'to' in struct becomes second field in csv
    strncat(serialized_string, dios_mio->to, strlen(dios_mio->to));
    strncat(serialized_string, "\",\"", 3);

    // 'data' in struct becomes third and last field
    // iterate through linked list to get all the lines
    struct data *current = dios_mio->contents;
	
	while (current != NULL) {
	
		 strncat(serialized_string, current->line, strlen(current->line));
		 
		 if(current->next != NULL) strncat(serialized_string, "<CR><LF>", 8);
		 
		 current = current->next;
	
	
	}
	
	strcat(serialized_string, "\"");

    return true;
}

// takes a command separated string and populates a struct with it
// returns true if success, false if otherwise
bool unserialize(const char *serialized_string, struct message *dios_mio) {
    if(!dios_mio || !serialized_string) return false; // check params are being passed

    char *fieldend = strstr(serialized_string, "\",\""); // get ptr to end of first field (first delimiter)
    if(fieldend == NULL) return false;
    //memcpy(dios_mio->from, &serialized_string[1], (fieldend-&serialized_string[1])); // first field goes in 'from' in the struct
	strncpy(dios_mio->from, serialized_string+1, (fieldend-serialized_string)-1);

    char *fieldstart = fieldend+3; // the start of the second field
    fieldend = strstr(fieldstart, "\",\""); // get ptr to end of second field (second delimiter)
    if(fieldend == NULL) return false;
    //memcpy(dios_mio->to, fieldstart, (fieldend-fieldstart)); // second field goes in 'to' in the struct
	strncpy(dios_mio->to, fieldstart, (fieldend-fieldstart));
	
	fieldstart = fieldend+3;	// +3 for CSV separation
	fieldend = fieldstart+strlen(serialized_string)-1;	// -1 for quote
	
	if ((strlen(fieldstart)-1) == 0) return true;
	
	dios_mio->contents = NULL; // start off null
	
	struct data* end = NULL;
	
	//char* nl = strstr(fieldstart, "<CR><LF>");
	char* nl;
	
	do {
	
		// Find first <CR><LF> literal
		nl = strstr(fieldstart, "<CR><LF>");
		
		struct data* tempLine = new struct data;
		
		// Fill in content
		if (nl != NULL) {
			strncpy(tempLine->line, fieldstart, (nl-fieldstart));
		} else {
			char* end = strstr(fieldstart, "\"");
			strncpy(tempLine->line, fieldstart, (end-fieldstart));
		
		}
		// Fill in pointer
		tempLine->next = NULL;
		
		
		if (dios_mio->contents == NULL) dios_mio->contents = tempLine;
		if (end != NULL) end->next = tempLine;
		end = tempLine;

		if (nl != NULL) fieldstart = nl+8;
		
	} while (nl != NULL);
	
	
    
    return true;
}


bool getmboxes(char **users, pthread_mutex_t **mutexes) {
    // open dir <mbox> relative to cwd or die
    DIR *mbox = opendir("mbox");
    if(mbox == NULL) { 
        perror("Fatal error: Opening dir <mbox> failed");
        exit(1);
    }

    // index for parallel arrays
    int index = 0;
	char* user;
	
    // load items in mbox into items struct and iterate through em
    struct dirent *items;
    while((items = readdir(mbox)) != NULL) {
        // skip over hidden files, ., and ..
        if(items->d_name[0] == '.') continue;
		
		//memset(user[index], '\0', sizeof users[index]);

		user = new char[100];
		
        // if index is 100 (buffer overflow risk) stop
        if(index >= 100) break;

        // put this filename in an array
		strcat(user, items->d_name);
        //*user = items->d_name;
        // and make a mutex for it in the mutex array, using the same index
        mutexes[index] = new pthread_mutex_t;
        pthread_mutex_init(mutexes[index], NULL);

        // floppy dicks
        //printf("Index: %d <%s>\n", index, items->d_name);
        //printf("\t%s | %p\n", user, mutexes[index]);
        //printf("\t%s | %p\n", user, user);
        
		users[index] = user;
		
        // be ready to use the next space in the arrays next time around
        index++;
    }
	
	for (int i=index; i<100; i++) memset(users[i], '\0', 0);

    // be kind, rewind
    closedir(mbox);
    return true;
}