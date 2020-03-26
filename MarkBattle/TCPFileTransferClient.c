/* This File is the Client file where the client can print out the required
 * items. The client takes in 3 or 4 arguments and attempts to establish 
 * a connection with the server. It sends the name of the file as one of the 
 * arguments to the server if connection is established. It then receives 
 * either an error message that the file did not exist or the contents of the 
 * file requested. It also prints out the number of bytes received.
 */

#include <stdio.h> /*for printf() and fprintf()*/
#include <sys/socket.h> /*for socket(), connect(), send(), and recv()*/
#include <arpa/inet.h> /*for sockaddr_in and inet_addr()*/
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define RCVFILEBUFSIZE 2048 /*size of the receive buffer*/

void DieWithError(char *errMsg);

int main(int argc, char *argv[])
{
	int sock; /*Socket descriptor*/
	struct sockaddr_in echoServAddr;
	unsigned short servPort;
	char *servIP;
	char *fileName; /* file name from argument sent to server */
	char fileBuffer[RCVFILEBUFSIZE]; /* receives file or error message */
	unsigned int fileNameLen; 
	int bytesRcvd; /* keeps track of number of bytes in file (1 char = 1 byte)*/
	int rcvdLength;

	if ((argc<3)||(argc>4))
	{
			fprintf(stderr, "Usage: %s <Server IP> <File Name> [<Port>]\n"), argv[0];
			exit(1);
	}

	servIP = argv[1];
	fileName = argv[2];

	if(argc == 4)
		servPort = atoi(argv[3]);
	else
		servPort = 7;

	/*Create a socket using TCP*/
	if((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP))<0)
		DieWithError("socket() failed");

	/*Construct the server address structure*/
	memset(&echoServAddr, 0, sizeof(echoServAddr));
	echoServAddr.sin_family = AF_INET;
	echoServAddr.sin_addr.s_addr = inet_addr(servIP);
	echoServAddr.sin_port = htons(servPort);

	/*Establish connection to server*/
	if (connect(sock, (struct scokaddr*) &echoServAddr, sizeof (echoServAddr))<0)
		DieWithError("connect( ) failed");

	fileNameLen = strlen(fileName);

	/*send the string*/
	if (send(sock, fileName, fileNameLen, 0)!=fileNameLen)
		DieWithError("send() sent a different number of bytes than expected");

		
	/*Receive message from server (either error that file doesnt exist or
	 * the contents of the file requested)
	*/
	printf("Received: ");

	if((bytesRcvd = recv(sock, fileBuffer, RCVFILEBUFSIZE, 0))<=0)
		DieWithError("recv() failed or connection closed prematurely");
	/* Next section is to get rid of any extra junk received at the end of the buffer so it is just the string from the file */
	rcvdLength = 0;
	while(rcvdLength < bytesRcvd){
		rcvdLength += 1;
	}
	while(rcvdLength < strlen(fileBuffer)){
		fileBuffer[rcvdLength] = '\0';
		rcvdLength += 1;
	}

	printf(fileBuffer);

	printf("\n");

	/* each individual character is 1 byte so the length of the string will give you the total bytes received */
	printf("Received %d bytes\n", strlen(fileBuffer));

	close(sock);
	exit(0);
}
