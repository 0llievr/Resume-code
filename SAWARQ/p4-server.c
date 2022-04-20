//Oliver
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include "program4Functions.h"
#define MAX_LINE 1400 //256
//#define SEQ_START 1
#define header_size 1
#define MAX_PENDING 5
#define debug 0

int bind_and_listen(const char *service);

int main(int argc, char *argv[])
{
	char buf[MAX_LINE];
	//char ack[header_size];
	const char *SERVER_PORT;
	int recvflnm = 0;
	int s, new_s = 0;
	int acked = 0;
	char seq = 48;
	char ack[MAX_LINE];
	int y = 0;
	int bytesread = 0;
	fd_set fdclient;

	if (argc == 2){ //Bind socket to local interface and passive open
		SERVER_PORT = argv[1];
	}else{
		printf("ERROR: No port given.\n");
		exit(1);
	}
	
	if ((s = bind_and_listen(SERVER_PORT)) < 0){
		exit(1);
	}

	if (debug){
		printf("[Server]DEBUG: Entering server loop\n");
	}

	while (1){ //Endless loop to keep server up.
		if ((new_s = accept(s, NULL, NULL)) < 0){
			perror("stream-talk-server: accept");
			close(s);
			exit(1);
		}
		recvflnm = receiveAndVerifyFilename(new_s, buf);
		if (recvflnm == 0){
			FILE *ifile = fopen(buf, "r");
			if (debug){
				printf("[Server]DEBUG:Attempting file transfer...\n");
			}
			while ((bytesread = fread(buf + 1, 1, MAX_LINE - 1, ifile)) > 0){
				acked = 0;
				buf[0] = seq;
				while (acked != 1){
					struct timeval timev;
					timev.tv_sec = 0;
					timev.tv_usec = 50000;
					if (debug){
						printf("[Server]DEBUG:Sending data chunk #%d\n", y);
					}
					packetErrorSend(new_s, buf, bytesread+1, 0);

					FD_ZERO(&fdclient);
					FD_SET(new_s, &fdclient);
					int x = select(new_s + 1, &fdclient, NULL, NULL, &timev);
					if (x > 0){
						recv(new_s, &ack, 1, 0);
						if (ack[0] == seq){
							if (seq == 57){ //prevents roll over
								seq = 48;
							}
							else{
								seq++;
							}

							acked = 1;
						}
					}
					y = y + 1;
				}
			}
			close(new_s);
			close(s);
			return 0;
		}
		else if (recvflnm == -1){
			printf("[Server]ERROR: There was an error receiving the filename (e.g., bad socket, recv error)\n");
			close(new_s);
		}else if (recvflnm == -2){
			printf("[Server]ERROR: There was an error opening the file (e.g., doesn't exist, permissions)\n");
			close(new_s);
		}else if (recvflnm == -3){
			printf("[Server]ERROR:There was an error sending the response to the client\n");
			close(new_s);
		}

		close(s);
	}
}
int bind_and_listen(const char *service){
	//DEBUG
	if (debug)
		printf("[Server]DEBUG: Entering bind_and_listen\n");
	struct addrinfo hints;
	struct addrinfo *rp, *result;
	int s;

	/* Build address data structure */
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_protocol = 0;

	/* Get local address info */
	if ((s = getaddrinfo(NULL, service, &hints, &result)) != 0){
		fprintf(stderr, "stream-talk-server: getaddrinfo: %s\n", gai_strerror(s));
		return -1;
	}

	/* Iterate through the address list and try to perform passive open */
	for (rp = result; rp != NULL; rp = rp->ai_next){
		if ((s = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol)) == -1){
			continue;
		}

		if (!bind(s, rp->ai_addr, rp->ai_addrlen)){
			break;
		}

		close(s);
	}
	if (rp == NULL){
		perror("stream-talk-server: bind");
		return -1;
	}
	if (listen(s, MAX_PENDING) == -1){
		perror("stream-talk-server: listen");
		close(s);
		return -1;
	}
	freeaddrinfo(result);
	//DEBUG
	if (debug)
		printf("[Server]DEBUG: Exiting bind_and_listen. Returning socket: %d\n", s);
	return s;
}
