/*
 *	212 SMTP Server, Final Project
 *	Group:      Sunnyvale
 *	Professor:  Dan Kennedy
 *	October/November, 2012
 *
 *	server.cpp
 *		All code contained within in property of IAN FLOURNOY
 *		This code cannot be modified, reproduced or sampled 
 *		without expressed written consent of the author.
 *
 *	Contact: icf6667@rit.edu
 *
 *	*NOTE Any code that's beyond the 80 column limit hurts me.
 *		Attribute lines such as 604 to late-night coding shenanigans 
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>
#include <vector>
#include <time.h>
#include <stdbool.h>
#include <dirent.h>

using namespace std;

// Custom headers
#include "support_functions.h"
#include "vlad.h"

#define SMTP_PORT "4040"
#define MRP_PORT  "4242"
#define MAX_QUEUE 42
#define BUFFER_LENGTH 4096
#define MAIN_LOG "all_messages.log"
#define FORWARD_QUEUE "forward.queue"
#define STATE_ENTR 0
#define STATE_MAIL 2
#define STATE_RCPT 4
#define STATE_DATA 6

/*	SMTP Worker Thread
 *
 *	Will actively listen on SMTP_PORT for clients wishing to communicate using
 *	SMTP. Will spawn an smtp_client thread to carry out protocol.
*/
void* smtp_worker_thread(void*);


/*	MRP Worker Thread
 *
 *	Will actively listen on MRP_PORT for clients wishing to communicate  using
 *	MRP. Will spawn an mrp_client thread to carry out protocol.
 *
 *	Right now, it spawns threads of smtp_client. Listens on port 4242 though!
*/
void* mrp_worker_thread(void*);


/*	Forward Worker Thread
 *	
 *	Will actively monitor `forward.queue` file for any messages needing to be
 *	forwarded to a remote server.
 *	Will then carry out a conversation, acting as a client with the remote svr
*/
void* forward_worker_thread(void*);


/*	SMTP Client
 *
 *	Will carry out an SMTP conversation with a compatible client.
 *	Spawns smtp_message to deal with actual message data.
*/
void* smtp_client(void*);

/*	SMTP Message
 *	Will queue messages appropriately in a buffer for the forward_worker.
 *	Deal with an incoming message.
*/
int smtp_message(struct message*);

/*	MRP Client
 *
 *	Will carry out an MRP converstaion with a compatible client.
 *	Will send oldest unread mail message to newest messages.
 *	Currently does nothing.
*/
void* mrp_client(void*);

/*	Signal Handler
 *
 *	Will handle a signal sent to the program
 *	Used to cleanup after receiving SIGINT
 *
 *	Possible improvements for this would include sending actual term signals
 *	to client threads and the appropriate socket code be written to close
 *	the socket properly.
 *
*/
void sig_callback_handler(int);

/*	thread and mutex namespace
 *
 *	Allows us to keep things tidier than they were before, also no parameters
*/
namespace thread {

	pthread_t					smtp_worker;
	pthread_t					mrp_worker;
	pthread_t					forward_worker;

}

namespace mutex {

	pthread_mutex_t* 			forwarder;
	pthread_mutex_t*			log;
	pthread_mutex_t*			mbox[100]; // Staticed at 100 mailboxes

}

char*							users[100];	// late night coding

/*############################################################################*/
/*##########################   MAIN SERVER TURN ON  ##########################*/
/*############################################################################*/

