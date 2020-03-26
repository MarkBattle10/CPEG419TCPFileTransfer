#include <stdio.h> /* for printf() and fprintf() */
#include <stdio.h> /* for printf() and fprintf() */
#include <unistd.h> /* for close() */
#include <string.h> 

#define RCVBUFSIZE 32 /* Size of receive buffer */
#define ERRBUFSIZE 32 /* Size of error buffer */
#define READFILEBUFSIZE 2048 /* Size of read file buffer */

void DieWithError(char *errMsg);

void HandleTCPClient(int clntSocket)
{
	char fileNameBuffer[RCVBUFSIZE];     /* Buffer for file name string */
	char *errorMessage;
	char errorBuffer[ERRBUFSIZE];       /* Buffer that is sent if file cannot be found */
	char readFileBuffer[READFILEBUFSIZE]; /* buffer for reading the file its int because fgetc returns ascii ints of each character */
	int recvMsgSize;
	int strLength;
	int readFile;
	int index;
	int totalBytes;
	FILE *fptr;

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
	//printf("file Name: %s\n", fileNameBuffer);
	
	/* Open the file for reading */
	fptr = fopen(fileNameBuffer, "r");
	
	if(!fptr){
		errorMessage = "Error: file does not exist";
		for(int i=0;i<strlen(errorMessage);i++){
			errorBuffer[i] = errorMessage[i];
			//printf("%c", errorBuffer[i]);
		}
		//printf("\n");
		if (send(clntSocket, errorBuffer, strlen(errorBuffer), 0) != strlen(errorBuffer))
			DieWithError("send() failed");

	}
	else{
		index = 0;
		totalBytes = 0;
		while((readFile = fgetc(fptr)) != EOF){
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
	
	/* Send received string and receive again until end of transmission */
	
//	while (recvMsgSize > 0) /* zero indicates end of transmission */
//	{
//		/* Echo message back to client */
//		if (send(clntSocket, fileNameBuffer, recvMsgSize, 0) != recvMsgSize)
//			DieWithError("send() failed");
//
//		/* See if there is more data to receive */
//		if ((recvMsgSize = recv(clntSocket, fileNameBuffer, RCVBUFSIZE, 0)) < 0)
//			DieWithError("recv() failed") ;
//
//	}
//
//	close(clntSocket); /* Close client socket */
}
