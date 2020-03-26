List of Relevant files: DieWithError.c, HandleTCPClient.c, TCPFileTransferClient.c, TCPFileTransferServer.c, makefile, fileToDownload.txt

Compilation instructions: To compile this program simply type "make" in the command line.

Configuration file: This program uses a makefile. The makefile essentially calls all of the commands that you would have to enter in the command line in a simpler way. So, instead of typing gcc -c DieWithError.c, gcc -c HandleTCPClient.c, gcc -c TCPFileTransferClient.c, and gcc -c TCPFileTransferServer.c, you simply type make. Also you can remove all of the extra files created by typing make clean.

Running Instructions: To run this program after you created the executables by calling make in the command line, you run the "TCPFileTransferServer" executable first with a port number as the argument. This first executable runs the server forever and looks for a client to connect to. Once connected, it receives a file name, prints it out, then either sends an error message that the file didn't exist or sends the contents of the file to the client and prints out the number of bytes it sent.
example: ./TCPFileTransferServer 1234
Then you run the "TCPFileTransferClient" executable with 2 arguments and an optional argument. the first argument is an ip address, the second argument is the name of the file that you would like to download, and the optional argument is the port number (which should be the same as the one used to run the TCPFileTransferServer executable). This executable connects to the server and sends it the name of the file it wants to download. It prints out either an error message that the file didn't exist or the contents of the file it requested as well as the number of bytes it received from the server
example: ./TCPFileTransferClient 127.0.0.1 fileToDownload.txt 1234