int main (int argc, char *argv[]) {

	printf("[INFO] Starting the Sunnyvale SMTP Server, PID: %d\n", getpid());
	
	// Declare main-scope variables
	int							ret; 				// temporary return value

	// Set SIGINT callback
	signal(SIGINT, sig_callback_handler);
	
	// Initialize mutexes	
	mutex::forwarder 		= new pthread_mutex_t;
	mutex::log 				= new pthread_mutex_t;
	pthread_mutex_init(mutex::forwarder, NULL);
	pthread_mutex_init(mutex::log, NULL);
	
	// Bring in mailboxes
	getmboxes(users, mutex::mbox);
	
	for (int i=0; i<100; i++) {
	
		if (users[i] == NULL || mutex::mbox[i] == NULL) break;
		
		printf("[INFO] Loaded user [%d] %s@sunnyvale.\n", i+1, users[i]);
	
	}
	
	
	// Bring alive SMTP Worker
	if ((ret = pthread_create(&thread::smtp_worker, NULL,
				smtp_worker_thread, NULL)) != 0) {
	
		fprintf(stderr, "[ERROR] Could not create SMTP Worker thread.\n");
		exit(ret);
	
	}
	
	// Bring alive MRP Worker
	if ((ret = pthread_create(&thread::mrp_worker, NULL,
				mrp_worker_thread, NULL)) != 0) {
	
		fprintf(stderr, "[ERROR] Could not create MRP Worker thread.\n");
		exit(ret);
	
	}
	
	// Bring alive Forward Worker
	if ((ret = pthread_create(&thread::forward_worker, NULL,
				forward_worker_thread, NULL)) != 0) {
	
		fprintf(stderr, "[ERROR] Could not create Forward Worker thread.\n");
		exit(ret);
	
	}
	
	// However, I do not like it.
	pthread_exit(NULL);
	
	return EXIT_SUCCESS;

}
/*############################################################################*/

/*
 *	smtp thread
 *
 * This code is responsible for listening on the SMTP_PORT and accepting clients
 * who connect to it. Another thread will be created from this thread that will
 * handle the individual client, allowing this thread to get back to listening.
*/

void* smtp_worker_thread(void* info) {

	printf("[SMTP Worker] Worker thread started.\n");
	
	// Declare SMTP Worker scope variables
	int 						socket_listen;
	int							socket_newclient;
	int 						ret;				// tmp return value holder
	int							yes = 1;			// No comment
	struct		addrinfo		hints;				// Holds enough data for
													// getaddrinfo() success
	struct		addrinfo*		info_server;		// will hold the server info
	struct		addrinfo*		p;
	struct	sockaddr_storage	newclient_addr;
	vector		<pthread_t>		clients;			// Will hold list of clients
	pthread_t					thread_newclient;
	
	socklen_t					sin_size = sizeof newclient_addr;
	char 						addr[INET6_ADDRSTRLEN];
	
	hints.ai_family = AF_INET; 			// We will want IPv4 only for now
	hints.ai_socktype = SOCK_STREAM; 	// TCP Communicadtion (no datagram)
	hints.ai_flags = AI_PASSIVE;
	
	// Populate the rest of our addrinfo struct with candy
	if ((ret = getaddrinfo(NULL, SMTP_PORT, &hints, &info_server)) != 0) {
	
		fprintf(stderr, "[ERROR SMTP Worker] Could not get address info.\n");
		
		pthread_exit((void*)&ret);
	
	}
	
	// Run through the linked list that getaddrinfo gave us, trying to bind
	for (p = info_server; p != NULL; p = p->ai_next) {
	
		// Try to create our socket IPv4, TCP Socket
		if ((socket_listen = socket(p->ai_family, p->ai_socktype,
			p->ai_protocol)) == -1) {
			
			fprintf(stderr, "[ERROR SMTP Worker] Could not create socket.\n");
			
			pthread_exit(NULL);
		
		}
		
		if (setsockopt(socket_listen, SOL_SOCKET, SO_REUSEADDR, &yes,
			sizeof(int)) == -1) {
			
			fprintf(stderr,
				"[ERROR SMTP Worker] Could not set socket options.\n");
			
			pthread_exit(NULL);
			
		}
		
		if (bind(socket_listen, p->ai_addr, p->ai_addrlen) == -1) {
		
			close(socket_listen);
			fprintf(stderr,
				"[ERROR SMTP Worker] Could not bind socket to interface.\n");
			
			pthread_exit(NULL);
		
		}
		
		// If we reach here it means socket and bind have returned success
		// we are now able to start listening for connections.
		break;
	
	}
	
	// If we end up with a null p value, it means no valid address info structs
	// were found. This is a fatal error.
	if (p == NULL) {
	
		fprintf(stderr,
			"[ERROR SMTP Worker] Server failed to find a place to bind.\n");
			
		pthread_exit(NULL);
	
	}
	
	// Save memory, free willy
	freeaddrinfo(info_server);
	
	// Start listening on socket. Now can faithfully accept clients afterwards.
	if (listen(socket_listen, SOMAXCONN) == -1) { // Changed max conn to const
	
		fprintf(stderr,
			"[ERROR SMTP Worker] Can't listen on binded socket.\n");
	
	}
	
	// If we've reached here all went well. We are now ready for clients
	printf("[SMTP Worker] Ready for connections ...\n");
	
	// We will remain in this loop, forever accepting our clients.
	while (true) {
	
		// Accept connection
		socket_newclient = accept(socket_listen,
			(struct sockaddr*)&newclient_addr, &sin_size);
		
		if (socket_newclient == -1) {
		
			fprintf(stderr,
				"[ERROR SMTP Worker] Unable to accept new connection.\n");
			continue;
		
		}		
		
		// Figure out addr info
		inet_ntop(newclient_addr.ss_family,
			&(((struct sockaddr_in*)&newclient_addr)->sin_addr),
			addr, sizeof addr);
		
		printf("[SMTP Worker] Accepted connection from %s\n", addr);
		
		// Thread out
		ret = pthread_create(&thread_newclient, NULL, smtp_client,
			(void*)&socket_newclient);
		
		clients.push_back(thread_newclient);
		
		if (ret != 0) {
		
			fprintf(stderr,
				"[ERROR SMTP Worker] Could not spawn client thread.\n");
			close(socket_newclient);
			continue;
		
		}
		
		// Unneccesary line.
		//printf("[SMTP Worker] Spawned new thread with ID: %u\n",
		//	clients.back());
		
	
	}
	
	// Wait for all of our clients to finish ?
	for (int i=0; i<clients.size(); i++) {
	
		pthread_join(clients[i], NULL);
	
	}

}
/*############################################################################*/

