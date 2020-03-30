/* This file is called when the server connects to a client. This file begins by
 * receiving the filename from the client and printing it out. It then checks if
 * the file is there. If the file is not there then it sends an error message 
 * back to the client to say that there is no file. If the file is there, it 
 * reads the file one character at a time into a buffer and sends the buffer to
 * the client. It then closes the client socket.
 */


#include <stdio.h> /* for printf() and fprintf() */
#include <stdio.h> /* for printf() and fprintf() */
#include <unistd.h> /* for close() */
#include <string.h> 

#define RCVBUFSIZE 32 /* Size of receive buffer */
#define ERRBUFSIZE 32 /* Size of error buffer */
#define READFILEBUFSIZE 64 /* Size of read file buffer */

void DieWithError(char *errMsg);

void HandleTCPClient(int clntSocket)
{
	char fileNameBuffer[RCVBUFSIZE];     /* Buffer for file name string */
	char *errorMessage;
	char errorBuffer[ERRBUFSIZE];       /* Buffer that is sent if file cannot be found */
	char readFileBuffer[READFILEBUFSIZE]; /* buffer for reading the file its int because fgetc returns ascii ints of each character */
	int recvMsgSize; /* used to receive the first packet sent from the clientwhich would be the file name*/
	int strLength; /* used to get the length of the filename */
	int readFile; /* used to read one character at a time from the fgetc command which turns the character into its ascii integer */
	int index; /* used to increment the readFileBuffer with each character */
	int totalBytes; /*keeps track of the bytes returned from the file (1 char = 1 byte)*/
	FILE *fptr; /*used to open the file*/

	/* Receive message from client */
	if ((recvMsgSize = recv(clntSocket, fileNameBuffer, RCVBUFSIZE, 0)) < 0)
		DieWithError("recv() failed") ;

	/* Print out File Name received from client */
	strLength = 0;
	printf("File Name: ");
	while(strLength < recvMsgSize){
		printf("%c",fileNameBuffer[strLength]);
		strLength++;
	}
	printf("\n");
	
	/*remove the extra characters at the end of the fileNameBuffer*/
	while(strLength < strlen(fileNameBuffer)){
		fileNameBuffer[strLength] = '\0';
		strLength++;
	}
	
	/* Open the file for reading */
	fptr = fopen(fileNameBuffer, "r");

	/* check if file is there. if not send error message to client. If it is
	 * there, read the file one character at a time into a buffer and send
	 * the buffer to the client.
	 */
	if(!fptr){
		errorMessage = "Error: file does not exist";
		for(int i=0;i<strlen(errorMessage);i++){
			errorBuffer[i] = errorMessage[i];
		}
		if (send(clntSocket, errorBuffer, strlen(errorBuffer), 0) != strlen(errorBuffer))
			DieWithError("send() failed");
		totalBytes = strlen(errorBuffer);
		printf("Sending %d bytes\n",totalBytes);

	}
	else{
		index = 0;
		totalBytes = 0;
		while((readFile = fgetc(fptr)) != EOF){
			if(index == READFILEBUFSIZE){
				if(send(clntSocket, readFileBuffer, READFILEBUFSIZE, 0) != strlen(readFileBuffer))
					DieWithError("send() failed");
				index = 0;
				for(int i=0; i<=READFILEBUFSIZE; i++){
					readFileBuffer[i] = '\0';	
				}
			}
			readFileBuffer[index] = (char) readFile;
			totalBytes++;
			index++;	
		}

		printf("Sending %d bytes\n",totalBytes);
		
		if (send(clntSocket, readFileBuffer, strlen(readFileBuffer), 0) != strlen(readFileBuffer))
			DieWithError("send() failed");
		
		fclose(fptr);	/* close the file that was read from */	
	}
	
	close(clntSocket); /* Close client socket */
	
}
