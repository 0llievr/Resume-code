 //Oliver
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/socket.h>
#include<netdb.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<ctype.h>
#include<unistd.h>
#include "program4Functions.h"

#define MAX 1400 //256
#define HeaderSize 1

int lookup_and_connect(const char *host, const char *service);

int main(int argc, char *argv[]) {
	const char *host;
	const char *port;
	const char *fileN;
	int s;
	int byterecv = 1; 
	char buff[MAX];
	char ack = 5;


	if(argc == 4){
		host = argv[1];
		port = argv[2];
		fileN = argv[3];
	}else{
		printf("Missing information.\n");
		exit(1);
	}

	if ((s = lookup_and_connect( host, port)) < 0){
		printf("Connection failed.\n");
		exit(1);
	}

	int rtnS = deliverFilename(s, fileN); //send the filename
	
	if(rtnS == 0){ //file exists and opens
		int ofileD = open(fileN, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR|S_IWUSR);
		printf("file opened\n"); 
		while(byterecv != 0){
			byterecv = recv(s,buff, MAX ,0);
			
			if(buff[0] != ack){
				write(ofileD, buff+1, byterecv); //write only the data from buff
				ack = buff[0];
			}
			
			packetErrorSend(s, buff, HeaderSize, 0); //send ack
		}		
		close(ofileD);




	}else if(rtnS == -1){ //bad socket
		printf("Bad Socket.\n");
	}else if(rtnS == -2){
		printf("File does not exist.\n");
	}else{
		printf("Get fucked buddy\n");
	}

	close(s);
	return 0;
}

int lookup_and_connect( const char *host, const char *service ) {
	struct addrinfo hints;
	struct addrinfo *rp, *result;
	int s;

	/* Translate host name into peer's IP address */
	memset( &hints, 0, sizeof( hints ) );
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0;
	hints.ai_protocol = 0;

	if ( ( s = getaddrinfo( host, service, &hints, &result ) ) != 0 ) {
		fprintf( stderr, "stream-talk-client: getaddrinfo: %s\n", gai_strerror( s ) );
		return -1;
	}

	/* Iterate through the address list and try to connect */
	for ( rp = result; rp != NULL; rp = rp->ai_next ) {
		if ( ( s = socket( rp->ai_family, rp->ai_socktype, rp->ai_protocol ) ) == -1 ) {
			continue;
		}

		if ( connect( s, rp->ai_addr, rp->ai_addrlen ) != -1 ) {
			break;
		}

		close( s );
	}
	if ( rp == NULL ) {
		perror( "stream-talk-client: connect" );
		return -1;
	}
	freeaddrinfo( result );

	return s;
}