/*
 *	MRP Worker Thread
*/
void* mrp_worker_thread(void* info) {

	printf("[MRP Worker] Worker thread started.\n");
	
	// Declare SMTP Worker scope variables
	int 						socket_listen;
	int							socket_newclient;
	int 						ret;				// tmp return value holder
	int							yes = 1;			// No comment
	struct		addrinfo		hints;				// Holds enough data for
													// getaddrinfo() success
	struct		addrinfo*		info_server;		// will hold the server info
	struct		addrinfo*		p;
	struct	sockaddr_storage	newclient_addr;
	vector		<pthread_t>		clients;			// Will hold list of clients
	pthread_t					thread_newclient;
	
	socklen_t					sin_size = sizeof newclient_addr;
	char 						addr[INET6_ADDRSTRLEN];
	
	hints.ai_family = AF_INET; 			// We will want IPv4 only for now
	hints.ai_socktype = SOCK_STREAM; 	// TCP Communicadtion (no datagram)
	hints.ai_flags = AI_PASSIVE;
	
	// Populate the rest of our addrinfo struct with candy
	if ((ret = getaddrinfo(NULL, MRP_PORT, &hints, &info_server)) != 0) {
	
		fprintf(stderr, "[ERROR MRP Worker] Could not get address info.\n");
		
		pthread_exit((void*)&ret);
	
	}
	
	// Run through the linked list that getaddrinfo gave us, trying to bind
	for (p = info_server; p != NULL; p = p->ai_next) {
	
		// Try to create our socket IPv4, TCP Socket
		if ((socket_listen = socket(p->ai_family, p->ai_socktype,
			p->ai_protocol)) == -1) {
			
			fprintf(stderr, "[ERROR MRP Worker] Could not create socket.\n");
			
			pthread_exit(NULL);
		
		}
		
		if (setsockopt(socket_listen, SOL_SOCKET, SO_REUSEADDR, &yes,
			sizeof(int)) == -1) {
			
			fprintf(stderr,
				"[ERROR MRP Worker] Could not set socket options.\n");
			
			pthread_exit(NULL);
			
		}
		
		if (bind(socket_listen, p->ai_addr, p->ai_addrlen) == -1) {
		
			close(socket_listen);
			fprintf(stderr,
				"[ERROR MRP Worker] Could not bind socket to interface.\n");
			
			pthread_exit(NULL);
		
		}
		
		// If we reach here it means socket and bind have returned success
		// we are now able to start listening for connections.
		break;
	
	}
	
	// If we end up with a null p value, it means no valid address info structs
	// were found. This is a fatal error.
	if (p == NULL) {
	
		fprintf(stderr,
			"[ERROR MRP Worker] Server failed to find a place to bind.\n");
			
		pthread_exit(NULL);
	
	}
	
	// Save memory, free willy
	freeaddrinfo(info_server);
	
	// Start listening on socket. Now can faithfully accept clients afterwards.
	if (listen(socket_listen, SOMAXCONN) == -1) { // Changed max conn to const
	
		fprintf(stderr,
			"[ERROR MRP Worker] Can't listen on binded socket.\n");
	
	}
	
	// If we've reached here all went well. We are now ready for clients
	printf("[MRP Worker] Ready for connections ...\n");
	
	// We will remain in this loop, forever accepting our clients.
	while (true) {
	
		// Accept connection
		socket_newclient = accept(socket_listen,
			(struct sockaddr*)&newclient_addr, &sin_size);
		
		if (socket_newclient == -1) {
		
			fprintf(stderr,
				"[ERROR MRP Worker] Unable to accept new connection.\n");
			continue;
		
		}		
		
		// Figure out addr info
		inet_ntop(newclient_addr.ss_family,
			&(((struct sockaddr_in*)&newclient_addr)->sin_addr),
			addr, sizeof addr);
		
		printf("[MRP Worker] Accepted connection from %s\n", addr);
		
		// Thread out
		ret = pthread_create(&thread_newclient, NULL, smtp_client,
			(void*)&socket_newclient);
		
		clients.push_back(thread_newclient);
		
		if (ret != 0) {
		
			fprintf(stderr,
				"[ERROR MRP Worker] Could not spawn client thread.\n");
			close(socket_newclient);
			continue;
		
		}
		
		// Unneccesary line.
		//printf("[SMTP Worker] Spawned new thread with ID: %u\n",
		//	clients.back());
		
	
	}
	
	// Wait for all of our clients to finish ?
	for (int i=0; i<clients.size(); i++) {
	
		pthread_join(clients[i], NULL);
	
	}

}
/*############################################################################*/

