CFLAGS=-Wall

all: TCPFileTransferClient TCPFileTransferServer

OTHER_OBSS = DieWithError.o HandleTCPClient.o

TCPFileTransferClient :	TCPFileTransferClient.o	$(OTHER_OBSS)

TCPFileTransferServer :	TCPFileTransferServer.o	$(OTHER_OBSS)

DieWithError.o : DieWithError.c
				gcc -c DieWithError.c

HandleTCPClient.o : HandleTCPClient.c
				gcc -c HandleTCPClient.c

TCPFileTransferClient.o: TCPFileTransferClient.c
				gcc -c TCPFileTransferClient.c

TCPFileTransferSever.o: TCPFileTransferServer.c 
				gcc -c TCPFileTransferServer.c

clean:
		rm -f TCPFileTransferClient.o DieWithError.o HandleTCPClient.o TCPFileTransferServer.o TCPFileTransferClient TCPFileTransferServer
				
