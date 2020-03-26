#include <stdio.h> /*for perror*/
#include <stdlib.h> /*for exit*/

void DieWithError(char *errMsg){
	perror(errMsg);
	exit(1);
}