/*
 *	Forward Worker Thread
*/
void* forward_worker_thread(void* info) {

	printf("[Forwarder] Worker thread started..\n");
	
	char input[4096];
	char buffer[BUFFER_LENGTH];
	char domain[256];
	char address[INET6_ADDRSTRLEN];
	struct message* curmsg;
	struct addrinfo hints, *servinfo, *next;
	int ret;
	int socket1;
	memset(&hints, 0, sizeof hints);
	
	printf("[Forwarder] Ready to forward.\n");
	while (true) {
	
		// Sleep for random time
		sleep(rand() % 10 + 20);
	
		printf("[Forwarder] Witch has been startled!\n");
		
		pthread_mutex_lock(mutex::forwarder);
		printf("[Forwarder] Mutex achieved.\n");
		
		
		FILE *h = fopen(FORWARD_QUEUE, "r");
		remove("forward.temp");
		FILE *proxy = fopen("forward.temp", "w+");
		
		memset(input, '\0', sizeof input);
		
		fgets(input, 4096, h);
		
		if (strlen(input) > 0) {
		
			printf("[Forwarder] Found a message, will forward.\n");
		
		} else {
		
			fclose(h);
			fclose(proxy);
			pthread_mutex_unlock(mutex::forwarder);
			printf("[Forwarder] Mutex released -- no messages.\n");
			continue;
		}
		
		curmsg = new struct message;
		
		unserialize(input, curmsg);
	
		/*
		
		
		printf("from: %s\n", curmsg->from);
		printf("to: %s\n", curmsg->to);
		
		
		struct data* n = curmsg->contents;
		puts("--msg--");
		while (n != NULL) {
		
			printf("\t{%s}\n", n->line);
			n = n->next;
		
		}
		
		
		*/
		
		printf("[Forwarder] Sending message from {%s} to {%s}.\n", curmsg->from, curmsg->to);
		
		extractDomain(curmsg->to, domain);	
		
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		
		
		if ((ret = getaddrinfo(domain, SMTP_PORT, &hints, &servinfo)) != 0) {
	
			fprintf(stderr, "[Forwarder] Error resolving host: {%s}.\n", domain);
			pthread_mutex_unlock(mutex::forwarder);
			printf("[Forwarder] Mutex released.\n");
			continue;
		
		}
		
		for (next = servinfo; next != NULL; next = next->ai_next) {
	
			if ((socket1 = socket(next->ai_family, next->ai_socktype, next->ai_protocol)) == -1) continue;
			
			if (connect(socket1, next->ai_addr, next->ai_addrlen) == -1) {
			
				close(socket1);
				continue;
			
			}
			
			break; // We've found a good address (maybe)
		
		}
		
		if (next = NULL) {
		
			fprintf(stderr, "[Forwarder] could not connect to remote server: {%s}.\n", domain);
			pthread_mutex_unlock(mutex::forwarder);
			printf("[Forwarder] Mutex released.\n");
			continue;
			
		}
		
		freeaddrinfo(servinfo);
		
		{
			memset(buffer, '\0', sizeof buffer);
			recv(socket1, buffer, sizeof buffer, 0);
			debastardize(buffer);
			printf("[Forwarder] [SMTP] {%s}\n", buffer);
		}
		
		send(socket1, "HELO Sunnyvale\r\n", 16, 0);
		
		{
			memset(buffer, '\0', sizeof buffer);
			recv(socket1, buffer, sizeof buffer, 0);
			debastardize(buffer);
			printf("[Forwarder] [SMTP] {%s}\n", buffer);
		}
		
		memset(buffer, '\0', sizeof buffer);
		strcat(buffer, "MAIL FROM: <");
		strcat(buffer, curmsg->from);
		strcat(buffer, ">\r\n");
		send(socket1, buffer, strlen(buffer), 0);
		
		{
			memset(buffer, '\0', sizeof buffer);
			recv(socket1, buffer, sizeof buffer, 0);
			debastardize(buffer);
			printf("[Forwarder] [SMTP] {%s}\n", buffer);
		}
		
		memset(buffer, '\0', sizeof buffer);
		strcat(buffer, "RCPT TO: <");
		strcat(buffer, curmsg->to);
		strcat(buffer, ">\r\n");
		send(socket1, buffer, strlen(buffer), 0);
		
		{
			memset(buffer, '\0', sizeof buffer);
			recv(socket1, buffer, sizeof buffer, 0);
			debastardize(buffer);
			printf("[Forwarder] [SMTP] {%s}\n", buffer);
		}
		
		send(socket1, "DATA\r\n", 6, 0);
		
		{
			memset(buffer, '\0', sizeof buffer);
			recv(socket1, buffer, sizeof buffer, 0);
			debastardize(buffer);
			printf("[Forwarder] [SMTP] {%s}\n", buffer);
		}
		
		struct data* n = curmsg->contents;
		while (n != NULL) {
		
			printf("[Forwarder] [SMTP] [MSG] {%s}\n", n->line);
			
			send(socket1, n->line, sizeof n->line, 0);
			
			usleep(800);
			n = n->next;
		
		}
		
		
		printf("[Forwarder] [SMTP] Sending end sequence.\n", n->line);
		send(socket1, "\r\n.\r\n", 5, 0);
		printf("[Forwarder] [SMTP] end sent.\n", n->line);
		
	/*		
		{
			memset(buffer, '\0', sizeof buffer);
			recv(socket1, buffer, sizeof buffer, 0);
			debastardize(buffer);
			printf("[Forwarder] [SMTP] {%s}\n", buffer);
		}
	*/	
		send(socket1, "QUIT\r\n", 6, 0);
		/*
		{
			memset(buffer, '\0', sizeof buffer);
			recv(socket1, buffer, sizeof buffer, 0);
			debastardize(buffer);
			printf("[Forwarder] [SMTP] {%s}\n", buffer);
		}
		*/
		
		printf("[Forwarder] Done forwarding message.\n");
		
		
		delete curmsg;
		
		while (fgets(input, 4096, h) != NULL) fputs(input, proxy);
		
		fclose(h);
		fclose(proxy);
		
		remove(FORWARD_QUEUE);
		rename("forward.temp", FORWARD_QUEUE);
		
		pthread_mutex_unlock(mutex::forwarder);
		printf("[Forwarder] Mutex released.\n");
		
	}

}
/*############################################################################*/

/*
 *	SMTP Client Thread
*/
void* smtp_client(void* info) {

	int sock = *(int*)info;
	int ret;
	char buffer[BUFFER_LENGTH];
	char temp[BUFFER_LENGTH];
	char pipe[BUFFER_LENGTH];
	int n;
	bool clean = true;
	
	printf("[Client.%d] SMTP Client thread active.\n", sock);

	
	// According to the RFC, the connection is to be closed only when QUIT is
	// issued, so therefore we will loop until the client sends HELO
	
	// Get establishment of state business out of the way
	n = sprintf(pipe, "220 Sunnyvale SMTP Server\r\n");
	send(sock, pipe, n, 0);
		
	do {
	
		ret = recv(sock, buffer, BUFFER_LENGTH, 0);
		
		// If client terminates connection prematurely, cleanup
		if (ret == -1) 	{ clean = false; break; }
		
		touppern(buffer, 4);
		if (strncmp(buffer, "HELO", 4) != 0) {
			
			printf("[Client.%d] Did not receive HELO, send back 501.\n", sock);
			// Send 501 error
			n = sprintf(pipe, "501 Syntax error in parameters, arguments\r\n");
			send(sock, pipe, n, 0);
			
		}
	
	} while (strncmp(buffer, "HELO", 4) != 0);
	
	// Send them secondary welcome
	n = sprintf(pipe, "250 SUNNYVALE Willkommen \r\n");
	send(sock, pipe, n, 0);
	
	// Flag definition
	struct mail_flags flag;
	flag.noop = false;
	flag.rset = true;
	flag.message = 0;
	
	// New message definition
	struct message* newmsg = new struct message;
	
	// And thus begins our SMTP conversation
	while (true && clean) { // <BEGIN CLIENT CONVERSATION>
	
		// clear buffers & flags
		if (flag.rset) { // noop should not affect present state
		
			delete newmsg;			
			newmsg = new struct message;
			
			printf("[Client.%d] -- States cleared. --\n", sock);
			
			flag.rset = false;
		
		} else if (flag.noop) {
		
			// reset noop flag
			flag.noop = false;
		
			printf("[Client.%d] NOOPed.\n", sock);
		}
		
		memset(buffer, '\0', BUFFER_LENGTH);
		memset(temp,   '\0', BUFFER_LENGTH);
		memset(pipe,   '\0', BUFFER_LENGTH);
		printf("[Client.%d] -- Buffers cleared. --\n", sock);
		
		
		// receive from client
		ret = recv(sock, buffer, BUFFER_LENGTH, 0);
		
		// So we can compare command, leaving buffer untouched for later
		strncpy(temp, buffer, 512); // 512 is the max command length, RFC
		
		// If client terminates connection prematurely, cleanup
		if (ret == -1) {
		
			printf("[Client.%d] Client prematurely closed socket.\n", sock);
			break;
		
		}
		
		printf("[Client.%d] Read %d bytes.\n", sock, ret);
		
		// process received data
		// strip newline
		debastardize(buffer);
		debastardize(temp);
		
		
		{ // Check for QUIT
			touppern(temp, 4);
			if (strncmp(temp, "QUIT", 4) == 0) {
			
				n = sprintf(pipe,
					"221 Service closing transmission channel\r\n");
				send(sock, pipe, n, 0);
				break;
			
			}
		}
		
		{ // Check for NOOP
			touppern(temp, 4);
			if (strncmp(temp, "NOOP", 4) == 0) {
			
				flag.noop = true;
				send(sock, "220 OK\r\n", 8, 0);
				continue;
			
			}
		}
		
		{ // Check for RSET
			touppern(temp, 4);
			if (strncmp(temp, "RSET", 4) == 0) {
			
				flag.rset = true;
				send(sock, "220 OK\r\n", 8, 0);
				continue;
			
			}
		}
		
		// MAIL STATES
		/*
			STATE_MAIL
			STATE_RCPT
			STATE_DATA
		*/
		
		
		{ // Check for MAIL
		
			if (flag.message == STATE_ENTR) {
				touppern(temp, 9);
				
				if (strncmp(temp, "MAIL FROM", 9) == 0) { // <MAIL FROM>
				
					
					// Get the sender of the email, TEST
					if (!extractAddress(buffer, newmsg->from)) {
					
						printf("[Client.%d] Malformed Sender Address\n", sock);
					
						n = sprintf(pipe, "501 Syntax error in args.\r\n");
						send(sock, pipe, n, 0);
						
						continue;
					
					}
					
					flag.message = STATE_MAIL;
					
					printf("[Client.%d] Sender: {%s}\n", sock, newmsg->from);
					send(sock, "250 Ok\r\n", 8, 0);
					
					continue;
				
				} // </MAIL FROM>
			}
			
			
			if (flag.message == STATE_MAIL) {
				touppern(temp, 7);
				
				if (strncmp(temp, "RCPT TO", 7) == 0) { // <RCPT TO>
				
					
					if (!extractAddress(buffer, newmsg->to)) {
					
						printf("[Client.%d] 501\n", sock);
						
						n = sprintf(pipe, "501 Syntax error in args.\r\n");
						send(sock, pipe, n, 0);
						
						continue;
					
					}
			
					flag.message = STATE_RCPT;
					
					printf("[Client.%d] Receiver: {%s}\n", sock, newmsg->to);
					send(sock, "250 Ok\r\n", 8, 0);
					
					continue;
					
				} // </MAIL FROM>
			}
			
			
			if (flag.message == STATE_RCPT) {
				touppern(temp, 4);
				
				if (strncmp(temp, "DATA", 4) != 0) { // <RCPT>
				
					// Means we didn't receive the data command.
					printf("[Client.%d] Did not receive DATA, send back 503", sock);
					n = sprintf(pipe, "503 Bad Sequence of Commands\r\n");
					send(sock, pipe, n, 0);
				
				} // </RCPT>
				
				// OK to receive data from SMTP-Sender
				n = sprintf(pipe,
					"354 Start mail input; end with <CRLF>.<CRLF>\r\n");
				send(sock, pipe, n, 0);
				
				// Prepare linked-list
				newmsg->contents = NULL;	// Set null pointer to first line
				
				struct data* end = NULL; // last item
				
				while(true) { // <DATA>
				
					struct data* tempLine = new struct data; // Temp line
					
					memset(buffer, '\0', BUFFER_LENGTH);
					memset(temp,   '\0', BUFFER_LENGTH);
					
					ret = recv(sock, buffer, BUFFER_LENGTH, 0);
					// If client terminates connection prematurely, cleanup
					if (ret == -1) 	{ clean = false; break; }
					
					strncpy(temp, buffer, ret);
					debastardize(temp);
					
					printf("[Client.%d] Read %d bytes.\n", sock, ret);
					printf("[Client.%d] Received: {%s}.\n", sock, temp);
					
					if ((strcmp(buffer, ".\r\n") == 0)
					 || (strcmp(buffer, "\r\n.\r\n") == 0)
					 || (strcmp(buffer, ".\n") == 0)) {
					
						printf("[Client.%d] Received <CRLF>.<CRLF>, ending.\n",
							sock);
						break;
						
					} else {
					
						debastardize(buffer);
						strncpy(tempLine->line, buffer, 1005);
						
						tempLine->next = NULL;
						
						// Add as thing in list					
						if (newmsg->contents == NULL) newmsg->contents = tempLine;
						if (end != NULL) end->next = tempLine; // update last
						end = tempLine; // point to new
					
					}
				
				} // </DATA>

				printf("[Client.%d] -- Line by line (Linked-List) --\n");
				
				struct data* next = newmsg->contents;
				
				while (next != NULL) {
				
					printf("\t{%s}\n", next->line);
					next = next->next;
				
				}
				
				/*
				printf("[Client.%d] -- Print CSV Record --\n", sock);
				
				memset(temp, '\0', sizeof temp);
				
				serialize(newmsg, temp);
				
				printf("%s\n\n", temp);
				*/
				
				// Pass off message to function
				ret = smtp_message(newmsg);
				if (ret > 0) {
				
					printf("[Client.%d] Message Queued!\n", sock, ret);
					
					n = sprintf(pipe, "250 Ok, Message queued with ID: %d\n", ret);
					send(sock, pipe, n, 0);
				
				} else if (ret == -1) {
				
					printf("[Client.%d] Message not delivered. Error: %d\n", sock, ret);
				
					n = sprintf(pipe, "550 Mail action not taken, mailbox not found\r\n");
					send(sock, pipe, n, 0);
				
				} else if (ret == -2) {
				
					printf("[Client.%d] Message will be forwarded.\n", sock, ret);
				
					n = sprintf(pipe, "251 User not local; will forward.\r\n");
					send(sock, pipe, n, 0);
				
				
				}
				
				
				
				flag.message = STATE_ENTR;
				flag.rset = true;
				continue;
			
			} // </RCPT> 
			
		}
		
		
		/*
		IF WE REACH HERE, IT MEANS THE RECEIVED COMMAND IS NOT VALID
		This makes our SMTP conversation very volatile, meaning that if
		a client is in the middle of conversing a message, and they send 
		an incorrect command, states get cleared.
		This could be fixed if we set f.noop = true; and let it act as as if
		NOOP happened
		*/
		
		// Send 500 error
		printf("[Client.%d] Received unhandled command, 500 error\n", sock);
		n = sprintf(pipe, "500 Syntax error, command unrecognised.\r\n");
		send(sock, pipe, n, 0);
		
	
	} // </END CLIENT LOOP>
	
	close(sock);
	printf("[Client.%d] Closing connection.\n", sock);
	pthread_exit(NULL);
	
}
/*############################################################################*/

/*
 *	SMTP Message handling thread
*/
int smtp_message(struct message* m) {

	srand(time(NULL));
	int mid = rand() % 100;
	
	char domain[46]; // 46 chars, RFC bitch!
	char user[64]; // 64 chars, RFC...again
	
	char temp[BUFFER_LENGTH];
	char csv[4096]; // hard limit, oh well.
	
	memset(temp, '\0', sizeof temp);
	memset(csv, '\0', sizeof csv);
	
	//struct message* m = (struct message*)info;
	
	printf("[Message.%d] Message Handler Thread Active.\n", mid);

	// ##########################################
	
	serialize(m, csv);
	strcat(csv, "\r\n");
	
	// Write to main queue
	pthread_mutex_lock(mutex::log);
	
	FILE *h;
	h = fopen(MAIN_LOG, "a"); // Open for append
	
	if (h == NULL) fprintf(stderr, "[Message.%d] CAN'T OPEN MAIN LOG.\n", mid);
	
	fprintf(h, csv);
	
	fclose(h);
	pthread_mutex_unlock(mutex::log);
	
	
	// Figure out who it's destined for
	extractDomain(m->to, domain);
	touppern(domain, strlen(domain));
	
	// Is the user local, two-step process
	if (strcmp(domain, "SUNNYVALE") == 0) { // User is local
	
		printf("[Message.%d] Is destined for local user.\n", mid);
		
		// Figure out user, and if they exist
		extractUser(m->to, user);
		
		if (!checkUser(user, users)) return -1;
		
		// Achieve mutex lock on mailbox file
		// Fuck the mutex!
		
		// Write message to file
		char mboxpath[133] = "mbox/";
		strcat(mboxpath, user);
		printf("\n\n\n\t%s\n\n\n", mboxpath);
		FILE *h = fopen(mboxpath, "a");
		
		fprintf(h, csv);
		
		fclose(h);
		
		return mid;
		
		// Release mutex
		
	} else {
	
		printf("[Message.%d] Is destined for remote user, will forward.\n", mid);
	
		pthread_mutex_lock(mutex::forwarder);
	
		printf("[Message.%d] Mutex achieved.\n", mid);
		
		FILE *h = fopen(FORWARD_QUEUE, "a");
		
		fprintf(h, csv);

		fclose(h);
		
		pthread_mutex_unlock(mutex::forwarder);
	
		return -2;
	}
	
	
	// ##########################################
	
	return mid;

}
/*############################################################################*/

/*
 *	MRP Client Thread
*/
void* mrp_client(void* info) {

	// things will go here

}
/*############################################################################*/

/*
 *	Signal Callback Handler
*/
void sig_callback_handler(int sig) {

	printf("[SIG.%d] Caught signal, exiting program.\n", sig);
	
	printf("[SIG.%d] Cancelling SMTP Worker.\n", sig);
	
	/* Ideally we should use pthread_kill as that will send a signal to the
		thread, and we could handle that signal to properly close the socket
		and wait for connections to finish up. As of now, cancelling a thread
		may leave the socket in an unopen state	which causes issues when
		starting up the server again. (undefined behavior)
		The socket bind	lags around after program termination and prevents us
		from opening up another listen socket for a few seconds.
	*/
	int ret = pthread_cancel(thread::smtp_worker);
	
	// Terminate MRP Worker
	printf("[SIG.%d] Cancelling MRP Worker.\n", sig);
	pthread_cancel(thread::mrp_worker);
	
	// Terminate Forwarder Worker
	
	// Exit program
	exit(sig);

}
/*############################################################################*/
